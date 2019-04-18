#pragma once
#include "Game.h"
#include "World.h"
#include "Define.h"
#include "Graphic.h"
#include "MainCharacter.h"
#include "Stage1.h"
#include "Stage2.h"
#include "KeyGame.h"
#include "StageManager.h"

class KeyEventHandler : public Input {
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};


class ProcessGame
{
private:
	static ProcessGame* _instance;
	KeyEventHandler* keyHandler;

public:
	ProcessGame(HINSTANCE hInstance, int nShowCmd);
	// Dùng để chạy và update nhân vật
	int GameRun();
	void Update(DWORD dt);
	void Render();
	static ProcessGame* GetInstance(HINSTANCE hInstance, int nShowCmd) {
		if (_instance == NULL) _instance = new ProcessGame(hInstance, nShowCmd);
		return _instance;
	}
};

