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

#include "database.h"

using namespace std;

database::database()
    : sdblist(), keylist(), sdbtype(),
      env(0), db(0), sdb(0)
{
    env.open(0, DB_INIT_MPOOL | DB_CREATE | DB_PRIVATE, 0);
}

database::~database()
{
    close();
    env.close(0);
}

//
//  open a new database
//
void database::open(const char* filename)
{
    close();
    db = new Db(&env, 0);
    try {
        db->open(0, filename, 0, DB_UNKNOWN, DB_RDONLY | DB_RDWRMASTER, 0);
        multiple = db->get_multiple() != 0;
        if (multiple)
            buildDatabaseList();
        this->filename = filename;
    } catch (DbException ex) {
        close();
        throw dbexception(QString("%1\n\nfilename: %2\n\nerrno: %3").arg(ex.what()).arg(filename).arg(ex.get_errno()));
    }
}

//
//  close current database
//
void database::close()
{
    if (isopen()) {
        closesubdb();
        db->close(0);
        delete db;
        db = 0;
        filename = "";
    }
}

//
// convert a byte buffer to a QString
//
static QString getString(void *buf, int len)
{
    char *p = static_cast<char *>(buf);
    QString s;
    while (len--) {
        // Do not append ending NULL character!
        if(!(len == 0 && *p == '\0')) {
            s.append(QChar(*p++));
        }
    }
    return s;
}

//
//  create list of available sub-databases
//
void database::buildDatabaseList()
{
    sdblist.clear();
    Dbc *cursor;
    db->cursor(0, &cursor, 0);
    Dbt key, data;
    while (cursor->get(&key, &data, DB_IGNORE_LEASE | DB_NEXT) != DB_NOTFOUND)
        sdblist.append(getString(key.get_data(), key.get_size()));
}

//
//  open a sub-database
//
void database::opensubdb(const QString &dbname)
{
    closesubdb();
    try {
        sdb = new Db(&env, 0);
        sdb->open(0, filename.toAscii(), dbname.toAscii(), DB_UNKNOWN, DB_RDONLY | DB_RDWRMASTER, 0);
        buildKeyList();
    } catch (DbException ex) {
        closesubdb();
        throw dbexception(QString("%1\n\ndatabase: %2\n\nerrno: %3").arg(ex.what()).arg(dbname).arg(ex.get_errno()));
    }
}

//
//  close sub-database
//
void database::closesubdb()
{
    if (sdb != 0) {
        sdb->close(0);
        delete sdb;
        sdb = 0;
    }
}

//
// generate a "visible" string by converting non-ASCII characters to visible escape sequences
//
static QString makeVisible(const QString& s) {
    QString r;
    foreach (QChar c, s) {
        if (c != QChar('\n') && (c < QChar(' ') || c > QChar('~')))
            r.append(QString("\\%1").arg(c.toAscii() & 0xff, 2, 16, QChar('0')));
        else if (c == QChar('\\'))
            r.append("\\\\");
        else
            r.append(c);
    }
    return r;
}

//
//  build key list for sub-database
//
void database::buildKeyList()
{
    // record sub-database type
    DBTYPE t;
    sdb->get_type(&t);
    switch (t) {
    case DB_RECNO: sdbtype = "DB_RECNO"; break;
    case DB_QUEUE: sdbtype = "DB_QUEUE"; break;
    case DB_BTREE: sdbtype = "DB_BTREE"; break;
    case DB_HASH: sdbtype = "DB_HASH"; break;
    default: sdbtype = "unknown"; break;
    }

    // build the key list
    keylist.clear();
    Dbc *cursor;
    sdb->cursor(0, &cursor, 0);
    Dbt key, data;
    while (cursor->get(&key, &data, DB_IGNORE_LEASE | DB_NEXT) != DB_NOTFOUND) {
        dbkey k;
        if (t == DB_RECNO || t == DB_QUEUE) {
            char *src = static_cast<char *>(key.get_data());
            k.display = QString("%1").arg(*reinterpret_cast<int *>(&src[0]));
        } else {
            k.display = makeVisible(getString(key.get_data(), key.get_size()));
        }
        k.data = getString(data.get_data(), data.get_size());
        keylist.push_back(k);
    }
}

//
//  fetch a record using the key at index
//
QString database::getRecord(int index)
{
    if (index < 0 || index >= keylist.size())
        return QString("-- bad index: %1").arg(index);
    return makeVisible(keylist[index].data);
}
