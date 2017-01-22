#ifndef SCENE_H
#define SCENE_H

#include "Layer.h"

class Scene : public IPlayable, public IContainer<Layer>
{
    public:
        Scene(std::string name = "NoName");
        virtual ~Scene();
        void update();
        void render();
        void stopAll();

    protected:

    private:
};

#endif // SCENE_H
