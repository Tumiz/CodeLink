#ifndef LINK_H
#define LINK_H
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include "Block.h"
#include <stdlib.h>
#include "CodeLink.h"
using namespace nana;
using namespace std;
class Link:public panel<true>
{
    public:
        Block* b1;
        Block* b2;
        window win;
        Link(window w,Block* blk1,Block* blk2);
        void update();
        virtual ~Link();
    protected:
    private:
};

#endif // LINK_H
