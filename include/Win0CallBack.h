#ifndef WIN0CALLBACK_H
#define WIN0CALLBACK_H
#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/dragger.hpp>
using namespace nana;
class Win0CallBack
{
    public:
        Win0CallBack(form& fm);
        virtual ~Win0CallBack();

    protected:

    private:
        form fm;
};

#endif // WIN0CALLBACK_H
