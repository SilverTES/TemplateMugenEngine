#ifndef ANIMATION_H
#define ANIMATION_H

#include "MugenEngine.h"

struct Rect
{
    int _x;
    int _y;
    int _w;
    int _h;
};

struct Frame
{
    int _id ;
    Rect _rect;
    int _delay;
    int _count;
    int _axeX;
    int _axeY;
    float _scaleX;
    float _scaleY;
    float _angle;

    Frame(int id, Rect rect, int delay = 0, int axeX = 0, int axeY = 0, float scaleX = 1, float scaleY = 1, float angle = 0)
    {
        _id = id;
        _rect = rect;

        _delay = delay;
        _count = 0;

        _axeX = axeX;
        _axeY = axeY;

        _scaleX = scaleX;
        _scaleY = scaleY;
        _angle = angle;


    }

};

class Animation
{
    public:
        Animation(ALLEGRO_BITMAP *atlas);
        virtual ~Animation();

        void addFrame(Frame *frame);

        Frame *frame(unsigned index) const;

        void drawFrame(unsigned index, int x, int y);
        void drawFrame(Frame *frame, int x, int y);
        int nbFrame() const;


    protected:

    private:
        int _nbFrame = 0;

        ALLEGRO_BITMAP * _atlas = nullptr;
        std::vector<Frame*> _vecFrame;
};

#endif // ANIMATION_H
