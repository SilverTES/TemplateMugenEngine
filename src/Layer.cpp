#include "Layer.h"

Layer::Layer(std::string name)
{
    _name = name;
    //ctor
}

Layer::~Layer()
{
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
                  "LAYER : %s", _name.c_str());
}

void Layer::stopAll()
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
