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
        static vector<string> split(string s,string delim);
        static string replace(string src,string origin,string dest);
        static string voidspace(string src);
        static vector<string> voidempty(vector<string> v);
        static bool space(string s);
        static bool isNumber(const string& s);
        static string print(vector<string> v,string div="|");
    protected:

    private:
};

#endif // XSTR_H
