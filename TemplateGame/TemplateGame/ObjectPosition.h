#pragma once
#include "ObjectDefine.h"
#include <d3dx9.h>

// Class này dùng để chứa thông tin vị trí của Object
// Position này được xác định là vị trí TOP LEFT
class ObjectPosition
{
private:
	float posX;
	float posY;
	int objectWidth;
	int objectHeight;

	ObjectPosition *posCenter;
public:
	ObjectPosition();
	ObjectPosition(float postX, float posY, int width = DEFAULT_OBJECT_WIDTH, int height = DEFAULT_OBJECT_HEIGHT);
	~ObjectPosition();

	RECT* GetBoudingBox();

	void SetPosX(float posX);
	void SetPosY(float posY);
	float GetPosX();
	float GetPosY();
	ObjectPosition* GetPosCenter();
	void SetObjectWidth(int width);
	void SetObjectHeight(int height);
	int GetObjectWidth();
	int GetObjectHeight();
};

