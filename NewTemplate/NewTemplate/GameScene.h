#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>


#include "debug.h"
#include "KeyBoard.h"
#include "KeyGame.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Define.h"
#include "Simon.h"
#include "Brick.h"
#include "Camera.h"
#include "Map.h"
#include "Hunk.h"

class GameScene
{

protected:


	Map* map;
	vector<LPGAMEOBJECT> *ground;
	vector<LPGAMEOBJECT> *item;
	vector<LPGAMEOBJECT> *enemy;
	vector<LPGAMEOBJECT> *staticObjects;

	int numOfGround, numOfEnemy, numOfItem, numOfStaticObjects;

	int endOfWorldX, endOfWorldY, startOfWorldX, startOfWorldY;



public:
	GameScene();
	GameScene(LPCWSTR filePath, CSimon *simon);
	~GameScene();

	virtual void initialize(LPCWSTR filePath);

	virtual void update(DWORD dt, CSimon *simon);

	virtual void render(CCamera *cam, CSimon *simon);
};

