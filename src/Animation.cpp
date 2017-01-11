#include "Animation.h"

Animation::Animation(ALLEGRO_BITMAP *atlas)
{
    _atlas = atlas;
    //ctor
}

Animation::~Animation()
{
    if (!_vecFrame.empty())
    {
        for (auto & it: _vecFrame)
        {
            if (it != nullptr)
            {
                delete it;
                it = nullptr;
            }

        }
        _vecFrame.clear();
    }
    //dtor
}

void Animation::addFrame(Frame *frame)
{
    if (frame != nullptr)
        _vecFrame.push_back(frame);
}


void Animation::drawFrame(int id, int x, int y , int w, int h)
{
    if (w == 0)
        w = _vecFrame[id]->_rect._w;
    if (h == 0)
        h = _vecFrame[id]->_rect._h;


    al_draw_bitmap_region(
        _atlas,
        _vecFrame[id]->_rect._x,
        _vecFrame[id]->_rect._y,
        _vecFrame[id]->_rect._w,
        _vecFrame[id]->_rect._h,
        x,y,
        0
    );
}

int Animation::nbFrame() const
{
    return _vecFrame.size();
}

