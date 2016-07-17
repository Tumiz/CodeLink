#include "Xstr.h"
using namespace std;
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
    if(!s.empty())
    {
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
    }
    return ret;
}
string Xstr::replace(string src,string origin,string dest)
{
    while(1)
    {
        size_t pos=src.find(origin);
        if(pos!=string::npos)
            src.replace(pos,origin.length(),dest);
        else
            break;
    }
    return src;
}
string Xstr::voidspace(string src)
{
    return replace(src," ","");
}
vector<string> Xstr::voidempty(vector<string> v)
{
    vector<string> o;
    for(size_t i=0; i<v.size() ; i++ )
    {
        if(!v[i].empty())
            o.push_back(v[i]);
    }
    return o;
}
string Xstr::print(vector<string> v)
{
    string ret="[";
    for(size_t i=0; i<v.size() ; i++ )
    {
        if(i==0)
            ret+=v[i];
        else
            ret+="|"+v[i];
    }
    ret+="]";
    return ret;
}
bool Xstr::space(string s)
{
    for(size_t i=0; i<s.length(); i++)
    {
        if(s[i]!=' ')
            return false;
    }
    return true;
}
