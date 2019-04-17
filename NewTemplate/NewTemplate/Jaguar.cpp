#include "Jaguar.h"

Jaguar* Jaguar::_instance = NULL;

Jaguar::Jaguar()
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);

	this->SetVeclocity(0, 0);
	this->SetPosition(0, 0);
	this->SetObjectType(JAGUAR);

	this->isActive = false;

	//this->direction = 1;
	this->score = 0;
	this->gravity = 0;
}

Jaguar::~Jaguar()
{
	if (this->jaguar != NULL) delete this->jaguar;
}

void Jaguar::InitJaguarInfo()
{
	this->SetPosition(200, 194);
	this->SetState(JAGUARS_LEFT);
	this->SetVx(0.1f);
}

JAGUARS_STATE Jaguar::GetState()
{
	return this->state;
}

void Jaguar::SetState(JAGUARS_STATE value)
{
	this->state = value;
}

void Jaguar::Update(float deltaTime, vector<Object*>* object)
{
	if (this->isActive == true)
	{
		if (this->GetVeclocity().x <= 0 && this->GetVeclocity().y <= 0
			&& this->GetPosition().x <= 0 && this->GetPosition().y <= 0)
			this->InitJaguarInfo();
		else
		{
			Object::Update(deltaTime);
			if (isOnGround == true)
			{
				if (MainCharacter::GetInstance()->GetVeclocity().x > 0)
					Jaguar::GetInstance()->SetState(JAGUARS_LEFT);
				else if (MainCharacter::GetInstance()->GetVeclocity().x < 0)
					Jaguar::GetInstance()->SetState(JAGUARS_RIGHT);
				else if (MainCharacter::GetInstance()->GetVeclocity().x == 0)
				{
					
				}

				if (MainCharacter::GetInstance()->GetPosition().x <= Jaguar::GetInstance()->GetPosition().x)
					Jaguar::GetInstance()->SetState(JAGUARS_RIGHT);
				else if (MainCharacter::GetInstance()->GetPosition().x >= Jaguar::GetInstance()->GetPosition().x)
					Jaguar::GetInstance()->SetState(JAGUARS_LEFT);

				if (this->GetState() == JAGUARS_LEFT)
					this->PlusPosition(this->GetVeclocity().x * deltaTime, 0);
				else if (this->GetState() == JAGUARS_RIGHT)
					this->PlusPosition(-this->GetVeclocity().x * deltaTime, 0);
			}
			else
			{
				this->PlusPosition(this->GetVeclocity().x * deltaTime, this->GetVeclocity().y * deltaTime);
			}

			this->jaguar->UpdateSprite();
			this->HandleCollision(object);
		}
	}
}

void Jaguar::Render()
{
	/*if (this->position.y < 32)
		return;*/
	if (this->isActive == true)
	{
		RenderBoundingBox();
		this->position.z = 0;

		D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

		switch (this->GetState()) {
		case JAGUARS_LEFT:
			this->jaguar->DrawSprite(pos, true);
			break;
		case JAGUARS_RIGHT:
			this->jaguar->DrawSprite(pos, false);
			break;
		}

		this->objectHeight = this->jaguar->GetHeight();
		this->objectWidth = this->jaguar->GetWidth();
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
	}
	else {

		float minTx, minTy, nX = 0, nY;

		this->FilterCollision(coEvents, coEventsResult, minTx, minTy, nX, nY);

		this->PlusPosition(minTx*this->deltaX + nX * 0.1f, minTy*this->deltaY + nY * 0.1f);

		if (nX != 0)
			this->veclocity.x = 0;
		if (nY != 0)
			this->veclocity.y = 0;

		for (UINT i = 0; i < coEventsResult->size(); i++) {
			CollisionEvent *e = coEventsResult->at(i);

			if (dynamic_cast<Brick*> (e->obj)) {
				Brick* brick = dynamic_cast<Brick*>(e->obj);
				if (nY == -1)
					isOnGround = true;
				this->CheckCollisionWithGround(brick);			
			}
			else if (dynamic_cast<MainCharacter*> (e->obj)) {
				MainCharacter* main = dynamic_cast<MainCharacter*>(e->obj);
				
				this->CheckCollisionWithMain(main);
			}
		}

	}

	for (int i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void Jaguar::CheckCollisionWithGround(Brick * brick)
{
	if (isOnGround == true)
		this->SetVy(0);
	else
	{
		gravity = 0.8f;
		this->SetVy(gravity);
		isOnGround = false;
	}
}

void Jaguar::CheckCollisionWithMain(MainCharacter * main)
{
	this->SetVx(0);
	this->SetVy(0);
}

void Jaguar::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = position.x;
	t = position.y;
	r = l + objectWidth;
	b = t + objectHeight;
}

