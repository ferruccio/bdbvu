/*
    Copyright (c) Ferruccio Barletta (ferruccio.barletta@gmail.com), 2010

    This file is part of BDBVu.

    BDBVu is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BDBVu is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BDBVu.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if (a.arguments().length() > 1)
       w.openFile(a.arguments()[1]);
    return a.exec();
}
