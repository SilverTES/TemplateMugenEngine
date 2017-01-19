#ifndef DIRECTOR_H
#define DIRECTOR_H


#include "MugenEngine.h"
#include "IContainer.h"
#include "IPlayable.h"
#include "Layer.h"
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
