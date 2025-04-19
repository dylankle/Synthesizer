cmake_minimum_required(VERSION 3.15)

project(soundboard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES arm64)

set(SOURCES
        src/main.cpp
        src/backend/audio.cpp
        src/backend/device.cpp
)

add_executable(soundboard ${SOURCES})

find_library(COREAUDIO_LIBRARY CoreAudio)
find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)

target_link_libraries(soundboard
        ${COREAUDIO_LIBRARY}
        ${AUDIOTOOLBOX_LIBRARY}
)

target_include_directories(soundboard PRIVATE
        src
        src/backend
        src/frontend
)
