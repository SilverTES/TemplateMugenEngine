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

void Sprite::addAnimation(Animation* animation)
{
    if (animation != nullptr)
        _vecAnimation.push_back(animation);
}
int Sprite::addedAnimation() const
{
    return _vecAnimation.size();
}


Animation* Sprite::animation(int index) const
{
    return _vecAnimation[index];
}

int Sprite::frameDelay(Animation *animation, unsigned index) const
{
    if (animation->frame(index) != nullptr)
        return animation->frame(index)->_delay;
    else
        return 0;
}

void Sprite::drawAnimation(unsigned index, int x, int y, unsigned frame)
{
    _currentFrame = frame;

    if (_vecAnimation[index] != nullptr)
        _vecAnimation[index]->drawFrame(_currentFrame, x, y);
}

void Sprite::drawAnimation(Animation *animation, int x, int y, unsigned frame)
{
    _currentFrame = frame;

    if (animation != nullptr)
        animation->drawFrame(_currentFrame, x, y);
}
