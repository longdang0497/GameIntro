#pragma once
#include "Stage.h"
#include "HUD.h"
#include "Text.h"
#include "Stage1.h"
#include "ProcessGame.h"
#include "MainCharacter.h"


class EndStage:public Stage
{
private:
	static EndStage* _instance;

	LPDIRECT3DTEXTURE9 Result;

	int Score;
	int Time;

	int MainScore;
	int MainTime;
	DWORD StartCalculate;

	Text* text;
public:
	EndStage();
	~EndStage();

	void LoadResource();
	void Update(float deltaTime);
	void Render();


	static EndStage* GetInstance() {
		if (_instance == NULL) _instance = new EndStage();
		return _instance;
	}

	void NextStage();
};

