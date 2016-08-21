#ifndef LINK_H
#define LINK_H
#include <nana/gui.hpp>
#include <nana/gui/widgets/widget.hpp>
using namespace std;
using namespace nana;
struct LinkRange
{
    int xmax;
    int xmin;
    int ymax;
    int ymin;
};
class Desk;
class Link: public drawing
{
public:
    Desk* dsk;
    int id;
    int B1;
    int P1;
    int B2;
    int P2;
    color lcolor;
    point startp,endp;
    drawing::diehard_t drawfunc;
    Link(Desk* dk,int blockid,int outportid);
    void endAt(int blockid,int inportid);
    bool isPointOnLink(point p);
    point projectOnLink(point p);
    double dist(point p1,point p2);
    LinkRange range();
    virtual ~Link();

protected:

private:
};

#endif // LINK_H
