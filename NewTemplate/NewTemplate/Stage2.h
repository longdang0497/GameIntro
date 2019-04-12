#pragma once
#include "Stage.h"
#include "Define.h"
#include "Map.h"
#include "Brick.h"

class Stage2: public Stage
{
private:
	static Stage2 * _instance;

public:
	Stage2();
	~Stage2();

	void LoadResource();
	void Update(float deltaTime);
	void Render();

	static Stage2* GetInstance() {
		if (_instance == NULL) _instance = new Stage2();
		return _instance;
	}
};

