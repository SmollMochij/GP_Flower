#ifndef FLOWER_H
#define FLOWER_H

#include "sprite.h"

class Flower {
public:
    int x;
    int y;
    int health;
    Sprite* sprite;
public:
    Flower();
    void SetSprite(Sprite* sprite);
    void Update();
};

#endif // FLOWER_H
