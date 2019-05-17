﻿#include "Jaguar.h"

Jaguar::Jaguar(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);
	this->HP = 1;
	this->SetObjectType(JAGUAR);
	this->isActive = false;
}

void Jaguar::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (this->HP <= 0 && limitX1 == limitX2) {
		return;
	}
	
	if (this->position.y >= Graphic::GetInstance(NULL, NULL, L"", 1)->GetHeight()) {
		this->Destroy();
		return;
	}

	// Xét theo camera bên phải
	if (this->enemyAppearanceDirection == 1) {
		/*int temp = Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 1)->GetWidth();
		if (temp - this->position.x <= 3.0 && temp - this->position.x >= 0.0) {
			this->isActive = true;
			this->direction = 0;
		}*/
	}
	// Xét theo camera bên trái
	else {
		if (Camera::GetInstance()->getPosition().x - this->position.x <= 3.0 && Camera::GetInstance()->getPosition().x - this->position.x >= 0.0) {
			this->isActive = true;
			this->direction = 1;
		}
	}

	if (!this->isActive) return;

	if (this->enemyAppearanceDirection == 0 && this->position.x < Camera::GetInstance()->getPosition().x - 3.0
		|| this->position.x > Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 1)->GetWidth()) {
		this->Destroy();
		return;
	}

	Object::Update(deltaTime, objects);

	this->veclocity.y += 0.0015f*deltaTime;

	if (isOnGround) {
		if (this->direction == 1)
			this->veclocity.x = 0.18*direction;
		else
			this->veclocity.x = -0.18*direction;
		this->jaguar->UpdateSprite();
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

void Jaguar::Render()
{

	if (!this->isActive) {
		return;
	}

	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT) {
		this->jaguar->DrawSprite(pos, true);
	}
	else {
		this->jaguar->DrawSprite(pos, false);
	}
}

void Jaguar::HandleCollision(vector<Object*>* objects)
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

		this->PlusPosition(minTx*this->deltaX + nX * 0.1f, minTy*this->deltaY + nY * 0.1f);

		if (nX != 0)
			this->veclocity.x = 0;
		if (nY != 0)
			this->veclocity.y = 0;
		if (nY == -1)
			isOnGround = true;

	}

	for (int i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void Jaguar::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (HP > 0)
	{
		this->objectWidth = jaguar->GetWidth();
		this->objectHeight = jaguar->GetHeight();
		l = position.x;
		t = position.y;
		r = l + objectWidth;
		b = t + objectHeight;
	}
	else l = r = b = t = 0;
}

void Jaguar::Destroy()
{
	this->position = defaultPosition;
	this->position.y -= 2;
	this->HP = 1;
	this->isActive = false;
}
