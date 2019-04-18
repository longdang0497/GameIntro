#include "Sword.h"

Sword* Sword::_instance = NULL;

Sword::Sword()
{
	isActive = false;
	direction = RIGHT;
	swordSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_SWORD);
	objectType = SWORD;
	currentSprite = swordSprite;
}
void Sword::HandleCollision(vector<Object*> *objects)
{
	for (auto iter : *objects)
	{
		// normal intersect colision
		switch (iter->GetObjectType())
		{
		case JAGUAR:
		case SOLDIER:
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);
			if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				iter->Hurt();
			}
			break;
		}
		default:
			break;
		}
	}

	// sweptAABB colision
	vector<CollisionEvent*> *coEvents = new vector<CollisionEvent*>();
	coEvents->clear();

	CalcPotentialCollisions(objects, coEvents);

	for (auto iter : *coEvents)
	{
		switch (iter->obj->GetObjectType())
		{
		case JAGUAR:
		case SOLDIER:
			iter->obj->Hurt();
			break;
		default:
			break;
		}
	}
	for (auto iter : *coEvents) delete iter;
	coEvents->clear();
}

Sword::~Sword()
{

}

void Sword::Update(float t, vector<Object*> *object)
{
	//position = MainCharacter::GetInstance()->GetPosition();
	if (isActive)
		currentSprite->UpdateSprite();
	if (isActive && currentSprite->getDone())
	{
		isActive = false;
		currentSprite->setDone(false);
	}

	HandleCollision(object);
}


void Sword::Render()
{
	//RenderBoundingBox();
	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (isActive)
	{

		if (direction == RIGHT)
		{
			currentSprite->DrawSprite(pos, true);
		}
		else
		{
			currentSprite->DrawSprite(pos, false);
		}

	}
}

void Sword::CalCulatePosition()
{

}

void Sword::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (isActive)
	{
		switch (currentSprite->GetIndex())
		{
		case 0:
			l = position.x;
			t = position.y;
			b = t;
			r = l;
			break;
		case 1:
			l = position.x;
			t = position.y + 5;
			b = t + 10;
			r = l + 27;
			break;
		case 2:
			if (direction == RIGHT)
				l = position.x;
			else
				l = position.x + 16;
			t = position.y;
			b = t + 5;
			r = l + 9;
			break;
		}
	}
	else
	{
		l = position.x;
		t = position.y;
		b = t;
		r = l;
	}
}

void Sword::checkCollisioWithEnemy(vector<Object*> *coObjects)
{

}