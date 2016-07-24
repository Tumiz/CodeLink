#include "Block.h"
using namespace std;
using namespace nana;
Block::Block(window f,int i,string s,int x,int y,int w,int h)
{
    name=s;
    id=i;
    win=f;
    create(win, rectangle(x, y, w, h));
    caption(s);
    dg.trigger(*this);
    dg.target(*this);
    events().move([this]()
    {
        drawing d(win);
        d.update();
    });
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
    obs.push_back(blk);
    blk->ibs.push_back(this);
    drawing d(win);
    d.draw([this,&blk](paint::graphics& graph)
    {
        graph.line(outport(),blk->inport(),colors::black);
    });
    d.update();
    exec();
}
void Block::link2(Block* blk)
{

}
Block::~Block()
{
    //dtor
}
