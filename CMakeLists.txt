cmake_minimum_required (VERSION 2.6)
project (SoundCity)

SET(CMAKE_CXX_FLAGS  "-std=c++11")

include_directories( ${PROJECT_SOURCE_DIR}/include )


set(SOUNDCITY_LIB_SRCS
  ${PROJECT_SOURCE_DIR}/src/Track.cpp
  ${PROJECT_SOURCE_DIR}/src/ContextData.cpp
  ${PROJECT_SOURCE_DIR}/src/SignalData.cpp
  ${PROJECT_SOURCE_DIR}/src/Artist.cpp
  ${PROJECT_SOURCE_DIR}/src/Album.cpp
  ${PROJECT_SOURCE_DIR}/src/OptionList.cpp
  ${PROJECT_SOURCE_DIR}/src/SQLiteDatabase.cpp
  ${PROJECT_SOURCE_DIR}/src/Generator.cpp
  ${PROJECT_SOURCE_DIR}/src/SimilarityStrategy.cpp
  ${PROJECT_SOURCE_DIR}/src/Playlist.cpp)

add_library( soundcity ${SOUNDCITY_LIB_SRCS} )

add_subdirectory( ${PROJECT_SOURCE_DIR}/test )