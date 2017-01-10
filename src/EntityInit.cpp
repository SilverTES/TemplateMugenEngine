#include "Game.h"

void Game::initEntity()
{

    _manEntity = std::make_shared<EntityManager>();


// Define Entity EXPLOSION

    _explosion = new Entity(nullptr, "Explosion");

    _explosion->add(new Position(100, 100, 0));
    _explosion->add(new Velocity(1, 1, 0));
    _explosion->add(new Tempo(10));
    _explosion->add(new Lambda());

    _explosion->del(componentType("Lambda"));
    _explosion->del(componentType("LAMBDA"));


    auto it = _mapComponentType.begin();

    while (it != _mapComponentType.end())
    {
            log ("- Type : "+ std::to_string(it->second) + " of component : " + it->first + "\n");
            //delete it->second;
            //it->second = nullptr;

        it++;
    }




    _explosion->setFont(_mainFont);
    _explosion->setWindow(_window);
    _explosion->play(true);


    _explosion->setUpdate([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Position>() != nullptr &&
                e->get<Velocity>() != nullptr &&
                e->get<Tempo>() != nullptr)
        {
            e->get<Tempo>()->update();

            if (e->get<Tempo>()->_tic)
                _manEntity->del(e->_id); // Delete this Entity;
        }

    });

    _explosion->setRender([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Position>() != nullptr &&
                e->get<Tempo>() != nullptr)
        {
            int x = e->get<Position>()->_x;
            int y = e->get<Position>()->_y;
            int tempo = e->get<Tempo>()->_tempo;

            //al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
            //al_draw_filled_circle(x,y,2+tempo, al_map_rgba(255,220,0,10));
            al_draw_circle(x, y, 2 + tempo, al_map_rgb(255, 55, 0), 0);
//            al_draw_bitmap_region(_jet,
//                                  379, 403,
//                                  30, 32,
//                                  x-15, y-16, 0);

        }
    });

    _explosion->del(componentType("LAMBDA"));

// Define Entity LASER !
    _laser = new Entity(nullptr, "Laser");

    _laser->add(new Position(100, 200, 0));
    _laser->add(new Velocity(1, 0, 1));

    _laser->setFont(_mainFont);
    _laser->setWindow(_window);
    _laser->play(true);

    _laser->setUpdate([&](Entity * e)
    {

        if (e->window() != nullptr &&
                e->get<Position>() != nullptr &&
                e->get<Velocity>() != nullptr)
        {
            e->get<Position>()->_x += e->get<Velocity>()->_x * e->get<Velocity>()->_z;

            e->get<Position>()->_z++;
            if (e->get<Position>()->_z > 8)
            {
                e->get<Position>()->_z = 0;
                //e->get<Velocity>()->_z += e->get<Velocity>()->_z;
                if (e->get<Velocity>()->_z < 16) e->get<Velocity>()->_z += e->get<Velocity>()->_z;
            }

            //if (e->get<Velocity>()->_z > 16) e->get<Velocity>()->_z = 16;

            if (e->get<Position>()->_x > e->window()->screenW() - 16)
            {

                al_play_sample(_soundExplose, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                // Create new Explosion by clone !
                Entity *explosion = Entity::cloneOf(_explosion, "cloneExplosion");
                explosion->get<Position>()->_x = e->get<Position>()->_x;
                explosion->get<Position>()->_y = e->get<Position>()->_y;
                _manEntity->add(explosion);

                _manEntity->del(e->_id); // Delete this Entity;
            }

        }

    });
    _laser->setRender([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Position>() != nullptr &&
                e->get<Velocity>() != nullptr)
        {
            int x = e->get<Position>()->_x;
            int y = e->get<Position>()->_y;

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

    //_manEntity->add(new Entity(nullptr,"Ball"));
    _ball = new Entity(nullptr, "Ball");

//    _manEntity->at("Ball")->add(new Position(100,100,0));
//    _manEntity->at("Ball")->add(new Velocity(1,1,0));

    _ball->add(new Position(100, 100, 50));
    _ball->add(new Velocity(1, 1, 0));
    _ball->add(new Tempo(32));

    _ball->setFont(_mainFont);
    _ball->setWindow(_window);
    _ball->play(true);

    //_manEntity->at("Ball")->setUpdate([&](Entity * e)
    _ball->setUpdate([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Position>() != nullptr &&
                e->get<Velocity>() != nullptr &&
                e->get<Tempo>() != nullptr)
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

            e->get<Position>()->_z += 1;

            if (e->get<Position>()->_z > 100)
                e->get<Position>()->_z = 50;

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
//                _manEntity->add(explosion);

                al_play_sample(_soundLaser, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                // Create new Laser by clone !
                Entity *laser = Entity::cloneOf(_laser, "Clone Laser");
                laser->get<Position>()->_x = e->get<Position>()->_x + 26;
                laser->get<Position>()->_y = e->get<Position>()->_y + 8;
                _manEntity->add(laser);
            }
//            }

        }
    });

    //_manEntity->at("Ball")->setRender([&](Entity * e)
    _ball->setRender([&](Entity * e)
    {
        if (e->window() != nullptr &&
                e->get<Position>() != nullptr)
        {
            int x = e->get<Position>()->_x;
            int y = e->get<Position>()->_y;
            int z = e->get<Position>()->_z;

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

            al_draw_tinted_scaled_rotated_bitmap_region
            (
                _jet,     // source bitmap region
                487, 259, // Position source
                26, 16,   // Size source
                al_map_rgb(25+(z*4), 255-(z*2), 255), // Tint
                //500,268,
                13,8,  // Center of Rotation/Scaling
                x, y,  // Position
                1, 1,  // scale
                0,//(1.0/(z))*400,     // angle
                0      // flags


            );


//            al_draw_line(0,y+.5,
//                         e->window()->screenW(),y+.5,
//                         al_map_rgba(55,25,20,25),0);
//
//            al_draw_line(x+.5,0,
//                         x+.5,e->window()->screenH(),
//                         al_map_rgba(55,25,20,25),0);

            if (e->font() != nullptr)
            {
//                al_draw_textf(e->font(), al_map_rgb(205,200,20),
//                              x, y-12,-1,
//                              "%s", e->_name.c_str());
//
//                al_draw_textf(e->font(), al_map_rgb(205,200,20),
//                              x, y+8,-1,
//                              "%i", e->_id);

//                al_draw_textf(e->font(), al_map_rgb(205,200,20),
//                              x, y+8,-1,
//                              "%i", z);

            }


        }

    });



    //_manEntity->add(Entity::cloneOf(_explosion, "cloneExplosion"));

    _manEntity->add(Entity::cloneOf(_ball, "Ball"));

    //int b = _manEntity->indexByName("Ball");

    //_manEntity->index(b)->render();
    //_manEntity->index(b)->play(true);

    _manEntity->add(Entity::cloneOf(_manEntity->at("Ball"), "First Clone Ball"));

    _manEntity->at("First Clone Ball")->get<Position>()->_x = 240;
    _manEntity->at("First Clone Ball")->get<Position>()->_y = 120;

    for (int i = 0; i < 5; i++)
    {
        //Entity *e = Entity::cloneOf(_manEntity->at("Ball"),"Clone Ball"+std::to_string(i));
        Entity *e = Entity::cloneOf(_ball, "Clone Ball" + std::to_string(i));
        e->get<Position>()->_x = random(0, _screenW);
        e->get<Position>()->_y = random(0, _screenH);
        _manEntity->add(e);

        e = Entity::cloneOf(_laser, "Clone Laser" + std::to_string(i));
        e->get<Position>()->_x = random(0, _screenW);
        e->get<Position>()->_y = random(0, _screenH);
        _manEntity->add(e);


    }

    _manEntity->at("First Clone Ball")->del(componentType("VELOCITY"));

    for (int i = 0; i < _manEntity->vecSize(); i++)
    {
        _manEntity->index(i)->setFont(_mainFont);
        _manEntity->index(i)->setWindow(_window);
    }

    std::function<void(std::string)> showId = [&](std::string name)
    {
        if (_manEntity->idByName(name) != -1)
            std::cout << "--- index = _id of " << name << " = " << _manEntity->idByName(name) << "\n";
    };


    showId("Clone Ball2");



}


void Game::doneEntity()
{
    delete _ball;
    delete _laser;
    delete _explosion;
}














