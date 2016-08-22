#include "Desk.h"
using namespace std;
using namespace nana;
Desk::Desk():form(API::make_center(600,400))
{
    caption(L"CodeLink");//name it
    bgcolor(colors::white_smoke);
    place pl(*this);
    menubar mn(*this);
    pl.div("<vertical <menu weight=25>>");
    pl.field("menu") << mn;
    linking=false;
    readConfig();
    mn.push_back("File");
    mn.at(0).append("New",[this](menu::item_proxy& ip)
    {
        clean();
    });
    mn.at(0).append("Load",[this](menu::item_proxy& ip)
    {
        string fs=pickFile(true);
        if(!fs.empty())
        {
            clean();
            loadFile(fs);
            cfg.file=fs;
        }
    });
    mn.at(0).append("Save",[this](menu::item_proxy& ip)
    {
        if(file.empty())
            file=pickFile(false);
        saveFile(file);
    });
    mn.at(0).append("Save as",[this](menu::item_proxy& ip)
    {
        file=pickFile(false);
        caption("CodeLink -"+file);
        saveFile(file);
    });
    mn.at(0).append("Exit",[](menu::item_proxy& ip){API::exit();});
    mn.push_back("Add");
    mn.at(1).append("Block",[this](menu::item_proxy& ip)
    {
        stringstream blkname;
        blkname<<"block"<<blockset.size();
        newBlock(blkname.str(),rand()%20+10, rand()%20+30, 80, 30);
    });
    mn.push_back("Delete");
    mn.at(2).append("Block",[this](menu::item_proxy& ip){deleteBlock();});
    mn.at(2).append("Link",[this](menu::item_proxy& ip){deleteLink();});
    mn.push_back("Run");
    mn.at(3).append("Run",[this](menu::item_proxy& ip){run();});
    pl.collocate();
    show();
    events().mouse_down([this](const arg_mouse& e)
    {
        if(e.left_button)
        {
            point p=e.pos;
            for(unsigned int i=0; i<linkset.size(); i++)
            {
                Link* l=linkset[i];
                if(l!=nullptr&&l->isPointOnLink(p))
                {
                    l->setSelected();
                    int id=l->id;
                    cout<<s(id)<<s(curlink)<<endl;
                    break;
                }
            }
        }
    });
    if(!cfg.file.empty())
        loadFile(cfg.file);
    exec();
}
void Desk::readConfig()
{
    ifstream rcfg("config.txt");
    rcfg>>cfg.file;
    rcfg.close();
}
void Desk::saveConfig()
{
    ofstream wcfg("config.txt");
    wcfg<<cfg.file;
    wcfg.close();
}
void Desk::saveFile(string fs)
{
    ofstream ofs(fs.c_str());
    for(size_t i=0; i<blockset.size(); i++)
    {
        Block *b=blockset[i];
        if(b!=nullptr)
        {
            point p=b->pos();
            nana::size siz=b->size();
            ofs<<b->name<<','<<p.x<<','<<p.y<<','<<siz.width<<','<<siz.height<<','<<b->info.otype<<','<<b->info.itype<<endl;
        }
    }
    ofs.close();
}
string Desk::pickFile(bool is_open) const
{
    filebox fbox(is_open);
    fbox.add_filter("csv", "*.csv");
    fbox.add_filter("All Files", "*.*");
    return (fbox.show() ? fbox.file() : "" );
}
Block* Desk::newBlock(string s,int x,int y,int w,int h)
{
    curblock=new Block(this,s,x,y,w,h);
    blockset.push_back(curblock);
    cout<<"new "<<curblock->name<<s(curblock->id)<<endl;
    curblock->events().dbl_click([this]()
    {
        CodeEditor ce(curblock);
    });
    return curblock;
}
void Desk::deleteBlock()
{
        if(curblock!=nullptr)
        {
            int curid=curblock->id;
            cout<<"delete "<<curblock->name<<s(curid)<<endl;
            delete curblock;
            blockset[curid]=nullptr;
            curblock=nullptr;
        }
}
Link* Desk::newLink(int B,int P)
{
    linking=true;
    curlink=new Link(this,B,P);
    linkset.push_back(curlink);
    return curlink;
}
void Desk::deleteLink()
{
        if(curlink!=nullptr)
        {
            cout<<"delete Link"<<curlink->B1<<curlink->P1<<curlink->B2<<curlink->P2<<endl;
            int curid=curlink->id;
            delete curlink;
            linkset[curid]=nullptr;
            curlink=nullptr;
        }
}
void Desk::loadFile(string fs)
{
    file=fs;
    caption("CodeLink -"+fs);
    ifstream ifs(fs.c_str());
    string blkinfo;
    int i=0;
    while(ifs>>blkinfo)
    {
        Xstr xstr;
        string name;
        int x,y,w,h;
        stringstream ssinfo(xstr.replace(blkinfo,","," "));
        ssinfo>>name>>x>>y>>w>>h;
        Block *b=newBlock(name,x, y, w, h);
        string itypes;
        ssinfo>>b->info.otype>>itypes;
        b->info.itype=xstr.split(itypes,"|");
        b->setPorts(b->info.itype.size(),1);
        cout<<b->name<<','<<x<<','<<y<<','<<b->info.otype<<','<<xstr.print(b->info.itype)<<endl;
        i++;
    }
    cout<<"-----------------------------"<<endl;
    show();
    exec();
}
void Desk::clean()
{
    file="";
    caption("CodeLink -new");
    for(size_t i=0; i<blockset.size(); i++)
    {
        delete blockset[i];
    }
    blockset.clear();
    for(size_t i=0; i<linkset.size(); i++)
    {
        delete linkset[i];
    }
    linkset.clear();
    drawing d(*this);
    d.clear();
    d.update();
}
void Desk::run()
{
     string name;
        if(file.empty())
            name="Generated";
        else
        {
            size_t dotpos=file.find(".csv");
            name=file.erase(dotpos,4);
        }

        stringstream ss;
        for(size_t i=0; i<blockset.size(); i++)
        {
            ifstream ifs((blockset[i]->name+".cpp").c_str());
            string temp;
            for(int j=0; ifs; j++)
            {
                getline(ifs,temp,'\n');
                ss<<temp;
                cout<<temp<<j;
            }
            ifs.close();
        }
        cout<<ss.str();
        ofstream ofs(name+".cpp");
        ofs<<"\
#include <iostream>\n\
#include <stdlib.h>\n\
using namespace std;\n"
           <<ss.str()
           <<"int main()\n\
{\n\
    for(int i=0;i<100;i++)\n\
           cout<<k(i)<<endl;\n\
    system(\"pause\");\n\
    return 0;\n\
}";
        ofs.close();
        system(("g++ "+name+".cpp -o gen").c_str());
        system("gen");
}
Desk::~Desk()
{
    saveConfig();
}
