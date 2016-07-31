#include "Block.h"
using namespace std;
using namespace nana;
Block::Block(window f,int i,string s,int x,int y,int w,int h)
{
    cout<<0;
    name=s;
    id=i;
    win=f;cout<<1;
    create(win, rectangle(x, y, w, h));cout<<2;
    caption(s);cout<<3;
    dg.trigger(*this);
    dg.target(*this);cout<<4;
    events().move([this]()
    {
        cout<<"move "<<this->id;
        drawing d(win);cout<<0;
        d.update();cout<<1;
    });cout<<5<<endl<<"-------------------"<<endl;
}
point Block::inport()
{
    point p=pos();
    nana::size z=size();
    point ip=point(p.x,p.y+z.height/2);
    return ip;
}
point Block::outport()
{
    point p=pos();
    nana::size z=size();
    point op=point(p.x+z.width,p.y+z.height/2);
    return op;
}
int Block::getHeight()
{
    nana::size z=size();
    return z.height;
}
int Block::getWidth()
{
    nana::size z=size();
    return z.width;
}
string Block::getName()
{
    return name;
}
void Block::setName(string s)
{
    if(s!="")
    {
        name=s;
        caption(s);
    }
}
string Block::getFileName()
{
    return name+".cpp";
}
bool Block::isEmpty()
{
    return name.empty();
}
void Block::connect2(Block*& blk)
{
    cout<<this<<" "<<blk<<endl;
    drawing d(win);
    d.draw([this,&blk](paint::graphics& graph)
    {
        cout<<this<<" "<<blk;
        if(this!=NULL&&blk!=NULL)
        {
            cout<<"Link "<<this->id<<" "<<blk->id<<endl;
            graph.line(outport(),blk->inport(),colors::black);
        }
        else
            cout<<"Link NULL"<<endl;
    });
    d.update();
    exec();
}
Block::~Block()
{
    //dtor
}
