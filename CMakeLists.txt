#
# Copyright 2012-2014 Falltergeist Developers.
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

find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
	  message(FATAL_ERROR "Zlib library not found")
endif(NOT ZLIB_FOUND)
include_directories(${ZLIB_INCLUDE_DIRS})

set(SOURCES libfalltergeist.cpp
            src/AafFileType.cpp
            src/AafGlyph.cpp
            src/AcmFileType.cpp
            src/decoder.cpp
            src/unpacker.cpp
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
            src/RixFileType.cpp)

set(HEADERS libfalltergeist.h
            src/AafFileType.h
            src/AafGlyph.h
            src/AcmFileType.h
            src/decoder.h
            src/unpacker.h
            src/general.h
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
            src/RixFileType.h)

add_definitions (-std=c++11 -Wall)
set(CMAKE_BUILD_TYPE Debug)

add_library( falltergeist SHARED ${SOURCES})
target_link_libraries(falltergeist ${ZLIB_LIBRARIES})
