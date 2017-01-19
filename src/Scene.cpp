#include "Scene.h"

Scene::Scene(std::string name)
{
    _name = name;
    log("- Scene Created !\n");
    //ctor
}

Scene::~Scene()
{
    log("- Scene Deleted !\n");
    //dtor
}
void Scene::update()
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

void Scene::render()
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
                  4, 4, 0,
                  "SCENE : %s", _name.c_str());

}

void Scene::stopAll()
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
