// COMP710 GP Framework 2022
// This include:
#include "game.h"

#include <random>
#include <fmod.hpp>

// Library includes:
#include "renderer.h"
#include "logmanager.h"
#include "sprite.h"
#include "scenegarden.h"
#include "sceneaut.h"

// Static Members:
Game *Game::sm_pInstance = 0;
Game &Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}
	return (*sm_pInstance);
}
void Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
	: m_pRenderer(0), m_bLooping(true)
	, m_fElapsedSecondsTotal(0)
{
}
Game::~Game()
{
	delete m_pRenderer;
	m_pRenderer = 0;
}
void Game::Quit()
{
	m_bLooping = false;
}

bool Game::Initialise()
{
	srand((int)time(0));

	int bbWidth = 1024;
	int bbHeight = 720;
	m_pRenderer = new Renderer();
	if (!m_pRenderer->Initialise(true, bbWidth, bbHeight))
	{
		LogManager::GetInstance().Log("Renderer failed to initialise!");
		return false;
	}
	m_pRenderer->SetClearColour(0, 0, 0);

	bbWidth = m_pRenderer->GetWidth();
	bbHeight = m_pRenderer->GetHeight();
	m_iLastTime = SDL_GetPerformanceCounter();

	// sound
	FMOD::System_Create(&m_soundSystem);
	m_soundSystem->init(512, FMOD_INIT_NORMAL, 0);

	// scenes
	m_iCurrentScene = 0;
	m_pScenes = new Scene *[10];
	Scene **pScenes = m_pScenes;

	pScenes[0] = new SceneAUT();
	pScenes[0]->Initialise(*m_pRenderer);

	pScenes[1] = new SceneGarden();
	pScenes[1]->Initialise(*m_pRenderer);
	pScenes[1]->ProcessAudio(m_soundSystem);

	for (int i = 0; i <= 10; i++)
	{
		m_scenes.push_back(pScenes[i]);
	}

	return true;
}
bool Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	// TODO: Process input here!
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		continue;
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	m_pScenes[m_iCurrentScene]->ProcessInput(state);
	if (state[SDL_SCANCODE_ESCAPE]) Quit();

	if (m_bLooping)
	{

		Uint64 current = SDL_GetPerformanceCounter();
		float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

		m_iLastTime = current;

		m_fExecutionTime += deltaTime;

		Process(deltaTime);

#ifdef USE_LAG
		m_fLag += deltaTime;

		int innerLag = 0;

		while (m_fLag >= stepSize)
		{
			Process(stepSize);

			m_fLag -= stepSize;

			++m_iUpdateCount;
			++innerLag;
		}
#endif // USE_LAG

		Draw(*m_pRenderer);
	}

	return m_bLooping;
}

void Game::Process(float deltaTime)
{
	ProcessFrameCounting(deltaTime);

	if (m_fElapsedSecondsTotal >= 2.0) {
		m_iCurrentScene = 1;
		m_pRenderer->SetClearColour(0, 128, 255);
	}

	m_scenes[m_iCurrentScene]->Process(deltaTime);
}
void Game::Draw(Renderer &renderer)
{
	m_iFrameCount++;

	renderer.Clear();

	m_scenes[m_iCurrentScene]->Draw(renderer);

	renderer.Present();
}
void Game::ProcessFrameCounting(float deltaTime)
{
	// Count total simulation time elapsed:
	m_fElapsedSeconds += deltaTime;
	m_fElapsedSecondsTotal += deltaTime;

	// Frame Counter:
	if (m_fElapsedSeconds > 1.0f)
	{
		m_fElapsedSeconds -= 1.0f;
		m_iFPS = m_iFrameCount;
		m_iFrameCount = 0;
	}
}
