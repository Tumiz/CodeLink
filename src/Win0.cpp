#include "Win0.h"

using namespace nana;
void exit(menu::item_proxy& ip)
{
    API::exit();
}
void newBlock(menu::item_proxy& ip)
{

}
Win0::Win0()
{

}

Win0::~Win0()
{
    //dtor
}

form Win0::getForm()
{
    return fm;
}


