#include "snail.h"
#include "inlinehelper.h"
#include "sprite.h"

Snail::Snail()
{
	x = GetRandom(200, 1000);
	y = GetRandom(200, 1000);

	sprite = NULL;
}

void Snail::SetSprite(Sprite* newsprite) {
	sprite = newsprite;
	sprite->SetX(x);
	sprite->SetY(y);
	sprite->SetScale(-1);
}