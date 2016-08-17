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
#ifndef CODELINK_H_INCLUDED
#include "CodeLink.h"
#endif
using namespace nana;
using namespace std;
struct SelectBorder
{
    bool left;
    bool right;
    bool top;
    bool bottom;
};
class Desk:public form
{
public:
    Desk();
    virtual ~Desk();
    vector<Block*> blockset;
    int curid,preid;
    point linkp1,linkp2;
    string file;
    SelectBorder sb;
    MouseState ms;
    bool flag_linking;
protected:

private:
    string pickFile(bool is_open) const;
    Block* createBlock(string s,int x,int y,int w,int h);
    void link(int id1,int id2);
    void loadFile(string fs);
    void saveFile(string fs);
    void clean();
};

#endif // DESK_H
