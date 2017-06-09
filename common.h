#ifndef COMMON_H
#define COMMON_H

struct Date
{
    Date();
    
    std::string string;
    int year;
    int mon;
    int day;
};

struct Data
{
    struct Date date;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

#endif /* COMMON_H */

