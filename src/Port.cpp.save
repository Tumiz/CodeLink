#include "Port.h"
#include "Desk.h"

using namespace std;
using namespace nana;
Port::Port(Block* b,int t,int i,int x,int y)
{
    blk=b;
    type=t;
    id=i;
    window w=blk->handle();
    create(w, rectangle(x, y-2, 8, 5));
    bgcolor(colors::sky_blue);
    borderless(true);
    if(t==OutPort)
    {
        events().mouse_down([this](const arg_mouse& e)
        {
            blk->dsk->curlink=new Link(blk->dsk,blk->id,id);
            cout<<blk->caption()<<" id:"<<blk->dsk->curlink->B1<<" OutPort:"<<blk->dsk->curlink->P1<<endl;
        });
    }
    if(t==InPort)
    {
        events().mouse_enter([this](const arg_mouse& e)
        {
            if(blk->dsk->linking&&e.left_button)
            {
                if(blk->dsk->curlink!=nullptr)
                {
                    blk->dsk->curlink->endAt(blk->id,id);
                    blk->dsk->linking=false;
                    cout<<blk->caption()<<" id:"<<blk->dsk->curlink->B2<<" InPort:"<<blk->dsk->curlink->P2<<endl;
                }
            }
        });
    }
}
point Port::cpos()
{
    switch(type)
    {
    case InPort:
        return pos()+point(0,2);
    case OutPort:
        return pos()+point(8,2);
    default:
        return point(0,0);
    }
}
Port::~Port()
{
    //dtor
}
