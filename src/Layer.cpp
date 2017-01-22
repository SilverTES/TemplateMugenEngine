#include "Layer.h"

Layer::Layer(std::string name) :
    IPlayable(name)
{
    log("- Layer Created !\n");
    //ctor
}

Layer::~Layer()
{
    log("- Layer Deleted !\n");
    //dtor
}

void Layer::update()
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

void Layer::render()
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

    al_draw_textf(_font,
                  al_map_rgb(205,200,20),
                  4, _window->screenH() - 48, 0,
                  "LAYER : %s at Frame : %i",
                  _name.c_str(), _currentFrame);
}

void Layer::stopAll()
{
    if (!_vecObject.empty())
    {
        for (auto & it: _vecObject)
        {
            if (it != nullptr)
                it->stop();

        }
    }
}
