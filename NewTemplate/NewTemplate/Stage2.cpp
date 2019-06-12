#include "Stage2.h"

Stage2* Stage2::_instance = NULL;

Stage2::Stage2()
{
	HUD::GetInstance()->ReSetTime();
	MainCharacter::GetInstance()->SetIsInTheEndOfMap(false);
	Grid::GetInstance()->ReSetGrid(STAGE2_HEIGHT, STAGE2_WIDTH, false);

	MainCharacter::GetInstance()->SetPosition(50, 120);

	this->LoadResource();
	Camera::GetInstance()->setWorldBoundary(3072);
	//Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));

	SpecialPoint.push_back(0);
	SpecialPoint.push_back(1000);
	SpecialPoint.push_back(1245);
	SpecialPoint.push_back(2779);

	alpha = 255;
	fadeIn = true;
	fadeOut = false;
	TimeToFade = GetTickCount();
}



Stage2::~Stage2()
{
}

void Stage2::LoadResource()
{
	bool soundInit = GameSound::GetInstance()->Init(this->window_handler);
	if (soundInit == false)
		return;
	else
		soundS2 = GameSound::GetInstance()->LoadSound(STAGE2_SOUND);

	objects->clear();

	MainCharacter::GetInstance()->SetPosition(10.0f, 183.8f);

	this->objects->push_back(MainCharacter::GetInstance());
	

	this->map = new Map(PATH_POS_MAP_2, PATH_TEXTURE_MAP_2, ID_TEXTURE_MAP_2);

	fstream fs(PATH_POS_GROUND_MAP_2);

	int numberOfGround, left, top, right, bottom, canStick;

	fs >> numberOfGround;

	vector<RECT> *bricks = new vector<RECT>();
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


	fstream fs1(PATH_POS_LADDER_SATGE_2);

	fs1 >> numberOfGround;

	vector<RECT> *ladders = new vector<RECT>();
	for (int i = 0; i < numberOfGround; i++) {
		ladders->clear();
		fs1 >> left >> top >> right >> bottom;

		RECT rect;
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;

		this->InitStaticObjects(rect, ladders);

		for (int i = 0; i < ladders->size(); i++) {
			RECT rect = ladders->at(i);
			Ladder * brick = new Ladder(rect.left, rect.top, rect.right, rect.bottom);
			this->objects->push_back(brick);
		}
	}

	fs1.close();

	fstream fs2(PATH_POS_HIDE_SATGE_2);

	fs2 >> numberOfGround;
	int type;

	vector<RECT>* hides = new vector<RECT>();
	for (int i = 0; i < numberOfGround; i++) {
		hides->clear();
		fs2 >> type;
		fs2 >> left >> top >> right >> bottom;

		RECT rect;
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;

		this->InitStaticObjects(rect, hides);

		switch (type)
		{
		case 0:
			for (int i = 0; i < hides->size(); i++) {
				RECT rect = hides->at(i);
				HideObject* brick = new HideObject(rect.left, rect.top, rect.right, rect.bottom,TOP_LADDER);
				this->objects->push_back(brick);
			}
			break;
		case 1:
			for (int i = 0; i < hides->size(); i++) {
				RECT rect = hides->at(i);
				HideObject* brick = new HideObject(rect.left, rect.top, rect.right, rect.bottom, BOTTOM_LADDER);
				this->objects->push_back(brick);
			}
			break;
		case 2:
			for (int i = 0; i < hides->size(); i++) {
				RECT rect = hides->at(i);
				HideObject* brick = new HideObject(rect.left, rect.top, rect.right, rect.bottom, END_MAP);
				this->objects->push_back(brick);
			}
			break;

		default:
			break;
		}
	}

	fs2.close();
	this->InitEnemies(PATH_POS_ENEMIES_MAP_2);
	

	for (int i = 0; i < this->objects->size(); i++) {
		Grid::GetInstance()->Add(this->objects->at(i));
	}

	delete bricks;
	delete ladders;
}

void Stage2::Update(float deltaTime)
{

	Stage::Update(deltaTime);

	if (MainCharacter::GetInstance()->GetIsInTheEndOfMap())
	{
		MainCharacter::GetInstance()->SetState(STATE_IDLE);
		fadeOut = true;
	}
	for (int i = 0; i < this->objects->size(); i++)
	{
		if (this->objects->at(i)->GetObjectType() == CROW)
		{
			if (this->objects->at(i)->GetHP() <= 0)
			{
				if (this->objects->at(i + 1)->GetObjectType() == ITEM && this->objects->at(i + 1)->GetActive() == false &&
					this->objects->at(i + 1)->GetPosition() == this->objects->at(i)->GetPosition())
				{
					this->objects->at(i + 1)->SetActive(true);
				}
			}
		}
	}
}

void Stage2::Render()
{
	Stage::Render();
	if (fadeIn)
	{
		FadeInEffect();
	}
	if (fadeOut)
		FadeOutEffect();

}

void Stage2::FadeInEffect()
{
	if (alpha >= 200)
	{
		if (GetTickCount() - TimeToFade > 20)
		{
			Game::GetInstance()->Draw(0, 80, Texture::GetInstance()->Get(ID_TEXTURE_BLACK), 0, 80, 256, 320, alpha);
			TimeToFade = GetTickCount();
			alpha -= 1;
		}
		GameSound::GetInstance()->Loopsound(soundS2);
	}
	else
	{
		fadeIn = false;
		TimeToFade = GetTickCount();
	}
}

void Stage2::FadeOutEffect()
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

		if (MainCharacter::GetInstance()->GetIsInTheEndOfMap())
		{
			Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));
			GameSound::GetInstance()->Stopsound(soundS2);
			ProcessGame::GetInstance(NULL, 0)->SetGameStage(STAGE3);
			Game::GetInstance()->SetGameStage(STAGE3);
		}
		else if (MainCharacter::GetInstance()->GetRepawn())
		{
			MainCharacter::GetInstance()->LoseLive();
			MainCharacter::GetInstance()->SetPosition(50, 80);
			MainCharacter::GetInstance()->SetHP(16);
			MainCharacter::GetInstance()->SetRepawn(false);
		}
		else if (MainCharacter::GetInstance()->GetLives() < 0)
		{
			Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));
			GameSound::GetInstance()->Stopsound(soundS2);
			ProcessGame::GetInstance(NULL, 0)->SetGameStage(END_STAGE);
		}
	}
	/*if (alpha < 255)
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
		MainCharacter::GetInstance()->SetPosition(50, 120);
		Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));
		ProcessGame::GetInstance(NULL, 0)->SetGameStage(STAGE3);
	}*/
}
