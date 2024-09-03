#include "snail.h"
#include "inlinehelper.h"
#include "sprite.h"

Snail::Snail()
{
	x = GetRandom(0, 500);
	y = GetRandom(0, 500);

	sprite = NULL;
}

void Snail::SetSprite(Sprite* newsprite) {
	sprite = newsprite;
	sprite->SetX(x);
	sprite->SetY(y);
}