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

	for (auto iter : *object)
	{
		switch (iter->GetObjectType())
		{

		case JAGUAR:
		case SOLDIER: case GREEN_SOLDIER:
		case BUTTERFLY: case CROW:
		case ZOMBIE:

		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);
			if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				iter->SetHP(0);
				MainCharacter::GetInstance()->Score();
			}

			break;
		}
		case BOSS_BULLET:
		{
			BossBullet *bossBullet = dynamic_cast<BossBullet*>(iter);
			bossBullet->Destroy();
			OutputDebugString(L"Chạm đạn \n");
			break;
		}
		default:
			break;
		}
	}

	// sweptAABB colision
	vector<CollisionEvent*> *coEvents = new vector<CollisionEvent*>();
	coEvents->clear();

	CalcPotentialCollisions(object, coEvents);

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
