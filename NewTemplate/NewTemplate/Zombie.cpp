#include "Zombie.h"

Zombie::Zombie(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->ZombieWalk = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_WALK);
	this->ZombieKill = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_KILL);
	this->HP = 1;
	this->SetObjectType(ZOMBIE);
	if (appearanceDirection == 0)
		direction = LEFT;
	else
		direction = RIGHT;
	this->isActive = true;
	currentSprite = ZombieWalk;

	this->Swords = new vector<ZombieSword*>();
	ZombieSword *S1 = new ZombieSword();
	ZombieSword *S2 = new ZombieSword();
	ZombieSword *S3 = new ZombieSword();

	Swords->push_back(S1);
	Swords->push_back(S2); 
	Swords->push_back(S3);

	WaitTime = GetTickCount();
	Throwing = false;
	count = 0;
}

void Zombie::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (HP <= 0)
		return;

	for (auto iter : *Swords)
	{
		iter->Update(deltaTime,objects);
	}


	if (position.x >= limitX2 && direction == RIGHT)
	{
		direction = LEFT;
		
	}

	if (position.x <= limitX1 && direction == LEFT)
	{
		direction = RIGHT;
	}

	if (GetTickCount() - WaitTime > 1200 && !Throwing && currentSprite == ZombieKill)
	{
		count = 0;
		Throwing = true;
		WaitNext = GetTickCount();
		Throw();
	}

	if (Throwing)
		Throw();

	int t = MainCharacter::GetInstance()->GetPosition().x;

	if (abs(t - position.x) <= 100)
	{
		currentSprite = ZombieKill;
	}
	else
	{
		currentSprite = ZombieWalk;
	}

	Object::Update(deltaTime, objects);

	this->veclocity.y += 0.0015f*deltaTime;

	this->veclocity.x = 0.04*direction;
	this->currentSprite->UpdateSprite();

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

void Zombie::Render()
{
	if (!this->isActive || this->HP <= 0) {
		return;
	}

	for (auto iter : *Swords)
	{
		iter->Render();
	}

	this->position.z = 0;
	Object::Render();

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (enemyAppearanceDirection == RIGHT) {
		this->currentSprite->DrawSprite(pos, true);
	}
	else {
		this->currentSprite->DrawSprite(pos, false);
	}
}

void Zombie::HandleCollision(vector<Object*>* objects)
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
					this->veclocity.x = 0;
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

void Zombie::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (HP > 0)
	{
		l = position.x;
		t = position.y;
		r = l + 24;
		b = t + 43;
	}
	else l = r = b = t = 0;
}

void Zombie::Destroy()
{
}

void Zombie::Throw()
{
	if(count!=3)
	{
		if (GetTickCount() - WaitNext >= 400)
		{
			Swords->at(count)->SetPosition(this->position.x, this->position.y);
			Swords->at(count)->SetVeclocity(0.2*this->direction, -0.09f);
			Swords->at(count)->SetHP(1);
			Swords->at(count)->SetIsActive(true);
			Swords->at(count)->SetDirection(this->direction * -1);
			count++;
			WaitNext = GetTickCount();
		}
	}
	else
	{
		Throwing = false;
		WaitTime = GetTickCount();
		count = 0;
	}
}

vector<ZombieSword*>* Zombie::GetSwords()
{
	return this->Swords;
}