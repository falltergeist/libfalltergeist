#
# Copyright 2012-2015 Falltergeist Developers.
#
# This file is part of Falltergeist.
#
# Falltergeist is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Falltergeist is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required( VERSION 2.8 )

project( libfalltergeist )

set(libfalltergeist_MAJOR_VERSION "0")
set(libfalltergeist_MINOR_VERSION "2")
set(libfalltergeist_PATCH_VERSION "7")

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

#add extra search paths for libraries and includes
set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE STRING "Directory where binary will install")
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Directory where library will install")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

# Check that current CMakeLists.txt is invoked from another one
# If true don't install the library and build as static
get_directory_property(LIBFALLTERGEIST_EMBEDDED PARENT_DIRECTORY)

set(SOURCES
    src/libfalltergeist.cpp
    src/AafFileType.cpp
    src/AafGlyph.cpp
    src/AcmFileType.cpp
    src/AcmFileType/Decoder.cpp
    src/AcmFileType/Unpacker.cpp
    src/BioFileType.cpp
    src/DatFile.cpp
    src/DatFileEntry.cpp
    src/DatFileItem.cpp
    src/Exception.cpp
    src/FonFileType.cpp
    src/FonGlyph.cpp
    src/FrmFileType.cpp
    src/GamFileType.cpp
    src/GcdFileType.cpp
    src/IntFileType.cpp
    src/LipFileType.cpp
    src/LstFileType.cpp
    src/MapElevation.cpp
    src/MapObject.cpp
    src/MapFileType.cpp
    src/MapScript.cpp
    src/MsgFileType.cpp
    src/MsgMessage.cpp
    src/MveFileType.cpp
    src/PalFileType.cpp
    src/PalColor.cpp
    src/ProFileType.cpp
    src/RixFileType.cpp
    src/SveFileType.cpp)

set(HEADERS
    src/libfalltergeist.h
    src/AafFileType.h
    src/AafGlyph.h
    src/AcmFileType.h
    src/AcmFileType/Decoder.h
    src/AcmFileType/General.h
    src/AcmFileType/Unpacker.h
    src/BioFileType.h
    src/DatFile.h
    src/DatFileEntry.h
    src/DatFileItem.h
    src/Exception.h
    src/FonFileType.h
    src/FonGlyph.h
    src/FrmFileType.h
    src/GamFileType.h
    src/GcdFileType.h
    src/IntFileType.h
    src/LipFileType.h
    src/LstFileType.h
    src/MapElevation.h
    src/MapObject.h
    src/MapFileType.h
    src/MapScript.h
    src/MsgFileType.h
    src/MsgMessage.h
    src/MveFileType.h
    src/PalFileType.h
    src/PalColor.h
    src/ProFileType.h
    src/RixFileType.h
    src/SveFileType.h)

add_definitions (-std=c++11 -Wall)

add_library( falltergeist ${SOURCES})
target_link_libraries(falltergeist ${ZLIB_LIBRARIES})

if(NOT ANDROID)
  set_target_properties(falltergeist PROPERTIES
                        VERSION ${libfalltergeist_MAJOR_VERSION}.${libfalltergeist_MINOR_VERSION}.${libfalltergeist_PATCH_VERSION}
                        SOVERSION ${libfalltergeist_MAJOR_VERSION})
endif()

set_target_properties(falltergeist PROPERTIES
                      PUBLIC_HEADER "${HEADERS}")

if(NOT LIBFALLTERGEIST_EMBEDDED)
    install(TARGETS falltergeist
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        PUBLIC_HEADER DESTINATION "${INCLUDE_INSTALL_DIR}/falltergeist")
else()
  # Build libfalltergeist as static lib only when is used as bundled
  set(BUILD_SHARED_LIBS OFF)
endif()
