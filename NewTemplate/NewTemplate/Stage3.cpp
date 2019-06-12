#include "Stage3.h"

Stage3* Stage3::_instance = NULL;

Stage3::Stage3()
{
	HUD::GetInstance()->ReSetTime();
	Grid::GetInstance()->ReSetGrid(STAGE3_WIDTH, STAGE3_HEIGHT, false);
	MainCharacter::GetInstance()->SetIsInTheEndOfMap(false);
	this->LoadResource();

	Camera::GetInstance()->setWorldBoundary(STAGE3_WIDTH);
	alpha = 255;
	fadeIn = true;
	fadeOut = false;
	TimeToFade = GetTickCount();
}


Stage3::~Stage3()
{
}

void Stage3::LoadResource()
{
	this->objects->clear();

	MainCharacter::GetInstance()->SetPosition(30.0f, 193.8f);

	this->objects->push_back(MainCharacter::GetInstance());

	this->map = new Map(PATH_POS_MAP_3, PATH_TEXTURE_MAP_3, ID_TEXTURE_MAP_3);

	fstream fs(PATH_POS_GROUND_MAP_3);

	int numberOfGround, left, top, right, bottom, canStick;

	fs >> numberOfGround;

	vector<RECT>* bricks = new vector<RECT>();

	for (int i = 0; i < numberOfGround; i++) {
		bricks->clear();
		fs >> left >> top >> right >> bottom >> canStick;

		RECT rect;
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;

		this->InitStaticObjects(rect, bricks);

		for (int i = 0; i < bricks->size(); i++) {
			RECT rect = bricks->at(i);
			Brick * brick = new Brick(rect.left, rect.top, rect.right, rect.bottom, canStick);
			this->objects->push_back(brick);
		}
	}

	fs.close();

	this->objects->push_back(Boss::GetInstance());

	for (auto obj : *objects) {
		Grid::GetInstance()->Add(obj);
	}
	
	vector<BossBullet*> *bullets = Boss::GetInstance()->GetBullets();

	for (int i = 0; i < bullets->size(); i++) 
	{
		this->objects->push_back(bullets->at(i));
	}

	delete bricks;
}

void Stage3::Update(float deltaTime)
{
	if (Boss::GetInstance()->GetEnd())
	{
		if (!fadeOut)
		{
			alpha = 200;
			fadeOut = true;
		}
	}
	Stage::Update(deltaTime);

	

}

void Stage3::Render()
{
	Stage::Render();
	if (fadeOut)
		FadeOutEffect();
}

void Stage3::FadeInEffect()
{
	if (alpha >= 200)
	{
		if (GetTickCount() - TimeToFade > 20)
		{
			Game::GetInstance()->Draw(0, 80, Texture::GetInstance()->Get(ID_TEXTURE_BLACK), 0, 80, 256, 320, alpha);
			TimeToFade = GetTickCount();
			alpha -= 1;
		}
	}
	else
	{
		fadeIn = false;
		TimeToFade = GetTickCount();
	}
}

void Stage3::FadeOutEffect()
{

	if (alpha < 255)
	{
		if (GetTickCount() - TimeToFade > 20)
		{
			Game::GetInstance()->Draw(0, 80, Texture::GetInstance()->Get(ID_TEXTURE_BLACK), 1792, 80, 2048, 300, alpha);
			TimeToFade = GetTickCount();
			alpha += 1;
		}
	}
	else
	{
		fadeOut = false;

		if (MainCharacter::GetInstance()->GetRepawn())
		{
			MainCharacter::GetInstance()->LoseLive();
			MainCharacter::GetInstance()->SetPosition(50, 80);
			MainCharacter::GetInstance()->SetHP(16);
			MainCharacter::GetInstance()->SetRepawn(false);
		}
		else if (MainCharacter::GetInstance()->GetLives() < 0)
		{
			Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));
			ProcessGame::GetInstance(NULL, 0)->SetGameStage(END_STAGE);
		}
		else
		{
			Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));
			ProcessGame::GetInstance(NULL, 0)->SetGameStage(END_STAGE);
		}
	}
}
