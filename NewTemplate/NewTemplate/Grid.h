#pragma once
#include <set> 
#include "Game.h"
#include "GameObject.h"

class Grid
{
	set<LPGAMEOBJECT>** groundObjects;
	set<LPGAMEOBJECT> moveObjects;
	int column;
	int row;
public:
	Grid(int column, int row);
	~Grid();

	void InsertObject(LPGAMEOBJECT object);
	void LoadObjects(vector<LPGAMEOBJECT>* objects);
	void GetObjects(vector<LPGAMEOBJECT>* objects);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

typedef Grid* LPGRID;