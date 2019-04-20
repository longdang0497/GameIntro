#include "Soldier.h"

Soldier::Soldier()
{
	this->SoldierWalk = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIERS_WALK);
	this->SoldierKill = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIERS_KILL);
	this->SetObjectType(SOLDIER);
	this->HP = 1;

	direction = LEFT;
	currentSprite = SoldierWalk;
	state = Walk;
	LimitX1 = LimitX2 = 0;
}

Soldier::~Soldier()
{
	if (this->SoldierWalk != NULL) delete this->SoldierWalk;
	if (this->SoldierKill != NULL) delete this->SoldierKill;
}

Soldier::Soldier(D3DXVECTOR3 pos, int direction)
{
	this->SoldierWalk = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIERS_WALK);
	this->SoldierKill = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIERS_KILL);
	this->SetObjectType(SOLDIER);
	this->HP = 1;
	this->position = pos;
	this->direction = direction;
	currentSprite = SoldierWalk;
	state = Walk;
	LimitX1 = LimitX2 = 0;
}

Soldier::Soldier(D3DXVECTOR3 pos, int direction, int LimitX1, int LimitX2)
{
	this->SoldierWalk = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIERS_WALK);
	this->SoldierKill = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIERS_KILL);
	this->SetObjectType(SOLDIER);
	this->HP = 1;
	this->position = pos;
	this->direction = direction;
	currentSprite = SoldierWalk;
	state = Walk;
	this->LimitX1 = LimitX1;
	this->LimitX2 = LimitX2;
}

void Soldier::Update(float deltaTime, vector<Object*>* object)
{
	if (HP <= 0)
		return;
	Object::Update(deltaTime, object);

	if (LimitX1 != LimitX2)
	{
		if (LimitX1 >= this->GetPosition().x && direction == LEFT) {
			direction = RIGHT;

		}
		else if (LimitX2 <= this->GetPosition().x && direction == RIGHT) {
			direction = LEFT;
		}
	}

	this->veclocity.y += 0.0015f*deltaTime;

	if (isOnGround)
	{
		this->veclocity.x = 0.05*direction;

	}
	else
		this->veclocity.x = 0;


	if (abs(MainCharacter::GetInstance()->GetPosition().x - this->position.x) <= 50)
	{
		if (state != Kill)
		{
			state = Kill;
			currentSprite = SoldierKill;
		}
	}
	else
	{
		state = Walk;
		currentSprite = SoldierWalk;
	}

	this->currentSprite->UpdateSprite();

	vector<Object*> *ground = new vector<Object*>();
	ground->clear();

	for (auto iter : *object)
	{
		if (iter->GetObjectType() == BRICK)
			ground->push_back(iter);
	}

	this->HandleCollision(ground);
}

void Soldier::Render()
{
	if (HP <= 0)
		return;

	Object::Render();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT)
		this->currentSprite->DrawSprite(pos, true);
	else
		this->currentSprite->DrawSprite(pos, false);
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

		this->PlusPosition(minTx*this->deltaX + nX * 0.4f, minTy*this->deltaY + nY * 0.4f);

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



void Soldier::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	if (HP > 0)
	{
		switch (state)
		{
		case Walk:
			l = position.x ;
			t = position.y +8;
			break;
		case Kill:
			l = position.x;
			t = position.y + 8;

			break;
		default:
			break;
		}

		r = l + currentSprite->GetWidth();
		b = t + 32;
	}
	else l = r = b = t = 0;
}

