#include "Windmill.h"


Windmill* Windmill::_instance = NULL;

Windmill::Windmill()
{
	isActive = false;
	direction = RIGHT;
	WindmillSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ITEM), PATH_WINDMILL);
	currentSprite = WindmillSprite;
	this->veclocity.x = 0;
	this->veclocity.y = 0;
	this->explode = new Explode();
	NumOfChangeDirection = 0;
}


Windmill::~Windmill()
{

}

void Windmill::Update(float t, vector<Object*> *object)
{
	this->explode->Update(deltaTime, object);
	//position = MainCharacter::GetInstance()->GetPosition();


	if (!isActive)
		return;

	currentSprite->UpdateSprite();

	if (this->position.x < Camera::GetInstance()->getPosition().x || this->position.x > Camera::GetInstance()->getPosition().x + 276)
	{
		this->isActive = false;
	}
	position.x += 5 * direction;

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

void Windmill::Render()
{
	if (!isActive)
		return;
	Object::Render();
	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);
	this->explode->Render();
	currentSprite->DrawSprite(pos, true);
}

void Windmill::HandleCollision(vector<Object*>* objects)
{
}

void Windmill::CalCulatePosition()
{

}

void Windmill::GetBoundingBox(float &l, float &t, float &r, float &b)
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

void Windmill::checkCollisioWithEnemy(vector<Object*> *coObjects)
{

}

void Windmill::Reset()
{

}
