#pragma once
#include "Stage.h"
#include "Text.h"
#include "Stage1.h"
#include "ProcessGame.h"


class IntroStage : public Stage
{
private:
	static IntroStage* _instance;

	Text* text;


public:
	IntroStage();
	~IntroStage();

	void LoadResource();
	void Update(float deltaTime);
	void Render();


	static IntroStage* GetInstance() {
		if (_instance == NULL) _instance = new IntroStage();
		return _instance;
	}

	void NextStage();
};

