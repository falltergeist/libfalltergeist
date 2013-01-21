#
# Copyright 2012-2013 Falltergeist Developers.
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

set(SOURCES libfalltergeist.cpp
            src/DatFile.cpp
            src/DatFileItem.cpp
            src/AafFileType.cpp
            src/AafGlyph.cpp
            src/BioFileType.cpp
            src/FonFileType.cpp
            src/FonGlyph.cpp
            src/FrmFileType.cpp
            src/FrmDirection.cpp
            src/FrmFrame.cpp
            src/GcdFileType.cpp
            src/LstFileType.cpp
            src/MsgFileType.cpp
            src/MsgMessage.cpp
            src/PalFileType.cpp
            src/PalColor.cpp)

set(HEADERS libfalltergeist.h
            src/DatFile.h
            src/DatFileItem.h
            src/AafFileType.h
            src/AafGlyph.h
            src/BioFileType.h
            src/FonFileType.h
            src/FonGlyph.h
            src/FrmFileType.h
            src/FrmDirection.h
            src/FrmFrame.h
            src/GcdFileType.h
            src/LstFileType.h
            src/MsgFileType.h
            src/MsgMessage.h
            src/PalFileType.h
            src/PalColor.h)

add_library( falltergeist SHARED ${SOURCES})
