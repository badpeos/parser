#include <string>
#include <deque>

#include <stdio.h>
#include <string.h>

#include "common.h"
#include "parse.h"
#include "database.h"

int main(int argc, char *argv[])
{
    std::string file;
    std::string dbfile;
    std::string text;
    Database db;

    if (argc>1)
    {
        file = argv[1];
        dbfile = argv[2];
    }
    else
    {
        file = "/root/database/2016_08.htm";
        dbfile = "/root/database/stock.db";
    }
    
    printf ("file: %s ... ", file.c_str());
    
    readFile(file, text);
    
    std::deque<struct Data> datas;
    if (text.length())
    {
        parse(text, datas);
    }
    printf ("   count: %-2ld", datas.size());
    
    db.init(dbfile);
    db.insert(std::string("0001"), datas);
    printf ("   records inserted\n");

    return 0;
}
