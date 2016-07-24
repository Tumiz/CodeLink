#include "Desk.h"
using namespace std;
using namespace nana;
Desk::Desk()
{
    preselctBlock=selectedBlock=0;
    caption(L"CodeLink");//name it
    place pl(*this);
    menubar mn(*this);
    pl.div("<vertical <menu weight=25>>");
    pl.field("menu") << mn;

    mn.push_back("File");
    mn.at(0).append("New",[this](menu::item_proxy& ip)
    {
        file="";
        caption("CodeLink -new");
        for(size_t i=0; i<blockset.size(); i++)
        {
            delete blockset[i];
        }
        blockset.clear();
    });
    mn.at(0).append("Load",[this](menu::item_proxy& ip)
    {
        string fs=pickFile(true);
        loadFile(fs);
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
        int id=int(blockset.size());
        stringstream blkname;
        blkname<<"block"<<id;
        createBlock(blkname.str(),10+rand()%100, 50+rand()%100, 80, 20);
    });
    mn.at(1).append("Link",[this](menu::item_proxy& ip)
    {
        Link link(*this,this->blockset[this->preselctBlock],this->blockset[this->selectedBlock]);
    });
    mn.at(1).append("Scope",[this](menu::item_proxy& ip)
    {

    });
    mn.at(1).append("Source",[this](menu::item_proxy& ip)
    {

    });
    mn.push_back("Run");
    mn.at(2).append("Run",[this](menu::item_proxy& ip)
    {
        size_t dotpos=file.find(".csv");
        string name=file.erase(dotpos,4);
        system(("g++ "+name+".cpp -o gen").c_str());
    });
    pl.collocate();
    show();
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
    blk->events().dbl_click([blk]()
    {
        CodeEditor ce(blk);
    });
    blk->events().click([this,blk]()
    {
        this->preselctBlock=this->selectedBlock;
        this->selectedBlock=blk->id;
        cout<<"curid:"<<this->selectedBlock<<endl
        <<"preid:"<<this->preselctBlock<<endl;
    });
    blockset.push_back(blk);
    return blk;
}
void Desk::loadFile(string fs)
{
    if(!fs.empty())
    {
        file=fs;
        caption("CodeLink -"+fs);
        for(size_t i=0; i<blockset.size(); i++)
        {
            delete blockset[i];
        }
        blockset.clear();
    }
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
Desk::~Desk()
{
    //dtor
}
