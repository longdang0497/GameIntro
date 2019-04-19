#include "Jaguar.h"

Jaguar::Jaguar()
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);
	this->SetObjectType(JAGUAR);
	this->HP = 1;
	this->objectWidth = jaguar->GetWidth();
	this->objectHeight = jaguar->GetHeight();
	MainPos1 = MainPos2 = 0;
}

Jaguar::~Jaguar()
{
	if (this->jaguar != NULL) delete this->jaguar;
}

Jaguar::Jaguar(D3DXVECTOR3 pos, int direction, int MainPos1, int MainPos2)
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);
	this->SetObjectType(JAGUAR);
	this->HP = 0;
	this->position = pos;
	this->direction = direction;
	this->defaultPosition = pos;
	this->MainPos1 = MainPos1;
	this->MainPos2 = MainPos2;
}

Jaguar::Jaguar(D3DXVECTOR3 pos, int direction)
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);
	this->SetObjectType(JAGUAR);
	this->HP = 1;
	this->position = pos;
	this->direction = direction;
	MainPos1 = MainPos2 = 0;
}

void Jaguar::Update(float deltaTime, vector<Object*>* object)
{
	if (HP <= 0 && MainPos1 == MainPos2)
		return;

	if (MainCharacter::GetInstance()->GetPosition().x >= MainPos1 &&
		MainCharacter::GetInstance()->GetPosition().x <= MainPos2 &&
		HP == 0)
	{
		HP = 1;
		this->position = defaultPosition;
	}


	Object::Update(deltaTime, object);

	this->veclocity.y += 0.0015f*deltaTime;
	if (isOnGround)
	{
		this->veclocity.x = 0.15*direction;
		this->jaguar->UpdateSprite();
	}
	else
		this->veclocity.x = 0;

	vector<Object*> *ground = new vector<Object*>();
	ground->clear();

	for (auto iter : *object)
	{
		if (iter->GetObjectType() == BRICK)
			ground->push_back(iter);
	}



	this->HandleCollision(ground);
}

void Jaguar::Render()
{
	if (HP <= 0)
		return;

	Object::Render();

	//RenderBoundingBox();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT)
		this->jaguar->DrawSprite(pos, true);
	else
		this->jaguar->DrawSprite(pos, false);
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

void Jaguar::GetBoundingBox(float &l, float &t, float &r, float &b)
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

