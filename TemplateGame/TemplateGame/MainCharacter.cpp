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
}

// Khởi tạo Sprite với texture có sẵn (texture ở đây là một hình chứa tất cả các sprite ở trong đó)
//void MainCharacter::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
//{
//	if(d3ddv == NULL) return;
//
//	//this->standSprite = new Sprite(this->spriteHandler, texture, MAIN_STAND_PATH, MAIN_STAND_COUNT, MAIN_STAND_WIDTH, MAIN_STAND_HEIGHT);
//	//this->runSprite = new Sprite(this->spriteHandler, texture, MAIN_RUN_PATH, MAIN_RUN_COUNT, MAIN_RUN_WIDTH, MAIN_RUN_HEIGHT);
//}

// Khởi tạo vị trí ban đầu cho main
void MainCharacter::InitPostition()
{
	this->curPos->SetPosX(50);
	this->curPos->SetPosY(50);
	this->curVec->SetVx(0);
	this->curVec->SetVy(0);
	this->lastVec->SetVx(1.0f);
}

bool MainCharacter::GetStateActive()
{
	return false;
}

void MainCharacter::Reset(float x, float y)
{
	// Cho samus active trở lại
	this->isActive = true;

	// Đặt vị trí trước đó
	this->lastPos->SetPosX(this->curPos->GetPosX());
	this->lastPos->SetPosY(this->curPos->GetPosY());

	//Đặt lại vị trí
	this->curPos->SetPosX(x);
	this->curPos->SetPosY(y);
}

void MainCharacter::Update(float t)
{
	this->curPos->SetPosX(this->curPos->GetPosX() + this->curVec->GetVx() * t);
	this->curPos->SetPosY(this->curPos->GetPosY() + this->curVec->GetVy() * t);

	DWORD now = GetTickCount();
	if (now - lastTime > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case STAND_RIGHT: case STAND_LEFT:
			//this->standSprite->UpdateSprite();
			break;
		case RUN_RIGHT: case RUN_LEFT:
			//this->runSprite->UpdateSprite();
			break;
		}
		lastTime = now;
	}
}

// cái render này là render sprite lên nè
// Sprite nào quay qua phải thì tham số truyền vào là true
// Ngược lại là false
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
			this->animations[0]->Render(position);
			break;
		case STAND_LEFT:
			//this->standSprite->DrawSprite(position, false);
			break;
		case RUN_RIGHT:
			//this->runSprite->DrawSprite(position, true);
			break;
		case RUN_LEFT:
			//this->runSprite->DrawSprite(position, false);
			break;
		}

	}
}

void MainCharacter::Destroy()
{
	//Ngưng active
	this->isActive = false;
}

MAIN_CHARACTER_STATE MainCharacter::GetState()
{
	return this->state;
}

void MainCharacter::SetState(MAIN_CHARACTER_STATE value)
{
	this->state = value;
}

bool MainCharacter::handleCollision(Object * otherObject)
{
	return isCollided;
}
