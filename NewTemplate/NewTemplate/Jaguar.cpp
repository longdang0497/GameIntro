#include "Jaguar.h"

Jaguar::Jaguar(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);
	this->HP = 1;
	this->SetObjectType(JAGUAR);
	if(appearanceDirection == 0)
		direction = LEFT;
	else
		direction = RIGHT;
	this->isActive = false;
	WaitTime = GetTickCount();
}

void Jaguar::Update(float deltaTime, std::vector<Object*>* objects)
{

	if (HP <= 0)
		return;

	if (MainCharacter::GetInstance()->IsStopWatch())
		return;

	int t = MainCharacter::GetInstance()->GetPosition().x;

	if (t >= limitX1 &&
		t <= limitX2 &&
		isActive == false
		)
	{
		isActive = true;
		position = defaultPosition;
	}


	if (position.y >=260) {
		isActive = false;
	}

	

	if (!this->isActive)
		return;

	Object::Update(deltaTime, objects);

	this->veclocity.y += 0.0015f*deltaTime;

	if (isOnGround) {
		this->veclocity.x = 0.15*direction;
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

	if (!this->isActive || this->HP<=0) {
		return;
	}
	Object::Render();
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
