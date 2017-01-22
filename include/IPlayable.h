#ifndef IPLAYABLE_H
#define IPLAYABLE_H

#include "MugenEngine.h"
#include "Sprite.h"

class IPlayable
{
    public:
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


    protected:
        int _id = 0;
        std::string _name;
        bool _isPlay      = false;

        int _currentFrame = 0;
        int _nbFrame = 0;

        ALLEGRO_FONT *_font = nullptr;

        Sprite *_sprite = nullptr;

        std::shared_ptr<Window> _window;

    private:
};

#endif // IPLAYABLE_H
