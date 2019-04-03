#include <algorithm>
#include "debug.h"
#include "Simon.h"
#include "Game.h"
#include "Brick.h"

CSimon::CSimon()
{
	CreateAnimation();
	code = simon_code;
	item = none;
	doneAttack = false;
	untouchable = 0;
	jump = false;
	attacking = false;
	hp = 16;
	doneStage = false;
	alpha = 255;
	sword = new Sword();
	isOnGround = false;
}

CSimon::~CSimon()
{

}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *Ground, vector<LPGAMEOBJECT> *StaticObject, vector<LPGAMEOBJECT> *Item, vector<LPGAMEOBJECT> *Enemy)
{
	CGameObject::Update(dt);

	KeyBoardHandler();

	if (GetState() == SIMON_STATE_ATTACK)
	{
		int index = (direction == 1) ? SIMON_ANI_ATTACK_RIGHT : SIMON_ANI_ATTACK_LEFT;

		if (animations.at(index)->getDone())
		{
			SetState(SIMON_STATE_IDDLE);
			animations.at(index)->setDone(false);
		}
	}
	if (GetState() == SIMON_STATE_SIT_ATTACK)
	{
		int index = (direction == 1) ? SIMON_ANI_SIT_ATTACK_RIGHT : SIMON_ANI_SIT_ATTACK_LEFT;

		if (animations.at(index)->getDone())
		{
			SetState(SIMON_STATE_SIT);
			animations.at(index)->setDone(false);
		}
	}

	velocity.y += SIMON_GRAVITY*dt;

	checkCollisioWithStaticObjects(StaticObject);

	checkCollisionWithGround(Ground);

	checkCollisioWithEnemy(Enemy);

	checkCollisionWithItem(Item);
	sword->Update(dt, Ground, StaticObject, Item, Enemy);
}

void CSimon::checkCollisionWithGround(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		Move();
		isOnGround = false;
	}
	else
	{
		isOnGround = true;
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
			if (GetState() == SIMON_STATE_JUMP || GetState() == SIMON_STATE_JUMP_TO || GetState() == SIMON_STATE_JUMP_ATTACK || GetState() == SIMON_STATE_HURT)
			{
				SetState(SIMON_STATE_IDDLE);
			}
		}
	}
}

void CSimon::checkCollisionWithItem(vector<LPGAMEOBJECT> *coObjects)
{

}

void CSimon::checkCollisioWithStaticObjects(vector<LPGAMEOBJECT> *coObjects)
{

}

void CSimon::checkCollisioWithEnemy(vector<LPGAMEOBJECT> *coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
	}
	else
	{
		float min_tx = 0, min_ty = 0, nx = 0, ny = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//position += {dPos.x*min_tx + nx *0.1f, min_ty*dPos.y + ny*0.1f};

		SetState(SIMON_STATE_HURT);


	}
}

void CSimon::Render(CCamera *cam)
{
	D3DXVECTOR2 pos = cam->transformObjectPosition(position);
	animations[ani]->Render(pos, alpha);
	sword->Render(cam);
	//RenderBoundingBox(cam);
}

void CSimon::Move()
{
	//CGame::Move();
	position += dPos;
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALK:
		velocity.x = SIMON_WALKING_SPEED*direction;
		if (direction == -1)
			ani = SIMON_ANI_WALKING_LEFT;
		else
			ani = SIMON_ANI_WALKING_RIGHT;
		break;
	case SIMON_STATE_IDDLE:
		isOnGround = true;
		velocity.x = 0;
		if (direction == -1)
			ani = SIMON_ANI_IDLE_LEFT;
		else
			ani = SIMON_ANI_IDLE_RIGHT;
		break;
	case SIMON_STATE_SIT:
		velocity.x = 0;
		if (direction == -1)
			ani = SIMON_ANI_SIT_LEFT;
		else ani = SIMON_ANI_SIT_RIGHT;
		break;
	case SIMON_STATE_JUMP:
		velocity = { 0, -SIMON_JUMP_SPEED_Y };
		ani = SIMON_ANI_JUMP_RIGHT;
		break;
	case SIMON_STATE_JUMP_TO:
		velocity.x = SIMON_WALKING_SPEED*direction;
		break;
	case SIMON_STATE_ATTACK:
		sword->setIsActive(true);
		sword->setDirection(direction);


		velocity.x = 0;
		if (direction == -1)
		{
			ani = SIMON_ANI_ATTACK_LEFT;
			sword->SetPosition(D3DXVECTOR2(position.x - 16, position.y + 6));
		}
		else
		{
			ani = SIMON_ANI_ATTACK_RIGHT;
			sword->SetPosition(D3DXVECTOR2(position.x + 14, position.y + 6));
		}
		break;
	case SIMON_STATE_SIT_ATTACK:
		sword->setIsActive(true);
		sword->setDirection(direction);
		velocity.x = 0;

		if (direction == -1)
		{
			ani = SIMON_ANI_SIT_ATTACK_LEFT;
			sword->SetPosition(D3DXVECTOR2(position.x - 16, position.y + 15));
		}
		else
		{
			ani = SIMON_ANI_SIT_ATTACK_RIGHT;
			sword->SetPosition(D3DXVECTOR2(position.x + 14, position.y + 15));
		}
		break;
	case SIMON_STATE_JUMP_ATTACK:
		if (direction == -1)
			ani = SIMON_ANI_JUMP_ATTACK_LEFT;
		else ani = SIMON_ANI_JUMP_ATTACK_RIGHT;
		break;
	case SIMON_STATE_JUMP_ATTACK_TO:
		velocity.x = SIMON_WALKING_SPEED*direction;
		if (direction == -1)
			ani = SIMON_ANI_JUMP_ATTACK_LEFT;
		else ani = SIMON_ANI_JUMP_ATTACK_RIGHT;
		break;
	case SIMON_STATE_HURT:
		position.x -= 50 * direction;
		velocity.x = 0;
		position.y -= 50;
		isOnGround = false;
		if (direction == -1)
			ani = SIMON_ANI_IDLE_LEFT;
		else ani = SIMON_ANI_IDLE_RIGHT;
		break;
	}
}

void CSimon::CreateAnimation()
{
	CTextures *textures = CTextures::GetInstance();
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

	textures->Add(ID_SIMON_TEX, SIMON_TEXTURE_PATH, SIMON_COLOR);
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_SIMON_TEX);


	//1xxxx : left
	//2xxxx : right

	sprites->Add(10004, 81, 6, 100, 36, true, texSimon); //walk left
	sprites->Add(10003, 50, 6, 71, 36, true, texSimon);
	sprites->Add(10002, 20, 6, 39, 36, true, texSimon);

	sprites->Add(20004, 81, 6, 100, 36, false, texSimon); //walk right
	sprites->Add(20003, 50, 6, 71, 36, false, texSimon);
	sprites->Add(20002, 20, 6, 39, 36, false, texSimon);

	sprites->Add(10001, 420, 5, 436, 36, true, texSimon);//idle left
	sprites->Add(20001, 420, 5, 436, 36, false, texSimon); //idle right

	sprites->Add(10010, 420, 45, 436, 75, true, texSimon); //sit left
	sprites->Add(20010, 420, 45, 436, 75, false, texSimon); //sit right


	sprites->Add(10024, 282, 44, 296, 74, true, texSimon); //jump
	sprites->Add(10023, 252, 40, 273, 70, true, texSimon);
	sprites->Add(10022, 231, 44, 248, 74, true, texSimon);
	sprites->Add(10021, 201, 40, 222, 70, true, texSimon);

	sprites->Add(10031, 379, 6, 397, 36, true, texSimon); //hit left
	sprites->Add(10032, 355, 6, 373, 36, true, texSimon);
	sprites->Add(10033, 310, 6, 328, 36, true, texSimon);

	sprites->Add(20031, 379, 6, 397, 36, false, texSimon); //hit right
	sprites->Add(20032, 355, 6, 373, 36, false, texSimon);
	sprites->Add(20033, 310, 6, 328, 36, false, texSimon);

	sprites->Add(10041, 387, 45, 404, 75, true, texSimon); //sit hit left
	sprites->Add(10042, 366, 45, 381, 75, true, texSimon);
	sprites->Add(10043, 324, 45, 339, 75, true, texSimon);

	sprites->Add(20041, 387, 45, 404, 75, false, texSimon); //sit hit right
	sprites->Add(20042, 366, 45, 381, 75, false, texSimon);
	sprites->Add(20043, 324, 45, 339, 75, false, texSimon);

	sprites->Add(10051, 57, 51, 81, 74, true, texSimon); //jump hit left
	sprites->Add(10052, 89, 51, 112, 75, true, texSimon);
	sprites->Add(10053, 121, 51, 145, 74, true, texSimon);
	sprites->Add(10054, 153, 50, 176, 74, true, texSimon);

	sprites->Add(20051, 57, 51, 81, 74, false, texSimon); //jump hit right
	sprites->Add(20052, 89, 51, 112, 75, false, texSimon);
	sprites->Add(20053, 121, 51, 145, 74, false, texSimon);
	sprites->Add(20054, 153, 50, 176, 74, false, texSimon);


	LPANIMATION ani;

	ani = new CAnimation(100); //walk left
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(SIMON_ANI_WALKING_RIGHT, ani);

	ani = new CAnimation(100); //walk right
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(SIMON_ANI_WALKING_LEFT, ani);


	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(SIMON_ANI_IDLE_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(20001);
	animations->Add(SIMON_ANI_IDLE_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(10010);
	animations->Add(SIMON_ANI_SIT_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(20010);
	animations->Add(SIMON_ANI_SIT_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(10024);
	ani->Add(10023);
	ani->Add(10022);
	ani->Add(10021);
	animations->Add(SIMON_ANI_JUMP_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	animations->Add(SIMON_ANI_ATTACK_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(20031);
	ani->Add(20032);
	ani->Add(20033);
	animations->Add(SIMON_ANI_ATTACK_LEFT, ani);

	ani = new CAnimation(100);
	ani->Add(10041);
	ani->Add(10042);
	ani->Add(10043);
	animations->Add(SIMON_ANI_SIT_ATTACK_RIGHT, ani);

	ani = new CAnimation(100);
	ani->Add(20041);
	ani->Add(20042);
	ani->Add(20043);
	animations->Add(SIMON_ANI_SIT_ATTACK_LEFT, ani);

	ani = new CAnimation(100); //sit hit left
	ani->Add(10051);
	ani->Add(10052);
	ani->Add(10053);
	ani->Add(10054);
	animations->Add(SIMON_ANI_JUMP_ATTACK_LEFT, ani);

	ani = new CAnimation(100); //sit hit right
	ani->Add(20051);
	ani->Add(20052);
	ani->Add(20053);
	ani->Add(20054);
	animations->Add(SIMON_ANI_JUMP_ATTACK_RIGHT, ani);

	this->AddAnimation(SIMON_ANI_IDLE_RIGHT);
	this->AddAnimation(SIMON_ANI_IDLE_LEFT);
	this->AddAnimation(SIMON_ANI_WALKING_RIGHT);
	this->AddAnimation(SIMON_ANI_WALKING_LEFT);
	this->AddAnimation(SIMON_ANI_SIT_LEFT);
	this->AddAnimation(SIMON_ANI_SIT_RIGHT);
	this->AddAnimation(SIMON_ANI_JUMP_RIGHT);
	this->AddAnimation(SIMON_ANI_ATTACK_LEFT);
	this->AddAnimation(SIMON_ANI_ATTACK_RIGHT);
	this->AddAnimation(SIMON_ANI_SIT_ATTACK_LEFT);
	this->AddAnimation(SIMON_ANI_SIT_ATTACK_RIGHT);
	this->AddAnimation(SIMON_ANI_JUMP_ATTACK_LEFT);
	this->AddAnimation(SIMON_ANI_JUMP_ATTACK_RIGHT);

}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == SIMON_STATE_SIT)
	{
		left = position.x;
		top = position.y + 7;
		right = position.x + SIMON_WIDTH_STAND;
		bottom = position.y + SIMON_HEIGHT_STAND;
	}
	else if (state == SIMON_STATE_JUMP || state == SIMON_STATE_JUMP_TO)
	{
		if (animations.at(SIMON_ANI_JUMP_RIGHT)->GetCurrentFrame() % 2 == 0)
		{
			left = position.x;
			top = position.y + 15;
			right = position.x + 17;
			bottom = position.y + SIMON_HEIGHT_STAND;
		}
		else
		{
			left = position.x;
			top = position.y + 9;
			right = position.x + 21;
			bottom = position.y + SIMON_HEIGHT_STAND;
		}
	}
	else if (state == SIMON_STATE_SIT_ATTACK)
	{
		left = position.x;
		top = position.y + 8;
		right = position.x + SIMON_WIDTH_STAND;
		bottom = position.y + SIMON_HEIGHT_STAND;
	}
	else
	{
		left = position.x;
		top = position.y;
		right = position.x + SIMON_WIDTH_STAND;
		bottom = position.y + SIMON_HEIGHT_STAND;
	}
	bdbpos = { left, top };
}

void CSimon::KeyBoardHandler()
{
	CKeyGame* k = CKeyGame::getInstance();

	if (isOnGround)
	{
		if (k->keyJump && (GetState() != SIMON_STATE_JUMP || GetState() != SIMON_STATE_JUMP_TO))
		{
			SetState(SIMON_STATE_JUMP);
			isOnGround = false;
		}
		else if (k->keyAttack)
		{
			if (k->keyDown)
			{
				SetState(SIMON_STATE_SIT_ATTACK);
			}
			else
			{
				SetState(SIMON_STATE_ATTACK);
			}
		}
		else if (k->keyDown && state != SIMON_STATE_SIT_ATTACK)
		{
			SetState(SIMON_STATE_SIT);

			if (k->keyLeft)
				direction = -1;
			else if (k->keyRight)
				direction = 1;
		}
		else if (k->keyRight && GetState() != SIMON_STATE_SIT && GetState() != SIMON_STATE_SIT_ATTACK && GetState() != SIMON_STATE_ATTACK && GetState() != SIMON_STATE_HURT)
		{
			direction = 1;
			SetState(SIMON_STATE_WALK);
		}
		else if (k->keyLeft  && GetState() != SIMON_STATE_SIT && GetState() != SIMON_STATE_SIT_ATTACK && GetState() != SIMON_STATE_ATTACK && GetState() != SIMON_STATE_HURT)
		{
			direction = -1;
			SetState(SIMON_STATE_WALK);
		}
		else if (k->keyAttack)
		{
			if (k->keyDown)
			{
				SetState(SIMON_STATE_SIT_ATTACK);
			}
			else
			{
				SetState(SIMON_STATE_ATTACK);
			}
		}
		else if (k->keyDown && state != SIMON_STATE_SIT_ATTACK)
		{
			SetState(SIMON_STATE_SIT);

			if (k->keyLeft)
				direction = -1;
			else if (k->keyRight)
				direction = 1;
		}
		else if (GetState() != SIMON_STATE_ATTACK && GetState() != SIMON_STATE_SIT_ATTACK)
		{
			SetState(SIMON_STATE_IDDLE);
			isOnGround = true;
		}
	}
	else
	{
		if (k->keyAttack)
		{
			if (GetState() == SIMON_STATE_JUMP)
				SetState(SIMON_STATE_JUMP_ATTACK);
			else if (GetState() == SIMON_STATE_JUMP_TO)
				SetState(SIMON_STATE_JUMP_ATTACK_TO);
		}

		if (k->keyLeft && (GetState() == SIMON_STATE_JUMP || GetState() == SIMON_STATE_JUMP_ATTACK))
		{
			direction = -1;
			if (GetState() == SIMON_STATE_JUMP)
				SetState(SIMON_STATE_JUMP_TO);
			else
				SetState(SIMON_STATE_JUMP_ATTACK_TO);
		}
		else if (k->keyRight && (GetState() == SIMON_STATE_JUMP || GetState() == SIMON_STATE_JUMP_ATTACK))
		{
			direction = 1;
			if (GetState() == SIMON_STATE_JUMP)
				SetState(SIMON_STATE_JUMP_TO);
			else
				SetState(SIMON_STATE_JUMP_ATTACK_TO);
		}
	}
}
