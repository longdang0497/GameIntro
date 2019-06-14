#include "Stage1.h"

Stage1* Stage1::_instance = NULL;

Stage1::Stage1()
{
	Grid::GetInstance()->ReSetGrid(STAGE1_HEIGHT, STAGE1_WIDTH, false);
	
	this->LoadResource();

	//Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));

	Camera::GetInstance()->setWorldBoundary(2048);

	SpecialPoint.push_back(0);
	SpecialPoint.push_back(700);
	SpecialPoint.push_back(1880);

	alpha = 255;
	fadeIn = true;
	fadeOut = false;
	TimeToFade = GetTickCount();

	D3DXVECTOR3 a = MainCharacter::GetInstance()->GetPosition();
}

Stage1::~Stage1()
{
}

void Stage1::LoadResource()
{
	this->objects->clear();
	MainCharacter::GetInstance()->SetPosition(30.0f,186.8f);
	bool soundInit = GameSound::GetInstance()->Init(this->window_handler);
	if (soundInit == false)
		return;
	else
		soundS1 = GameSound::GetInstance()->LoadSound(STAGE1_SOUND);

	this->objects->push_back(MainCharacter::GetInstance());

	this->map = new Map(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);

	fstream fs(PATH_POS_GROUND_MAP_1);

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

	fstream fs2(PATH_POS_HIDE_SATGE_1);

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
				HideObject* brick = new HideObject(rect.left, rect.top, rect.right, rect.bottom, TOP_LADDER);
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


	this->InitEnemies(PATH_POS_ENEMIES_MAP_1);

	 /*Enemy* e = new Bat({ 100, 100,0 }, 0, 0, 0);
	 this->objects->push_back(e);*/

	//Enemy* e = new Eagle({ 300, 100, 0.0 }, 1, 50, 70);
	//this->objects->push_back(e);

	for (int i = 0; i < this->objects->size(); i++) {
		Grid::GetInstance()->Add(this->objects->at(i));
	}

	delete bricks;
	//MainCharacter::GetInstance()->SetPosition(1270, 0);



}

void Stage1::Update(float deltaTime)
{
	Stage::Update(deltaTime);

	if (MainCharacter::GetInstance()->GetIsInTheEndOfMap())
	{
		MainCharacter::GetInstance()->SetState(STATE_IDLE);
		fadeOut = true;
	}
	for (int i = 0; i < this->objects->size(); i++)
	{
		if (this->objects->at(i)->GetObjectType() == BUTTERFLY)
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

void Stage1::Render()
{
	Stage::Render();
	if (fadeIn)
		FadeInEffect();
	if(fadeOut)
		FadeOutEffect();
}

void Stage1::FadeInEffect()
{
	if (alpha >= 200)
	{
		if (GetTickCount() - TimeToFade > 20)
		{
			Game::GetInstance()->Draw(0, 80, Texture::GetInstance()->Get(ID_TEXTURE_BLACK), 0, 80, 256, 320, alpha);
			TimeToFade = GetTickCount();
			alpha -= 1;
		}
		GameSound::GetInstance()->Loopsound(soundS1);
	}
	else
	{
		fadeIn = false;
		TimeToFade = GetTickCount();
	}
}

void Stage1::FadeOutEffect()
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
			GameSound::GetInstance()->Stopsound(soundS1);
			ProcessGame::GetInstance(NULL, 0)->SetGameStage(STAGE2);
			Game::GetInstance()->SetGameStage(STAGE2);
			
		}
		else if (MainCharacter::GetInstance()->GetRepawn())
		{
			MainCharacter::GetInstance()->LoseLive();
			MainCharacter::GetInstance()->SetPosition(50, 80);
			MainCharacter::GetInstance()->SetHP(16);
			this->ResetEnemyPosition();
			MainCharacter::GetInstance()->SetRepawn(false);
		}
		else if (MainCharacter::GetInstance()->GetLives() < 0)
		{
			Camera::GetInstance()->setPosition(D3DXVECTOR2(0, 0));
			GameSound::GetInstance()->Stopsound(soundS1);
			ProcessGame::GetInstance(NULL, 0)->SetGameStage(END_STAGE);
		}
	}
}
