#ifndef LINK_H
#define LINK_H
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include "Block.h"
#include <stdlib.h>
#include <vector>
#include "CodeLink.h"
using namespace nana;
using namespace std;
class Link
{
    public:
        Block* b1;
        Block* b2;
        window win;
        vector<point> curve;
        Link(window w,Block* blk1,Block* blk2);
        virtual ~Link();
    protected:
    private:
};

#endif // LINK_H
