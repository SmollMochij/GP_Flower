#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"

class Player {
public:
    int x;
    int y;
    Sprite* sprite;
public:
    Player(int x, int y);
    void SetSprite(Sprite* sprite);
    void Update();
};

#endif // PLAYER_H
