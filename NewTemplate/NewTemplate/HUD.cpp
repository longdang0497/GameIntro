#include "HUD.h"

HUD* HUD::__instance;

HUD::HUD()
{
	//player = CSimon::GetInstance();
	this->texBackground = Texture::GetInstance()->Get(ID_TEX_HUD_BG);
	this->ShurikenSprite = Texture::GetInstance()->Get(ID_TEXTURE_MAIN);
	this->texHealth = Texture::GetInstance()->Get(ID_TEX_HEALTH);
	text = Text::GetInstance();
	for (int i = 0; i < 3; i++)
		listHealth.insert(pair<int, RECT>(i, { 5 * i, 0, 5 * (i + 1), 8 }));

	enemyHealth = 16;
	time = 150;
	bufferTime = 0;
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

	// scores
	text->DrawString("SCORE-", { 1,3 });
	text->DrawString(IntToChar(MainCharacter::GetInstance()->GetScore(), 6), { 49, 3 }); //49

	// time
	text->DrawString("TIME", { 150,3 });
	text->DrawString(IntToChar(time, 6), { 183, 3 });

	// state
	text->DrawString("STAGE - ", { 1,23 });
	text->DrawString("03", { 50, 23 });


	// state
	text->DrawString("P -", { 97,23 });
	//text->DrawString("02", {122, 23 });
	text->DrawString(IntToChar(MainCharacter::GetInstance()->GetLives(), 2), { 121, 23 });


	Game::GetInstance()->Draw(150, 23, texBackground, 0, 0, 62, 48);

	if (MainCharacter::GetInstance()->GetHasShuriken() == true)
	{
		Game::GetInstance()->Draw(151, 24, ShurikenSprite , 278,88, 295, 105);
	}


	// player's health
	text->DrawString("PLAYER", { 1,43 });

	int i = 0;
	int player = MainCharacter::GetInstance()->GetHP();
	for (i; i < player; i++)
	{
		DrawHealth(0, { float(55 + i * 5), 43 });
	}

	for (i; i < 16; i++)
	{
		DrawHealth(1, { float(55 + i * 5), 43 });
	}

	i = 0;
	int boss = Boss::GetInstance()->GetHP();
	text->DrawString("ENEMY", { 1,63 });
	for (i; i < boss; i++)
	{
		DrawHealth(0, { float(55 + i * 5), 63 });
	}

	for (i; i < 16; i++)
	{
		DrawHealth(2, { float(55 + i * 5), 63 });
	}

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

void HUD::Update(float dt)
{

	if (!StopCounting)
	{
		bufferTime += dt;
		if (bufferTime >= 1000)
		{
			this->time -= 1;
			bufferTime -= 1000;
		}
	}
}

void HUD::ResetTime()
{
	this->time = 150;
	bufferTime = 0;
}