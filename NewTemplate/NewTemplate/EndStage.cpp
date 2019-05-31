#include "EndStage.h"



EndStage* EndStage::_instance = NULL;

EndStage::EndStage()
{
	this->Result = Texture::GetInstance()->Get(ID_RESULT);
	this->LoadResource();
	Score = 0;
	MainScore = MainCharacter::GetInstance()->GetScore();

	Time = 0;
	MainTime = HUD::GetInstance()->GetTime();
	StartCalculate = GetTickCount();
	HUD::GetInstance()->SetStopCounting(true);
}


EndStage::~EndStage()
{
}

void EndStage::LoadResource()
{
	//Stage::Update(deltaTime);
}


void EndStage::Update(float deltaTime)
{
	HUD::GetInstance()->Update(deltaTime);


	if (Score < MainScore)
	{
		if (GetTickCount() - StartCalculate >= 20)
		{
			Score+=2;
			MainCharacter::GetInstance()->SubtractScore(2);
			StartCalculate = GetTickCount();
			
		}
	}
	else

	{


		if (MainTime != 0)
		{
			if (GetTickCount() - StartCalculate >= 20)
			{
				Score += 20;
				HUD::GetInstance()->SubtractTime(1);
				MainTime--;
				StartCalculate = GetTickCount();
			}
		}
	}





	//CKeyGame* k = CKeyGame::getInstance();
	//if (k->keyChangeScene)
	//	this->NextStage();
	//Stage::Update(deltaTime);
}


char* IntToChar1(int value, int len = 10)
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

void EndStage::Render()
{
	//Stage::Render();
	text = Text::GetInstance();
	Game::GetInstance()->Draw(40, 120, Result, 0, 0, 68, 24);
	HUD::GetInstance()->Draw(Camera::GetInstance()->getPosition());

	if (MainCharacter::GetInstance()->GetLives() < 0)
	{
		Game::GetInstance()->Draw(108, 120, Result, 145, 0, 230, 24);
	}
	else
	{
		Game::GetInstance()->Draw(108, 120, Result, 69, 0, 144, 24);
		
	}

	text->DrawString(IntToChar1(Score, 6), { 80,150 });

}

void EndStage::NextStage()
{
	//StageController::GetInstance()->ChangeStage(Stage1::GetInstance());
	ProcessGame::GetInstance(NULL, 0)->SetGameStage(STAGE1);
}

