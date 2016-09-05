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
    curlink=nullptr;
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
        caption("CodeLink -"+file);
    });
    mn.at(0).append("Save as",[this](menu::item_proxy& ip)
    {
        file=pickFile(false);
        caption("CodeLink -"+file);
        saveFile(file);
    });
    mn.at(0).append("Exit",[](menu::item_proxy& ip)
    {
        API::exit();
    });
    mn.push_back("Edit");
    mn.at(1).append("Add Block",[this](menu::item_proxy& ip)
    {
        stringstream blkname;
        blkname<<"block"<<blockset.size();
        new Block(this,blkname.str(),rand()%20+10, rand()%20+30, 80, 30);
    });
    mn.at(1).append("Undo",[this](menu::item_proxy& ip)
    {

    });
    mn.push_back("Run");
    mn.at(2).append("Run",[this](menu::item_proxy& ip)
    {
        run();
    });
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
                    l->onClick();
                    break;
                }
            }
        }
    });
    events().mouse_move([this](const arg_mouse& e)
    {
        if(e.left_button)
        {
            curp=e.pos;
            drawing(*this).update();
            cout<<s(curp)<<endl;
        }
    });
    events().key_press([this](const arg_keyboard& e)
    {
        cout<<"key_press"<<endl;
        if(e.key==keyboard::os_del)
            deleteLink();
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
void Desk::loadFile(string fs)
{
    file=fs;
    caption("CodeLink -"+fs);
    ifstream ifs(fs.c_str());
    string temps;
    Xstr xstr;
    while(ifs>>temps)
    {
        if(temps.empty())
            break;
        stringstream ssinfo(xstr.replace(temps,","," "));
        string type;
        ssinfo>>type;
        if(type=="B")
        {
            string name;
            int x,y,w,h;
            ssinfo>>name>>x>>y>>w>>h;
            Block *b=new Block(this,name,x, y, w, h);
            string itypes;
            ssinfo>>b->info.otype>>itypes;
            b->info.itype=xstr.split(itypes,"|");
            b->setPorts(b->info.itype.size(),1);
            cout<<b->caption()<<','<<x<<','<<y<<','<<b->info.otype<<','<<xstr.print(b->info.itype)<<endl;
        }
        else
        {
            int B1,P1,B2,P2;
            ssinfo>>B1>>P1>>B2>>P2;
            Link* l=new Link(this,B1,P1);
            l->endAt(B2,P2);
        }
    }
    ifs.close();
    curlink->unFocus();
    cout<<"-----------------------------"<<endl;
    show();
    exec();
}
void Desk::saveFile(string fs)
{
    vector<int> idmap;
    int j=0;
    ofstream ofs(fs.c_str());
    for(size_t i=0; i<blockset.size(); i++)
    {
        Block *b=blockset[i];
        if(b!=nullptr)
        {
            idmap.push_back(j);
            point p=b->pos();
            nana::size siz=b->size();
            ofs<<"B,"<<b->caption()<<','<<p.x<<','<<p.y<<','<<siz.width<<','<<siz.height<<','<<b->info.otype<<','<<b->info.itype<<endl;
            j++;
        }
        else
            idmap.push_back(-1);
    }
    for(size_t i=0;i<linkset.size();i++)
    {
        Link* l=linkset[i];
        if(l!=nullptr)
        {
            ofs<<"L,"<<idmap[l->B1]<<","<<l->P1<<","<<idmap[l->B2]<<","<<l->P2<<endl;
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
void Desk::deleteBlock()
{
    if(curblock!=nullptr)
    {
        int curid=curblock->id;
        cout<<"delete "<<curblock->caption()<<s(curid)<<endl;
        delete curblock;
        blockset[curid]=nullptr;
        curblock=nullptr;
    }
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

void Desk::clean()
{
    file="";
    caption("CodeLink -new");
    for(size_t i=0; i<linkset.size(); i++)
    {
        delete linkset[i];
    }
    linkset.clear();
    for(size_t i=0; i<blockset.size(); i++)
    {
        delete blockset[i];
    }
    blockset.clear();
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
        ifstream ifs((blockset[i]->caption()+".cpp").c_str());
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
