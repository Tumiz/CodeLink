#ifndef CODELINK_H_INCLUDED
#define CODELINK_H_INCLUDED
#include <iostream>
#include <math.h>
#define s(X) " {"<<#X<<":"<<X<<"} "
using namespace nana;
using namespace std;
inline ostream &operator << (ostream& s,vector<string>& v)
{
    for(size_t i=0; i<v.size() ; i++ )
    {
        if(i==0)
            s<<v[i];
        else
            s<<"|"<<v[i];
    }
    return s;
}
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
static double dist(point p1,point p2)
{
    double dx=p1.x-p2.x;
    double dy=p1.y-p2.y;
    double d2=dx*dx+dy*dy;
    return sqrt(d2);
}
#endif // CODELINK_H_INCLUDED
