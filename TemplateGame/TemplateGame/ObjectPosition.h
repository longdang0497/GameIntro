#pragma once
#include "ObjectDefine.h"

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

	void setPosX(float posX);
	void setPosY(float posY);
	float getPosX();
	float getPosY();
	ObjectPosition* getPosCenter();
	void setObjectWidth(int width);
	void setObjectHeight(int height);
	int getObjectWidth();
	int getObjectHeight();
};

