#pragma once
#include "Game.h"
#include "World.h"
#include "Define.h"
#include "Graphic.h"
#include "MainCharacter.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "IntroStage.h"
#include "KeyGame.h"



class ProcessGame
{
private:
	static ProcessGame* _instance;
	GAME_STAGE gameStage;


	DWORD Time; //dung cho chuyen canh
	int alpha;




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

	GAME_STAGE GetGameStage() { return this->gameStage; }

	//Stage* GetCurrentStage() { return this->CurrentStage; }


	void SetGameStage(GAME_STAGE gameStage)
	{ 
		this->gameStage = gameStage; 

	}


};


