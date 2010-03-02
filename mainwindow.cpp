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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings("Ferruccio Barletta", "bdbvu")
{
    ui->setupUi(this);
    ui->databaseType->setText("");
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//
// slot: open a new database file using an open file dialog
//
void MainWindow::openFile()
{
    QString path = settings.value("path", QDir::homePath()).toString();
    QFileDialog ofd(this, tr("open BDB file"), path, tr("All Files (*)"));
    if (ofd.exec()) {
        // remember where we parked
        settings.setValue("path", ofd.directory().absolutePath());
        openFile(ofd.selectedFiles().first());
    }
}

void MainWindow::openFile(QString filename)
{
    db.close();
    try {
        db.open(filename.toAscii());
    }
    catch (dbexception ex) {
        QMessageBox::critical(this, "BDBVu", ex.what());
    }
    ui->databaseSelector->clear();
    if (db.sdblist.length() > 0) {
        foreach (QString dbname, db.sdblist)
            ui->databaseSelector->addItem(dbname, dbname);
        selectDatabase(db.sdblist[0]);
    }
    else
        ui->databaseSelector->setEnabled(false);
}

//
//  slot: select a new sub-database
//
void MainWindow::selectDatabase(const QString& dbname) {
    db.opensubdb(dbname);
    ui->listWidget->clear();
    foreach (dbkey k, db.keylist) {
        QListWidgetItem *li = new QListWidgetItem(k.display);
        ui->listWidget->addItem(li);
    }
    ui->listWidget->setCurrentRow(0);
    ui->databaseType->setText(db.sdbtype);
}

//
//  slot: select a new sub-database key at index
//
void MainWindow::selectKey(int index)
{
    ui->textBrowser->clear();
    ui->textBrowser->append(db.getRecord(index));
}
