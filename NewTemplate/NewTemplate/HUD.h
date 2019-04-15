#pragma once
#include "debug.h"
#include "Game.h"
#include "Texture.h"
#include "Text.h"
#include "MainCharacter.h"
#include "Sprite.h"
#include "define.h"

class HUD
{
	static HUD* __instance;

	LPDIRECT3DTEXTURE9 texBackground;
	LPDIRECT3DTEXTURE9 texHealth;
	unordered_map<int, RECT> listHealth;

	Text* text;

	int enemyHealth;

	HUD();
	void DrawHealth(int id, D3DXVECTOR2 position);

	Sprite* GetItemSprite();
	Sprite* GetMultiShootSprite();

public:
	~HUD();

	void Draw(D3DXVECTOR2 position);
	static HUD* GetInstance();

	void SetEnemyHealth(int health);
};
