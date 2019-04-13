#include "HUD.h"

HUD* HUD::__instance;

HUD::HUD()
{
	//player = CSimon::GetInstance();
	this->texBackground = Texture::GetInstance()->Get(ID_TEX_HUD_BG);
	this->texHealth = Texture::GetInstance()->Get(ID_TEX_HEALTH);
	text = Text::GetInstance();
	for (int i = 0; i < 3; i++)
		listHealth.insert(pair<int, RECT>(i, { 5 * i, 0, 5 * (i + 1), 8 }));

	enemyHealth = 16;
}

void HUD::DrawHealth(int id, D3DXVECTOR2 position)
{
	RECT sourceRect = listHealth[id];
	Game::GetInstance()->Draw(position.x, position.y, texHealth, sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom);
}

char* IntToChar(int value, int len = 10)
{
	char* c = new char[len + 1];
	c[len] = '\0';
	for (int i = len - 1; i >= 0; i--)
	{
		c[i] = value % 10 + 48;
		value = value / 10;
	}
	return c;
}


void HUD::Draw(D3DXVECTOR2 position)
{
	Game::GetInstance()->Draw(0, 0, texBackground, 0, 0, 512, 80);

	// scores
	text->DrawString("SCORE-", { 1,3 });
	text->DrawString(IntToChar(MainCharacter::GetInstance()->GetScore(), 6), { 97, 3 }); //49

	// time
	text->DrawString("TIME", { 200,3 });
	text->DrawString(IntToChar(0, 3), { 265, 3 });

	// state
	text->DrawString("STAGE", { 315,3 });
	text->DrawString("03", { 400, 3 });

	// player's heart
	//text->DrawString(IntToChar(10, 2), { 205, 32 });

	// player's health
	text->DrawString("PLAYER", { 1,3 + 20 });
	for (int i = 0; i < 16; i++)
	{
		//int tmpId = i < player->GetHealth() ? 0 : 1;
		int tmpId = 0;
		DrawHealth(tmpId, { float(55 + i * 5), 23 });
	}

	//// enemy's health
	text->DrawString("ENEMY", { 1,3 + 40 });
	for (int i = 0; i < 16; i++)
	{
		//int tmpId = i < enemyHealth ? 2 : 1;
		int tmpId = 2;
		DrawHealth(tmpId, { float(55 + i * 5), 44 });
	}

	//// item
	//GetItemSprite()->Draw(165, 31);

	//// multi shoot
	//GetMultiShootSprite()->Draw(230, 32);

	//// player's life
	//text->DrawString(IntToChar(player->GetLife(), 2), { 205, 25 });
}

HUD::~HUD()
{
}

HUD * HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}

Sprite* HUD::GetItemSprite()
{
	return NULL;
}

Sprite* HUD::GetMultiShootSprite()
{
	return NULL;
}

void HUD::SetEnemyHealth(int health)
{
	enemyHealth = health;
}