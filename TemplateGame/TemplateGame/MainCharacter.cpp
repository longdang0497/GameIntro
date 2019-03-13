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
	this->SetState(STAND_RIGHT);
	this->objectWidth = 32;
	this->objectHeight = 64;

	this->curPos->SetPosX(8 * 32);
	this->curPos->SetPosY(10);
	this->curVec->SetVx(0);
	this->curVec->SetVy(30.0f);
}

MainCharacter::~MainCharacter()
{
	delete(this->standSprite);
	delete(this->runSprite);
}

// Khởi tạo Sprite với texture có sẵn (texture ở đây là một hình chứa tất cả các sprite ở trong đó)
void MainCharacter::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if(d3ddv == NULL) return;

	this->standSprite = new Sprite(this->spriteHandler, texture, MAIN_STAND_PATH, MAIN_STAND_COUNT, MAIN_STAND_WIDTH, MAIN_STAND_HEIGHT);
	this->runSprite = new Sprite(this->spriteHandler, texture, MAIN_RUN_PATH, MAIN_RUN_COUNT, MAIN_RUN_WIDTH, MAIN_RUN_HEIGHT);
}

// Khởi tạo vị trí ban đầu cho main
void MainCharacter::InitPostition()
{
	this->curPos->SetPosX(8*32);
	this->curPos->SetPosY(10);
	this->curVec->SetVx(0);
	this->curVec->SetVy(10.0f);
	this->lastVec->SetVx(1.0f);
}

void MainCharacter::ResetAllSprites()
{
	this->standSprite->Reset();
	this->runSprite->Reset();
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

void MainCharacter::Update(float t, vector<Object*> *collisionObjects)
{

	Object::Update(t);

	// Gỉa bộ rơi xuống
	this->curVec->SetVy(this->curVec->GetVy() + 20.0f * t);
	
	vector<CollisionEvent *> *coEvents = new vector<CollisionEvent*>();
	vector<CollisionEvent*> *coEventsResult = new vector<CollisionEvent*>();

	coEvents->clear();

	this->CalcPotentialCollisions(collisionObjects, coEvents);

	if (coEvents->size() == 0) {
		this->curPos->Add(this->deltaPosX, this->deltaPosY);
	}
	else {
		float minTx, minTy, nx = 0, ny;
		this->FilterCollision(coEvents, coEventsResult, minTx, minTy, nx, ny);

		this->curPos->Add(minTx*this->deltaPosX + nx * 0.4f, minTy*this->deltaPosY + ny * 0.4f);

		if (nx != 0) this->curVec->SetVx(0);
		if (ny != 0)  this->curVec->SetVy(0);

	}

	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	DWORD now = GetTickCount();
	if (now - lastTime > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case STAND_RIGHT: case STAND_LEFT:
			this->standSprite->UpdateSprite();
			break;
		case RUN_RIGHT: case RUN_LEFT:
			this->runSprite->UpdateSprite();
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
			this->standSprite->DrawSprite(position, true);
			break;
		case STAND_LEFT:
			this->standSprite->DrawSprite(position, false);
			break;
		case RUN_RIGHT:
			this->runSprite->DrawSprite(position, true);
			break;
		case RUN_LEFT:
			this->runSprite->DrawSprite(position, false);
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
