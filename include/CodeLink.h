#ifndef CODELINK_H_INCLUDED
#define CODELINK_H_INCLUDED
#include <iostream>
using namespace nana;
using namespace std;
struct MouseState
{
    bool leftPress;
};
//void clLine(window f,point p1,point p2,const color& clr)
//{
//    drawing d(f);
//    d.draw([&p1,&p2,&clr](paint::graphics& graph)
//    {
//        graph.line(p1,p2,clr);
//    });
//    d.update();
//}

inline ostream &operator << (ostream& s, point& p)
 {
     s<<"("<<p.x<<","<<p.y<<")";
     return s;
 }
inline ostream &operator << (ostream& s, size& p)
 {
     s<<"["<<p.width<<","<<p.height<<"]";
     return s;
 }


#endif // CODELINK_H_INCLUDED
