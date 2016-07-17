#include "Link.h"
Link::Link(window w):drawing(w)
{
}
void Link::connect(Block* blk1,Block* blk2)
{
    draw([blk1,blk2](paint::graphics& graph)
    {
        point p1=blk1->pos();
        point p2=blk2->pos();
        graph.line(p1,p2);
    });
}
Link::~Link()
{
    //dtor
}
