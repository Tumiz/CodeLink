#include "Block.h"
Block::Block()
{

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
