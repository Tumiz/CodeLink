#ifndef DESK_H
#define DESK_H
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/dragger.hpp>
#include "CodeEditor.h"
#include "CodeLink.h"
using namespace nana;
using namespace std;

class Desk:public form
{
public:
    Desk();
    virtual ~Desk();
    vector<Block*> blockset;
    int curid,preid;
    point curp;
    string file;
protected:

private:
    string pickFile(bool is_open) const;
    Block* createBlock(string s,int x,int y,int w,int h);
    void link(Block*& blk1,Block*& blk2);
    void loadFile(string fs);
    void saveFile(string fs);
    void clean();
};

#endif // DESK_H
