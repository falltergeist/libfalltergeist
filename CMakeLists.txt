cmake_minimum_required(VERSION 2.8)

set(SOURCES  libfalltergeist.cpp)
foreach( SOURCE_FILE ${SOURCES} )
    add_library( libfalltergeist SHARED ${SOURCE_FILE})
endforeach( SOURCE_FILE )