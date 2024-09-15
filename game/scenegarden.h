#pragma once

// COMP710 GP Framework 2022

#ifndef SCENEGARDEN_H
#define SCENEGARDEN_H
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

protected:
private:
	SceneGarden(const SceneGarden&sceneGarden);
	SceneGarden&operator=(const SceneGarden&sceneGarden);

	// Member data:
public:
private:
protected:
	Renderer* m_pRenderer;
	Sprite **m_pSprites;
	AnimatedSprite** m_pAnimatedSprites;
	Sprite* m_pGameOver;
	Snail** snails;
	Flower** flowers;
	Player* player;
	int snail_count;
	int bGameOver;
};

#endif //   SCENEGARDEN_H
