cmake_minimum_required (VERSION 2.6)
project (SoundCity)

add_executable(test_track test_track.cpp ${SOUNDCITY_LIB_SRCS})
target_link_libraries(test_track sqlite3)
#target_link_libraries(test_track souncity)

add_executable(test_sqlite test_sqlite.cpp ${SOUNDCITY_LIB_SRCS})
target_link_libraries(test_sqlite sqlite3)
#target_link_libraries(test_sqlite souncity)

<<<<<<< HEAD
add_executable(soundcity_console soundcity_console.cpp ${SOUNDCITY_LIB_SRCS})
=======
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
  ../src/NaiveSimilarityStrategy.cpp
  ../src/Playlist.cpp)

add_executable(soundcity_console ${sc_console_SRC})
>>>>>>> 44ed9203854ea96c776065949a35639e83092ed5
target_link_libraries(soundcity_console sqlite3)
#target_link_libraries(soundcity_console souncity)

add_executable(test_similarity test_similarity.cpp ${SOUNDCITY_LIB_SRCS})
target_link_libraries(test_similarity sqlite3)
#target_link_libraries(test_similarity souncity)
