# The MIT License (MIT)
#
# Copyright (c) 2012-2015 Falltergeist developers
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

cmake_minimum_required( VERSION 2.8 )

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (by default Debug)")

project( libfalltergeist )

set(libfalltergeist_MAJOR_VERSION "0")
set(libfalltergeist_MINOR_VERSION "4")
set(libfalltergeist_PATCH_VERSION "0")

set(libfalltergeist_VERSION_STRING "${libfalltergeist_MAJOR_VERSION}.${libfalltergeist_MINOR_VERSION}.${libfalltergeist_PATCH_VERSION}")

# On Windows debug library should have 'd' postfix.
# On Mac OS X '_debug' postfix
if(WIN32)
    set(CMAKE_DEBUG_POSTFIX "d")
elseif(APPLE)
    set(CMAKE_DEBUG_POSTFIX "_debug")
endif(WIN32)

# BUILD_SHARED_LIBS is cmake variable. Need to change default value.
option(BUILD_SHARED_LIBS "Build shared library" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#add extra search paths for libraries and includes
set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE STRING "Directory where binary will install")
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Directory where library will install")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

add_definitions (-std=c++11 -Wall)

file(GLOB_RECURSE SOURCES  "src/*.cpp")
file(GLOB_RECURSE HEADERS  "src/*.h")

# Copy library headers to separate directory
file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/src" 
     DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/include"
     FILES_MATCHING PATTERN "*.h")
file(RENAME "${CMAKE_CURRENT_SOURCE_DIR}/include/src" "${CMAKE_CURRENT_SOURCE_DIR}/include/libfalltergeist")

if(LIBFALLTERGEIST_EMBEDDED)
    set(BUILD_SHARED_LIBS OFF)
endif()

add_library(falltergeist ${SOURCES} ${HEADERS})
target_link_libraries(falltergeist ${ZLIB_LIBRARIES})

if(NOT ANDROID)
    set_target_properties(falltergeist PROPERTIES
                        VERSION ${libfalltergeist_MAJOR_VERSION}.${libfalltergeist_MINOR_VERSION}.${libfalltergeist_PATCH_VERSION}
                        SOVERSION ${libfalltergeist_MAJOR_VERSION})
endif()

if(NOT LIBFALLTERGEIST_EMBEDDED)
    install(TARGETS falltergeist
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR})

    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/libfalltergeist" DESTINATION ${INCLUDE_INSTALL_DIR})
endif()

