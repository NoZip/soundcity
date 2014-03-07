cmake_minimum_required (VERSION 2.6)
project (SoundCity)

SET(CMAKE_CXX_FLAGS  "-std=c++11")

set(soundcity_SRCS
  ./test_track.cpp
  ../src/Track.cpp
  ../src/ContextData.cpp
  ../src/SignalData.cpp
  ../src/Artist.cpp
  ../src/Album.cpp)

add_executable(test_track ${soundcity_SRCS})