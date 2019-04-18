#include "Jaguar.h"

//Jaguar* Jaguar::_instance = NULL;

Jaguar::Jaguar()
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);
	this->SetObjectType(JAGUAR);
	this->HP = 1;
}

Jaguar::Jaguar(D3DXVECTOR3 position, Direction direction)
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);
	this->SetObjectType(JAGUAR);
	this->position = position;
	this->direction = direction;
	this->HP = 1;
}

Jaguar::~Jaguar()
{
	if (this->jaguar != NULL) delete this->jaguar;
}

void Jaguar::Update(float deltaTime, vector<Object*>* object)
{

	if (HP > 0)
	{
		Object::Update(deltaTime, object);

		veclocity.y += 0.0015f*deltaTime;
		veclocity.x = 0.1f*direction;

		jaguar->UpdateSprite();

		HandleCollision(object);
	}


}

void Jaguar::Render()
{
	if (HP > 0)
	{
		//RenderBoundingBox();
		D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);
		if (direction == 1)
			this->jaguar->DrawSprite(pos, true);
		else this->jaguar->DrawSprite(pos, false);
	}



}

void Jaguar::HandleCollision(vector<Object*>* objects)
{
	vector<Object*> *staticObject = new vector<Object*>();
	for (int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->GetObjectType() == BRICK)
		{
			staticObject->push_back(objects->at(i));
		}
	}

	CheckCollisionWithGround(staticObject);

}

void Jaguar::CheckCollisionWithGround(vector<Object*>* objects)
{
	vector<CollisionEvent*> *coEvents = new vector<CollisionEvent*>();
	vector<CollisionEvent*> *coEventsResult = new vector<CollisionEvent*>();

	coEvents->clear();

	this->CalcPotentialCollisions(objects, coEvents);

	if (coEvents->size() == 0) {
		this->PlusPosition(this->deltaX, this->deltaY);
	}
	else {

		float minTx, minTy, nX = 0, nY = 0;

		this->FilterCollision(coEvents, coEventsResult, minTx, minTy, nX, nY);

		this->PlusPosition(minTx*this->deltaX + nX * 0.1f, minTy*this->deltaY + nY * 0.1f);


		if (nX != 0)
			this->veclocity.x = 0;
		if (nY != 0)
			this->veclocity.y = 0;


	}

	for (int i = 0; i < coEvents->size(); i++)
	{
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void Jaguar::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (HP > 0)
	{
		this->objectHeight = this->jaguar->GetHeight();
		this->objectWidth = this->jaguar->GetWidth();
		l = position.x;
		t = position.y;
		r = l + objectWidth;
		b = t + objectHeight;
	}
	else l = r = t = b = 0;
}

