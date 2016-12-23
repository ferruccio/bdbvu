#
#    Copyright (c) Ferruccio Barletta (ferruccio.barletta@gmail.com), 2010
#
#    This file is part of BDBVu.
#
#    BDBVu is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    BDBVu is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with BDBVu.  If not, see <http://www.gnu.org/licenses/>.

TARGET = bdbvu
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    database.cpp
HEADERS += mainwindow.h \
    database.h
FORMS += mainwindow.ui
DEFINES += HAVE_CXX_STDHEADERS

# environment specific settings (OS X)
osx {
    INCLUDEPATH += /usr/local/BerkeleyDB.4.8/include
    LIBS += /usr/local/BerkeleyDB.4.8/lib/libdb.a
    LIBS += /usr/local/BerkeleyDB.4.8/lib/libdb_cxx.a
}

#environment specific settings (Windows)
win32 {
    INCLUDEPATH += "C:\Program Files\Oracle\Berkeley DB 4.8.26\include"
    LIBS += "C:\Program Files\Oracle\Berkeley DB 4.8.26\lib\libdb48.lib"
}
