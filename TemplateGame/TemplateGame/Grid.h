#pragma once
#include "GameDefine.h"
#include "SpaceDefine.h"
#include "OtherObjectsDefine.h"
#include "ObjectDefine.h"
#include "Object.h"
#include <cmath>
#include <iostream>

class Grid
{
private:
	int numOfRow;			// Số dòng của Grid (y)
	int numOfColumn;		// Số cột của Grid (x)
	Object ***cells;		// Với 3 tham số truyền vào lần lượt là: Số dòng, số cột, và số chiều sâu
	float deltaTime;		// deltaTime này là cái số thời gian thực tế mà cái sprite nó được vẽ

	void InitObjectForGrid();

	bool HandleObject(Object* objSrc, Object* objDes);
public:
	Grid();
	Grid(int mapHeight, int mapWidth);
	~Grid();

	void Add(Object *object);
	void ReSetGrid(int width, int height);
	bool HandleCell(Object* object, int row, int column);
	void UpdateGrid(Object* object, float newPosX, float newPosY);

	void SetDeltaTime(float deltaTime);
	float GetDeltaTime();
};

