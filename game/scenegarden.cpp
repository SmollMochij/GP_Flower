// COMP710 GP Framework 2022
// This include:
#include "scenegarden.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inlinehelper.h"
#include "snail.h"

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
	snail_count = 0;
	for (int i = 0; i < 10; i++)
	{
		m_pSprites[i] = NULL;
		snails[i] = NULL;
	}

	m_pSprites[0] = m_pRenderer->CreateSprite("images/temp_flower.png");
	m_pSprites[0]->SetX(200);
	m_pSprites[0]->SetY(200);
	m_pSprites[0]->SetScale(-1);

	return true;
}

void SceneGarden::Process(float deltaTime)
{
	if (GetRandomPercentage() < 0.005f) {
		if (snail_count < 10) {
			snails[snail_count] = new Snail;
			snails[snail_count]->sprite = m_pRenderer->CreateSprite("images/snail.png");
			snails[snail_count]->sprite->SetX(snails[snail_count]->x);
			snails[snail_count]->sprite->SetY(snails[snail_count]->y);
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
	for (int i = 0; i < snail_count; i++) {
		snails[i]->sprite->Draw(renderer);
	}

	for (int i = 0; i < 10; i++){
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Draw(renderer);
	}
}
