#include "Sword.h"

Sword::Sword()
{
	isActive = false;
	CreateAnimation();
}


Sword::~Sword()
{

}

void Sword::Update(DWORD dt, vector<LPGAMEOBJECT> *Ground, vector<LPGAMEOBJECT> *StaticObject, vector<LPGAMEOBJECT> *Item, vector<LPGAMEOBJECT> *Enemy)
{
	CGameObject::Update(dt);

	if (isActive)
	{
		checkCollisioWithStaticObjects(StaticObject);
		checkCollisionWithItem(Item);
		checkCollisioWithEnemy(Enemy);

	}
	if (animations.at(ani)->getDone())
	{
		isActive = false;
		animations.at(ani)->setDone(false);
	}
}


void Sword::checkCollisionWithItem(vector<LPGAMEOBJECT> *coObjects)
{

}

void Sword::checkCollisioWithStaticObjects(vector<LPGAMEOBJECT> *coObjects)
{

}

void Sword::checkCollisioWithEnemy(vector<LPGAMEOBJECT> *coObjects)
{
	for (auto iter : *coObjects)
	{
		// normal intersect colision
		switch (iter->GetCode())
		{
		case hunk:
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);
			if (CGame::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				iter->setHp(0);
			}
			break;
		}
		default:
			break;
		}
	}

	// sweptAABB colision
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	for (auto iter : coEvents)
	{
		switch (iter->obj->GetCode())
		{
		case hunk:
			iter->obj->setHp(0);
			break;
		default:
			break;
		}
	}
	for (auto iter : coEvents) delete iter;
	coEvents.clear();
}

void Sword::Render(CCamera *cam)
{

	if (isActive)
	{
		if (direction == -1)
			ani = 1;
		else ani = 0;
		D3DXVECTOR2 pos = cam->transformObjectPosition(position);
		animations[ani]->Render(pos, 255);
	}

	//RenderBoundingBox(cam);
}

void Sword::Move()
{
	//CGame::Move();
	//position += dPos;
}

void Sword::SetState(int state)
{
	CGameObject::SetState(state);
}

void Sword::CreateAnimation()
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_SIMON_TEX);

	//1xxxx : left
	//2xxxx : right

	sprites->Add(11002, 0, 0, 19, 6, true, texSimon); //sword left
	sprites->Add(11003, 335, 12, 354, 18, true, texSimon);
	sprites->Add(11004, 290, 7, 309, 13, true, texSimon);

	sprites->Add(21002, 0, 0, 19, 6, false, texSimon); //sword right
	sprites->Add(21003, 335, 12, 354, 18, false, texSimon);
	sprites->Add(21004, 290, 7, 309, 13, false, texSimon);

	LPANIMATION ani;

	ani = new CAnimation(100); //sword left
	ani->Add(11002);
	ani->Add(11003);
	ani->Add(11004);
	animations->Add(600, ani);

	ani = new CAnimation(100); //sword right
	ani->Add(21002);
	ani->Add(21003);
	ani->Add(21004);
	animations->Add(601, ani);

	this->AddAnimation(600);
	this->AddAnimation(601);

}

void Sword::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isActive)
	{
		switch (animations.at(ani)->GetCurrentFrame())
		{
		case 0:
			left = position.x;
			top = position.y;
			bottom = top;
			right = left;
			break;
		case 1:
			left = position.x;
			top = position.y;
			bottom = top + 6;
			right = left + 19;
			break;
		case 2:
			if (direction == 1)
				left = position.x;
			else left = position.x + 10;
			top = position.y;
			bottom = top + 3;
			right = left + 9;
			break;
		}
	}
	else
	{
		left = position.x;
		top = position.y;
		bottom = top;
		right = left;
	}
	bdbpos = { left, top };
}

void Sword::KeyBoardHandler()
{
}
