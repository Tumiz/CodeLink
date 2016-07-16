#include "CodeEditor.h"
CodeEditor::CodeEditor(Block* p)
{
    blk=p;
    if(!blk->getName().empty())
        textbox_.load(blk->getFileName());
    textbox_.borderless(true);
    API::effects_edge_nimbus(textbox_, effects::edge_nimbus::none);
    textbox_.enable_dropfiles(true);
    textbox_.events().mouse_dropfiles([this](const arg_dropfiles& arg)
    {
        if (arg.files.size() && _m_ask_save())
            textbox_.load(arg.files.at(0).data());
    });

    _m_make_menus();

    place_.div("vert<menubar weight=28><textbox>");
    place_["menubar"] << menubar_;
    place_["textbox"] << textbox_;
    place_.collocate();

    events().unload([this](const arg_unload& arg)
    {
        if (!_m_ask_save())
            arg.cancel = true;
    });
    caption(blk->name);
    show();
    exec();
}

string CodeEditor::_m_pick_file(bool is_open) const
{
    filebox fbox(*this, is_open);
    fbox.add_filter("Text", "*.cpp");
    fbox.add_filter("All Files", "*.*");

    return (fbox.show() ? fbox.file() : "" );
}

bool CodeEditor::_m_ask_save()
{
    if (textbox_.edited())
    {
        auto fs = textbox_.filename();
        msgbox box(*this, "Block Editor", msgbox::button_t::yes_no_cancel);
        box << "Do you want to save changes?";

        switch (box.show())
        {
        case msgbox::pick_yes:
            textbox_.store(fs.data());
            break;
        case msgbox::pick_no:
            break;
        default:
            return false;
        }
    }
    return true;
}

void CodeEditor::_m_make_menus()
{
    menubar_.push_back("&FILE");
    menubar_.at(0).append("Load", [this](menu::item_proxy& ip)
    {
        if (_m_ask_save())
        {
            auto fs = _m_pick_file(true);
            if (fs.size())
                textbox_.load(fs.data());
            string ret=readFirstLine();
            blk->setName(ret);
            caption(blk->name+error);
        }
    });
    menubar_.at(0).append("Apply", [this](menu::item_proxy&)
    {
        string ret=readFirstLine();
        if(ret.empty())
        {
            blk->bgcolor(colors::red);
        }
        else
        {
            blk->bgcolor(colors::white);
            blk->setName(ret);
            textbox_.store(blk->getFileName());
        }
        caption(blk->name+error);
    });

    menubar_.push_back("F&ORMAT");
    menubar_.at(1).append("Line Wrap", [this](menu::item_proxy& ip)
    {
        textbox_.line_wrapped(ip.checked());
    });
    menubar_.at(1).check_style(0, menu::checks::highlight);
}
string CodeEditor::readFirstLine()
{
    error="";
    string s;
    textbox_.getline(0,s);
    if(s.empty())
    {
        error= " -Empty";
        return "";
    }
    Xstr X;
    vector<string> s1=X.split(s,"(");
    if(s1.size()==1)
    {
        error= " -No ( or )";
        return "";
    }
    vector<string> s2=X.split(s1[0]," ");
    if(s2.size()==1||s2[0].empty())
    {
        error= " -No return type";
        return "";
    }
    string result=s2[s2.size()-1];
    return result;
}
CodeEditor::~CodeEditor()
{
    //dtor
}
