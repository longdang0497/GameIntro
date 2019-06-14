#include "Soldier.h"

Soldier::Soldier(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->SoldierWalk = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIERS_WALK);
	this->SoldierKill = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIERS_KILL);
	this->HP = 1;
	this->SetObjectType(SOLDIER);
	if (appearanceDirection == 0)
		direction = LEFT;
	else
		direction = RIGHT;
	this->isActive = true;
	currentSprite = SoldierWalk;
}

void Soldier::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (HP <= 0)
		return;
	if (MainCharacter::GetInstance()->IsStopWatch())
		return;
	

	if (limitX1 != 0 && limitX2 != 0)

	{
		if (position.x >= limitX2 && direction == RIGHT)
		{
			direction = LEFT;
		}

		if (position.x <= limitX1 && direction == LEFT)
		{
			direction = RIGHT;
		}
	}
	/*else if (limitX1 == 0 && limitX2 == 0)
		this->veclocity.x = 0;*/

	int t = MainCharacter::GetInstance()->GetPosition().x;

	if (abs(t - position.x) <= 100)
	{
		currentSprite = SoldierKill;
	}
	else
	{
		currentSprite = SoldierWalk;
	}

	Object::Update(deltaTime, objects);

	this->veclocity.y += 0.0015f*deltaTime;

	if (isOnGround) {
		this->veclocity.x = 0.015*direction;
		this->currentSprite->UpdateSprite();
	}

	vector<Object*> *ground = new vector<Object*>();
	ground->clear();

	for (auto iter : *objects) {
		if (iter->GetObjectType() == BRICK) 
		{
			ground->push_back(iter);
		}
	}

	this->HandleCollision(ground);

	delete ground;
}

void Soldier::Render()
{
	if (!this->isActive || this->HP <= 0) {
		return;
	}

	this->position.z = 0;
	Object::Render();

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT) {
		this->currentSprite->DrawSprite(pos, true);
	}
	else {
		this->currentSprite->DrawSprite(pos, false);
	}
}

void Soldier::HandleCollision(vector<Object*>* objects)
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

		
		for (auto iter : *coEventsResult) {
			if (iter->obj->GetObjectType() == BRICK)
			{
				if (nX != 0)
				{
					if (direction == LEFT && nX == 1)
						direction = RIGHT;
					if (direction == RIGHT && nX == -1)
						direction = LEFT;
				}
				if (nY != 0)
					this->veclocity.y = 0;
				if (nY == -1)
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

void Soldier::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (HP > 0)
	{
		l = position.x;
		t = position.y;
		r = l + 24;
		b = t + 40;
	}
	else l = r = b = t = 0;
}

void Soldier::Destroy()
{
}
