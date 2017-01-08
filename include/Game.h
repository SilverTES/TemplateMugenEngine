//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef GAME_H
#define GAME_H

#include "MugenEngine.h"
#include "EntityManager.h"

class Game : public MugenEngine
{
    public:
        int init() override;
        int done() override;
        void update() override;
        void render() override;

        static void *mouseThread(ALLEGRO_THREAD *thr, void *arg);

    protected:
        ALLEGRO_BITMAP * scaledBitmap (ALLEGRO_BITMAP * srcBitmap, int scale);
        void scaleMouseCursor(int scale=1);
        void runAssignButton(int player, int id);

    private:
        const char * _name;
        bool _redraw;

        ALLEGRO_MOUSE_STATE _mouseState;

        // Events
        ALLEGRO_EVENT_QUEUE* _eventQueue;
        ALLEGRO_EVENT _event;



        Data _data;
        json _config;

//        PlayerManager _manPlayer;
//        // pour tester les controlleurs !
//        std::vector<EntityPlayer> _vecEntityPlayer;
//
//        std::vector<Graph> _vecGraph;

        ALLEGRO_FONT   *_mainFont      = NULL;
        ALLEGRO_BITMAP *_mouseCursor   = NULL;
        ALLEGRO_BITMAP *_gamepadSNES   = NULL;
        ALLEGRO_BITMAP *_background    = NULL;

        ALLEGRO_BITMAP *_jet           = NULL;


        bool _isVsync = false;
        bool _isSmooth = false;
        bool _isFullScreen = false;
        bool _turbo;
        int _screenW;
        int _screenH;
        int _scaleWin;
        int _scaleFull;

        bool _keyFull;
        bool _keySwitch;
        bool _keyDelete;
        bool _keyInsert;

        // Mouse
        float _xMouse;
        float _yMouse;

        int _frame = 0;

        int _x = 0;


        std::shared_ptr<Controller> _input;
        std::shared_ptr<Framerate> _framerate;

        std::shared_ptr<EntityManager> _manEntity;

        int _fadeScreen = 0;

};

#endif // GAME_H
