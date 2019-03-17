#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"

#define ID_TEXTURE_MAIN 0
#define PATH_TEXTURE_MAIN L"sprite\\main_character_sprite.png"
#define PATH_POS_MAIN_STAND L"sprite\\main\\MAIN_STAND.txt"
#define PATH_POS_MAIN_RUN L"sprite\\main\\MAIN_RUN.txt"

class World
{
private:
	static World * _instance;
	Sprite* testSpriteStand;
public:
	World();
	~World();
	
	void LoadResource();
	void Update(float deltaTime);
	void Render();

	static World* GetInstance() {
		if (_instance == NULL) _instance = new World();
		return _instance;
	}
};

