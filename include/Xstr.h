#ifndef XSTR_H
#define XSTR_H
#include <vector>
#include <string>
using namespace std;

class Xstr
{
    public:
        Xstr();
        virtual ~Xstr();
        vector<string> split(string s,string delim);
    protected:

    private:
};

#endif // XSTR_H
