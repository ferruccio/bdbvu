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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "database.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openFile();
    void openFile(QString filename);
    void selectDatabase(const QString& dbname);
    void selectKey(int index);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QSettings settings;

    database db;
};

#endif // MAINWINDOW_H
