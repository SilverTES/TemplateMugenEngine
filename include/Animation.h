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
    int _centerX;
    int _centerY;

    Frame(int id, Rect rect, int centerX = 0, int centerY = 0)
    {
        _id = id;
        _rect = rect;
        _centerX = centerX;
        _centerY = centerY;

        if (centerX == 0)
            _centerX = _rect._x;

        if (centerY == 0)
            _centerY = _rect._y;



    }

};

class Animation
{
    public:
        Animation(ALLEGRO_BITMAP *atlas);
        virtual ~Animation();

        void addFrame(Frame *frame);

        void drawFrame(int id, int x, int y , int w = 0, int h = 0);
        int nbFrame() const;


    protected:

    private:
        int _nbFrame = 0;

        ALLEGRO_BITMAP * _atlas = nullptr;
        std::vector<Frame*> _vecFrame;
};

#endif // ANIMATION_H
