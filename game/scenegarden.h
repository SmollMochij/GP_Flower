#pragma once

// COMP710 GP Framework 2022

#ifndef SCENEGARDEN_H
#define SCENEGARDEN_H
// Local includes:
#include "scene.h"
// Forward declarations:
class Renderer;
class Sprite;
class Snail;
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
	Snail** snails;
	int snail_count;
};

#endif //   SCENEGARDEN_H
