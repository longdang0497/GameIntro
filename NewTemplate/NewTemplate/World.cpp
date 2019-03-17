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
	texture->Add(ID_TEXTURE_MAP_1, PATH_TEXTURE_MAP_1);

	this->testSpriteStand = new Sprite(texture->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1, 17, 32);

	MainCharacter *main = MainCharacter::GetInstance();

}

void World::Update(float deltaTime)
{
	MainCharacter::GetInstance()->Update(deltaTime, new vector<Object*>);
}

void World::Render()
{
	// Phương thức dùng để vẽ background lên
	// Game::GetInstance()->Draw(0, 0, Texture::GetInstance()->Get(ID_TEXTURE_MAP_1), 0, 0, 300, 200);

	// D3DXVECTOR3 p(100, 100, 0);
	// this->testSpriteStand->DrawSprite(p, true);
	MainCharacter::GetInstance()->Render();
}
