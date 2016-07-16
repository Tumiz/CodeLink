#include "Xstr.h"

Xstr::Xstr()
{
    //ctor
}

Xstr::~Xstr()
{
    //dtor
}
vector<string> Xstr::split(string s,string delim)
{
    vector<string> ret;
    size_t last = 0;
    size_t index=s.find_first_of(delim,last);
    while (index!=string::npos)
    {
        ret.push_back(s.substr(last,index-last));
        last=index+1;
        index=s.find_first_of(delim,last);
    }
    if (index-last>0)
        ret.push_back(s.substr(last,index-last));
    return ret;
}
