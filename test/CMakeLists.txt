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
