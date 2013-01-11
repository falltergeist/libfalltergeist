cmake_minimum_required(VERSION 2.8)

project(libfalltergeist)

set(SOURCES libfalltergeist.cpp
            src/DatFileItem.cpp)

add_library( falltergeist SHARED ${SOURCES})
