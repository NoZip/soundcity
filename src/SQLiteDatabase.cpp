#include <cassert>
#include <sstream>

#include <iostream>

#include <SQLiteDatabase.h>

using std::size_t;
using std::string;
using std::stringstream;

using namespace SoundCity;

SQLiteDatabase::SQLiteDatabase(const string &file)
: filename(file), dbConnection(nullptr){

}

SQLiteDatabase::~SQLiteDatabase() {
  if (dbConnection)
  {
    sqlite3_close(dbConnection);
  }
}

int SQLiteDatabase::initialization()
{
  // @see http://www.sqlite.org/c3ref/open.html
  std::cout << filename.c_str() << std::endl;
  int status = sqlite3_open_v2(
    filename.c_str(),
    &dbConnection,
    SQLITE_OPEN_READONLY,
    nullptr
  );

  if(status != SQLITE_OK)
  {
    std::cout << status << ": " << sqlite3_errstr(status) << std::endl;
    assert(status == SQLITE_OK);
  }

  return 1;
}

enum RowIndex {
  TRACK_ID,
  TRACK_DURATION,
  CONTEXT_POPULARITY,
  CONTEXT_ARTIST_ID,
  CONTEXT_ARTIST_NAME,
  CONTEXT_ARTIST_FAMILIARITY,
  CONTEXT_ARTIST_POPULARITY,
  CONTEXT_ALBUM_ID,
  CONTEXT_ALBUM_TITLE,
  CONTEXT_ALBUM_RELEASE,
  CONTEXT_ALBUM_ARTIST_ID,
  CONTEXT_ALBUM_ARTIST_NAME,
  CONTEXT_ALBUM_ARTIST_FAMILIARITY,
  CONTEXT_ALBUM_ARTIST_POPULARITY,
  SIGNAL_RHYTHM,
  SIGNAL_ENERGY,
  SIGNAL_TONALITY
};

TrackPool SQLiteDatabase::select(const OptionList &options, size_t size)
{
  stringstream buffer;
  buffer << u8"SELECT ";
    // Track
    buffer << u8"tracks.id, ";
    buffer << u8"tracks.duration, ";
      // Context
      buffer << u8"tracks.popularity, ";
        // Artist
        buffer << u8"artists.id, ";
        buffer << u8"artists.name, ";
        buffer << u8"artists.familiarity, ";
        buffer << u8"artists.popularity, ";
        // Album
        buffer << u8"albums.id, ";
        buffer << u8"albums.title, ";
        buffer << u8"albums.release, ";
          // Album Artist
          buffer << u8"album_artists.id, ";
          buffer << u8"album_artists.name, ";
          buffer << u8"album_artists.familiarity, ";
          buffer << u8"album_artists.popularity, ";
      // Signal
      buffer << u8"tracks.tempo, tracks.loudness, 0.0 ",
  buffer << u8" ";
  buffer << u8"FROM tracks ";
  buffer << u8"INNER JOIN albums ";
  buffer << u8"ON tracks.album_id = albums.id ";
  buffer << u8"INNER JOIN artists ";
  buffer << u8"ON tracks.artist_id = artists.id ";
  buffer << u8"INNER JOIN artists AS album_artists ";
  buffer << u8"ON albums.artist_id = album_artists.id ";

  stringstream whereBuffer;
  bool firstWhere = true;

  // Year filtering
  if (options.getStartYear() > 0 && options.getEndYear() > 0)
  {
    if (firstWhere)
      firstWhere = false;
    else
      whereBuffer << "AND ";

    whereBuffer << u8"albums.release BETWEEN "
                << options.getStartYear()
                << u8"AND"
                << options.getEndYear()
                << u8" ";
  }


  string whereRequest = whereBuffer.str();
  if (!whereRequest.empty()) buffer << u8"WHERE " << whereRequest;
  buffer << u8"ORDER BY random() ";
  buffer << u8"LIMIT " << size << u8";";

  string request = buffer.str();

  // Request compilation
  sqlite3_stmt *preparedRequest = nullptr;
  int status = sqlite3_prepare_v2(
    dbConnection,
    request.c_str(),
    request.size(),
    &preparedRequest,
    nullptr
  );

  if(status != SQLITE_OK)
  {
    std::cout << status << ": " <<sqlite3_errstr(status) << std::endl;
    assert(status == SQLITE_OK);
  }

  TrackPool pool(size);

  // Contruction de la pool de pistes
  while ((status = sqlite3_step(preparedRequest)) != SQLITE_DONE)
  {
    //status = sqlite3_step(preparedRequest);

    assert(status == SQLITE_ROW);

    Track track(
      sqlite3_column_int(preparedRequest, TRACK_ID),
      SignalData(
        sqlite3_column_double(preparedRequest, SIGNAL_RHYTHM),
        sqlite3_column_double(preparedRequest, SIGNAL_ENERGY),
        sqlite3_column_double(preparedRequest, SIGNAL_TONALITY)
      ),
      ContextData(
        Artist(
          sqlite3_column_int(preparedRequest, CONTEXT_ARTIST_ID),
          reinterpret_cast<char const *>(
            sqlite3_column_text(preparedRequest, CONTEXT_ARTIST_NAME)
          ),
          //"",
          sqlite3_column_double(preparedRequest, CONTEXT_ARTIST_FAMILIARITY),
          sqlite3_column_double(preparedRequest, CONTEXT_ARTIST_POPULARITY)
        ),
        Album(
          sqlite3_column_int(preparedRequest, CONTEXT_ALBUM_ID),
          reinterpret_cast<char const *>(
            sqlite3_column_text(preparedRequest, CONTEXT_ALBUM_TITLE)
          ),
          reinterpret_cast<char const *>(
            sqlite3_column_text(preparedRequest, CONTEXT_ALBUM_ARTIST_NAME)
          ),
          sqlite3_column_int(preparedRequest, CONTEXT_ALBUM_RELEASE)
        ),
        sqlite3_column_double(preparedRequest, CONTEXT_POPULARITY)
      )
    );

    pool.insert(track);
  }

  return pool;
}
