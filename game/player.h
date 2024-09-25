#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"

class Player {
public:
    int x;
    int y;
    AnimatedSprite* sprite;
private:
    int spawnX;
    int spawnY;

public:
    Player(int x, int y);
    void SetAnimatedSprite(AnimatedSprite* sprite);
    void Reset();
    void Update();
};

#endif // PLAYER_H
