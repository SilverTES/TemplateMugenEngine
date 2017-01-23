#ifndef IPLAYABLE_H
#define IPLAYABLE_H

#include "MugenEngine.h"
#include "Sprite.h"

struct IPlayable
{
        bool _isPlay      = false;
        int _id = 0;
        int _currentFrame = 0;
        int _nbFrame = 0;

        int _x = 0;
        int _y = 0;
        int _z = 0;

        std::string _name;

        ALLEGRO_FONT *_font = nullptr;

        Sprite *_sprite = nullptr;

        std::shared_ptr<Window> _window;


        IPlayable(std::string name = "");
        virtual ~IPlayable();

        // Player methods
        bool isPlay() const;

        void play();
        void stop();

        void playAt(int frame);
        void stopAt(int frame);
        bool onFrame(int frame);
        void prevFrame();
        void nextFrame();


        void setFont(ALLEGRO_FONT *font);
        ALLEGRO_FONT *font() const;

        void setWindow(std::shared_ptr<Window> window);
        std::shared_ptr<Window> window() const;

        void setSprite(Sprite *sprite);
        Sprite *sprite() const;

        int id();
        void setId(int id);
        std::string name();

        void setPos(int x, int y, int z);




};

#endif // IPLAYABLE_H
