// COMP710 GP Framework 2022
// This include:
#include "scenegarden.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"

SceneGarden::SceneGarden()
{
}

SceneGarden::~SceneGarden()
{
}
bool SceneGarden::Initialise(Renderer &renderer)
{
	Renderer *m_pRenderer = &renderer;

	m_pSprites = new Sprite *[10];
	for (int i = 0; i < 10; i++)
	{
		m_pSprites[i] = 0;
	}

	int n = -1;

	n++;
	m_pSprites[n] = m_pRenderer->CreateSprite("images/board8x8.png");
	m_pSprites[n]->SetX(200);
	m_pSprites[n]->SetY(200);

	return true;
}

void SceneGarden::Process(float deltaTime)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Process(deltaTime);
	}
}

void SceneGarden::Draw(Renderer &renderer)
{
	for (int i = 0; i < 10; i++)
	{
		if (m_pSprites[i] == 0)
			break;
		m_pSprites[i]->Draw(renderer);
	}
}
