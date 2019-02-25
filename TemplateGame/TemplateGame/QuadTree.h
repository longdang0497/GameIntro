#pragma once
#include "SpaceDefine.h"
#include "MainCharacter.h"
#include "trace.h"
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class QuadTree
{
private:
	int nodeLevel;
	vector<Object*> *vectorObject;
	RECT* mapBoundary;
	QuadTree** quadNodes;

	// 4 biến này dùng để chia mỗi node thành 4 ô
	RECT* topLeftRect;
	RECT* topRightRect;
	RECT* bottomLeftRect;
	RECT* bottomRightRect;

	int GetIndex(Object* obj);
public:
	QuadTree();
	QuadTree(int nodeLevel, RECT* mapBoundary);
	~QuadTree();

	void ClearQuadTree();
	void SplitQuadTree();
	void Insert(Object* obj);
	void Retrieve(vector<Object*>* returnObjects, Object* obj);
};