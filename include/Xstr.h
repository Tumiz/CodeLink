#ifndef XSTR_H
#define XSTR_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Xstr
{
    public:
        Xstr();
        virtual ~Xstr();
        vector<string> split(string s,string delim);
        string replace(string src,string origin,string dest);
        string voidspace(string src);
        vector<string> voidempty(vector<string> v);
        bool space(string s);
        string print(vector<string> v);
    protected:

    private:
};

#endif // XSTR_H
