//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include "MugenEngine.h"

template <class M = std::string, class E = int>
static E log(M msg, E error = 0);

int random(int beginRange, int endRange);

float pourcent(float maxValue, float value);
float proportion(float maxValue, float value, float range);

void showVideoAdapters();
void drawGrid(int sizeX, int sizeY, ALLEGRO_COLOR color, int screenW, int screenH);

#include "Misc.inl"


#endif // MISC_H_INCLUDED
