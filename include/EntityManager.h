#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


#include "IContainer.h"
#include "Entity.h"

class EntityManager : public IContainer<Entity>
{
    public:

        EntityManager();
        virtual ~EntityManager();

        void update();
        void render();

        void stopAll();


};

#endif // ENTITYMANAGER_H
