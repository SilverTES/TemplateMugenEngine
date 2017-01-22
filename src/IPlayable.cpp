#include "IPlayable.h"

IPlayable::IPlayable(std::string name):
    _name(name)
{
    //ctor
}

IPlayable::~IPlayable()
{
    _sprite = nullptr;
    //dtor
}

// Player
bool IPlayable::isPlay() const
{
    return _isPlay;
}

void IPlayable::play()
{
    _isPlay = true;
}
void IPlayable::stop()
{
    _isPlay = false;
}

void IPlayable::playAt(int frame)
{
    _currentFrame = frame;
    _isPlay = true;
}

void IPlayable::stopAt(int frame)
{
    _currentFrame = frame;
    _isPlay = false;
}

bool IPlayable::onFrame(int frame)
{
    if (_currentFrame == frame)
        return true;
    else
        return false;
}

void IPlayable::prevFrame()
{
    ++_currentFrame;
}

void IPlayable::nextFrame()
{
    --_currentFrame;
}


void IPlayable::setFont(ALLEGRO_FONT *font)
{
    _font = font;
}
ALLEGRO_FONT* IPlayable::font() const
{
    return _font;
}

void IPlayable::setWindow(std::shared_ptr<Window> window)
{
    _window = window;
}
std::shared_ptr<Window> IPlayable::window() const
{
    return _window;
}

void IPlayable::setSprite(Sprite* sprite)
{
    _sprite = sprite;
}

Sprite* IPlayable::sprite() const
{
    return _sprite;
}

int IPlayable::id()
{
    return _id;
}

void IPlayable::setId(int id)
{
    _id = id;
}

std::string IPlayable::name()
{
    return _name;
}
