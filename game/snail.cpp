#include "snail.h"
#include "inlinehelper.h"

Snail::Snail()
{
	x = GetRandom(0, 500);
	y = GetRandom(0, 500);

	sprite = NULL;
}
