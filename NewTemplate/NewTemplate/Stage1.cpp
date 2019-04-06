#include "Stage1.h"

Stage1* Stage1::_instance = NULL;

Stage1::Stage1()
{
	this->LoadResource();
}


Stage1::~Stage1()
{
}

void Stage1::LoadResource()
{
	// Grid::GetInstance()->Add(MainCharacter::GetInstance());
	this->objects->push_back(MainCharacter::GetInstance());
}

void Stage1::Update(float deltaTime)
{
	Stage::Update(deltaTime);
}

void Stage1::Render()
{
	Stage::Render();
}
