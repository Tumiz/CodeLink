#ifndef CODELINK_H_INCLUDED
#define CODELINK_H_INCLUDED
#include <iostream>
using namespace nana;
using namespace std;
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
