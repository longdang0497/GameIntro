#pragma once
#include "Stage.h"
#include "Define.h"



class StageManager
{
	static StageManager * Instance;
	Stage * currentStage;
public:
	StageManager();
	~StageManager();

	static StageManager * GetInstance() 
	{
		if (Instance == NULL)
			Instance = new StageManager();
		return Instance;
	}

	void SetStage(Stage* stage) { this->currentStage = stage; }
	Stage* GetStage() { return this->currentStage; }

	void LoadResources();
	void Update(DWORD dt);
	void Render();
};


