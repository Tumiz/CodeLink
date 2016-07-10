#include "Desk.h"
Desk::Desk()
{
    fm.caption(L"CodeLink");//name it
    place pl(fm);
    menubar mn(fm);
    pl.div("<vertical <menu weight=25>>");
    pl.field("menu") << mn;

    mn.push_back("File");
    mn.at(0).append("new block",[this](menu::item_proxy& ip)
    {
        Block blk(int(blockset.size()));
        blk.create(fm, rectangle(10+rand()%100, 50+rand()%100, 80, 20));
        stringstream blkname;
        blkname<<"block"<<blk.id;
        blk.setName(blkname.str());
        blk.events().dbl_click([&]()
        {
            CodeEditor ce(&blk);
            ce.caption(blk.name);
            ce.show();
            exec();
        });
        dragger dg;
        dg.trigger(blk);
        dg.target(blk);
        blockset.push_back(&blk);
        exec();
    });
    mn.at(0).append("exit",[](menu::item_proxy& ip)
    {
        API::exit();
    });
    mn.push_back("Run");
    mn.at(1).append("Run",[this](menu::item_proxy& ip)
    {
        system("g++ new.cpp -o gen");
    });
    pl.collocate();
    fm.show();
    exec();
}

Desk::~Desk()
{
    //dtor
}
