#ifndef LINK_H
#define LINK_H
#include <nana/gui.hpp>
#include <nana/gui/drawing.hpp>
#include <nana/basic_types.hpp>
#include "Block.h"
using namespace nana;
using namespace std;
class Link: public drawing
{
    public:
        Link(window w);
        virtual ~Link();
        void connect(Block* blk1,Block* blk2);
    protected:

    private:
};

#endif // LINK_H
