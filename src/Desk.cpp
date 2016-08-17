#include "Desk.h"
using namespace std;
using namespace nana;
Desk::Desk()
{
    caption(L"CodeLink");//name it
    place pl(*this);
    menubar mn(*this);
    pl.div("<vertical <menu weight=25>>");
    pl.field("menu") << mn;
    preid=0;
    curid=0;
    sb.left=sb.right=sb.top=sb.bottom=false;
    ms.leftPress=false;
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
    mn.at(0).append("Exit",[](menu::item_proxy& ip)
    {
        API::exit();
    });
    mn.push_back("Add");
    mn.at(1).append("Block",[this](menu::item_proxy& ip)
    {
        cout<<"add block ";
        int id=int(blockset.size());
        cout<<1;
        stringstream blkname;
        blkname<<"block"<<id;
        createBlock(blkname.str(),rand()%20+10, rand()%20+10, 80, 40);
    });
    mn.at(1).append("Link",[this](menu::item_proxy& ip)
    {
        cout<<"link: "<<preid<<" "<<curid<<endl;
        link(preid,curid);
    });
    mn.push_back("Delete");
    mn.at(2).append("Block",[this](menu::item_proxy& ip)
    {
        cout<<"delete "<<curid<<endl;
        delete blockset[curid];
        blockset[curid]=NULL;
        curid=preid;
    });
    mn.push_back("Run");
    mn.at(3).append("Run",[this](menu::item_proxy& ip)
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
    });
    pl.collocate();
    show();
    events().mouse_down([this](const arg_mouse& e)
    {
        ms.leftPress=true;
    });
    events().mouse_up([this](const arg_mouse& e)
    {
        ms.leftPress=false;
    });
    exec();
}
void Desk::saveFile(string fs)
{
    Xstr x;
    ofstream ofs(fs.c_str());
    for(size_t i=0; i<blockset.size(); i++)
    {
        Block *b=blockset[i];
        point p=blockset[i]->pos();
        ofs<<b->name<<','<<p.x<<','<<p.y<<','<<b->info.otype<<','<<x.print(b->info.itype)<<endl;
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
Block* Desk::createBlock(string s,int x,int y,int w,int h)
{
    Block *blk=new Block(*this,blockset.size(),s,x,y,w,h);
    blockset.push_back(blk);
    cout<<preid<<curid<<" ";
    preid=curid;
    curid=blk->id;
    cout<<preid<<curid<<" ";
    cout<<"new:  id "<<blk->id<<" addr "<<blk<<endl<<"-------------------"<<endl;
    blk->events().dbl_click([blk]()
    {
        CodeEditor ce(blk);
    });
    blk->events().mouse_down([this,blk](const arg_mouse& e)
    {
        if(e.left_button)
            preid=blk->id;
        if(e.right_button)
        {
            curid=blk->id;
            link(preid,curid);
        }
    });
    return blk;
}
void Desk::link(int id1,int id2)
{
    drawing d(*this);
    d.draw([this,&id1,&id2](paint::graphics& graph)
    {
        point po=blockset[id1]->outport();
        point pi=blockset[id2]->inport();
        if(blockset[id1]!=NULL&&blockset[id1]!=NULL)
        {
            if(id1==id2)
            {
                int h=blockset[id1]->getHeight();
                point p1= {po.x,po.y+h/2+10};
                point p2= {pi.x,po.y+h/2+10};
                graph.line(po,p1,colors::black);
                graph.line(p1,p2,colors::black);
                graph.line(p2,pi,colors::black);
            }
            else
                graph.line(po,pi,colors::black);
        }
        else
            cout<<"Link NULL"<<endl;
    });
    d.update();
    exec();
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
        int x,y;
        stringstream ssinfo(xstr.replace(blkinfo,","," "));
        ssinfo>>name>>x>>y;
        Block *b=createBlock(name,x, y, 80, 20);
        string itypes;
        ssinfo>>b->info.otype>>itypes;
        b->info.itype=xstr.split(itypes,"|");
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
    drawing d(*this);
    d.clear();
    d.update();
}
Desk::~Desk()
{
    //dtor
}
