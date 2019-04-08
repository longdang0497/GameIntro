#include "MainCharacter.h"

MainCharacter* MainCharacter::_instance = NULL;

MainCharacter::MainCharacter()
{
	this->SetObjectType(MAIN_CHARACTER);
	this->SetState(STAND_RIGHT);

	this->objectWidth = 20;
	this->objectHeight = 31;

	this->SetPosition(10, 10);
	this->SetVeclocity(0, 0);

	this->standSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_STAND);
	this->runSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_RUN);
	this->sitSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_SIT);
	this->jumpScrollSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_JUMP_SCROLL);
}


MainCharacter::~MainCharacter()
{
	if (this->standSprite != NULL) delete this->standSprite;
	if (this->runSprite != NULL) delete this->runSprite;
	if (this->sitSprite != NULL) delete this->sitSprite;
	if (this->jumpScrollSprite != NULL) delete this->jumpScrollSprite;
}


MAIN_CHARACTER_STATE MainCharacter::GetState()
{
	return this->state;
}

void MainCharacter::SetState(MAIN_CHARACTER_STATE value)
{
	this->state = value;
}

void MainCharacter::ResetAllSprites()
{
	this->standSprite->Reset();
	this->runSprite->Reset();
	this->sitSprite->Reset();
	this->jumpScrollSprite->Reset();
}

bool MainCharacter::GetStateActive()
{
	return this->isActive;
}

void MainCharacter::Reset(float x, float y)
{
	this->isActive = true;
	this->SetLastPos(this->GetPosition());
	this->SetPosition(x, y);
}

void MainCharacter::Update(float t, vector<Object*>* object)
{
	
	Object::Update(t);

	// simple fall down
	this->veclocity.y += 0.0002*t;

	vector<CollisionEvent*> *coEvents = new vector<CollisionEvent*>();
	vector<CollisionEvent*> *coEventsResult = new vector<CollisionEvent*>();

	coEvents->clear();

	if (this->veclocity.y > 0 && this->deltaY > 0)
		int i = 0;

	this->CalcPotentialCollisions(object, coEvents);

	if (this->position.x > 544)
		int i = 0;

	if (coEvents->size() == 0) {
		this->PlusPosition(this->deltaX, this->deltaY);
	}
	else {
		float minTx, minTy, nX = 0, nY;

		this->FilterCollision(coEvents, coEventsResult, minTx, minTy, nX, nY);

		this->PlusPosition(minTx*this->deltaX + nX * 0.4f, minTy*this->deltaY + nY * 0.4f);

		if (nX != 0) this->veclocity.x = 0;
		if (nY != 0) this->veclocity.y = 0;
	}

	for (int i = 0; i < coEvents->size(); i++)
		delete coEvents->at(i);
	delete coEvents;

	delete coEventsResult;

	switch (this->state) {
	case STAND_RIGHT: case STAND_LEFT:
		this->standSprite->UpdateSprite();
		break;
	case RUN_RIGHT: case RUN_LEFT: 
		this->runSprite->UpdateSprite();
		break;
	case SIT_RIGHT: case SIT_LEFT:
		this->sitSprite->UpdateSprite();
	default:break;
	}
}

void MainCharacter::Render()
{

	this->position.z = 0;

	switch (this->state) {
	case STAND_RIGHT:
		this->standSprite->DrawSprite(this->position, true);
		break;

	case STAND_LEFT:
		this->standSprite->DrawSprite(this->position, false);
		break;
	case RUN_RIGHT:
		this->runSprite->DrawSprite(this->position, true);
		break;
	case RUN_LEFT:
		this->runSprite->DrawSprite(this->position, false);
		break;
	case SIT_RIGHT:
		this->sitSprite->DrawSprite(this->position, true);
		break;
	case SIT_LEFT:
		this->sitSprite->DrawSprite(this->position, false);
		break;
	case JUMP_SCROLL_RIGHT:
		this->jumpScrollSprite->DrawSprite(this->position, true);
		break;
	case JUMP_SCROLL_LEFT:
		this->jumpScrollSprite->DrawSprite(this->position, false);
		break;
	default:break;
	}
}

