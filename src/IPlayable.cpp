#include "IPlayable.h"

IPlayable::IPlayable()
{
    //ctor
}

IPlayable::~IPlayable()
{
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
