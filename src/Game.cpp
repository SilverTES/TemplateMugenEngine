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
    _isSmooth           = _config.at("smooth");
    _screenW            = _config.at("width");
    _screenH            = _config.at("height");
    _scaleWin           = _config.at("scaleWin"); // scale in windowMode !
    _scaleFull          = _config.at("scaleFull"); // 0 = Max zoom !
    _keyFull            = false;

    _eventQueue         = al_create_event_queue();

    //al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    //al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR);

    _window->init(_name, _screenW, _screenH, _scaleWin, _scaleFull, _isFullScreen, _isVsync, _isSmooth);




    al_hide_mouse_cursor(_window->display());
    //al_show_mouse_cursor(_window->display());

    _linkSheet = al_load_bitmap("data/link.png");
    _knuckleSheet = al_load_bitmap("data/knuckles.png");

    _soundExplose = al_load_sample("data/Explosion.wav");
    _soundLaser = al_load_sample("data/LaserBlast.wav");


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

    initEntity();

    _oldTime = al_get_time();

    return log("- init Game OK !\n");
}
//------------------------------------------------------------------------------ Done Game
int Game::done()
{


    doneEntity();

    if (_myAnimLink)
        delete _myAnimLink;

    if (_mySprite)
        delete _mySprite;


    _manEntity.reset();
    _framerate.reset();
    _input.reset();
    _window.reset();

    al_destroy_event_queue(_eventQueue);

    al_destroy_font(_mainFont);

    al_destroy_sample(_soundExplose);
    al_destroy_sample(_soundLaser);

    al_destroy_bitmap(_linkSheet);
    al_destroy_bitmap(_mouseCursor);
    al_destroy_bitmap(_gamepadSNES);
    al_destroy_bitmap(_background);
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


    if (!(_mouseState.buttons & 1)) _mouseButtonL = false;
    if (!(_mouseState.buttons & 2)) _mouseButtonR = false;


    if (_input->getKey(ALLEGRO_KEY_F1))
    {
        for (auto & it :_manEntity->groupAt("First Clone Ball"))
        {
            it->del(componentType("VELOCITY"));
            it->add(new Velocity(-1,0,0));
        }

    }
    if (_input->getKey(ALLEGRO_KEY_F2))
    {
        for (auto & it :_manEntity->groupAt("First Clone Ball"))
        {
            it->del(componentType("VELOCITY"));
        }

    }


    if (_input->getKey(ALLEGRO_KEY_F3))
    {

        for (auto & it :_manEntity->groupAt("Clone of Ball"))
        {

            if (it->get<Velocity>() == nullptr)
            {
                //it->del(componentType("VELOCITY"));
                it->add(new Velocity(-1,0,0));
            }
        }

    }
    if (_input->getKey(ALLEGRO_KEY_F4))
    {
        for (auto & it :_manEntity->groupAt("Clone of Ball"))
        {
            it->del(componentType("VELOCITY"));
        }

    }



    if ((_mouseState.buttons & 2) && !_mouseButtonR)
    {
        _mouseButtonR = true;

        Entity *e = Entity::cloneOf(_manEntity->at("First Clone Ball"));

        e->get<Animate>()->start(0, 2, 1, 0, _myAnimKnuckle->nbFrame()-1);
        e->get<Position>()->_x = _xMouse;
        e->get<Position>()->_y = _yMouse;
        e->get<Velocity>()->_x = -1;
        _manEntity->add(e);
    }



    if (!_input->getKey(ALLEGRO_KEY_DELETE)) _keyDelete = false;
    if (_input->getKey(ALLEGRO_KEY_DELETE) && !_keyDelete)
    {
        _keyDelete = true;
        if (_input->getKey(ALLEGRO_KEY_RSHIFT))
            _manEntity->delAll();
        else
        if (_input->getKey(ALLEGRO_KEY_RCTRL))
            _manEntity->del(random(0,_manEntity->vecSize()));
        else
            _manEntity->del("Clone of Ball");
    }

    if (!_input->getKey(ALLEGRO_KEY_INSERT)) _keyInsert = false;
    if ((_input->getKey(ALLEGRO_KEY_INSERT) && !_keyInsert) ||
        _mouseState.buttons & 1)
    {
        _keyInsert = true;

        Entity *e = Entity::cloneOf(_ball,"Clone of Ball");

        e->del(componentType("VELOCITY"));

//        e->get<Position>()->_x = random(0, _screenW);
//        e->get<Position>()->_y = random(0, _screenH);

        e->get<Position>()->_x = _xMouse;
        e->get<Position>()->_y = _yMouse;


//        e = Entity::cloneOf(_laser,"Clone Laser");
//        e->get<Position>()->_x = random(0, _screenW);
//        e->get<Position>()->_y = random(0, _screenH);
//        _manEntity->add(e);
        _manEntity->add(e);

    }

    _framerate->pollFramerate();

    al_flush_event_queue(_eventQueue);

    _x++;
    if (_x>_window->screenW()) _x = 0;

    if (!_input->getKey(ALLEGRO_KEY_ENTER)) _keyPause = false;
    if (_input->getKey(ALLEGRO_KEY_ENTER) && !_keyPause)
    {
        _keyPause = true;
        _gamePause = !_gamePause;

        if (!_gamePause)
            _fadeScreen = 0;
    }

    if (!_gamePause)
    {
        _frame++;
        _manEntity->update();
    }
    else
    {
        _fadeScreen = 150;
    }


    _newTime = al_get_time();
    _deltaTime = _newTime - _oldTime;
    _fps = 1000*(1/(_deltaTime*1000));
    _oldTime = _newTime;

    _currentFps ++;
    _vecFps.push_back(_fps);

    if (_currentFps > 60)
    {
        _currentFps = 0;
        _averageFPS = accumulate(_vecFps.begin(), _vecFps.end(), 0.0) / _vecFps.size();
        _vecFps.clear();
    }

    //_mySprite->setPos(280,20);
    //_mySprite->setFrame(3);

}


//------------------------------------------------------------------------------ Render Game
void Game::render()
{
    _window->beginRender();
    //al_hold_bitmap_drawing(true);

    al_clear_to_color(al_map_rgb(15,65,85));
    //al_clear_to_color(al_map_rgb(0,0,0));

    //al_draw_bitmap(_background,0,0,0);

    drawGrid(_config.at("gridW"),_config.at("gridH"),al_map_rgba(30,40,50,50), _screenW, _screenH);

    _manEntity->render();

    al_draw_textf(_mainFont, al_map_rgb(225,120,20),
                  2, 2, 0,
                  "nb Entity = %i / %i ", _manEntity->numActiveObject(), _manEntity->vecSize());



//    for (int index = 0; index < _myAnimLink->nbFrame(); index++)
//    {
//        _myAnimLink->drawFrame(index, 10 + index*32,40);
//
//        al_draw_textf(_mainFont, al_map_rgb(250,250,200), 10 + index*32, 40-12, 0,
//                      "%i", index);
//    }

    //_mySprite->render();

//    float yGraph = 32.5;
//    al_draw_filled_rectangle(2.5, yGraph, _manEntity->vecSize(), yGraph+4, al_map_rgba(30,50,20,250));
//    for (int i=0 ; i<_manEntity->vecSize(); i++)
//    {
//        if (_manEntity->at(i))
//            al_draw_filled_rectangle(2.5+i, yGraph, 2.5+i+1, yGraph+4, al_map_rgba(250,150,120,250));
//    }
//    al_draw_rectangle(2.5, yGraph, _manEntity->vecSize()+1.5, yGraph+4, al_map_rgba(50,150,25,250),0);
//    al_draw_text(_mainFont, al_map_rgb(205,200,20),
//                 _manEntity->vecSize()+2.5, yGraph - 6,
//                 0," Data usage");

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

//    al_draw_bitmap_region(_jet,
//                          686, 53,
//                          46, 24,
//                          _x, _yMouse, 0);



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


    if (_gamePause)
        al_draw_text(_mainFont, al_map_rgb(205,200,20),
                     _screenW/2, _screenH/2,
                     -1,"-- P A U S E --");

    al_draw_bitmap(_mouseCursor, _xMouse, _yMouse, 0);


    al_draw_textf(_mainFont, al_map_rgb(205,200,200), _screenW -64, 12, 0,
                  "FPS: %i", _framerate->getFramerate());

    al_draw_textf(_mainFont, al_map_rgb(205,200,200), _screenW -64, 2, 0,
                  "FPS: %.2f", _averageFPS);


    //al_hold_bitmap_drawing(false);


    _window->endRender();


}

