#include "IntroStage.h"


IntroStage* IntroStage::_instance = NULL;

IntroStage::IntroStage()
{
	this->LoadResource();
}


IntroStage::~IntroStage()
{
}

void IntroStage::LoadResource()
{
	//Stage::Update(deltaTime);
}


void IntroStage::Update(float deltaTime)
{
	CKeyGame* k = CKeyGame::getInstance();
	if (k->keyChangeScene)
		this->NextStage();
	//Stage::Update(deltaTime);
}



void IntroStage::Render()
{
	//Stage::Render();
	text = Text::GetInstance();
	text->DrawString("PRESS ENTER TO PLAY GAME", D3DXVECTOR2(25, 120), 0);
	text->DrawString("PRESENT BY LONG-TUNG-ANH", D3DXVECTOR2(25, 200));
}

void IntroStage::NextStage()
{
	//StageController::GetInstance()->ChangeStage(Stage1::GetInstance());
	ProcessGame::GetInstance(NULL,0)->SetGameStage(STAGE1);
	Game::GetInstance()->SetGameStage(STAGE1);
}
