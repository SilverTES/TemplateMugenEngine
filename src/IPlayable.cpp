#include "IPlayable.h"

IPlayable::IPlayable()
{
    //ctor
}

IPlayable::~IPlayable()
{
    _sprite = nullptr;
    //dtor
}

void IPlayable::play(bool isPlay)
{
    _isPlay = isPlay;
}
bool IPlayable::isPlay() const
{
    return _isPlay;
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
