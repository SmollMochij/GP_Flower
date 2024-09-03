// COMP710 GP Framework 2022
// This include:
#include "scenegarden.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inlinehelper.h"
#include "snail.h"
#include "flower.h"
#include <cmath>

const int number_of_flowers = 4;

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

	int positions[][number_of_flowers] = {
		{400, 400},
		{800, 400},
		{400, 800},
		{800, 800},
	};
	for (int i = 0; i < number_of_flowers; i++) {
		int x = positions[i][0];
		int y = positions[i][1];
		Flower* newflower = new Flower(x, y);
		Sprite* flower_sprite = m_pRenderer->CreateSprite("images/temp_flower.png");
		newflower->SetSprite(flower_sprite);
		flowers[i] = newflower;
	}

	return true;
}

void SceneGarden::Process(float deltaTime)
{
	for (int i = 0; i < number_of_flowers; i++) {
		flowers[i]->Update();
		flowers[i]->sprite->Process(deltaTime);
	}

	// randomly spawn new snails
	if (GetRandomPercentage() < 0.005f) {
		if (snail_count < 10) {
			Snail * newsnail = new Snail;
			Sprite* snail_sprite = m_pRenderer->CreateSprite("images/snail.png");
			newsnail->SetSprite(snail_sprite);
			snails[snail_count] = newsnail;
			snail_count++;
		}
	}

	// snail eating flowers
	for (int i = 0; i < snail_count; i++) {
		for (int j = 0; j < number_of_flowers; j++) {
			int deltaX = snails[i]->x - flowers[j]->x;
			int deltaY = snails[i]->y - flowers[j]->y;
			int distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance <= 300) {
				flowers[j]->health -= SNAILEATING;
			}
		}
	}


	for (int i = 0; i < 10; i++)
	{
		if (m_pSprites[i] == NULL)
			break;
		m_pSprites[i]->Process(deltaTime);
	}
}

void SceneGarden::Draw(Renderer &renderer)
{
	for (int i = 0; i < snail_count; i++) {
		snails[i]->sprite->Draw(renderer);
	}

	for (int i = 0; i < 10; i++){
		if (m_pSprites[i] == NULL)
			break;
		m_pSprites[i]->Draw(renderer);
	}

	for (int i = 0; i < number_of_flowers; i++) {
		flowers[i]->sprite->Draw(renderer);
	}
}
