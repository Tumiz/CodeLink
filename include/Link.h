#ifndef LINK_H
#define LINK_H
#include <nana/gui.hpp>
#include <nana/gui/drawing.hpp>
#include "Block.h"
using namespace nana;
class Link: public drawing
{
    public:
        Link(window w);
        virtual ~Link();
        void connect(Block* blk1,Block* blk2);
        void line(point p1,point p2);
    protected:
    private:
};

#endif // LINK_H
