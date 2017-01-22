#ifndef SPRITE_H
#define SPRITE_H

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

        void addAnimation(std::shared_ptr<Animation> animation);
        int addedAnimation() const;

        std::shared_ptr<Animation> animation(int id) const;

        int frameDelay(std::shared_ptr<Animation> animation, unsigned index) const;

        void drawAnimation(unsigned index, int x, int y, unsigned frame = 0);
        void drawAnimation(std::shared_ptr<Animation> animation, int x, int y, unsigned frame = 0);

    protected:

    private:

        int _currentFrame = 0;
        std::vector<std::shared_ptr<Animation>> _vecAnimation;


};


#endif // SPRITE_H
