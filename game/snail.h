#ifndef SNAIL_H
#define SNAIL_H

#include "sprite.h"

class Snail {
public:
    int x;
    int y;
    Sprite* sprite;
public:
    Snail();
    void SetSprite(Sprite* sprite);
};

#endif // SNAIL_H
