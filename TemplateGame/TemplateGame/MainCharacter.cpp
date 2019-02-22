#include "MainCharacter.h"

MainCharacter::MainCharacter()
{
	this->isActive = true;
	this->SetObjectType(MAIN_CHARACTER);
}

MainCharacter::MainCharacter(LPD3DXSPRITE spriteHandler)
{
	this->isActive = true;
	this->SetObjectType(MAIN_CHARACTER);
	this->spriteHandler = spriteHandler;
}

MainCharacter::~MainCharacter()
{
	delete(stand_right);
	delete(stand_left);
	delete(run_right);
	delete(run_left);
}

void MainCharacter::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if(d3ddv == NULL) return;

	stand_right = new Sprite(this->spriteHandler, texture, STANDRIGHT_PATH, 1, STAND_WIDTH, STAND_HEIGHT);
	stand_left = new Sprite(this->spriteHandler, texture, STANDLEFT_PATH, 1, STAND_WIDTH, STAND_HEIGHT);
	run_right = new Sprite(this->spriteHandler, texture, RUNRIGHT_PATH, 3, RUN_WIDTH, RUN_HEIGHT);
	run_left = new Sprite(this->spriteHandler, texture, RUNLEFT_PATH, 3, RUN_WIDTH, RUN_HEIGHT);
}

void MainCharacter::InitPostition()
{
	this->curPos->SetPosX(300);
	this->curPos->SetPosY(300);
	this->curVec->SetVx(0);
	this->curVec->SetVy(0);
	this->lastVec->SetVx(1.0f);
}

MAIN_CHARACTER_MOVEMENT MainCharacter::GetState()
{
	return this->state;
}

void MainCharacter::SetState(MAIN_CHARACTER_MOVEMENT value)
{
	this->state = value;
}

void MainCharacter::ResetAllSprites()
{
	stand_left->Reset();
	stand_right->Reset();
	run_left->Reset();
	run_right->Reset();
}

bool MainCharacter::GetStateActive()
{
	return false;
}

void MainCharacter::Reset(float x, float y)
{
	// Cho samus active trở lại
	this->isActive = true;

	//Đặt lại vị trí
	this->curPos->SetPosX(x);
	this->curPos->SetPosY(y);
}

void MainCharacter::Update(float t)
{
	DWORD now = GetTickCount();
	if (now - lastTime > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case STAND_RIGHT:
			stand_right->UpdateSprite();
			break;
		case STAND_LEFT:
			stand_left->UpdateSprite();
			break;
		case RUN_RIGHT:
			run_right->UpdateSprite();
			break;
		case RUN_LEFT:
			run_left->UpdateSprite();
			break;
		}
		lastTime = now;
	}
}

void MainCharacter::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	else {
		D3DXVECTOR3 position;
		position.x = this->curPos->GetPosX();
		position.y = this->curPos->GetPosY();
		position.z = 0;

		switch (state)
		{
		case STAND_RIGHT:
			stand_right->DrawSprite(position);
			break;
		case STAND_LEFT:
			stand_left->DrawSprite(position);
			break;
		case RUN_RIGHT:
			run_right->DrawSprite(position);
			break;
		case RUN_LEFT:
			run_left->DrawSprite(position);
			break;
		}

	}
}

void MainCharacter::Destroy()
{
	//Ngưng active
	this->isActive = false;
}

bool MainCharacter::handleCollision(Object * otherObject)
{
	return isCollided;
}
