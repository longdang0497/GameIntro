#pragma once
#include "Object.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "Define.h"
using namespace std;


class Grid
{
private:
	static Grid* _instance;

	int numOfRow;			// Số dòng của Grid (y)
	int numOfColumn;		// Số cột của Grid (x)
	Object ***cells;		// Với 3 tham số truyền vào lần lượt là: Số dòng, số cột, và số chiều sâu
	float deltaTime;		// deltaTime này là cái số thời gian thực tế mà cái sprite nó được vẽ

	void InitObjectForGrid();

	void PushObjectToVector(std::vector<Object*> * vector, Object* cell, Object * obj);
	void DeleteGrid();
	void InitGrid(int mapHeight, int mapWidth, bool isArray);
public:
	Grid();
	Grid(int mapHeight, int mapWidth, bool isArray = true);
	~Grid();

	void Add(Object *object);
	void ReSetGrid(int height, int width, bool isArray = true);
	vector<Object*>* GetCollisionObjects(Object* object);
	void UpdateGrid(Object* object);

	static Grid* GetInstance();
	static Grid* GetInstance(int mapHeight, int mapWidth, bool isArray = true);
};



