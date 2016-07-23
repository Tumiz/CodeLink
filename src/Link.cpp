#include "Link.h"
#include <iostream>
using namespace nana;
using namespace std;
Link::Link(window w):drawing(w)
{

}
void Link::connect(Block* blk1,Block* blk2)
{
    point p1=blk1->pos();
    point p2=blk2->pos();
    window w1=blk1->handle();
    window w2=blk2->handle();
    size ws1=API::window_size(w1);cout<<ws1.width<<" "<<ws1.height<<endl;
    size ws2=API::window_size(w2);cout<<ws2.width<<" "<<ws2.height<<endl;
    point po1=point(p1.x+ws1.width,p1.y+ws1.height/2);cout<<po1.x<<" "<<po1.y<<endl;
    point po2=point(p2.x,p2.y+ws2.height/2);cout<<po2.x<<" "<<po2.y<<endl;
    line(po1,po2);
}
void Link::line(point p1,point p2)
{
    draw([p1,p2](paint::graphics& graph)
    {
        graph.line(p1,p2,colors::black);
    });
}
Link::~Link()
{
    //dtor
}
