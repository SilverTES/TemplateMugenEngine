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
        void setAnimation(Animation *animation, int flags = 0);

        Animation *animation() const;

        void setFrame(int frame);
        void draw(int x, int y, int frame = -1);  // -1 use _currentFrame;

    protected:

    private:

        Animation  *_currentAnimation = nullptr;
        int _currentFrame = 0;
        int _flags;

        std::vector<Animation*> _vecAnimation;


};

#endif // SPRITE_H
