#include "Game.h"

void Game::initEntity()
{

    _director = new Director("MainDirector");

    _scene = new Scene("Intro");
    _scene->setWindow(_window);
    _scene->setFont(_mainFont);
    _scene->play();

    _director->add(_scene);

    _layer0 = new Layer("Layer0");
    _layer0->setWindow(_window);
    _layer0->setFont(_mainFont);
    _layer0->play();

    _scene->add(_layer0);

    _layer1 = new Layer("Layer1");
    _layer1->setWindow(_window);
    _layer1->setFont(_mainFont);
    _layer1->stop();

    _scene->add(_layer1);

    //_scene->at("Layer0")->setFont(_mainFont);
    //_scene->at("Layer0")->play(true);



    _myAnimLink = new Animation(_linkSheet);

    _myAnimLink->addFrame(new Frame(0,Rect{13,10,17,25}));
    //_myAnimLink->addFrame(new Frame(1,Rect{38,10,17,25}, 10, 0, 0, 2.0, 2.0));
    _myAnimLink->addFrame(new Frame(1,Rect{38,10,17,25}));
    _myAnimLink->addFrame(new Frame(2,Rect{61,10,17,25}));

    _myAnimLink->addFrame(new Frame(3,Rect{84,10,17,25},4));
    _myAnimLink->addFrame(new Frame(4,Rect{106,10,17,25}));
    _myAnimLink->addFrame(new Frame(5,Rect{131,10,17,25}));

    _myAnimLink->addFrame(new Frame(6,Rect{155,10,19,23}));
    _myAnimLink->addFrame(new Frame(7,Rect{177,10,19,23},4));

//    for (float angle = 0; angle < 360; angle +=45)
//        _myAnimLink->addFrame(new Frame(8,
//                                    Rect{177,10,20,24},
//                                    0,
//                                    10, 12,
//                                    1.0, 1.0,
//                                    DEGTORAD(angle)));

    _myAnimKnuckle = new Animation(_knuckleSheet);

    _myAnimKnuckle->addFrame(new Frame(0,Rect{3,261,32,36},   1));
    _myAnimKnuckle->addFrame(new Frame(0,Rect{40,261,32,36},  1));
    _myAnimKnuckle->addFrame(new Frame(0,Rect{76,261,45,36},  1));
    _myAnimKnuckle->addFrame(new Frame(0,Rect{127,261,35,36}, 8));
    _myAnimKnuckle->addFrame(new Frame(0,Rect{171,261,32,36}, 1));
    _myAnimKnuckle->addFrame(new Frame(0,Rect{205,261,36,36}, 1));
    _myAnimKnuckle->addFrame(new Frame(0,Rect{253,261,44,36}, 1));
    _myAnimKnuckle->addFrame(new Frame(0,Rect{301,261,36,36}, 8));



    _mySprite = new Sprite();
    _mySprite->addAnimation(_myAnimLink);
    _mySprite->addAnimation(_myAnimKnuckle);


// Define Entity EXPLOSION

    _explosion = new Entity(nullptr, "Explosion");

    //_explosion->add(new Position(100, 100, 0));
    _explosion->setPos(100,100,0);
    _explosion->add(new Velocity(1, 1, 0));
    _explosion->add(new Tempo(10));

//    _explosion->add(new Lambda());
//    _explosion->del(componentType("Lambda")); // do nothing if no exist !
//    _explosion->del(componentType("LAMBDA")); // same

    _explosion->setFont(_mainFont);
    _explosion->setWindow(_window);
    _explosion->play();


    _explosion->setUpdate([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Velocity>() != nullptr &&
                e->get<Tempo>() != nullptr)
        {
            e->get<Tempo>()->update();

            if (e->get<Tempo>()->_tic)
                _layer0->del(e->id()); // Delete this Entity;
        }

    });

    _explosion->setRender([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Tempo>() != nullptr)
        {
            int x = e->_x;
            int y = e->_y;
            int tempo = e->get<Tempo>()->_tempo;

            //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
            al_draw_filled_circle(x,y,2+tempo, al_map_rgba(255,220,0,10));
            al_draw_circle(x, y, 2 + tempo, al_map_rgb(255, 55, 0), 0);
//            al_draw_bitmap_region(_jet,
//                                  379, 403,
//                                  30, 32,
//                                  x-15, y-16, 0);

        }
    });

    //_explosion->del(componentType("LAMBDA"));

// Define Entity LASER !
    _laser = new Entity(nullptr, "Laser");

    //_laser->add(new Position(100, 200, 0));
    _laser->setPos(100,200,0);
    _laser->add(new Velocity(1, 0, 1));
    _laser->add(new Tempo(8));
    _laser->setFont(_mainFont);
    _laser->setWindow(_window);
    _laser->play();

    //_laser->setSprite(_mySprite);

    //_laser->_sprite->addAnimation(_myAnimLink);
    //_laser->_sprite->setAnimation(_myAnimLink);

    _laser->setUpdate([&](Entity * e)
    {

        if (e->window() != nullptr &&
                e->get<Velocity>() != nullptr)
        {
            e->_x += e->get<Velocity>()->_x * e->get<Velocity>()->_z;

            e->get<Tempo>()->update();
            if (e->get<Tempo>()->_tic)
            {
                e->get<Tempo>()->_tic = false;
                //e->get<Velocity>()->_z += e->get<Velocity>()->_z;
                if (e->get<Velocity>()->_z < 16) e->get<Velocity>()->_z += e->get<Velocity>()->_z;
            }

            //if (e->get<Velocity>()->_z > 16) e->get<Velocity>()->_z = 16;

            if (e->_x > e->window()->screenW() - 16)
            {

                al_play_sample(_soundExplose, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                // Create new Explosion by clone !
                Entity *explosion = Entity::cloneOf(_explosion, "cloneExplosion");
                explosion->_x = e->_x;
                explosion->_y = e->_y;
                _layer0->add(explosion);

                _layer0->del(e->id()); // Delete this Entity;
            }



        }



    });
    _laser->setRender([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Velocity>() != nullptr)
        {
            int x = e->_x;
            int y = e->_y;

//            al_draw_filled_rectangle(x+.5, y-.5,
//                                     x-e->get<Velocity>()->_z+.5, y+1.5,
//                                     al_map_rgba(250-e->get<Velocity>()->_z*10,180,250,255));
//
//            al_draw_rectangle(x+.5, y-.5,
//                              x-e->get<Velocity>()->_z+.5, y+1.5,
//                              al_map_rgba(250-e->get<Velocity>()->_z*10,100,20+e->get<Velocity>()->_z*10,250),
//                              0);

            al_draw_bitmap_region(_jet,
                                  396, 317,
                                  12, 4,
                                  x, y, 0);



        }

    });

// Define Entity BALL :

    //_layer0->add(new Entity(nullptr,"Ball"));
    _ball = new Entity(nullptr, "Ball");

//    _layer0->at("Ball")->add(new Position(100,100,0));
//    _layer0->at("Ball")->add(new Velocity(1,1,0));

    //_ball->add(new Position(100, 100, 50));
    _ball->setPos(100,100,50);
    _ball->add(new Velocity(1, 1, 0));
    _ball->add(new Tempo(32));
    _ball->add(new Animate());
    _ball->add(new Lambda());


//    auto it = _mapComponentType.begin();
//
//    while (it != _mapComponentType.end())
//    {
//            log ("- Type : "+ std::to_string(it->second) + " of component : " + it->first + "\n");
//            //delete it->second;
//            //it->second = nullptr;
//
//        it++;
//    }
//
//
//
//    std::cout << "- get<Animate> = ";
//    std::cout << _ball->get<Animate>() << "\n";

    _ball->setFont(_mainFont);
    _ball->setWindow(_window);
    _ball->play();

    _ball->setSprite(_mySprite);

    _ball->get<Animate>()->start(0, 2, 1, 0,_myAnimLink->addedFrame()-1);

    //_layer0->at("Ball")->setUpdate([&](Entity * e)
    _ball->setUpdate([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Velocity>() != nullptr &&
                e->get<Tempo>() != nullptr)
        {
            e->_x += e->get<Velocity>()->_x;
            e->_y += e->get<Velocity>()->_y;



            if (e->_x < 0)
                e->get<Velocity>()->_x = 1;

            if (e->_x > e->window()->screenW())
                e->get<Velocity>()->_x = -1;

            if (e->_y < 0)
                e->get<Velocity>()->_y = 1;

            if (e->_y > e->window()->screenH())
                e->get<Velocity>()->_y = -1;

//            if (e->get<Tempo>() != nullptr)
//            {
            e->get<Tempo>()->update();

//            e->get<Tempo>()->_tempo += 1;
//            if (e->get<Tempo>()->_tempo > e->get<Tempo>()->_duration)
//            {
//                e->get<Tempo>()->_tic = true;
//                e->get<Tempo>()->_tempo = 0;
//            }

            if (e->get<Tempo>()->_tic)
            {
                e->get<Tempo>()->_tic = false;


//                // Create new Explosion by clone !
//                Entity *explosion = Entity::cloneOf(_explosion, "cloneExplosion");
//                explosion->get<Position>()->_x = e->get<Position>()->_x;
//                explosion->get<Position>()->_y = e->get<Position>()->_y;
//                _layer0->add(explosion);

                al_play_sample(_soundLaser, 0.05, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                // Create new Laser by clone !
                Entity *laser = Entity::cloneOf(_laser, "Clone Laser");
                laser->_x = e->_x + 26;
                laser->_y = e->_y + 8;
                _layer0->add(laser);
            }
//            }
            if (e->sprite() != nullptr)
            {

                // Manage Frame delay !
                e->get<Animate>()->_frameDelay = _myAnimLink->frame(e->get<Animate>()->_currentFrame)->_delay;

                if (e->get<Animate>() != nullptr)
                    e->get<Animate>()->update();

            }



        }
    });

    //_layer0->at("Ball")->setRender([&](Entity * e)
    _ball->setRender([&](Entity * e)
    {
        if (e->window() != nullptr)
        {
            int x = e->_x;
            int y = e->_y;
            e->_z = y;
//            int z = e->get<Position>()->_z;

            //al_draw_filled_circle(x+.5, y+.5, 8, al_map_rgba(255,0,255,50));

            //al_draw_circle(x+.5, y+.5, 8, al_map_rgb(25,155,255),0);

//            ALLEGRO_TRANSFORM trans, prevTrans;
//
//            al_copy_transform(&prevTrans, al_get_current_transform());
//
//            al_identity_transform(&trans);
//            al_rotate_transform(&trans, 1.0/e->get<Tempo>()->_tempo);
//            al_use_transform(&trans);
//
//            al_draw_bitmap_region(_jet,
//                                  487, 259,
//                                  26, 16,
//                                  x, y, 0);
//
//            al_use_transform(&prevTrans);

//
//            al_draw_tinted_scaled_rotated_bitmap_region
//            (
//                _jet,     // source bitmap region
//                487, 259, // Position source
//                26, 16,   // Size source
//                al_map_rgb(25+(z*4), 255-(z*2), 255), // Tint
//                //500,268,
//                13,8,  // Center of Rotation/Scaling
//                x, y,  // Position
//                1, 1,  // scale
//                0,//(1.0/(z))*400,     // angle
//                0      // flags
//
//
//            );


//            al_draw_line(0,y+.5,
//                         e->window()->screenW(),y+.5,
//                         al_map_rgba(55,25,20,25),0);
//
//            al_draw_line(x+.5,0,
//                         x+.5,e->window()->screenH(),
//                         al_map_rgba(55,25,20,25),0);

//            if (e->font() != nullptr)
//            {
//                al_draw_textf(e->font(), al_map_rgb(205,200,20),
//                              x, y-16,-1,
//                              "%s", e->_name.c_str());
//
//                al_draw_textf(e->font(), al_map_rgb(205,200,20),
//                              x, y+8,-1,
//                              "%i", e->_id);
//                al_draw_textf(e->font(), al_map_rgb(205,200,20),
//                              x, y+16,-1,
//                              "%i", e->get<Animate>()->_currentFrame);
//            }


            if (e->sprite() != nullptr)
            {
                //e->sprite()->setAnimation(_myAnimKnuckle);

                e->sprite()->drawAnimation
                (
                    _myAnimLink,
                    x,
                    y,
                    e->get<Animate>()->_currentFrame
                );
            }

        }

    });



    //_layer0->add(Entity::cloneOf(_explosion, "cloneExplosion"));

    _layer0->add(Entity::cloneOf(_ball, "First Clone Ball"));

    //_layer0->at("First Clone Ball")->del(componentType("ANIMATE"));
    //_layer0->at("First Clone Ball")->add(new Animate(1,4,true));

    _layer0->at("First Clone Ball")->get<Velocity>()->_x = -1;

    _layer0->at("First Clone Ball")->get<Animate>()->start(0, 2, 1, 0, _myAnimKnuckle->addedFrame()-1);

    _layer0->at("First Clone Ball")->setUpdate([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Velocity>() != nullptr &&
                e->get<Tempo>() != nullptr)
        {

            e->_x += e->get<Velocity>()->_x;

            if (e->_x < -40)
                e->_x = e->window()->screenW()+40;


            if (e->sprite() != nullptr)
            {
                // Manage Frame delay !
                e->get<Animate>()->_frameDelay = _myAnimKnuckle->frame(e->get<Animate>()->_currentFrame)->_delay;

                if (e->get<Animate>() != nullptr)
                    e->get<Animate>()->update();
            }
        }

    });

    _layer0->at("First Clone Ball")->setRender([&](Entity * e)
    {
        if (e->window() != nullptr)
        {

            int x = e->_x;
            int y = e->_y;

            e->_z = y;

            if (e->sprite() != nullptr)
            {
                e->sprite()->drawAnimation
                (
                    _myAnimKnuckle,
                    x,
                    y,
                    e->get<Animate>()->_currentFrame
                );
            }

//            if (e->font() != nullptr)
//            {
//                al_draw_textf(e->font(), al_map_rgb(205,200,20),
//                              x, y-16,-1,
//                              "%i", e->get<Animate>()->_currentFrame);
//            }

        }

    });




    //int b = _layer0->indexByName("Ball");

    //_layer0->index(b)->render();
    //_layer0->index(b)->play(true);

//    _layer0->add(Entity::cloneOf(_layer0->at("Ball"), "First Clone Ball"));
//    _layer0->at("First Clone Ball")->get<Position>()->_x = 240;
//    _layer0->at("First Clone Ball")->get<Position>()->_y = 120;
//    _layer0->at("First Clone Ball")->del(componentType("VELOCITY"));

//    for (int i = 0; i < 5; i++)
//    {
//        //Entity *e = Entity::cloneOf(_layer0->at("Ball"),"Clone Ball"+std::to_string(i));
//        Entity *e = Entity::cloneOf(_ball, "Clone Ball" + std::to_string(i));
//        e->get<Position>()->_x = random(0, _screenW);
//        e->get<Position>()->_y = random(0, _screenH);
//        _layer0->add(e);
//
//        e = Entity::cloneOf(_laser, "Clone Laser" + std::to_string(i));
//        e->get<Position>()->_x = random(0, _screenW);
//        e->get<Position>()->_y = random(0, _screenH);
//        _layer0->add(e);
//
//
//    }


//    std::function<void(std::string)> showId = [&](std::string name)
//    {
//        if (_layer0->idByName(name) != -1)
//            std::cout << "--- index = _id of " << name << " = " << _layer0->idByName(name) << "\n";
//    };
//
//
//    showId("Clone Ball2");

}


void Game::doneEntity()
{
    if (_ball)
        delete _ball;

    if (_laser)
        delete _laser;

    if (_explosion)
        delete _explosion;

//    if (_layer0)
//        delete _layer0;
//
//    if (_layer1)
//        delete _layer1;
//
//    if (_scene)
//        delete _scene;

    if (_director)
        delete _director;
}














