#include "Desk.h"
Desk::Desk()
{
    caption(L"CodeLink");//name it
    place pl(*this);
    menubar mn(*this);
    pl.div("<vertical <menu weight=25>>");
    pl.field("menu") << mn;

    mn.push_back("File");
    mn.at(0).append("Load",[this](menu::item_proxy& ip)
    {
        string fs=pickFile(true);
        loadFile(fs);
    });
    mn.at(0).append("Save",[this](menu::item_proxy& ip)
    {
        if(file.empty())
            file=pickFile(false);
        else
        {
            ofstream ofs(file);
            for(size_t i=0; i<blockset.size(); i++)
            {
                ofs<<blockset[i]->name<<endl;
            }
            ofs.close();
        }

    });
    mn.at(0).append("Save as",[this](menu::item_proxy& ip)
    {
        file=pickFile(false);
        caption("CodeLink -"+file);
        ofstream ofs(file);
        for(size_t i=0; i<blockset.size(); i++)
        {
            ofs<<blockset[i]->name<<endl;
        }
        ofs.close();
    });
    mn.at(0).append("Exit",[](menu::item_proxy& ip)
    {
        API::exit();
    });
    mn.push_back("Block");
    mn.at(1).append("New",[this](menu::item_proxy& ip)
    {
        int id=int(blockset.size());
        stringstream blkname;
        blkname<<"block"<<id;
        createBlock(blkname.str(),10+rand()%100, 50+rand()%100, 80, 20);
    });

    mn.push_back("Run");
    mn.at(2).append("Run",[this](menu::item_proxy& ip)
    {
        size_t dotpos=file.find(".txt");
        string name=file.erase(dotpos,4);
        system(("g++ "+name+".cpp -o gen").c_str());
    });
    pl.collocate();
    show();
    exec();
}
string Desk::pickFile(bool is_open) const
{
    filebox fbox(is_open);
    fbox.add_filter("Text", "*.txt");
    fbox.add_filter("All Files", "*.*");
    return (fbox.show() ? fbox.file() : "" );
}
Block* Desk::createBlock(string s,int x,int y,int w,int h)
{
    Block *blk=new Block();
    blk->id=blockset.size();
    blk->name=s;
    blk->create(*this, rectangle(x, y, w, h));
    blk->caption(s);
    blk->events().dbl_click([blk]()
    {
        CodeEditor ce(blk);
    });
    dragger *dg=new dragger();
    dg->trigger(*blk);  //When you drag the btn, then
    dg->target(*blk);   //move the btn
    blockset.push_back(blk);
    dragset.push_back(dg);
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
            delete dragset[i];
        }
        blockset.clear();
        dragset.clear();
    }
    ifstream ifs(fs.c_str());
    string blkname;
    while(ifs>>blkname)
    {
        createBlock(blkname,10+rand()%100, 50+rand()%100, 80, 20);
        cout<<blkname<<endl;
    }
    exec();
}
Desk::~Desk()
{
    //dtor
}
