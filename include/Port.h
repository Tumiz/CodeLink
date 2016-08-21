#ifndef PORT_H
#define PORT_H

#include <nana/gui/widgets/label.hpp>
using namespace std;
using namespace nana;
enum PortType
{
    InPort,
    OutPort
};
class Block;
class Desk;
class Port : public label
{
    public:
        Block* blk;
        int id;
        int type;
        Port(Block* b,int t,int i,int x,int y);
        point cpos();//center position, different from pos()
        virtual ~Port();

    protected:

    private:
};

#endif // PORT_H
