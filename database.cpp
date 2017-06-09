#include <deque>
#include <string>
#include <sstream>
#include <stdio.h>

#include "common.h"
#include "database.h"

Database::Database()
{
}

Database::~Database()
{
    sqlite3_close(_db);
}

void Database::init(const std::string &filename)
{
    std::string sql;
    char *msg;

    sqlite3_open(filename.c_str(), &_db);

    sql="pragma synchronous = normal;";
    sqlite3_exec(_db, sql.c_str(), NULL, NULL, &msg);
    if (msg)
        sqlite3_free(msg);

    sql="pragma temp_store = 2;";
    sqlite3_exec(_db, sql.c_str(), NULL, NULL, &msg);
    if (msg)
        sqlite3_free(msg);

    sql="pragma journal_mode = memory;";
    sqlite3_exec(_db, sql.c_str(), NULL, NULL, &msg);
    if (msg)
        sqlite3_free(msg);

    sql="create table info (code text not null, "
            "year integer not null, month integer not null, day integer not null, "
            "high real, low real, open real, close real, "
            "unique (code, year, month, day));";
    sqlite3_exec(_db, sql.c_str(), NULL, NULL, &msg);
    if (msg)
        sqlite3_free(msg);
}

void Database::insert(const std::string &code, std::deque<struct Data> &datas)
{
    std::string sql;
    std::deque<struct Data>::iterator iter;
    char *msg;
    
    iter = datas.begin();
    while (iter != datas.end())
    {
        std::ostringstream strs;
        strs << "insert into info (code, year, month, day, high, low, open, close) values (" <<
            "'" << code << "', " << iter->date.year << ", " << iter->date.mon << ", " << iter->date.day << ", " << 
            iter->high << ", " << iter->low << ", " << iter->open << ", " << iter->close << ");";

        sqlite3_exec(_db, strs.str().c_str(), NULL, NULL, &msg);
        if (msg)
        {
            printf ("error found: %s\n", msg);
            sqlite3_free(msg);
        }
        
        iter++;
    }
    
}
