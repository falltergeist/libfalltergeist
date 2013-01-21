cmake_minimum_required( VERSION 2.8 )

project( libfalltergeist )

set(SOURCES libfalltergeist.cpp
            src/DatFile.cpp
            src/DatFileItem.cpp)

set(HEADERS libfalltergeist.h
            src/DatFile.h
            src/DatFileItem.h)

add_library( falltergeist SHARED ${SOURCES})
