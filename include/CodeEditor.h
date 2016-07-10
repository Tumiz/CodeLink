#ifndef CODEEDITOR_H
#define CODEEDITOR_H
#include <nana/gui.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/filebox.hpp>
#include <string>
#include <fstream>
#include <vector>
#include "Block.h"
using namespace nana;
using namespace std;
class CodeEditor: public form
{
    place   place_  {*this};
    menubar menubar_{*this};
    textbox textbox_{*this};
    Block* blk;
public:
    CodeEditor(void* p,int id);
    virtual ~CodeEditor();
protected:

private:
    string _m_pick_file(bool is_open) const;
    bool _m_ask_save();
    void _m_make_menus();
    vector<string> split(string s,string delim);
};

#endif // CODEEDITOR_H
