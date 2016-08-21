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
#include "Link.h"
#ifndef CODELINK_H_INCLUDED
#include "CodeLink.h"
#endif
using namespace nana;
using namespace std;

struct Config
{
    string file;
};
class Desk:public form
{
public:
    bool linking;
    vector<Link*> linkset;
    vector<Block*> blockset;
    point curp;
    Block* curblock;
    Link* curlink;
    string file;
    bool flag_linking;
    Config cfg;
    Desk();
    Block* newBlock(string s,int x,int y,int w,int h);
    void deleteBlock();
    Link* newLink(int B,int P);
    void deleteLink();
    virtual ~Desk();

protected:

private:
    void readConfig();
    void saveConfig();
    string pickFile(bool is_open) const;
    void loadFile(string fs);
    void saveFile(string fs);
    void clean();
    void run();
};

#endif // DESK_H
