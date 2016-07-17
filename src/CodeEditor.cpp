#include "CodeEditor.h"
using namespace std;
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
            string ret=readFirstLine().name;
            blk->setName(ret);
            caption(blk->name+error);
        }
    });
    menubar_.at(0).append("Apply", [this](menu::item_proxy&)
    {
        string ret=readFirstLine().name;
        if(ret.empty())
        {
            blk->bgcolor(colors::red);
        }
        else
        {
            blk->bgcolor(colors::white);
            blk->setName(ret);
            string oldf=textbox_.filename();
            string newf=blk->getFileName();
            if(oldf!=newf)
                remove(oldf.c_str());
            textbox_.store(newf);
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
BlockInfo CodeEditor::readFirstLine()
{
    BlockInfo blkinfo;
    error="";
    string s;
    textbox_.getline(0,s);
    cout<<"s: "<<s<<endl;
    if(s.empty())
    {
        error= " -First line is empty";
        return blkinfo;
    }
    Xstr X;
    vector<string> oki=X.split(s,"(");//strings before and after (
    cout<<"oki"<<X.print(oki)<<endl;
    if(oki.size()<2)
    {
        error= " -No (";
        return blkinfo;
    }
    vector<string> vo=X.split(oki[0]," ");//strings before (
    vo=X.voidempty(vo);
    cout<<"vo"<<X.print(vo);
    if(vo.size()<2)
    {
        error= " -No return type";
        return blkinfo;
    }
    if(oki[1].length()<1)//string after (
    {
        error=" -No )";
        return blkinfo;
    }
    string is=oki[1].substr(0,oki[1].find(")"));
    cout<<"is"<<is<<endl;
    vector<string> vi=X.split(is,",");
    cout<<"vi"<<X.print(vi)<<endl;
    size_t in=vi.size();
    if(in!=1||!X.space(vi[0]))
    {
        for(size_t i=0; i<in; i++)
        {
            if(X.space(vi[i]))
            {
                error=" -No input before or after ,";
                return blkinfo;
            }
            vector<string> in=X.split(vi[i]," ");
            vector<string> inv=X.voidempty(in);
            blkinfo.itype.push_back(inv[0]);
        }
    }
    cout<<"itypes"<<X.print(blkinfo.itype)<<endl;
    blkinfo.name=vo[vo.size()-1];
    blkinfo.otype=vo[vo.size()-2];
    return blkinfo;
}
CodeEditor::~CodeEditor()
{
    //dtor
}
