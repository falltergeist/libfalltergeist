cmake_minimum_required(VERSION 2.8)

set(SOURCES libfalltergeist.cpp
            src/DatFileItem.cpp)

add_library( libfalltergeist SHARED ${SOURCES})
