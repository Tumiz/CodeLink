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
#include <iostream>
#include <vector>
#include "Block.h"
#include "Xstr.h"
using namespace nana;
using namespace std;
class CodeEditor: public form
{
    enum FirstLine
    {
        Empty,
        NoParent,
        NoReturnType,
        OK
    };
    place   place_  {*this};
    menubar menubar_{*this};
    textbox textbox_{*this};
    Block* blk;
    string error;
public:
    CodeEditor(Block* p);
    virtual ~CodeEditor();
protected:

private:
    string _m_pick_file(bool is_open) const;
    bool _m_ask_save();
    void _m_make_menus();
    BlockInfo readFirstLine();
};

#endif // CODEEDITOR_H
