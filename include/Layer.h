#ifndef LAYER_H
#define LAYER_H

#include "MugenEngine.h"
#include "IContainer.h"
#include "IPlayable.h"
#include "Entity.h"


class Layer : public IPlayable, public IContainer<Entity>
{
    public:
        Layer(std::string name = "NoName");
        virtual ~Layer();
        void update();
        void render();
        void stopAll();

    protected:

    private:
};



#endif // LAYER_H
