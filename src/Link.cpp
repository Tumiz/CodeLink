#include "Link.h"
using namespace nana;
using namespace std;
Link::Link(window w,Block* blk1,Block* blk2)
{
    b1=blk1;
    b2=blk2;
    win=w;
    point p1=b1->pos();
    point p2=b2->pos();
    nana::size ws1=b1->size();
    cout<<ws1<<endl;
    nana::size ws2=b2->size();
    cout<<ws2<<endl;
    point po1=point(p1.x+ws1.width,p1.y+ws1.height/2);
    point po2=point(p2.x,p2.y+ws2.height/2);
    drawing d(win);
    d .draw([&po1,&po2](paint::graphics& graph)
    {
        graph.line(po1,po2,colors::black);
        cout<<"po1"<<po1<<endl<<"po2"<<po2<<endl;
    });
    d.update();
}
Link::~Link()
{
    //dtor
}
