#ifndef DIRECTOR_H
#define DIRECTOR_H


#include "Scene.h"

class Director : public IPlayable, public IContainer<Scene>
{
    public:
        Director(std::string name = "NoName");
        virtual ~Director();
        void update();
        void render();
        void stopAll();

    protected:

    private:
};

#endif // DIRECTOR_H
