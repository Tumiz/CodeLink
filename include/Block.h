#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/dragger.hpp>
#include "Port.h"

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
class Desk;
class Block:public button
{
    public:
        int id;
        BlockInfo info;
        dragger dg;
        Desk* dsk;
        BlockState bs;
        int sSide;
        vector<Port*> inps,outps;//inport and outports
        void clearPorts();
        void clearInPorts();
        void clearOutPorts();
        void setPorts(int ins,int outs);
        void setInports(int n);
        void setOutports(int n);
        point inport(int i);
        point outport(int i);
        int getHeight();
        int getWidth();
        string getFileName();
        bool isEmpty();
        int checkBorder(int x,int y);
        nana::cursor changeCursor(int side);
        Block(Desk* f,string s="",int x=100,int y=100,int w=80,int h=20);
        virtual ~Block();
    protected:

    private:
};

#endif // BLOCK_H
