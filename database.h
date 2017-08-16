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

#ifndef DATABASE_H
#define DATABASE_H

#include <db_cxx.h>
#include <QList>
#include <QStringList>
#include <vector>

//
//  create our own exception class so that we can use something more flexible than a char* for messages
//
class dbexception : public std::exception
{
public:
    dbexception(const QString& message) : std::exception() { this->message = message; }
    virtual ~dbexception() throw() {}

    const char* what() const throw() { return message.toLatin1(); }

private:
    QString message;
};

//
//  maps displayed keys to searchable keys
//
class dbkey
{
public:
    QString             display;    // what is displayed to user
    QString data;
};

//
//  encapsulate BDB database
//
class database
{
public:
    database();
    virtual ~database();

    QStringList sdblist;            // sub-database list
    QList<dbkey> keylist;           // key list
    QString sdbtype;                // sub-database type

    bool isopen() { return db != 0; }
    void open(const char* filename);
    void close();

    void opensubdb(const QString& dbname);

    QString getRecord(int index);

private:
    QString     filename;           // db filename
    DbEnv       env;                // BDB environment
    Db          *db;                // current database
    Db          *sdb;               // current sub-database
    bool        multiple;           // does database contain sub-databases

    void buildDatabaseList();
    void closesubdb();
    void buildKeyList();
};

#endif // DATABASE_H
