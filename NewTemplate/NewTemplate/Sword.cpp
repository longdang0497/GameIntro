#include "Sword.h"

Sword* Sword::_instance = NULL;

Sword::Sword()
{
	isActive = false;
	direction = RIGHT;
	swordSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_SWORD);

	currentSprite = swordSprite;
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


	if (!isActive) return;

	vector<Object*> *tempObjs = object;

	for (int i = 0; i < tempObjs->size(); i++)
	{
		switch (tempObjs->at(i)->GetObjectType())
		{

		case JAGUAR:
		case SOLDIER:
		case BUTTERFLY:
		case ZOMBIE:

		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			tempObjs->at(i)->GetBoundingBox(bl, bt, br, bb);
			if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				tempObjs->at(i)->SetHP(0);
				MainCharacter::GetInstance()->Score();
				tempObjs->erase(tempObjs->begin() + i);
			}

			break;
		}
		case BOSS_BULLET:
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			BossBullet *bossBullet = dynamic_cast<BossBullet*>(tempObjs->at(i));
			bossBullet->GetBoundingBox(bl, bt, br, bb);

			if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				bossBullet->Destroy();
				tempObjs->erase(tempObjs->begin() + i);
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

	CalcPotentialCollisions(tempObjs, coEvents);

	for (auto iter : *coEvents)
	{
		switch (iter->obj->GetObjectType())
		{
		case JAGUAR:
		case SOLDIER:
		case BUTTERFLY:
		case ZOMBIE:
			iter->obj->SetHP(0);
			MainCharacter::GetInstance()->Score();
			break;
		default:
			break;
		}
	}
	for (auto iter : *coEvents) delete iter;
	coEvents->clear();

	delete tempObjs;
}
void Sword::Render()
{
	Object::Render();
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

void Sword::HandleCollision(vector<Object*>* objects)
{
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
