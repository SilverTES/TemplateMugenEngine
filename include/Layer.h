#ifndef LAYER_H
#define LAYER_H

#include "Entity.h"

struct ZIndex
{
    int _z = 0;
    int _index = 0;
};


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
        std::vector<ZIndex*> _vecZIndex;

        void sortZIndex(std::vector<Entity*> &vecEntity, std::vector<ZIndex*> &vecZIndex);
        unsigned zIndex(unsigned index);
};



#endif // LAYER_H
