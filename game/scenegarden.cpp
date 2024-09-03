// COMP710 GP Framework 2022
// This include:
#include "scenegarden.h"

#include <SDL.h>
// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inlinehelper.h"
#include "snail.h"
#include "flower.h"
#include "player.h"
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

	Sprite* player_sprite = m_pRenderer->CreateSprite("images/ball.png");
	player = new Player(100, 200);
	player->SetSprite(player_sprite);

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
	player->sprite->Process(deltaTime);
	player->Update();

	for (int i = 0; i < number_of_flowers; i++) {
		flowers[i]->Update();
		flowers[i]->sprite->Process(deltaTime);
	}

	// randomly spawn new snails
	if (GetRandomPercentage() < 0.00002f) {
		if (snail_count < 4) {
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
			if (snails[i] == NULL) {
				continue;
			}
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
		if (snails[i] == NULL) {
			continue;
		}
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

	player->sprite->Draw(renderer);
}

void SceneGarden::ProcessInput(const Uint8* state) {
	if (state[SDL_SCANCODE_W]) player->y -= 1; // Move up
	if (state[SDL_SCANCODE_A]) player->x -= 1; // Move left
	if (state[SDL_SCANCODE_S]) player->y += 1; // Move down
	if (state[SDL_SCANCODE_D]) player->x += 1; // Move right
	// Kill snail
	if (state[SDL_SCANCODE_K]) {
		for (int i = 0; i < snail_count; i++) {
			if (snails[i] == NULL) {
				continue;
			}
			int deltaX = snails[i]->x - player->x;
			int deltaY = snails[i]->y - player->y;
			int distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance <= 300) {
				snails[i] = NULL;
			}
			
		}
	}
}