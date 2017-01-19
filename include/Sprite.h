#ifndef SPRITE_H
#define SPRITE_H

#include "MugenEngine.h"
#include "Animation.h"

enum
{
    ONCE = 0,
    LOOP,
    PINGPONG
};

class Sprite
{
    public:
        Sprite();
        virtual ~Sprite();

        void addAnimation(Animation *animation);
        int addedAnimation() const;

        Animation *animation(int id) const;

        int frameDelay(Animation *animation, unsigned index) const;

        void drawAnimation(unsigned index, int x, int y, unsigned frame = 0);
        void drawAnimation(Animation *animation, int x, int y, unsigned frame = 0);

    protected:

    private:

        int _currentFrame = 0;
        std::vector<Animation*> _vecAnimation;


};


#endif // SPRITE_H
