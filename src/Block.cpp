#include "Block.h"

Block::Block(int index)
{
    id=index;
}
void Block::setName(string s)
{
    if(!s.empty())
    {
        name=s;
        caption(s);
    }
    else
        fgcolor(colors::red);
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
