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
Frame* Animation::frame(unsigned index) const
{
    if (index >= 0 && index < _vecFrame.size())
        return _vecFrame[index];
    else
        return nullptr;
}


void Animation::drawFrame(unsigned index, int x, int y)
{
    if (index >= 0 && index < _vecFrame.size())
    if (_vecFrame[index] != nullptr)
        al_draw_tinted_scaled_rotated_bitmap_region
        (
            // source bitmap region
            _atlas,

            // Source Position
            _vecFrame[index]->_rect._x,
            _vecFrame[index]->_rect._y,

            // Source Size
            _vecFrame[index]->_rect._w,
            _vecFrame[index]->_rect._h,

            // Tint
            al_map_rgb(255, 255, 255),

            // Center of Rotation/Scaling
            _vecFrame[index]->_axeX,
            _vecFrame[index]->_axeY,

            // Position of Frame on screen
            x, y,

            // scale
            _vecFrame[index]->_scaleX,
            _vecFrame[index]->_scaleY,

            // Angle of Rotation
            _vecFrame[index]->_angle,

             // flags
            0
        );

}

void Animation::drawFrame(Frame* frame, int x, int y)
{
    if (frame != nullptr)
        al_draw_tinted_scaled_rotated_bitmap_region
        (
            // source bitmap region
            _atlas,

            // Source Position
            frame->_rect._x,
            frame->_rect._y,

            // Source Size
            frame->_rect._w,
            frame->_rect._h,

            // Tint
            al_map_rgb(255, 255, 255),

            // Center of Rotation/Scaling
            frame->_axeX,
            frame->_axeY,

            // Position of Frame on screen
            x, y,

            // scale
            frame->_scaleX,
            frame->_scaleY,

            // Angle of Rotation
            frame->_angle,

             // flags
            0
        );
}


int Animation::nbFrame() const
{
    return _vecFrame.size();
}

