#include "Block.h"
using namespace std;
using namespace nana;
Block::Block(window f,int i,string s,int x,int y,int w,int h)
{
    name=s;
    id=i;
    win=f;
    create(win, rectangle(x, y, w, h));
    caption(s);
    cout<<s;
    dg.trigger(*this);
    dg.target(*this);
    drawing d(f);
    d.draw([this](paint::graphics& graph)
    {
        point po=outport();
        point pi=inport();
        point po0=point(po.x-10,po.y);
        point pi0=point(pi.x+10,pi.y);
        point pi1=point(pi0.x-8,pi0.y-2);
        point pi2=point(pi0.x-8,pi0.y+2);
        graph.line(po,po0,colors::black);
        graph.line(pi,pi0,colors::black);
        graph.line(pi0,pi1,colors::black);
        graph.line(pi0,pi2,colors::black);
    });
    d.update();
    events().mouse_down([this](const arg_mouse& e)
    {
        int x=e.pos.x;
        int y=e.pos.y;
        selectSide=checkBorder(x,y);
        cout<<"selectSide"<<selectSide<<endl;
        if(selectSide!=OutSide&&selectSide!=InSide)
        {
            dg.remove_target(*this);
            cout<<"romove target"<<endl;
            bs=ReSizing;
        }
    });
    events().mouse_up([this]()
    {
        bs=UnSelected;
        dg.target(*this);
    });
//    events().resizing([this](const arg_resizing& e)
//    {
//                    int w=size().width;
//            int h=size().height;
//            int dw,dh;
//        switch(e.border)
//        {
//        case window_border::left:
//            e.width+=2;
//            break;
//        case window_border::right:
//            e.width+=2;
//        }
//    });
    events().mouse_move([this](const arg_mouse& e)
    {
        int x=e.pos.x;
        int y=e.pos.y;
        cout<<e.pos.x<<" "<<e.pos.y<<" selectside: "<<selectSide<<endl;
        if(bs!=ReSizing)
        {
            int side=checkBorder(x,y);
            cout<<"side:"<<side<<endl;
            cursor(changeCursor(side));
        }
        if(bs==ReSizing)
        {
            int w=size().width;
            int h=size().height;
            int dw,dh;
            if(selectSide==LeftSide||selectSide==LeftTopCorner||selectSide==LeftBottomCorner)
            {
                dw=2-x;
                move(pos().x-dw,pos().y);
                w=w+dw;
            }
            if(selectSide==RightSide||selectSide==RightTopCorner||selectSide==RightBottomCorner)
            {
                dw=x-w+2;
                w=w+dw;
            }
            if(selectSide==TopSide||selectSide==LeftTopCorner||selectSide==RightTopCorner)
            {
                dh=2-y;
                move(pos().x,pos().y-dh);
                h=h+dh;
                cout<<" dh:"<<dh<<" h:"<<h<<endl;
            }
            if(selectSide==BottomSide||selectSide ==LeftBottomCorner||selectSide==RightBottomCorner)
            {
                dh=y-h+2;
                h=h+dh;
            }
            w=max(12,w);
            h=max(12,h);
            size(rectangle(2,2,w,h));
        }
        if(selectSide!=OutSide)
        {
            drawing d(win);
            d.update();
        }

    });
    cout<<"-------------------"<<endl;
}
point Block::inport()
{
    point p=pos();
    nana::size z=size();
    point ip=point(p.x-10,p.y+z.height/2);
    return ip;
}
point Block::outport()
{
    point p=pos();
    nana::size z=size();
    point op=point(p.x+z.width+10,p.y+z.height/2);
    return op;
}
int Block::getHeight()
{
    nana::size z=size();
    return z.height;
}
int Block::getWidth()
{
    nana::size z=size();
    return z.width;
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
int Block::checkBorder(int x,int y)
{
    int w=size().width;
    int h=size().height;
    if(x>=w-4&&y>=h-4)
        return RightBottomCorner;
    if(x<=4&&y>=h-4)
        return LeftBottomCorner;
    if(x<=4&&y<=4)
        return LeftTopCorner;
    if(x>=w-4&&y<=4)
        return RightTopCorner;
    if(x>=w-4)
        return RightSide;
    if(x<=4)
        return LeftSide;
    if(y>=h-4)
        return BottomSide;
    if(y<=4)
        return TopSide;
    if(x>4&&x<w-4&&y>4&&y<h-4)
        return InSide;
    return OutSide;
}
nana::cursor Block::changeCursor(int side)
{
    if(side==LeftSide||side==RightSide)
        return nana::cursor::size_we;
    if(side==TopSide||side==BottomSide)
        return nana::cursor::size_ns;
    if(side==LeftTopCorner)
        return nana::cursor::size_top_left;
    if(side==RightTopCorner)
        return nana::cursor::size_top_right;
    if(side==LeftBottomCorner)
        return nana::cursor::size_bottom_left;
    if(side==RightBottomCorner)
        return nana::cursor::size_bottom_right;
    return nana::cursor::arrow;
}
Block::~Block()
{
    //dtor
}
