#ifndef BLOCK_H
#define BLOCK_H
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/dragger.hpp>
#include <string>
#include <vector>
using namespace nana;
using namespace std;
struct BlockInfo
{
    string name;
    string otype;
    vector<string> itype;
};
class Block:public button
{
    public:
        int id;
        string name;
        string itype;
        string otype;
        string getName();
        BlockInfo info;
        dragger dg;
        void setName(string s);
        string getFileName();
        bool isEmpty();
        Block(window f,int i,string s="",int x=100,int y=100,int w=80,int h=20);
        virtual ~Block();
    protected:

    private:
};

#endif // BLOCK_H
