// COMP710 GP Framework 2022
// This include:
#include "scenegarden.h"

#include <SDL.h>
// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "animatedsprite.h"
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
	bGameOver = false;

	m_pRenderer = &renderer;

	m_pAnimatedSprites = new AnimatedSprite *[10];
	snails = new Snail * [50];
	flowers = new Flower * [10];
	snail_count = 0;
	for (int i = 0; i < 10; i++)
	{
		m_pAnimatedSprites[i] = NULL;
		snails[i] = NULL;
	}

	Sprite* player_sprite = m_pRenderer->CreateSprite("images/ball.png");
	player = new Player(100, 200);

	Sprite* background = m_pRenderer->CreateSprite("images/background.jpg");
	background->SetX(300);
	background->SetY(500);
	background->SetScale(6);
	m_pBG = background;

	AnimatedSprite* spriteanimated = m_pRenderer->CreateAnimatedSprite("images/sprite.png");
	spriteanimated->SetupFrames(32, 32); // 32x32 spritesheet
	spriteanimated->Animate();
	spriteanimated->SetLooping(true);
	spriteanimated->SetFrameDuration(0.2f); // animation interval
	spriteanimated->SetX(300);
	spriteanimated->SetY(300);
	spriteanimated->SetScale(5);
	m_pAnimatedSprites[0] = spriteanimated;
	player->SetAnimatedSprite(spriteanimated);

	Sprite* gameOver = m_pRenderer->CreateSprite("images/gameover.png");
	gameOver->SetX(1000);
	gameOver->SetY(1000);
	m_pGameOver = gameOver;

	Sprite* pressK = m_pRenderer->CreateSprite("images/pressK.png");
	pressK->SetScale(1);
	pressK->SetX(1000);
	pressK->SetY(1200);
	m_pControls = pressK;

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
		Sprite* flower_sprite = m_pRenderer->CreateSprite("images/rose.png");
		newflower->SetSprite(flower_sprite);
		flowers[i] = newflower;
	}

	return true;
}

void SceneGarden::Reset(void)
{
	bGameOver = false;
	snail_count = 0;
	for (int i = 0; i < 10; i++)
	{
		snails[i] = NULL;
	}
	for (int i = 0; i < number_of_flowers; i++) {
		flowers[i]->Revive();
	}
	player->Reset();
}

void SceneGarden::Process(float deltaTime)
{
#if _DEBUG
#else
	if (bGameOver) return;
#endif

	m_pBG->Process(deltaTime);
	m_pControls->Process(deltaTime);

	player->sprite->Process(deltaTime);
	player->Update();

	for (int i = 0; i < number_of_flowers; i++) {
		flowers[i]->Update();
		flowers[i]->sprite->Process(deltaTime);
	}

	// randomly spawn new snails
	if (GetRandomPercentage() < 0.0002f) {
			Snail * newsnail = new Snail;
			Sprite* snail_sprite = m_pRenderer->CreateSprite("images/snail.png");
			newsnail->SetSprite(snail_sprite);
			newsnail->sprite->SetScale(0.25);
#if _DEBUG
			newsnail->sprite->SetScale(0.5);
#endif
			snails[snail_count] = newsnail;
			snail_count++;
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

			if (distance <= 200) {
				flowers[j]->health -= SNAILEATING;
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (m_pAnimatedSprites[i] != NULL) {
			m_pAnimatedSprites[i]->Process(deltaTime);
		}
	}

	int deadflowers = 0;
	for (int i = 0; i < number_of_flowers; i++) {
		if (flowers[i]->health <= 0) {
			deadflowers++;
		}
	}
	if (deadflowers == number_of_flowers) {
		bGameOver = true;
	}
	if (bGameOver) {
		m_pGameOver->SetScale(-2);
		m_pGameOver->Process(deltaTime);
	}
	else {
		m_pGameOver->SetScale(0);
	}
}

void SceneGarden::Draw(Renderer &renderer)
{
	m_pBG->Draw(renderer);
	m_pControls->Draw(renderer);

	for (int i = 0; i < snail_count; i++) {
		if (snails[i] == NULL) {
			continue;
		}
		snails[i]->sprite->Draw(renderer);
	}

	for (int i = 0; i < 10; i++){
		if (m_pAnimatedSprites[i] != NULL) {
			m_pAnimatedSprites[i]->Draw(renderer);
		}
	}

	for (int i = 0; i < number_of_flowers; i++) {
		flowers[i]->sprite->Draw(renderer);
	}

	player->sprite->Draw(renderer);

	if (bGameOver) {
		m_pGameOver->Draw(renderer);
	}
}

void SceneGarden::ProcessInput(const Uint8* state) {
	int move = 3;
#if _DEBUG
	move = 10;
#endif
	if (state[SDL_SCANCODE_W]) player->y -= move; // Move up
	if (state[SDL_SCANCODE_A]) player->x -= move; // Move left
	if (state[SDL_SCANCODE_S]) player->y += move; // Move down
	if (state[SDL_SCANCODE_D]) player->x += move; // Move right
	// Kill snail
	if (state[SDL_SCANCODE_K]) {
		for (int i = 0; i < snail_count; i++) {
			if (snails[i] == NULL) {
				continue;
			}
			int deltaX = snails[i]->x - player->x;
			int deltaY = snails[i]->y - player->y;
			int distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

			if (distance <= 100) {
				snails[i] = NULL;
			}
		}
		// play sound
		FMOD::Channel* channel = 0;
		p_sSystem->playSound(pSound, 0, false, &channel);
	}
	if (state[SDL_SCANCODE_SPACE]) {
		Reset();
	}
}

void SceneGarden::ProcessAudio(FMOD::System* audio)
{
	p_sSystem = audio;
	audio->createSound("sfx/shing.wav", FMOD_DEFAULT, 0, &pSound);
}
