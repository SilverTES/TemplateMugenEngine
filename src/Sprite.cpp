#include "Sprite.h"

Sprite::Sprite()
{
    //ctor
}

Sprite::~Sprite()
{
    if (!_vecAnimation.empty())
    {
        for (auto & it: _vecAnimation)
        {
            if (it != nullptr)
            {
                delete it;
                it = nullptr;
            }

        }
        _vecAnimation.clear();
    }
    //dtor
}
void Sprite::setFrame(int frame)
{
    _currentFrame = frame;
}

void Sprite::addAnimation(Animation* animation)
{
    if (animation != nullptr)
        _vecAnimation.push_back(animation);
}


void Sprite::setAnimation(Animation* animation, int flags)
{
    if (animation != nullptr)
        _currentAnimation = animation;

    _flags = flags;
}

Animation* Sprite::animation() const
{
    return _currentAnimation;
}



void Sprite::draw(int x, int y, int frame)
{
    if (frame == -1)
        frame = _currentFrame;
    else
        _currentFrame = frame;

    if (_currentAnimation != nullptr)
        _currentAnimation->drawFrame(_currentFrame, x, y);
}
