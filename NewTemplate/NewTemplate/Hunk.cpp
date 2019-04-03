#include "Hunk.h"



Hunk::Hunk()
{
	CreateAnimation();
}

Hunk::Hunk(int x, int y, int direction)
{
	position.x = x;
	position.y = y;
	this->direction = direction;
	this->hp = 1;
	this->code = hunk;
	CreateAnimation();
}


Hunk::~Hunk()
{

}


void Hunk::Update(DWORD dt, vector<LPGAMEOBJECT> *Ground, vector<LPGAMEOBJECT> *StaticObject, vector<LPGAMEOBJECT> *Item, vector<LPGAMEOBJECT> *Enemy)
{
	CGameObject::Update(dt);


	if (hp > 0)
	{
		velocity.x = 0.05f *direction;
		velocity.y += SIMON_GRAVITY*dt;
		checkCollisionWithGround(Ground);
	}
	if (position.x <= 5)
	{
		direction = 1;
	}
	if (position.x >= 300)
	{
		direction = -1;
	}
}

void Hunk::checkCollisionWithGround(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		Move();
	}
	else
	{
		float min_tx = 0, min_ty = 0, nx = 0, ny = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		position += {dPos.x*min_tx + nx *0.1f, min_ty*dPos.y + ny*0.1f};

		if (nx != 0)
		{
			velocity.x = 0;
		}
		if (ny != 0)
		{
			velocity.y = 0;
		}
	}
}

void Hunk::checkCollisionWithItem(vector<LPGAMEOBJECT> *coObjects)
{

}

void Hunk::checkCollisioWithStaticObjects(vector<LPGAMEOBJECT> *coObjects)
{

}

void Hunk::checkCollisioWithEnemy(vector<LPGAMEOBJECT> *coObjects)
{

}

void Hunk::Render(CCamera *cam)
{
	if (direction == -1)
		ani = 1;
	else ani = 0;
	D3DXVECTOR2 pos = cam->transformObjectPosition(position);
	animations[ani]->Render(pos, 255);
	RenderBoundingBox(cam);
}

void Hunk::Move()
{
	//CGame::Move();
	position += dPos;
}

void Hunk::SetState(int state)
{
	CGameObject::SetState(state);
}

void Hunk::CreateAnimation()
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	textures->Add(ID_ENEMY_TEX, ENEMY_TEXTURE_PATH, SIMON_COLOR);
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_ENEMY_TEX);

	//1xxxx : left
	//2xxxx : right

	sprites->Add(11000, 322, 60, 344, 91, true, texSimon); //Hunk left
	sprites->Add(11001, 293, 60, 315, 91, true, texSimon);

	sprites->Add(21000, 322, 60, 344, 91, false, texSimon); //Hunk right
	sprites->Add(21001, 293, 60, 315, 91, false, texSimon);

	LPANIMATION ani;

	ani = new CAnimation(100); //Hunk left
	ani->Add(11000);
	ani->Add(11001);
	animations->Add(700, ani);

	ani = new CAnimation(100); //Hunk right
	ani->Add(21000);
	ani->Add(21001);
	animations->Add(701, ani);

	this->AddAnimation(700);
	this->AddAnimation(701);
}

void Hunk::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (hp > 0)
	{
		left = position.x;
		top = position.y;
		bottom = top + 31;
		right = left + 22;
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

void Hunk::KeyBoardHandler()
{

}
