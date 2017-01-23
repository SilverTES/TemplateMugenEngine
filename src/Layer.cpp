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

    sortZIndex(_vecObject, _vecZIndex);
}

void Layer::render()
{
    if (!_vecObject.empty())
    {
//        for (auto & it: _vecObject)
//        {
//            if (it != nullptr)
//                if (it->isPlay())
//                    it->render();
//
//        }

        for (unsigned index = 0; index < _vecObject.size(); ++index)
        {
            if (_vecObject[zIndex(index)] != nullptr)
                if (_vecObject[zIndex(index)]->isPlay())
                    _vecObject[zIndex(index)]->render();
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

void Layer::sortZIndex(std::vector<Entity*> &vecEntity, std::vector<ZIndex*> &vecZIndex)
{

    if (vecZIndex.size() < vecEntity.size())
    {
        //log("- Resize ZIndex !\n");
        for (unsigned index = vecZIndex.size(); index < vecEntity.size(); ++index)
        {
            vecZIndex.push_back(new ZIndex());
        }
    }

    for (unsigned index = 0; index < vecZIndex.size(); ++index)
    {
        vecZIndex[index]->_index = index;
        if (vecEntity[index] != nullptr)
            vecZIndex[index]->_z = vecEntity[index]->_z;
        else
            vecZIndex[index]->_z = 0;
    }

    std::stable_sort(vecZIndex.begin(), vecZIndex.end(), []( const ZIndex *a, const ZIndex *b ) ->bool
    {
        return a->_z < b->_z;
    });


}

unsigned Layer::zIndex(unsigned index)
{
    return _vecZIndex[index]->_index;
}
