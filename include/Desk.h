#ifndef DESK_H
#define DESK_H
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/dragger.hpp>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "CodeEditor.h"
#include "Link.h"
#include "CodeLink.h"
using namespace nana;
using namespace std;

class Desk:public form
{
public:
    Desk();
    virtual ~Desk();
    vector<Block*> blockset;
    int selectedBlock;
    int preselctBlock;
    string file;
protected:

private:
    string pickFile(bool is_open) const;
    Block* createBlock(string s,int x,int y,int w,int h);
    void loadFile(string fs);
    void saveFile(string fs);
};

#endif // DESK_H
