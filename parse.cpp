#include <string>
#include <fstream>
#include <streambuf>
#include <deque>
#include <sstream>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "parse.h"

Date::Date()
{
    string = "";
    year = 0;
    mon = 0;
    day = 0;
}

int readFile(const std::string &file, std::string &text)
{
    std::ifstream t(file.c_str());
    std::string str;
    
    if (t.good())
    {
        t.seekg(0, std::ios::end);
        str.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        str.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
        text = str;
    }
    
    return text.length();
}

bool iequals(const std::string &a, const std::string &b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

int monToInt(char *mon)
{
    std::string string(mon);
    int imon=-1;
    if (iequals(string, "jan"))
    {
        imon = 1;
    }
    else if (iequals(string, "feb"))
    {
        imon = 2;
    }
    else if (iequals(string, "mar"))
    {
        imon = 3;
    }
    else if (iequals(string, "apr"))
    {
        imon = 4;
    }
    else if (iequals(string, "may"))
    {
        imon = 5;
    }
    else if (iequals(string, "jun"))
    {
        imon = 6;
    }
    else if (iequals(string, "jul"))
    {
        imon = 7;
    }
    else if (iequals(string, "aug"))
    {
        imon = 8;
    }
    else if (iequals(string, "sep"))
    {
        imon = 9;
    }
    else if (iequals(string, "oct"))
    {
        imon = 10;
    }
    else if (iequals(string, "nov"))
    {
        imon = 11;
    }
    else if (iequals(string, "dec"))
    {
        imon = 12;
    }
    
    return imon;
}

void replaceString(std::string &str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

int getDate(const std::string &string, struct Date &result)
{
    char buffer[512]={0};
    char mon[8];
    int day;
    int year;
    
    strcpy(buffer, string.c_str());
    //char *token=strtok(buffer, ">");
    result.string="";
    char *token=strchr(buffer, '>');
    if (token)
    {
        sscanf(token+1, "%s %d, %d", &mon, &day, &year);
        
        result.mon = monToInt(mon);
        result.year = year;
        result.day = day;
        
        sprintf(buffer, "%04d%02d%02d", result.year, result.mon, result.day);
        result.string = buffer;
    }
}

double getDecimal(const std::string &string)
{
    char buffer[512]={0};
    std::string newString(string);
    double dec=0.0;
    
//    std::replace(newString.begin(), newString.end(), ",", "");
    replaceString(newString, std::string(","), std::string(""));
    strcpy(buffer, newString.c_str());
    char *token=strchr(buffer, '>');
    if (token)
    {
        sscanf(token+1, "%lf", &dec);
    }
    return dec;
}

int parse(const std::string &text, std::deque<struct Data> &datas)
{
    std::istringstream input(text);
    std::string line;
    const std::string begin("<table class=\"gf-table historical_price\">");
    const std::string end("</table>");
    const int skipCount = 1;
    int i = 0;
    
    input.ignore('"');
    
    //input.str(text);
    while (std::getline(input, line) && line != begin);
    while (std::getline(input, line) && line != end)
    {
        // read 7 lines
        std::string line2, line3, line4, line5, line6, line7;
        
//        std::getline(input, line1);
        std::getline(input, line2);
        std::getline(input, line3);
        std::getline(input, line4);
        std::getline(input, line5);
        std::getline(input, line6);
        std::getline(input, line7);
        
        if (skipCount && i >= skipCount)
        {
            struct Data data;
            getDate(line2, data.date);
            data.open = getDecimal(line3.c_str());
            data.high = getDecimal(line4.c_str());
            data.low = getDecimal(line5.c_str());
            data.close = getDecimal(line6.c_str());
            data.volume = getDecimal(line7.c_str());

            datas.push_back(data);
        }
        i++;
    }
}

