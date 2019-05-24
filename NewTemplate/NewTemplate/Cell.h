#pragma once
#include "Object.h"

class Cell
{
private:
	Object* objs;
public:
	Cell();
	~Cell();

	void Add(Object* obj);
	void Remove(Object* obj);
	void Delete();
	Object* GetObjs() { return this->objs; }
};

