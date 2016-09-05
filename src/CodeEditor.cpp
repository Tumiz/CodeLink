#include "CodeEditor.h"
using namespace nana;
using namespace std;
CodeEditor::CodeEditor(Block* p)
{
    blk=p;
    if(!blk->caption().empty())
        textbox_.load(blk->getFileName());
    textbox_.borderless(true);
    textbox_.indention(true);
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
    caption(blk->caption());
    show();
    exec();
}

string CodeEditor::_m_pick_file(bool is_open)
{
    filebox fbox(*this, is_open);
    fbox.add_filter("C++ File", "*.cpp;*.hpp");
    fbox.add_filter("C File", "*.c");
    fbox.add_filter("header File","*.h");
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
            if(format()==CodeLink::function)
                readFirstLine();
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
    menubar_.push_back("File");
    menubar_.at(0).append("Load", [this](menu::item_proxy& ip)
    {
        if (_m_ask_save())
        {
            auto fs = _m_pick_file(true);
            if (fs.size())
                textbox_.load(fs.data());
            blk->info=readFirstLine();
            string ret=blk->info.name;
            if(ret.empty())
            {
                blk->bgcolor(colors::red);
            }
            else
            {
                blk->bgcolor(colors::white);
                blk->caption(ret);
                blk->setPorts(blk->info.itype.size(),1);
                string oldf=textbox_.filename();
                string newf=blk->getFileName();
                if(oldf!=newf)
                    remove(oldf.c_str());
                textbox_.store(newf);
            }
            caption(blk->caption()+error);
        }
    });
    menubar_.push_back("Format");
    menubar_.at(1).append("Line Wrap", [this](menu::item_proxy& ip)
    {
        textbox_.line_wrapped(ip.checked());
    });
    menubar_.at(1).check_style(0, menu::checks::highlight);
    menubar_.at(1).append("Format",[this](menu::item_proxy& ip)
    {
        format();
    });
}
int CodeEditor::format()
{
    string s;
    stringstream temp;
    vector<string> oki;
    vector<string> vo;
    vector<vector<string> > vi;
    int decoded=0;
    for(int i=0; textbox_.getline(i,s); i++)
    {
        if(Xstr::space(s))
            continue;
        if(Xstr::isNumber(s))
        {
            blk->caption(s);
            blk->setPorts(0,1);
            return CodeLink::constant;
        }
        if(decoded==0)
        {
            oki=Xstr::split(s,"(");
            cout<<"oki:"<<Xstr::print(oki)<<endl;
            vo=Xstr::split(oki[0]," ");
            cout<<"vo:"<<Xstr::print(vo)<<endl;
            vo=Xstr::voidempty(vo);
            cout<<"vo:"<<Xstr::print(vo)<<endl;
            string is=oki[1].substr(0,oki[1].find(")"));
            vector<string> vis=Xstr::split(is,",");
            for(size_t i=0; i<vis.size(); i++)
            {
                vector<string> v=Xstr::split(vis[i]," ");
                v=Xstr::voidempty(v);
                vi.push_back(v);
            }
            temp<<Xstr::print(vo," ")<<"(";
            for(size_t i=0; i<vi.size(); i++)
            {
                if(i==0)
                    temp<<Xstr::print(vi[i]," ");
                else
                    temp<<","<<Xstr::print(vi[i]," ");
            }
            temp<<")";
            decoded++;
        }
        if(decoded>0)
            temp<<endl<<s;
    }
    cout<<temp.str()<<endl<<"----------------------"<<endl;
    string fs=textbox_.filename();
    if(!fs.empty())
    {
        ofstream ofs(fs);
        ofs<<temp.str();
        ofs.close();
        textbox_.load(fs);
    }
    return CodeLink::function;
}
BlockInfo CodeEditor::readFirstLine()
{
    BlockInfo blkinfo;
    error="";
    string s;
    textbox_.getline(0,s);
    cout<<"s:"<<s<<endl;
    if(s.empty())
    {
        error= " -First line is empty";
        return blkinfo;
    }
    vector<string> oki=Xstr::split(s,"(");//strings before and after (
    cout<<"oki:"<<Xstr::print(oki)<<endl;
    if(oki.size()<2)
    {
        error= " -No (";
        return blkinfo;
    }
    vector<string> vo=Xstr::split(oki[0]," ");//strings before (
    vo=Xstr::voidempty(vo);
    cout<<"vo:"<<Xstr::print(vo)<<endl;
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
    cout<<"is:"<<is<<endl;
    vector<string> vi=Xstr::split(is,",");
    cout<<"vi:"<<Xstr::print(vi)<<endl;
    size_t in=vi.size();
    if(in!=1||!Xstr::space(vi[0]))
    {
        for(size_t i=0; i<in; i++)
        {
            if(Xstr::space(vi[i]))
            {
                error=" -No input before or after ,";
                return blkinfo;
            }
            vector<string> in=Xstr::split(vi[i]," ");
            vector<string> inv=Xstr::voidempty(in);
            blkinfo.itype.push_back(inv[0]);
        }
    }
    cout<<"itypes:"<<Xstr::print(blkinfo.itype)<<endl
        <<"----------------------"<<endl;
    blkinfo.name=vo[vo.size()-1];
    blkinfo.otype=vo[vo.size()-2];
    return blkinfo;
}
CodeEditor::~CodeEditor()
{

}
