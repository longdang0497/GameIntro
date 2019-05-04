#pragma once
#include "Stage.h"

class Stage3 : public Stage
{
private:
	static Stage3* _instance;
public:
	Stage3();
	~Stage3();

	void LoadResource();
	void Update(float deltaTime);
	void Render();

	static Stage3* GetInstance() {
		if (_instance == NULL) _instance = new Stage3();
		return _instance;
	}
};

