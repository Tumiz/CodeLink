#include "xstring.h"

xstring::xstring()
{
    //ctor
}
xstring::xstring(string s)
{
    stri=s;
}
xstring::~xstring()
{
    //dtor
}

vector<xstring> xstring::split(string delim)
{
    vector<xstring> ret;
    size_t last = 0;
    size_t index=find_first_of(delim,last);
    while (index!=string::npos)
    {
        ret.push_back((xstring)substr(last,index-last));
        last=index+1;
        index=find_first_of(delim,last);
    }
    if (index-last>0)
        ret.push_back(substr(last,index-last));
    return ret;
}

string xstring::str()
{
    return stri;
}
