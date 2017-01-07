//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "MugenEngine.h"

class Controller;  // Important declaration before include Controller ! avoid compilation error!

class Player
{
    public:
        Player(std::string name = "");
        virtual ~Player();
        Player * getData();
        Controller * getController();
        std::string getName();
    protected:
    private:
        std::string _name;
        int _life;
        int _force;
        int _power;
        Controller  * _controller;
};

class PlayerManager
{
    public:
        PlayerManager();
        ~PlayerManager();

        void add(Player * player);
        int getNum();
        Player * getPlayer(unsigned index);

    protected:
    private:
        std::vector<Player*> _vecPlayer;

};

#endif // PLAYER_H_INCLUDED
