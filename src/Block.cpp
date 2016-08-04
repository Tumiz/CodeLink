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
    drawing d(f);
    d.draw([this](paint::graphics& graph)
    {
        point po=outport();
        point pi=inport();
        point po0=point(po.x-8,po.y);
        point pi0=point(pi.x+10,pi.y);
        point pi1=point(pi0.x-8,pi0.y-2);
        point pi2=point(pi0.x-8,pi0.y+2);
        graph.line(po,po0,colors::black);
        graph.line(pi,pi0,colors::black);
        graph.line(pi0,pi1,colors::black);
        graph.line(pi0,pi2,colors::black);
    });
    d.update();
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
    point ip=point(p.x-12,p.y+z.height/2);
    return ip;
}
point Block::outport()
{
    point p=pos();
    nana::size z=size();
    point op=point(p.x+z.width+8,p.y+z.height/2);
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

Block::~Block()
{
    //dtor
}
