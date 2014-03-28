cmake_minimum_required (VERSION 2.6)
project (SoundCity)

set(soundcity_SRCS
  ./test_track.cpp
  ../src/Track.cpp
  ../src/ContextData.cpp
  ../src/SignalData.cpp
  ../src/Artist.cpp
  ../src/Album.cpp)

add_executable(test_track ${soundcity_SRCS})

set(sqlite_SRCS
  ./test_sqlite.cpp
  ../src/Track.cpp
  ../src/ContextData.cpp
  ../src/SignalData.cpp
  ../src/Artist.cpp
  ../src/Album.cpp
  ../src/OptionList.cpp
  ../src/SQLiteDatabase.cpp)

add_executable(test_sqlite ${sqlite_SRCS})
target_link_libraries(test_sqlite sqlite3)

set(sc_console_SRC
  ./soundcity_console.cpp
  ../src/Track.cpp
  ../src/ContextData.cpp
  ../src/SignalData.cpp
  ../src/Artist.cpp
  ../src/Album.cpp
  ../src/OptionList.cpp
  ../src/SQLiteDatabase.cpp
  ../src/Generator.cpp
  ../src/SimilarityStrategy.cpp
  ../src/Playlist.cpp)

add_executable(soundcity_console ${sc_console_SRC})
target_link_libraries(soundcity_console sqlite3)

set(test_similarity_SRC
  ./test_similarity.cpp
  ../src/Track.cpp
  ../src/ContextData.cpp
  ../src/SignalData.cpp
  ../src/Artist.cpp
  ../src/Album.cpp
  ../src/SimilarityStrategy.cpp)

add_executable(test_similarity ${test_similarity_SRC})