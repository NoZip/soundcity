cmake_minimum_required (VERSION 2.6)
project (SoundCity)

add_executable(test_track test_track.cpp)
target_link_libraries(test_track soundcity)
target_link_libraries(test_track sqlite3)

add_executable(test_sqlite test_sqlite.cpp)
target_link_libraries(test_sqlite soundcity)
target_link_libraries(test_sqlite sqlite3)

add_executable(soundcity_console soundcity_console.cpp)
target_link_libraries(soundcity_console soundcity)
target_link_libraries(soundcity_console sqlite3)

add_executable(test_similarity test_similarity.cpp)
target_link_libraries(test_similarity soundcity)
target_link_libraries(test_similarity sqlite3)

add_executable(test_playlist_similarity test_playlist_similarity.cpp)
target_link_libraries(test_playlist_similarity soundcity)
target_link_libraries(test_playlist_similarity sqlite3)

# Tests unitaires
enable_testing()

add_executable(SQLiteTest SQLiteTest.cpp)
target_link_libraries(SQLiteTest soundcity)
target_link_libraries(SQLiteTest sqlite3)
target_link_libraries(SQLiteTest cppunit)

add_executable(SimilarityStrategyTest SimilarityStrategyTest.cpp)
target_link_libraries(SimilarityStrategyTest soundcity)
target_link_libraries(SimilarityStrategyTest cppunit)

add_test(sqlite_test SQLiteTest)
add_test(similarity_strategy_test SimilarityStrategyTest)
