#include "Block.h"
using namespace std;
using namespace nana;
Block::Block(window f,int i,string s,int x,int y,int w,int h)
{
    name=s;
    id=i;
    create(f, rectangle(x, y, w, h));
    caption(s);
    dg.trigger(*this);
    dg.target(*this);
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
