#include "EntityManager.h"


EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}


void EntityManager::update()
{
    for (auto & it: _vecChild)
    {
        if (it != nullptr)
            if (it->isPlay())
                it->update();

    }
}

void EntityManager::render()
{
    for (auto & it: _vecChild)
    {
        if (it != nullptr)
            if (it->isPlay())
                it->render();

    }
}

void EntityManager::stopAll()
{
    for (auto & it: _vecChild)
    {
        if (it != nullptr)
            it->play(false);

    }
}
