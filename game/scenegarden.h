#pragma once

// COMP710 GP Framework 2022

#ifndef SCENEGARDEN_H
#define SCENEGARDEN_H

#include <fmod.hpp>
// Local includes:
#include "scene.h"
// Forward declarations:
#include <SDL.h>
class Renderer;
class Sprite;
class Snail;
class Flower;
class Player;
class AnimatedSprite;
// Class declaration:
class SceneGarden : public Scene
{
	// Member methods:
public:
	SceneGarden();
	virtual ~SceneGarden();
	virtual bool Initialise(Renderer &renderer);
	virtual void Process(float deltaTime);
	virtual void Draw(Renderer &renderer);
	virtual void ProcessInput(const Uint8* state);
	virtual void ProcessAudio(FMOD::System* audio);
	virtual void Reset(void);

protected:
private:
	SceneGarden(const SceneGarden&sceneGarden);
	SceneGarden&operator=(const SceneGarden&sceneGarden);

	// Member data:
public:
protected:
	Renderer* m_pRenderer;
	AnimatedSprite** m_pAnimatedSprites;
	Sprite* m_pBG;
	Sprite* m_pGameOver;
	Sprite* m_pControls;
	Snail** snails;
	Flower** flowers;
	Player* player;
	int snail_count;
	int bGameOver;
private:
	FMOD::System* p_sSystem;
	FMOD::Sound* pSound;
};

#endif //   SCENEGARDEN_H
