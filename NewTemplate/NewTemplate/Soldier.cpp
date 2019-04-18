#include "Soldier.h"

//Soldier* Soldier::_instance = NULL;

Soldier::Soldier()
{
	this->walk = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIER_WALK);
	this->kill = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIER_KILL);

	this->SetObjectType(SOLDIER);
	this->HP = 1;
	this->currentSprite = kill;
}

Soldier::Soldier(D3DXVECTOR3 position, Direction direction)
{
	this->walk = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIER_WALK);
	this->kill = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_SOLDIER_KILL);
	this->SetObjectType(SOLDIER);
	this->HP = 1;
	this->currentSprite = kill;
	this->position = position;
	this->direction = direction;
}

Soldier::~Soldier()
{
	if (this->kill != NULL) delete this->kill;
	if (this->walk != NULL) delete this->walk;
}

void Soldier::Update(float deltaTime, vector<Object*>* object)
{
	if (HP > 0)
	{

		if (abs(MainCharacter::GetInstance()->GetPosition().x - this->GetPosition().x) < 100)
		{
			if(state != State_Kill)
				SetState(State_Kill);
		}
		else SetState(State_Walk);

		Object::Update(deltaTime, object);

		veclocity.y += 0.0015f*deltaTime;
		veclocity.x = 0.05f*direction;

		currentSprite->UpdateSprite();

		HandleCollision(object);
	}
}
void Soldier::SetState(Soldier_State s)
{ 
	this->state = s; 
	switch (state)
	{
	case State_Walk:
		currentSprite = walk;
		break;
	case State_Kill:
		currentSprite = kill;
		break;
	default:
		break;
	}
}

void Soldier::Render()
{
	if (HP > 0)
	{
		//RenderBoundingBox();
		D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);
		if (direction == 1)
			this->currentSprite->DrawSprite(pos, true);
		else this->currentSprite->DrawSprite(pos, false);
	}



}

void Soldier::HandleCollision(vector<Object*>* objects)
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

void Soldier::CheckCollisionWithGround(vector<Object*>* objects)
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

void Soldier::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (HP > 0)
	{
		this->objectWidth = this->currentSprite->GetWidth();
		l = position.x;
		r = l + objectWidth;

		switch (state)
		{
		case State_Walk:
			t = position.y;
	
			break;
		case State_Kill:
			t = position.y;
			break;
		default:
			break;
		} 
		b = t + 40;
	}
	else l = r = t = b = 0;
}

