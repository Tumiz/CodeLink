#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/dragger.hpp>

using namespace nana;
using namespace std;
struct BlockInfo
{
    string name;
    string otype;
    vector<string> itype;
};
enum SelectedSide
{
    LeftSide,
    RightSide,
    TopSide,
    BottomSide,
    LeftTopCorner,
    LeftBottomCorner,
    RightTopCorner,
    RightBottomCorner,
    InSide,
    OutSide
};
enum BlockState
{
    Moving,
    ReSizing,
    UnSelected
};
class Block:public button
{
    public:
        int id;
        string name;
        BlockInfo info;
        vector<Block*> obs,ibs;
        dragger dg;
        window win;
        bool flag_resizing;
        bool flag_onBorder;
        BlockState bs;
        int selectSide;
        point inport();
        point outport();
        void setName(string s);
        int getHeight();
        int getWidth();
        string getName();
        string getFileName();
        bool isEmpty();
        int checkBorder(int x,int y);
        nana::cursor changeCursor(int side);
        Block(window f,int i,string s="",int x=100,int y=100,int w=80,int h=20);
        virtual ~Block();
    protected:

    private:
};

#endif // BLOCK_H
