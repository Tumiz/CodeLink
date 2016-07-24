#include "Link.h"
using namespace nana;
using namespace std;
Link::Link(window w,Block* blk1,Block* blk2)
{
    b1=blk1;
    b2=blk2;
    win=w;
    update();
//    blk1->events().move([this,&blk1,&blk2]()
//    {
//        update();
//        API::refresh_window(*this);
//    });
//    blk2->events().move([this]()
//    {
//        update();
//        API::refresh_window(*this);
//    });
}
void Link::update()
{
    point p1=b1->pos();
    point p2=b2->pos();
    nana::size ws1=b1->size();
    cout<<ws1<<endl;
    nana::size ws2=b2->size();
    cout<<ws2<<endl;
    point po1=point(p1.x+ws1.width,p1.y+ws1.height/2);
    cout<<po1<<endl;
    point po2=point(p2.x,p2.y+ws2.height/2);
    cout<<po2<<endl;
    int x=min(po1.x,po2.x);
    int y=min(po1.y,po2.y);
    int width=abs(po1.x-po2.x);
    cout<<width<<endl;
    int height=abs(po1.y-po2.y);
    cout<<height<<endl;
    create(win,rectangle(x,y,width,height));
    point pn1(po1.x-x,po1.y-y);
    point pn2(po2.x-x,po2.y-y);
    drawing{*this} .draw([&pn1,&pn2](paint::graphics& graph)
    {
        graph.line(pn1,pn2,colors::black);
        cout<<"pn1"<<pn1<<endl<<"pn2"<<pn2<<endl;
    });
    API::refresh_window(*this);
    exec();
}
Link::~Link()
{
    //dtor
}
