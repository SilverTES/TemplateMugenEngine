//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#include "Game.h"

//------------------------------------------------------------------------------ Init Game
int Game::init()
{


    _config             = _data.loadJsonFile("data/config.json");

    std::string appName = _config.at("name");

    _name               = appName.c_str();
    _isFullScreen       = _config.at("fullscreen");
    _isVsync            = _config.at("vsync");
    _screenW            = _config.at("width");
    _screenH            =  _config.at("height");
    _scaleWin           = _config.at("scaleWin"); // scale in windowMode !
    _scaleFull          = _config.at("scaleFull"); // 0 = Max zoom !
    _keyFull            = false;

    _eventQueue         = al_create_event_queue();

    _window->init(_name, _screenW, _screenH, _scaleWin, _scaleFull, _isFullScreen, _isVsync);




    al_hide_mouse_cursor(_window->display());
    //al_show_mouse_cursor(_window->display());

    _mainFont = al_load_font("data/Kyrou.ttf", 8, 0);
    _mouseCursor = al_load_bitmap("data/mouse_cursor.png");

    if ( NULL == (_jet = al_load_bitmap("data/rtype3sheet1.png")) )
        return log("- load jet bitmap error !\n",1);


    al_set_physfs_file_interface();

    if (!PHYSFS_addToSearchPath("data/myData.zip",0))
        return log("- PHYSFS addToSearchPath error !\n",1);

    if (!PHYSFS_addToSearchPath("data/zero.zip",0))
        return log("- PHYSFS addToSearchPath error !\n",1);


    // Show file in zip archives !
//    char **rc = PHYSFS_enumerateFiles("");
//    char **i;
//    for (i = rc; *i != NULL; i++)
//        printf("---> [%s].\n", *i);
//
//    PHYSFS_freeList(rc);

    if ( NULL == (_gamepadSNES = al_load_bitmap("gamepad_snes.png")) )
        return log("- load gamepadSNES bitmap error !\n",1);

    if ( NULL == (_background = al_load_bitmap("bg0.png")) )
        return log("- load background bitmap error !\n",1);


    _framerate = std::make_shared<Framerate>();
    _framerate->setFramerate(_eventQueue, 60);

    _input = std::make_shared<Controller>();


    _manEntity = std::make_shared<EntityManager>();

    _manEntity->add(new Entity(nullptr,"Ball"));

    _manEntity->at("Ball")->add(new Position(100,100,0));
    _manEntity->at("Ball")->add(new Velocity(1,1,0));

    _manEntity->at("Ball")->setUpdate([&](Entity * e)
    {
        if (e->window() != nullptr)
        {
            e->get<Position>()->_x += e->get<Velocity>()->_x;
            e->get<Position>()->_y += e->get<Velocity>()->_y;


            if (e->get<Position>()->_x < 0)
                e->get<Velocity>()->_x = 1;

            if (e->get<Position>()->_x > e->window()->screenW())
                e->get<Velocity>()->_x = -1;

            if (e->get<Position>()->_y < 0)
                e->get<Velocity>()->_y = 1;

            if (e->get<Position>()->_y > e->window()->screenH())
                e->get<Velocity>()->_y = -1;
        }
    });

    _manEntity->at("Ball")->setRender([&](Entity * e)
    {
        int x = e->get<Position>()->_x;
        int y = e->get<Position>()->_y;

        al_draw_filled_circle(x+.5, y+.5, 8, al_map_rgba(255,0,255,50));

        al_draw_circle(x+.5, y+.5, 8, al_map_rgb(25,155,255),0);

        al_draw_line(0,y+.5,
                     _window->screenW(),y+.5,
                     al_map_rgba(55,25,20,25),0);

        al_draw_line(x+.5,0,
                     x+.5,_window->screenH(),
                     al_map_rgba(55,25,20,25),0);

        if (e->font() != nullptr)
            al_draw_textf(e->font(),
                          al_map_rgb(205,200,20),
                          x, y-20,
                          -1,
                          "%s", e->_name.c_str());

    });

    _manEntity->at("Ball")->render();

    _manEntity->at("Ball")->play(true);


    _manEntity->add(Entity::cloneOf(_manEntity->at("Ball"),"Clone Ball"));

    _manEntity->at("Clone Ball")->get<Position>()->_x = 240;
    _manEntity->at("Clone Ball")->get<Position>()->_y = 120;

    for (int i = 0; i < 10; i++)
    {
        _manEntity->add(Entity::cloneOf(_manEntity->at("Ball"),"Clone Ball"+std::to_string(i) ));

        _manEntity->at("Clone Ball"+std::to_string(i))->get<Position>()->_x = random(0, _screenW);
        _manEntity->at("Clone Ball"+std::to_string(i))->get<Position>()->_y = random(0, _screenH);

    }

//    _manEntity->add(Base::create<Scene>(0,"Intro", new Scene(true, _window)));
//
////    _manEntity->at("Intro")->play(true);
////    _manEntity->at("Intro")->setFont(_mainFont);
//
//    //_manEntity->index(0)->play(false);
//
//    _manEntity->add(Base::create<Ball>(10,"Ball_0", new Ball(true, _window, Vec3{20,80,0},Vec3{1,1,0} )));
//
//    _manEntity->add(Base::create<Ball>(11,"Ball_1", new Ball(true, _window, Vec3{110,40,0},Vec3{1,2,0} )));
//    _manEntity->add(Base::create<Ball>(12,"Ball_2", new Ball(true, _window, Vec3{10,140,0},Vec3{-2,2,0} )));
//    _manEntity->add(Base::create<Ball>(13,"Ball_3", new Ball(true, _window, Vec3{80,110,0},Vec3{1,-2,0} )));
//
//    _manEntity->add(Base::create<Ball>(13,"Ball_3", new Ball(true, _window, Vec3{180,70,0},Vec3{1,-2,0} )));
//    _manEntity->add(Base::create<Ball>(13,"Ball_3", new Ball(true, _window, Vec3{280,60,0},Vec3{2,-2,0} )));
//    _manEntity->add(Base::create<Ball>(13,"Ball_3", new Ball(true, _window, Vec3{380,50,0},Vec3{-1,-2,0} )));
//    _manEntity->add(Base::create<Ball>(13,"Ball_3", new Ball(true, _window, Vec3{480,240,0},Vec3{-2,-2,0} )));
//
    for (int i=0; i<_manEntity->vecSize(); i++)
    {
        _manEntity->index(i)->setFont(_mainFont);
        _manEntity->index(i)->setWindow(_window);
    }

    return log("- init Game OK !\n");
}
//------------------------------------------------------------------------------ Done Game
int Game::done()
{

    _manEntity.reset();

    _framerate.reset();
    _input.reset();
    _window.reset();

    if (_eventQueue)
        al_destroy_event_queue(_eventQueue);

    if (_mainFont)
        al_destroy_font(_mainFont);

    if (_mouseCursor)
        al_destroy_bitmap(_mouseCursor);

    if (_gamepadSNES)
        al_destroy_bitmap(_gamepadSNES);

    if (_background)
        al_destroy_bitmap(_background);

    if (_jet)
        al_destroy_bitmap(_jet);

    return log("- done Game OK !\n");
}

//------------------------------------------------------------------------------ Update Game
void Game::update()
{

    al_get_mouse_state(&_mouseState);
    _window->getMouse(&_mouseState, _xMouse, _yMouse);

    al_wait_for_event(_eventQueue, &_event);

    if (_input->getKey(ALLEGRO_KEY_ESCAPE))
        _quit = true;

    if (!_input->getKey(ALLEGRO_KEY_SPACE)) _keyFull = false;
    if (_input->getKey(ALLEGRO_KEY_SPACE) && !_keyFull)
    {
        _keyFull = true;
        _window->toggleFullScreen(-1);
        //_window->toggleFullScreen(0);
    }

    if (!_input->getKey(ALLEGRO_KEY_TAB)) _keySwitch = false;
    if (_input->getKey(ALLEGRO_KEY_TAB) && !_keySwitch)
    {
        _keySwitch = true;
        _window->switchMonitor(-1);
    }

    if (_input->getKey(ALLEGRO_KEY_PAD_0)) // scale 0 = Max Scale
        _window->setScale(0);

    if (_input->getKey(ALLEGRO_KEY_PAD_1)) // scale 1
        _window->setScale(1);

    if (_input->getKey(ALLEGRO_KEY_PAD_2)) // scale 2
        _window->setScale(2);

    if (_input->getKey(ALLEGRO_KEY_PAD_3)) // scale 3
        _window->setScale(3);

    if (_input->getKey(ALLEGRO_KEY_PAD_4)) // scale 4
        _window->setScale(4);

    if (_input->getKey(ALLEGRO_KEY_INSERT)) //
        _turbo = true;

    if (_input->getKey(ALLEGRO_KEY_DELETE)) //
        _turbo = false;


    if (_input->getKey(ALLEGRO_KEY_PAD_MINUS))
    {
        _fadeScreen += 8;
        if (_fadeScreen > 255)
            _fadeScreen = 255;
    }
    if (_input->getKey(ALLEGRO_KEY_PAD_PLUS))
    {
        _fadeScreen -= 8;
        if (_fadeScreen < 0)
            _fadeScreen = 0;
    }



    if (_input->getKey(ALLEGRO_KEY_F1))
    {
    }
    if (_input->getKey(ALLEGRO_KEY_F2))
    {
    }
    if (_input->getKey(ALLEGRO_KEY_F3))
    {
    }

    _framerate->pollFramerate();

    al_flush_event_queue(_eventQueue);


    _frame++;

    _x++;
    if (_x>_window->screenW()) _x = 0;

    _manEntity->update();

}


//------------------------------------------------------------------------------ Render Game
void Game::render()
{
    _window->beginRender();
    //al_hold_bitmap_drawing(true);

    al_clear_to_color(al_map_rgb(25,60,80));

    //al_draw_bitmap(_background,0,0,0);

    drawGrid(_config.at("gridW"),_config.at("gridH"),al_map_rgba(30,40,50,50), _screenW, _screenH);

    _manEntity->render();

//    al_draw_bitmap(_gamepadSNES,
//                   _window->centerX()-al_get_bitmap_width(_gamepadSNES)/2+140,
//                   _window->centerY()-al_get_bitmap_height(_gamepadSNES)/2,
//                   0);

//    al_draw_textf(_mainFont, al_map_rgb(250,250,200), 180, 12, 0,
//                  "_isFullScreen : %i", _window->isFullScreen());
//
//    al_draw_textf(_mainFont, al_map_rgb(25,250,200), 180, 22, 0,
//                  "window Pos : %i , %i", _window->x(), _window->y());
//
//    al_draw_textf(_mainFont, al_map_rgb(205,250,200), 2, 2, 0,
//                  "currentMonitor : %i", _window->currentMonitor(_window->display()));
//
//    al_draw_textf(_mainFont, al_map_rgb(205,250,200), 2, 12, 0,
//                  "currentMonitor selected : %i", _window->currentMonitor());
//
//    al_draw_textf(_mainFont, al_map_rgb(205,250,200), 2, 32, 0,
//                  "currentMonitor Pos : %i , %i", _window->currentMonitorX(), _window->currentMonitorY());
//
//    al_draw_textf(_mainFont, al_map_rgb(205,250,200), 2, 42, 0,
//                  "currentMonitor Size : %i , %i", _window->currentMonitorW(), _window->currentMonitorH());
//
//    al_draw_textf(_mainFont, al_map_rgb(205,20,200), 2, 52, 0,
//                  "view Pos : %i , %i", _window->viewX(), _window->viewY());
//
//    al_draw_textf(_mainFont, al_map_rgb(205,20,200), 2, 62, 0,
//                  "view Size : %i , %i", _window->viewW(), _window->viewH());
//
//    al_draw_textf(_mainFont, al_map_rgb(205,20,20), 140, 52, 0,
//                  "_scaleWin : %i", _window->scaleWin());
//
//    al_draw_textf(_mainFont, al_map_rgb(205,20,20), 140, 62, 0,
//                  "_scaleFull: %i", _window->scaleFull());

//    al_draw_circle(_x, _window->centerY(), 32, al_map_rgb(255,0,0),0);

    al_draw_bitmap_region(_jet,
                          686, 53,
                          46, 24,
                          _x, _yMouse, 0);



    al_draw_textf(_mainFont, al_map_rgb(205,200,20), 4, _screenH-16, 0,
                  "al_get_time: %f", al_get_time());

    al_draw_textf(_mainFont, al_map_rgb(25,200,120), 4, _screenH-24, 0,
                  "Frame : %i", _frame);

    al_draw_line(0,_yMouse+.5,
                 _screenW,_yMouse+.5,
                 al_map_rgba(55,125,100,25),0);

    al_draw_line(_xMouse+.5,0,
                 _xMouse+.5,_screenH,
                 al_map_rgba(55,125,100,25),0);

    al_draw_filled_rectangle(0, 0, _screenW, _screenH, al_map_rgba(0, 0, 0, _fadeScreen));

    al_draw_bitmap(_mouseCursor, _xMouse, _yMouse, 0);


    al_draw_textf(_mainFont, al_map_rgb(205,200,200), _screenW -64, 2, 0,
                  "FPS: %i", _framerate->getFramerate());



    //al_hold_bitmap_drawing(false);
    _window->endRender();


}

