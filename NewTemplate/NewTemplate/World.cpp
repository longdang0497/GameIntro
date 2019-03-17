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
	Texture *texture = Texture::GetInstance();

	texture->Add(ID_TEXTURE_MAIN, PATH_TEXTURE_MAIN);

	this->testSpriteStand = new Sprite(texture->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1, 17, 32);
}

void World::Update(float deltaTime)
{

}

void World::Render()
{
	D3DXVECTOR3 p(100, 100, 0);
	this->testSpriteStand->DrawSprite(p, true);
}
