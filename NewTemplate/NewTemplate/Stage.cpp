#include "Stage.h"

Stage::Stage()
{
	this->objects = new vector<Object*>();

	HUD::GetInstance();
}

Stage::~Stage()
{
}

void Stage::InitStaticObjects(RECT rect, vector<RECT> *staticObjects)
{

	int n = floor(rect.left / CELL_SIZE);
	int tempRight = (n+1) * CELL_SIZE;
	if (tempRight > rect.right) {
		this->InitStaticObjects1(rect, staticObjects);
		return;
	}
	else {
		RECT rect1;
		rect1.top = rect.top;
		rect1.left = rect.left;
		rect1.right = tempRight;
		rect1.bottom = rect.bottom;
		this->InitStaticObjects1(rect1, staticObjects);

		RECT rect2;
		rect2.top = rect.top;
		rect2.left = tempRight;
		rect2.bottom = rect.bottom;
		rect2.right = rect.right;

		this->InitStaticObjects(rect2, staticObjects);
	}

	
}

void Stage::InitStaticObjects1(RECT rect, vector<RECT> *staticObjects)
{
	int n = floor(rect.top / CELL_SIZE);
	int tempBottom = (n + 1) * CELL_SIZE;
	if (tempBottom > rect.bottom) {
		staticObjects->push_back(rect);
		return;
	}
	else {
		RECT rect1;
		rect1.top = rect.top;
		rect1.left = rect.left;
		rect1.right = rect.right;
		rect1.bottom = tempBottom;
		staticObjects->push_back(rect1);

		RECT rect2;
		rect2.top = tempBottom;
		rect2.left = rect.left;
		rect2.bottom = rect.bottom;
		rect2.right = rect.right;

		this->InitStaticObjects1(rect2, staticObjects);
	}
}

void Stage::Update(float deltaTime)
{
	HUD::GetInstance()->Update(deltaTime);
	for (int i = 0; i < this->objects->size(); i++) {

		if (this->objects->at(i)->GetObjectType() != BRICK && this->objects->at(i)->GetPosition().y >= 350)
		{
			this->objects->at(i)->SetHP(0);
		}
	}
	for (int i = 0; i < this->objects->size(); i++) {

		if (this->objects->at(i)->GetHP() != 0)
		{
			if (this->objects->at(i)->GetObjectType() != BRICK) {
				vector<Object*>* collisionsObject = Grid::GetInstance()->GetCollisionObjects(this->objects->at(i));

				this->objects->at(i)->Update(deltaTime, collisionsObject);

				for (int j = 0; j < collisionsObject->size(); j++) {
					if (collisionsObject->at(j)->GetHP() != 0)
						Grid::GetInstance()->UpdateGrid(collisionsObject->at(j));
				}

			}
			else {
				this->objects->at(i)->Update(deltaTime, NULL);
			}
			Grid::GetInstance()->UpdateGrid(this->objects->at(i));
		}
	}

	Camera::GetInstance()->Update(MainCharacter::GetInstance()->GetPosition());
}

void Stage::Render()
{
	HUD::GetInstance()->Draw(Camera::GetInstance()->getPosition());
	map->drawMap();
	for (int i = 0; i < this->objects->size(); i++) {
		this->objects->at(i)->Render();
	}



}
