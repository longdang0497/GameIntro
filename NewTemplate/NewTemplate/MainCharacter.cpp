#include "MainCharacter.h"

MainCharacter* MainCharacter::_instance = NULL;

MainCharacter::MainCharacter()
{
	this->SetObjectType(MAIN_CHARACTER);
	this->SetState(STAND_RIGHT);

	this->objectWidth = DEFAULT_MAIN_WIDTH;
	this->objectHeight = DEFAULT_MAIN_HEIGHT;

	this->SetPosition(200, 100);
	this->SetVeclocity(0, 0);

	this->standSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_STAND, 1, 17, 32);
	this->runSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_POS_MAIN_RUN, 3, 22, 31);
}


MainCharacter::~MainCharacter()
{
	if (this->standSprite != NULL) delete this->standSprite;
	if (this->runSprite != NULL) delete this->runSprite;
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
	this->PlusPosition(this->deltaX, this->deltaY);

	switch (this->state) {
	case STAND_RIGHT: case STAND_LEFT:
		this->standSprite->UpdateSprite();
		break;
	case RUN_RIGHT: case RUN_LEFT: 
		this->runSprite->UpdateSprite();
		break;
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
	default:break;
	}
}

