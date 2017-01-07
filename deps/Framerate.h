//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef FRAMERATE_H
#define FRAMERATE_H

#include "MugenEngine.h"

class Framerate
{
    public:
        Framerate();
        virtual ~Framerate();

        // Framerate
        int getFramerate() const;
        void setFramerate(ALLEGRO_EVENT_QUEUE * eventQueue, int framerate);
        void pollFramerate();
        ALLEGRO_EVENT_QUEUE * eventQueue();

    protected:

    private:
        float _prevTime;
        float _restTime;
        float _currentTime;
        float _deltaTime;

        // Framerate control
        float _framerate;
        int _nbFrame;
        int _nbFps;
        double _gameTime;
        double _oldTime;
        ALLEGRO_TIMER* _framerateTimer;
};

#endif // FRAMERATE_H
