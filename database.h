#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

class Database
{
public :
    Database();
    virtual ~Database();
    
    void init(const std::string &file);
    void insert(const std::string &code, std::deque<struct Data> &datas);
    
private :
    sqlite3 *_db;
};

#endif /* DATABASE_H */

