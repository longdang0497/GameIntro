﻿#include "GreenSodier.h"

GreenSodier::GreenSodier(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2, int state) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->HP = 1;
	this->SetObjectType(GREEN_SOLDIER);
	this->isActive = false;
	this->state = state;
	if (this->state == 0) // GREEN SOLDIER CHẠY
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_GREEN_SOLDIERS_WALK);
	else if (this->state == 1) // GREEN SOLDIER BẮN
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_GREEN_SOLDIERS_SHOOT);
}

GreenSodier::~GreenSodier()
{
	if (this->currentSprite != nullptr) {
		delete(currentSprite);
		currentSprite = NULL;
	}
}

void GreenSodier::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (this->HP <= 0 && limitX1 == limitX2) 
		return;
	
	if (this->position.y >= Graphic::GetInstance(NULL, NULL, L"", 1)->GetHeight()) {
		this->Destroy();
		return;
	}

	// Xét theo camera bên phải
	if (this->enemyAppearanceDirection == 1) {
		int temp = Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 1)->GetWidth();
		if (temp - this->position.x <= 3.0 && temp - this->position.x >= 0.0) {
			this->isActive = true;
			this->direction = -1;
		}
	}
	// Xét theo camera bên trái
	else {
		/*if (Camera::GetInstance()->getPosition().x - this->position.x <= 3.0 && Camera::GetInstance()->getPosition().x - this->position.x >= 0.0) {
			this->isActive = true;
			this->direction = 1;
		}*/
	}

	if (!this->isActive) return;

	Object::Update(deltaTime, objects);

	this->veclocity.y += 0.0018f * deltaTime;

	if (isOnGround) {
		this->veclocity.x = 0.05 * direction;
		this->currentSprite->UpdateSprite();
	}

	vector<Object*> *ground = new vector<Object*>();
	ground->clear();

	for (auto iter : *objects) {
		if (iter->GetObjectType() == BRICK) {
			ground->push_back(iter);
		}
	}

	this->HandleCollision(ground);

	delete ground;
}

void GreenSodier::Render()
{
	if (!this->isActive) {
		return;
	}

	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT) {
		this->currentSprite->DrawSprite(pos, true);
	}
	else {
		this->currentSprite->DrawSprite(pos, false);
	}
}

void GreenSodier::HandleCollision(vector<Object*>* objects)
{
	vector<CollisionEvent*> *coEvents = new vector<CollisionEvent*>();
	vector<CollisionEvent*> *coEventsResult = new vector<CollisionEvent*>();

	coEvents->clear();

	this->CalcPotentialCollisions(objects, coEvents);

	if (coEvents->size() == 0) {
		this->PlusPosition(this->deltaX, this->deltaY);
		isOnGround = false;
	}
	else {

		float minTx, minTy, nX = 0, nY;

		this->FilterCollision(coEvents, coEventsResult, minTx, minTy, nX, nY);

		if (nY == 1)
			this->PlusPosition(minTx * this->deltaX + nX * 0.1f, this->deltaY);
		else
			this->PlusPosition(minTx * this->deltaX + nX * 0.1f, minTy * this->deltaY + nY * 0.1f);

		if (nX != 0)
			this->veclocity.x = 0;
		if (nY != 0)
		{
			if (nY == -1)
			{
				this->veclocity.y = 0;
				isOnGround = true;
			}
		}
	}

	for (int i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void GreenSodier::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (HP > 0)
	{
		this->objectWidth = currentSprite->GetWidth();
		this->objectHeight = currentSprite->GetHeight();
		l = position.x;
		t = position.y;
		r = l + objectWidth;
		b = t + objectHeight;
	}
	else l = r = b = t = 0;
}

void GreenSodier::Destroy()
{
	this->position = defaultPosition;
	this->position.y -= 2;
	this->HP = 1;
	this->isActive = false;
}
