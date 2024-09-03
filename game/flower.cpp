#include "flower.h"
#include "inlinehelper.h"
#include "sprite.h"

Flower::Flower()
{
	x = 600;
	y = 600;
	health = 100;

	sprite = NULL;
}

void Flower::SetSprite(Sprite* newsprite) {
	sprite = newsprite;
	sprite->SetX(x);
	sprite->SetY(y);
	sprite->SetScale(-health / 100.0f);
}