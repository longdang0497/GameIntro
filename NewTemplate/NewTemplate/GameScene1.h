#pragma once
#include "GameScene.h"

class GameScene1 :public GameScene
{
public:
	GameScene1();
	GameScene1(LPCWSTR filePath, CSimon *simon);
	~GameScene1();


	void update(DWORD dt, CSimon *simon);

	void render(CCamera *cam, CSimon *simon);
};

