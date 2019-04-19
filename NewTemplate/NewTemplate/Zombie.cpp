#include "Zombie.h"

Zombie::Zombie()
{
	this->WalkSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_WALK);
	this->KillSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_KILL);
	this->SetObjectType(ZOMBIE);
	this->HP = 1;
	this->spriteDirection = direction;
	direction = LEFT;
	currentSprite = WalkSprite;
	state = ZombieWalk;
	LimitX1 = LimitX2 = 0;
}

Zombie::~Zombie()
{
	if (this->WalkSprite != NULL) delete this->WalkSprite;
	if (this->KillSprite != NULL) delete this->KillSprite;
}

Zombie::Zombie(D3DXVECTOR3 pos, int direction)
{
	this->WalkSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_WALK);
	this->KillSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_KILL);
	this->SetObjectType(ZOMBIE);
	this->HP = 1;
	direction = LEFT;
	currentSprite = WalkSprite;
	state = ZombieWalk;
	LimitX1 = LimitX2 = 0;
	this->position = pos;
	this->direction = direction;
	this->spriteDirection = direction;

}

Zombie::Zombie(D3DXVECTOR3 pos, int direction, int LimitX1, int LimitX2)
{
	this->WalkSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_WALK);
	this->KillSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_ZOMBIES_KILL);
	this->SetObjectType(ZOMBIE);
	this->HP = 1;
	direction = LEFT;
	currentSprite = WalkSprite;
	state = ZombieWalk;
	this->position = pos;
	this->direction = direction;
	this->LimitX1 = LimitX1;
	this->LimitX2 = LimitX2;
	this->spriteDirection = direction;
}

void Zombie::Update(float deltaTime, vector<Object*>* object)
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
		this->veclocity.x = 0.15*direction;

	}
	else
		this->veclocity.x = 0;


	if (abs(MainCharacter::GetInstance()->GetPosition().x - this->position.x) <= 100)
	{
		if (state != ZombieKill)
		{
			state = ZombieKill;
			currentSprite = KillSprite;
		}
	}
	else
	{
		state = ZombieWalk;
		currentSprite = WalkSprite;
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

void Zombie::Render()
{
	if (HP <= 0)
		return;

	Object::Render();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (this->spriteDirection == RIGHT)
		this->currentSprite->DrawSprite(pos, true);
	else
		this->currentSprite->DrawSprite(pos, false);
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



void Zombie::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	if (HP > 0)
	{
		switch (state)
		{
		case ZombieWalk:
			l = position.x;
			t = position.y;
			break;
		case ZombieKill:
			l = position.x;
			t = position.y;

			break;
		default:
			break;
		}

		r = l + currentSprite->GetWidth();
		b = t + 43;
	}
	else l = r = b = t = 0;
}


