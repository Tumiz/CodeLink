#ifndef XSTRING_H
#define XSTRING_H
#include <vector>
#include <string>
using namespace std;
class Xstr
{
    public:
        xstring();
        virtual ~xstring();
        vector<string> split(string delim);
        string str();
    protected:

    private:
        string stri;
};

#endif // XSTRING_H
