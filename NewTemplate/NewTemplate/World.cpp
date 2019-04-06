#include "World.h"

World *World::_instance = NULL;

World::World()
{
}


World::~World()
{
}

void World::LoadResource()
{

}

void World::Update(float deltaTime)
{
	MainCharacter::GetInstance()->Update(deltaTime, new vector<Object*>);
}

void World::Render()
{
	MainCharacter::GetInstance()->Render();
}
