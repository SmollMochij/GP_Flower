// COMP710 GP Framework 2022
// This include:
#include "scenegarden.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inlinehelper.h"
#include "snail.h"
#include "flower.h"

SceneGarden::SceneGarden()
{
}

SceneGarden::~SceneGarden()
{
}
bool SceneGarden::Initialise(Renderer &renderer)
{
	m_pRenderer = &renderer;

	m_pSprites = new Sprite *[10];
	snails = new Snail * [10];
	flowers = new Flower * [10];
	snail_count = 0;
	for (int i = 0; i < 10; i++)
	{
		m_pSprites[i] = NULL;
		snails[i] = NULL;
	}

	Flower* newflower = new Flower;
	Sprite* flower_sprite = m_pRenderer->CreateSprite("images/temp_flower.png");
	newflower->SetSprite(flower_sprite);
	flowers[0] = newflower;

	return true;
}

void SceneGarden::Process(float deltaTime)
{
	flowers[0]->sprite->Process(deltaTime);

	if (GetRandomPercentage() < 0.005f) {
		if (snail_count < 10) {
			Snail * newsnail = new Snail;
			Sprite* snail_sprite = m_pRenderer->CreateSprite("images/snail.png");
			newsnail->SetSprite(snail_sprite);
			snails[snail_count] = newsnail;
			snail_count++;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Process(deltaTime);
	}
}

void SceneGarden::Draw(Renderer &renderer)
{
	flowers[0]->sprite->Draw(renderer);

	for (int i = 0; i < snail_count; i++) {
		snails[i]->sprite->Draw(renderer);
	}

	for (int i = 0; i < 10; i++){
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Draw(renderer);
	}
}
