#include "Shuriken.h"

Shuriken* Shuriken::_instance = NULL;

Shuriken::Shuriken()
{
	isActive = false;
	direction = RIGHT;
	ShurikenSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ITEM), PATH_SHURIKEN);
	currentSprite = ShurikenSprite;
	this->veclocity.x = 0;
	this->veclocity.y = 0;
	this->explode = new Explode();
	NumOfChangeDirection = 0;
}


Shuriken::~Shuriken()
{

}

void Shuriken::Update(float t, vector<Object*> *object)
{
	this->explode->Update(deltaTime, object);
	//position = MainCharacter::GetInstance()->GetPosition();


	if (!isActive) 
		return;

	currentSprite->UpdateSprite();

	if (abs(this->position.x - MainCharacter::GetInstance()->GetPosition().x) >= 100)
	{
		if (direction == LEFT)
			direction = RIGHT;
		else direction = LEFT;
		NumOfChangeDirection += 1;
	}
	position.x += 5 * direction;


	if (this->NumOfChangeDirection >= 2 && abs(this->position.x - MainCharacter::GetInstance()->GetPosition().x) <= 10)
		this->isActive = false;
	//Xet  va cham
	for (auto iter : *object)
	{
		switch (iter->GetObjectType())
		{
		
		case GREEN_SOLDIER:

		case JAGUAR:
		case SOLDIER:

		case BUTTERFLY:
		case CROW:
		case ZOMBIE:
		case ZOMBIE_SWORD:

		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);
			if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				iter->SetHP(0);
				MainCharacter::GetInstance()->Score();
				this->explode->SetActive(D3DXVECTOR3(this->position.x, this->position.y, 0));
			}

			break;
		}
		case BOSS_BULLET:
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);

			BossBullet *bossBullet = dynamic_cast<BossBullet*>(iter);
			bossBullet->GetBoundingBox(bl, bt, br, bb);
			if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				bossBullet->Destroy();
			}


			break;
		}
		case BOSS:
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);

			Boss* boss = Boss::GetInstance();
			boss->GetBoundingBox(bl, bt, br, bb);
			if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				boss->Hurt();
			}

			break;
		}
		default:
			break;
		}
	}


}

void Shuriken::Render()
{
	if (!isActive)
		return;
	Object::Render();
	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);
	this->explode->Render();
	currentSprite->DrawSprite(pos, true);
}

void Shuriken::HandleCollision(vector<Object*>* objects)
{
}

void Shuriken::CalCulatePosition()
{

}

void Shuriken::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (isActive)
	{
		l = position.x;
		t = position.y;
		r = l + currentSprite->GetWidth();
		b = t + currentSprite->GetHeight();
	}
	else
	{
		l = t = r = b = 0;
	}
}

void Shuriken::checkCollisioWithEnemy(vector<Object*> *coObjects)
{

}

void Shuriken::Reset()
{
	this->NumOfChangeDirection = 0;
}