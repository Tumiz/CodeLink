#ifndef DESK_H
#define DESK_H
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/dragger.hpp>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include "CodeEditor.h"
#include "Block.h"
using namespace nana;
using namespace std;

class Desk
{
public:
    Desk();
    virtual ~Desk();
    vector<Block*> blockset;
protected:

private:
    form fm;
};

#endif // DESK_H
