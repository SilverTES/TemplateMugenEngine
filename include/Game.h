//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef GAME_H
#define GAME_H

#include "MugenEngine.h"
#include "EntityManager.h"
#include "SpriteManager.h"

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

        ALLEGRO_BITMAP *_linkSheet     = NULL;

        ALLEGRO_SAMPLE *_soundExplose = NULL;
        ALLEGRO_SAMPLE *_soundLaser = NULL;


        bool _gamePause = false;

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

        bool _keyPause;

        // Mouse
        float _xMouse;
        float _yMouse;

        int _frame = 0;

        int _x = 0;


        std::shared_ptr<Controller> _input = nullptr;
        std::shared_ptr<Framerate> _framerate = nullptr;
        std::shared_ptr<EntityManager> _manEntity = nullptr;

        Animation *_myAnim = nullptr;
        Sprite *_mySprite = nullptr;

        int _fadeScreen = 0;

        Entity *_ball;
        Entity *_laser;
        Entity *_explosion;

        void initEntity ();
        void doneEntity ();



        double _oldTime = 0;
        double _newTime = 0;
        double _deltaTime =0;
        int _fps = 0;
        int _currentFps = 0;
        double _averageFPS = 0;

        std::vector<double> _vecFps;



};

#endif // GAME_H
