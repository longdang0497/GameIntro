#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "Grid.h"
#include "MainCharacter.h"
#include "Define.h"
#include "Grid.h"
#include "Camera.h"
#include "Map.h"
#include "Ladder.h"
#include "Jaguar.h"
#include "HUD.h"
#include "Soldier.h"
#include "Butterfly.h"
#include "Zombie.h"
#include "ZombieSword.h"
#include "Eagle.h"
#include "GreenSodier.h"
#include "Bat.h"
#include "Brick.h"
#include "Boss.h"
#include "HideObject.h"
#include "Explode.h"
#include "Item.h"
#include "Crow.h"
#include "BazookaBullet.h"

class Stage
{
protected:
	vector<Object*> *objects;

	Map* map;
	//Item * item;

	vector<int> SpecialPoint; //use for demo cho thay coi

	bool fadeIn;
	bool fadeOut;

	DWORD TimeToFade;
	int alpha = 255;

public:
	Stage();
	~Stage();

	// Dùng để cắt theo hàng ngang
	void InitStaticObjects(RECT rect, vector<RECT> *staticObjects);

	// Dùng để cắt theo hàng dọc
	void InitStaticObjects1(RECT rect, vector<RECT> *staticObjects);

	void InitEnemies(LPCWSTR filePath);
	void InitItems(D3DXVECTOR3 pos, int objectID);

	virtual void LoadResource() = 0;
	virtual void Update(float deltaTime);
	virtual void Render();

	void FadeInEffect();
	void FadeOutEffect();

	int Nextpoint();

	void MoveNextPoint();

	void AddZombieSword(ZombieSword *Zw);
	void AddBazookaBullet(BazookaBullet *bullet);
};