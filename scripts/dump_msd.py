import sys
import os
import os.path
import argparse
import pprint
import tables
import sqlite3
import numpy

tracks_id_count = 0
album_id_count = 0
artist_id_count = 0

pretty_print = pprint.PrettyPrinter(indent=4, width=80).pprint
pretty_print_err = pprint.PrettyPrinter(indent=4, width=80, stream=sys.stderr).pprint

TRACK_TABLE = """
CREATE TABLE tracks (
    id INTEGER NOT NULL PRIMARY KEY,
    id_echonest TEXT NOT NULL,
    id_7digital INTEGER NOT NULL,
    title TEXT NOT NULL,
    album_id INTEGER NOT NULL,
    artist_id INTEGER NOT NULL,
    duration FLOAT NOT NULL,
    popularity FLOAT NOT NULL,
    genre TEXT,
    loudness INTEGER NOT NULL,
    tempo FLOAT NOT NULL,
    key INT NOT NULL,
    key_confidence FLOAT NOT NULL,
    mode INT NOT NULL,
    mode_confidence FLOAT NOT NULL,
    rhythm FLOAT NOT NULL,
    energy FLOAT NOT NULL,
    CONSTRAINT taa UNIQUE (title, album_id)
)
"""
ALBUM_TABLE = """
CREATE TABLE albums (
    id INTEGER NOT NULL PRIMARY KEY,
    id_7digital INTEGER NOT NULL,
    title TEXT NOT NULL,
    artist_id INTEGER NOT NULL,
    release INTEGER NOT NULL,
    CONSTRAINT aa UNIQUE (title, artist_id)
)
"""
ARTIST_TABLE = """
CREATE TABLE artists (
    id INTEGER NOT NULL PRIMARY KEY,
    id_echonest TEXT NOT NULL,
    id_7digital INTEGER NOT NULL,
    name TEXT NOT NULL UNIQUE,
    familiarity FLOAT NOT NULL,
    popularity FLOAT NOT NULL
)
"""

ARTIST_SIMILARITY_TABLE = """
CREATE TABLE artists_similarity (
    target TEXT,
    similar TEXT
)
"""

def create_tables(sql_connection):
    sql_connection.execute(TRACK_TABLE)
    sql_connection.execute(ALBUM_TABLE)
    sql_connection.execute(ARTIST_TABLE)
    sql_connection.execute(ARTIST_SIMILARITY_TABLE)
    sql_connection.commit()

def add_track(sql_connection, track):
    "Add a track to the sqlite database"

    id = sql_connection.execute("""
    SELECT MAX(id)
    FROM tracks 
    """).fetchone()[0]
    track["id"] = 0 if id is None else id + 1

    sql_connection.execute("""
    INSERT INTO tracks VALUES (
        :id,
        :id_echonest,
        :id_7digital,
        :title,
        :album_id,
        :artist_id,
        :duration,
        :popularity,
        :genre,
        :loudness,
        :tempo,
        :key,
        :key_confidence,
        :mode,
        :mode_confidence,
        :rhythm,
        :energy
    )
    """, track)

    # sql_connection.commit()

def add_album(sql_connection, album):
    "Add an album to the sqlite database"

    id = sql_connection.execute("""
    SELECT MAX(id)
    FROM albums 
    """).fetchone()[0]
    album["id"] = 0 if id is None else id + 1

    sql_connection.execute("""
    INSERT INTO albums VALUES (
        :id,
        :id_7digital,
        :title,
        :artist_id,
        :release
    )
    """, album)

    # sql_connection.commit()

def add_artist(sql_connection, artist):
    "Add an artist to the sqlite database"

    id = sql_connection.execute("""
    SELECT MAX(id)
    FROM artists 
    """).fetchone()[0]
    artist["id"] = 0 if id is None else id + 1

    sql_connection.execute("""
    INSERT INTO artists VALUES (
        :id,
        :id_echonest,
        :id_7digital,
        :name,
        :familiarity,
        :popularity
    )
    """, artist)

    # sql_connection.commit()

def add_similar_artist(sql_connection, target, similar):
    sql_connection.execute("INSERT INTO artists_similarity VALUES (?, ?)", (target, similar))
    # sql_connection.commit()

albums = {}
artists = {}
tracks = set()

def verify_song(song):
    return (
        song["artist"]["name"]
        and (0 <= song["artist"]["familiarity"] <= 1)
        and (0 <= song["artist"]["popularity"] <= 1)
        and song["album"]["title"]
        #and song["album"]["release"]
        and song["track"]["title"]
        and song["track"]["duration"] > 0
        and (0 <= song["track"]["popularity"] <= 1)
        # and song["track"]["loudness"]
        # and song["track"]["tempo"] > 0
        and song["track"]["id_7digital"] != -1
        #and song["artist"]["id_7digital"] >= 0
        #and song["album"]["id_7digital"] >= 0
        #and song["track"]["key_confidence"] > 0.5
        #and song["track"]["mode_confidence"] > 0.6
    )

def compute_score(value, min, max, f=None):
    score = value - min
    if score < 0:
        score = 0

    score /= max - min
    if score > 1:
        score = 1

    if f:
        score = f(score)

    return score

def saturate(value):
    if value < 0:
        return 0
    elif value > 1:
        return 1

    return value

def analyse_file(sql_connection, path):
    data = tables.open_file(path)

    global tracks_id_count

    metadata = data.root.metadata.songs[0]
    musicbrainz = data.root.musicbrainz.songs[0]
    analysis = data.root.analysis.songs[0]
    similar_artists = data.root.metadata.similar_artists[:]

    song = dict(
        artist = dict (
            id_echonest = metadata["artist_id"],
            id_7digital = int(metadata["artist_7digitalid"]),
            name = metadata["artist_name"].decode(),
            familiarity = saturate(metadata["artist_familiarity"]) \
                if not numpy.isnan(metadata["artist_familiarity"]) else 0,
            popularity = saturate(metadata["artist_hotttnesss"]) \
                if not numpy.isnan(metadata["artist_hotttnesss"]) else 0
        ),
        album = dict (
            id_7digital = int(metadata["release_7digitalid"]),
            title = metadata["release"].decode(),
            release = int(musicbrainz["year"])
        ),
        track = dict(
            id_echonest = analysis["track_id"],
            id_7digital = int(metadata["track_7digitalid"]),
            title = metadata["title"].decode(),
            duration = analysis["duration"],
            popularity = saturate(metadata["song_hotttnesss"]) \
                if not numpy.isnan(metadata["song_hotttnesss"]) else 0,
            genre = metadata["genre"],
            loudness = analysis["loudness"],
            tempo = analysis["tempo"],
            key = int(analysis["key"]),
            key_confidence = analysis["key_confidence"] \
                if not numpy.isnan(analysis["key_confidence"]) else 0,
            mode = int(analysis["mode"]),
            mode_confidence = analysis["mode_confidence"] \
                if not numpy.isnan(analysis["mode_confidence"]) else 0,
        )
    )

    print("Analyse de", song["track"]["title"], "par", song["artist"]["name"])

    if not verify_song(song):
        print("Reject", file=sys.stderr)
        pretty_print_err(song)
        data.close()
        return

    # Adds an artist if not in database
    if song["artist"]["name"] not in artists:
        artist = dict(
            id_echonest = song["artist"]["id_echonest"],
            id_7digital = song["artist"]["id_7digital"],
            name = song["artist"]["name"],
            familiarity = song["artist"]["familiarity"],
            popularity = song["artist"]["popularity"]
        )
        add_artist(sql_connection, artist)
        artists[artist["name"]] = artist["id"]

        #add similar artists
        for similar in similar_artists:
            add_similar_artist(sql_connection, artist["id_echonest"], similar)

    artist_id = artists[song["artist"]["name"]]

    # Adds an album if not in database
    if (song["album"]["title"], artist_id) not in albums:
        album = dict(
            id_7digital = song["album"]["id_7digital"],
            title = song["album"]["title"],
            artist_id = artist_id,
            release = song["album"]["release"]
        )
        add_album(sql_connection, album)
        albums[(album["title"], album["artist_id"])] = album["id"]

    album_id = albums[(song["album"]["title"], artist_id)]

    track = dict(
        id_echonest = song["artist"]["id_echonest"],
        id_7digital = song["artist"]["id_7digital"],
        title = song["track"]["title"],
        album_id = album_id,
        artist_id = artist_id,
        duration = song["track"]["duration"],
        popularity = song["track"]["popularity"],
        genre = song["track"]["genre"],
        loudness = song["track"]["loudness"],
        tempo = song["track"]["tempo"],
        key = song["track"]["key"],
        key_confidence = song["track"]["key_confidence"],
        mode = song["track"]["mode"],
        mode_confidence = song["track"]["mode_confidence"],
        rhythm=compute_score(song["track"]["tempo"], 40, 200),
        energy=compute_score(song["track"]["loudness"]+60, 20, 100)
    )

    if (track["title"], track["album_id"]) in tracks:
        print("Track already in database")
        data.close()
        return

    try:
        add_track(sql_connection, track)
        tracks.add((track["title"], track["album_id"]))
    except Exception as e:
        print(e)
        print(track)

    data.close()

def analyse_dir(sql_connection, path):
    for entry in os.listdir(path):
        if entry[-2:] == "h5":
            analyse_file(sql_connection, path + '/' + entry)
        elif os.path.isdir(path + '/' + entry):
            analyse_dir(sql_connection, path + '/' + entry)

    # sql_connection.commit()

if __name__ == "__main__":
    options_parser = argparse.ArgumentParser()
    options_parser.add_argument(
        "msd_directory",
        help="Directory (usualy data/) were the h5 files are."
    )
    options_parser.add_argument(
        "database_name",
        help="A little name for your database (usualy 'test')."
    )
    options = options_parser.parse_args()

    sql_connection = sqlite3.connect(options.database_name + ".sqlite")
    sql_connection.execute("DROP TABLE IF EXISTS tracks")
    sql_connection.commit()
    sql_connection.execute("DROP TABLE IF EXISTS albums")
    sql_connection.commit()
    sql_connection.execute("DROP TABLE IF EXISTS artists")
    sql_connection.commit()
    sql_connection.execute("DROP TABLE IF EXISTS artists_similarity")
    sql_connection.commit()
    create_tables(sql_connection)
    analyse_dir(sql_connection, options.msd_directory + "data/")
    sql_connection.commit()
    sql_connection.execute("DELETE FROM tracks WHERE id_7digital < 0")
    sql_connection.commit()
    sql_connection.close()
