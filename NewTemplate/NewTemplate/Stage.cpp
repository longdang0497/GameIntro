#include "Stage.h"

Stage::Stage()
{
	this->objects = new vector<Object*>();
}


Stage::~Stage()
{
}

void Stage::Update(float deltaTime)
{
	for (int i = 0; i < this->objects->size(); i++) {
		this->objects->at(i)->Update(deltaTime, this->objects);

		//if (this->objects->at(i)->GetObjectType() != BRICK) {
		//	Grid::GetInstance()->UpdateGrid(this->objects->at(i));
		//}
	}
}

void Stage::Render()
{
	for (int i = 0; i < this->objects->size(); i++) {
		this->objects->at(i)->Render();
	}
}
