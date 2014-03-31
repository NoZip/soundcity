cmake_minimum_required (VERSION 2.6)
project (SoundCity)

add_executable(test_track test_track.cpp ${SOUNDCITY_LIB_SRCS})
target_link_libraries(test_track sqlite3)
#target_link_libraries(test_track souncity)

add_executable(test_sqlite test_sqlite.cpp ${SOUNDCITY_LIB_SRCS})
target_link_libraries(test_sqlite sqlite3)
#target_link_libraries(test_sqlite souncity)

add_executable(soundcity_console soundcity_console.cpp ${SOUNDCITY_LIB_SRCS})
target_link_libraries(soundcity_console sqlite3)
#target_link_libraries(soundcity_console souncity)

add_executable(test_similarity test_similarity.cpp ${SOUNDCITY_LIB_SRCS})
target_link_libraries(test_similarity sqlite3)
#target_link_libraries(test_similarity souncity)
