#include "Director.h"

Director::Director(std::string name)
{
    _name = name;
    log("- Director Created !\n");
    //ctor
}

Director::~Director()
{
    log("- Director Deleted !\n");
    //dtor
}
void Director::update()
{

    if (!_vecObject.empty())
    {
        for (auto & it: _vecObject)
        {
            if (it != nullptr)
                if (it->isPlay())
                    it->update();

        }
    }
}

void Director::render()
{
    if (!_vecObject.empty())
    {
        for (auto & it: _vecObject)
        {
            if (it != nullptr)
                if (it->isPlay())
                    it->render();

        }
    }
}

void Director::stopAll()
{
    if (!_vecObject.empty())
    {
        for (auto & it: _vecObject)
        {
            if (it != nullptr)
                it->play(false);

        }
    }
}
