#pragma once
#include "Stage.h"
#include "Define.h"
#include "Map.h"
#include "Brick.h"

class Stage1 : public Stage
{
private:
	static Stage1 * _instance;
	Map* map;
public:
	Stage1();
	~Stage1();

	void LoadResource();
	void Update(float deltaTime);
	void Render();

	static Stage1* GetInstance() {
		if (_instance == NULL) _instance = new Stage1();
		return _instance;
	}
};

