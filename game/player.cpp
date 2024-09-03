#include "player.h"
#include "inlinehelper.h"
#include "sprite.h"

Player::Player(int _x, int _y){
	x = _x;
	y = _y;

	sprite = NULL;
}

void Player::SetSprite(Sprite* newsprite) {
	sprite = newsprite;
	sprite->SetX(x);
	sprite->SetY(y);
}

void Player::Update() {
	sprite->SetX(x);
	sprite->SetY(y);
}