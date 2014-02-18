import os
import os.path
import argparse
import tables
import sqlite3
import numpy

tracks_id_count = 0
album_id_count = 0
artist_id_count = 0

TRACK_TABLE = """
CREATE TABLE tracks (
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    album_id INTEGER NOT NULL,
    artist_id INTEGER NOT NULL,
    duration FLOAT NOT NULL,
    popularity FLOAT NOT NULL,
    loudness INTEGER NOT NULL,
    tempo FLOAT NOT NULL,
    key INT NOT NULL,
    mode INT NOT NULL,
    id_deezer INT,
    CONSTRAINT taa UNIQUE (title, album_id)
)
"""
ALBUM_TABLE = """
CREATE TABLE albums (
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    artist_id INTEGER NOT NULL,
    release INTEGER NOT NULL,
    id_deezer INT,
    CONSTRAINT aa UNIQUE (title, artist_id)
)
"""
ARTIST_TABLE = """
CREATE TABLE artists (
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE,
    familiarity FLOAT NOT NULL,
    popularity FLOAT NOT NULL,
    id_deezer INT
)
"""

def create_tables(sql_connection):
    sql_connection.execute(TRACK_TABLE)
    sql_connection.execute(ALBUM_TABLE)
    sql_connection.execute(ARTIST_TABLE)
    sql_connection.commit()

def add_track(sql_connection, track):
    "Add a track to the sqlite database"
    print("Ajout de le piste", track["title"])

    id = sql_connection.execute("""
    SELECT MAX(id)
    FROM tracks 
    """).fetchone()[0]
    track["id"] = 0 if id is None else id + 1

    sql_connection.execute("""
    INSERT INTO tracks VALUES (
        :id,
        :title,
        :album_id,
        :artist_id,
        :duration,
        :popularity,
        :loudness,
        :tempo,
        :key,
        :mode,
        NULL
    )
    """, track)

    sql_connection.commit()

def add_album(sql_connection, album):
    "Add an album to the sqlite database"
    #print("Ajout de l'album", album["title"])

    id = sql_connection.execute("""
    SELECT MAX(id)
    FROM albums 
    """).fetchone()[0]
    album["id"] = 0 if id is None else id + 1

    sql_connection.execute("""
    INSERT INTO albums VALUES (
        :id,
        :title,
        :artist_id,
        :release,
        NULL
    )
    """, album)

    sql_connection.commit()

def add_artist(sql_connection, artist):
    "Add an artist to the sqlite database"
    #print("Ajout de l'artiste", artist["name"])

    id = sql_connection.execute("""
    SELECT MAX(id)
    FROM artists 
    """).fetchone()[0]
    artist["id"] = 0 if id is None else id + 1

    sql_connection.execute("""
    INSERT INTO artists VALUES (
        :id,
        :name,
        :familiarity,
        :popularity,
        NULL
    )
    """, artist)

    sql_connection.commit()

albums = {}
artists = {}
tracks = set()

def verify_song(song):
    return (
        song["artist"]["name"]
        and song["artist"]["familiarity"]
        and not numpy.isnan(song["artist"]["familiarity"])
        and song["artist"]["popularity"]
        and not numpy.isnan(song["artist"]["popularity"])
        and song["album"]["title"]
        and song["album"]["release"]
        and song["track"]["title"]
        and song["track"]["duration"]
        and song["track"]["popularity"]
        and not numpy.isnan(song["track"]["popularity"])
        and song["track"]["loudness"]
        and song["track"]["tempo"]
        #and song["track"]["key_confidence"] > 0.5
        #and song["track"]["mode_confidence"] > 0.6
    )

def analyse_file(sql_connection, path):
    data = tables.open_file(path)
    global tracks_id_count
    for metadata, musicbrainz, analysis in zip(
        data.root.metadata.songs[:],
        data.root.musicbrainz.songs[:],
        data.root.analysis.songs[:]
    ):
        song = dict(
            artist = dict (
                name = metadata["artist_name"].decode(),
                familiarity = metadata["artist_familiarity"] \
                    if not numpy.isnan(metadata["artist_familiarity"]) else 0,
                popularity = metadata["artist_hotttnesss"] \
                    if not numpy.isnan(metadata["artist_hotttnesss"]) else 0
            ),
            album = dict (
                title = metadata["release"].decode(),
                release = int(musicbrainz["year"])
            ),
            track = dict(
                title = metadata["title"].decode(),
                duration = analysis["duration"],
                popularity = metadata["song_hotttnesss"] \
                    if not numpy.isnan(metadata["song_hotttnesss"]) else 0,
                loudness = analysis["loudness"],
                tempo = analysis["tempo"],
                key = int(analysis["key"]),
                key_confidence = analysis["key_confidence"],
                mode = int(analysis["mode"]),
                mode_confidence = analysis["mode_confidence"]
            )
        )

        # if not verify_song(song):
        #     print("Rejet de", song["track"]["title"])
        #     break

        print("Analyse de", song["track"]["title"])

        # Adds an artist if not in database
        if song["artist"]["name"] not in artists:
            artist = dict(
                name = song["artist"]["name"],
                familiarity = song["artist"]["familiarity"],
                popularity = song["artist"]["popularity"]
            )
            add_artist(sql_connection, artist)
            artists[artist["name"]] = artist["id"]

        artist_id = artists[song["artist"]["name"]]

        # Adds an album if not in database
        if (song["album"]["title"], artist_id) not in albums:
            album = dict(
                title = song["album"]["title"],
                artist_id = artist_id,
                release = song["album"]["release"]
            )
            add_album(sql_connection, album)
            albums[(album["title"], album["artist_id"])] = album["id"]

        album_id = albums[(song["album"]["title"], artist_id)]

        track = dict(
            title = song["track"]["title"],
            album_id = album_id,
            artist_id = artist_id,
            duration = song["track"]["duration"],
            popularity = song["track"]["popularity"],
            loudness = song["track"]["loudness"],
            tempo = song["track"]["tempo"],
            key = song["track"]["key"],
            mode = song["track"]["mode"],
        )


        if (track["title"], track["album_id"]) in tracks:
            print("Track already in database")
            break

        try:
            add_track(sql_connection, track)
            tracks.add((track["title"], track["album_id"]))
        except Exception as e:
            print(e)
            print(track)
            continue

    data.close()

def analyse_dir(sql_connection, path):
    for entry in os.listdir(path):
        if entry[-2:] == "h5":
            analyse_file(sql_connection, path + '/' + entry)
        elif os.path.isdir(path + '/' + entry):
            analyse_dir(sql_connection, path + '/' + entry)

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

    sql_connection = sqlite3.connect(options.database_name + ".db")
    create_tables(sql_connection)
    analyse_dir(sql_connection, options.msd_directory)
    print(tracks_id_count)