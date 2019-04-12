#include "MainCharacter.h"

MainCharacter* MainCharacter::_instance = NULL;

MainCharacter::MainCharacter()
{
	this->standSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_STAND);
	this->runSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_RUN);
	this->sitSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_SIT);
	this->jumpScrollSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_JUMP_SCROLL);
	this->hitSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_STAND_KILL);
	this->jumpHitSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_JUMP_SCROLL_KILL);
	this->sitHitSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_SIT_KILL);
	this->climb = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_CLIMB);

	this->SetObjectType(MAIN_CHARACTER);
	this->SetState(STATE_IDLE);

	this->objectWidth = 20;
	this->objectHeight = 31;

	this->SetPosition(10, 10);
	this->SetVeclocity(0, 0);
	this->SetDirection(1); //Right
	this->isOnGround = false;
	this->isOnLadder = false;

}

MainCharacter::~MainCharacter()
{
	if (this->standSprite != NULL) delete this->standSprite;
	if (this->runSprite != NULL) delete this->runSprite;
	if (this->sitSprite != NULL) delete this->sitSprite;
	if (this->jumpScrollSprite != NULL) delete this->jumpScrollSprite;
	if (this->hitSprite != NULL) delete this->hitSprite;
	if (this->jumpHitSprite != NULL) delete this->jumpHitSprite;
	if (this->sitHitSprite != NULL) delete this->sitHitSprite;
	if (this->climb != NULL) delete this->climb;
}

MAIN_CHARACTER_STATE MainCharacter::GetState()
{
	return this->state;
}

void MainCharacter::SetState(MAIN_CHARACTER_STATE value)
{
	this->state = value;

	switch (this->state)
	{
	case STATE_IDLE:
		Sword::GetInstance()->setIsActive(false);
		SetVx(0);
		currentSprite = standSprite;
		break;
	case STATE_WALK:
		SetVx(MAIN_WALK_PACE*direction);
		currentSprite = runSprite;
		break;
	case STATE_SIT:
		SetVx(0);
		currentSprite = sitSprite;
		break;
	case STATE_JUMP:
		SetVeclocity(0, -MAIN_JUMP_SPEED_Y);
		currentSprite = jumpScrollSprite;
		break;
	case STATE_JUMP_TO:
		currentSprite = jumpScrollSprite;
		SetVx(MAIN_WALK_PACE*direction);
		SetVy(-MAIN_JUMP_SPEED_Y);
		break;
	case STATE_ATTACK:
		Sword::GetInstance()->setIsActive(true);
		Sword::GetInstance()->SetDirection(direction);
		if (direction == 1)
			Sword::GetInstance()->SetPosition(position.x + 18, position.y + 3);
		else
			Sword::GetInstance()->SetPosition(position.x - 25, position.y + 3);
		Sword::GetInstance()->CalCulatePosition();
		SetVx(0);
		currentSprite = hitSprite;
		break;

	case STATE_SIT_ATTACK:
		Sword::GetInstance()->setIsActive(true);
		Sword::GetInstance()->SetDirection(direction);
		if (direction == 1)
			Sword::GetInstance()->SetPosition(position.x + 18, position.y + 10);
		else
			Sword::GetInstance()->SetPosition(position.x - 26, position.y + 10);
		SetVx(0);
		currentSprite = sitHitSprite;
		break;
	case STATE_JUMP_ATTACK:
		currentSprite = hitSprite;
		Sword::GetInstance()->setIsActive(true);
		Sword::GetInstance()->SetDirection(direction);
		if (direction == 1)
			Sword::GetInstance()->SetPosition(position.x + 18, position.y + 3);
		else
			Sword::GetInstance()->SetPosition(position.x - 25, position.y + 3);
		break;
	case STATE_JUMP_ATTACK_TO:
		SetVx(0.1*direction);
		currentSprite = hitSprite;
		Sword::GetInstance()->setIsActive(true);
		Sword::GetInstance()->SetDirection(direction);
		if (direction == 1)
			Sword::GetInstance()->SetPosition(position.x + 18, position.y + 3);
		else
			Sword::GetInstance()->SetPosition(position.x - 25, position.y + 3);
		break;
	case STATE_ON_LADDER:
		isOnGround = false;
		SetPosition(GetPosition().x, GetPosition().y);
		currentSprite = climb;
		SetVx(0);
		SetVy(0);
		isOnLadder = true;
		break;
	case STATE_CLIMBING:

		break;
	default:break;
	}

	int width, height;
	this->currentSprite->GetBoundingBox(width, height);

	this->SetBoundingBox(width, height);
}

void MainCharacter::ResetAllSprites()
{
	this->standSprite->Reset();
	this->runSprite->Reset();
	this->sitSprite->Reset();
	this->jumpScrollSprite->Reset();
}

bool MainCharacter::GetStateActive()
{
	return this->isActive;
}

void MainCharacter::Reset(float x, float y)
{
	this->isActive = true;
	this->SetLastPos(this->GetPosition());
	this->SetPosition(x, y);
}

void MainCharacter::Update(float t, vector<Object*>* object)
{

	Object::Update(t);

	Sword::GetInstance()->Update(t, object);

	if (GetState() == STATE_ATTACK)
	{
		if (hitSprite->getDone())
		{
			hitSprite->setDone(false);
			SetState(STATE_IDLE);
		}
	}
	if (GetState() == STATE_SIT_ATTACK)
	{
		if (sitHitSprite->getDone())
		{
			sitHitSprite->setDone(false);
			SetState(STATE_SIT);
		}
	}

	if (GetState() == STATE_JUMP_ATTACK || GetState() == STATE_JUMP_ATTACK_TO)
	{
		if (direction == 1)
			Sword::GetInstance()->SetPosition(position.x + 18, position.y + 3);
		else
			Sword::GetInstance()->SetPosition(position.x - 25, position.y + 3);
	}

	if (!isOnLadder)
		this->veclocity.y += 0.0015f *t;


	KeyBoardHandle();

	if(GetState()!=STATE_ON_LADDER)
		currentSprite->UpdateSprite();

	vector<Object*>*ground = new vector<Object*>;
	vector<Object*>*ladder = new vector<Object*>;
	vector<Object*>*other = new vector<Object*>;

	for (auto iter : *object)
	{
		if (iter->GetObjectType() == BRICK)
			ground->push_back(iter);
		else if (iter->GetObjectType() == LADDER)
			ladder->push_back(iter);
		else other->push_back(iter);
	}
	CheckCollisionWithGround(ground);
	CheckCollisionWithLadder(ladder);
}

void MainCharacter::Render()
{

	if (this->position.y < 32)
		return;
	RenderBoundingBox();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == 1)
		this->currentSprite->DrawSprite(pos, true);
	else
		this->currentSprite->DrawSprite(pos, false);

	Sword::GetInstance()->Render();

}

void MainCharacter::KeyBoardHandle()
{
	CKeyGame* k = CKeyGame::getInstance();

	if (isOnGround)
	{
		if (k->keyJump && (GetState() != STATE_JUMP || GetState() != STATE_JUMP_TO))
		{
			SetState(STATE_JUMP);
			isOnGround = false;
		}
		else if (k->keyAttack)
		{
			if (k->keyDown)
			{
				SetState(STATE_SIT_ATTACK);
			}
			else
			{
				SetState(STATE_ATTACK);
			}
		}
		else if (k->keyDown && state != STATE_SIT_ATTACK)
		{
			SetState(STATE_SIT);

			if (k->keyLeft)
				direction = -1;
			else if (k->keyRight)
				direction = 1;
		}
		else if (k->keyRight && GetState() != STATE_SIT && GetState() != STATE_SIT_ATTACK && GetState() != STATE_ATTACK && GetState() != STATE_HURT)
		{
			direction = 1;
			SetState(STATE_WALK);
		}
		else if (k->keyLeft  && GetState() != STATE_SIT && GetState() != STATE_SIT_ATTACK && GetState() != STATE_ATTACK && GetState() != STATE_HURT)
		{
			direction = -1;
			SetState(STATE_WALK);
		}
		else if (k->keyAttack)
		{
			if (k->keyDown)
			{
				SetState(STATE_SIT_ATTACK);
			}
			else
			{
				SetState(STATE_ATTACK);
			}
		}
		else if (k->keyDown && state != STATE_SIT_ATTACK)
		{
			SetState(STATE_SIT);

			if (k->keyLeft)
				direction = -1;
			else if (k->keyRight)
				direction = 1;
		}
		else if (GetState() != STATE_ATTACK && GetState() != STATE_SIT_ATTACK || GetState() != STATE_ON_LADDER)
		{
			SetState(STATE_IDLE);
			isOnGround = true;
		}
	}
	else if (GetState() == STATE_ON_LADDER || GetState() == STATE_CLIMBING)
	{
		if (k->keyUp)
		{
			SetVx(0);
			SetVy(-0.05);
			SetState(STATE_CLIMBING);
			currentSprite->UpdateSprite();
		}
		else if (k->keyDown)
		{
			SetVx(0);
			SetVy(0.05);
			SetState(STATE_CLIMBING);
			currentSprite->UpdateSprite();
		}
		else if (k->keyJump)
		{
			isOnLadder = false;
			direction *= -1;
			SetState(STATE_JUMP_TO);
		}
		else
		{
			SetState(STATE_ON_LADDER);
		}
	}
	else
	{
		if (k->keyAttack)
		{
			if (GetState() == STATE_JUMP)
				SetState(STATE_JUMP_ATTACK);
			else if (GetState() == STATE_JUMP_TO)
				SetState(STATE_JUMP_ATTACK_TO);
		}

		if (k->keyLeft && (GetState() == STATE_JUMP || GetState() == STATE_JUMP_ATTACK))
		{
			direction = -1;
			if (GetState() == STATE_JUMP)
				SetState(STATE_JUMP_TO);
			else
				SetState(STATE_JUMP_ATTACK_TO);
		}
		else if (k->keyRight && (GetState() == STATE_JUMP || GetState() == STATE_JUMP_ATTACK))
		{
			direction = 1;
			if (GetState() == STATE_JUMP)
				SetState(STATE_JUMP_TO);
			else
				SetState(STATE_JUMP_ATTACK_TO);
		}
	}
}

void MainCharacter::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (state == STATE_SIT)
	{
		l = position.x;
		t = position.y + 7;
		r = position.x + 17;
		b = position.y + 31;
	}
	else if (state == STATE_JUMP || state == STATE_JUMP_TO)
	{
		if (currentSprite->GetIndex() % 2 == 0)
		{
			l = position.x;
			t = position.y;
			r = position.x + 17;
			b = position.y + 31;
		}
		else
		{
			l = position.x;
			t = position.y + 9;
			r = position.x + 21;
			b = position.y + 31;
		}
	}
	else if (state == STATE_SIT_ATTACK)
	{
		l = position.x;
		t = position.y + 8;
		r = position.x + 17;
		b = position.y + 31;
	}
	else
	{
		l = position.x;
		t = position.y;
		r = position.x + 17;
		b = position.y + 31;
	}
}

void MainCharacter::CheckCollisionWithLadder(vector<Object*>* object)
{
	vector<CollisionEvent*> *coEvents = new vector<CollisionEvent*>();
	vector<CollisionEvent*> *coEventsResult = new vector<CollisionEvent*>();

	coEvents->clear();

	this->CalcPotentialCollisions(object, coEvents);

	if (coEvents->size() == 0) {
		//if (GetState() == STATE_CLIMBING || GetState() == STATE_ON_LADDER)
		//	SetState(STATE_IDLE);
	}
	else {

		float minTx, minTy, nX = 0, nY;


		this->FilterCollision(coEvents, coEventsResult, minTx, minTy, nX, nY);

		this->PlusPosition(minTx*this->deltaX + nX * 0.1f, minTy*this->deltaY + nY * 0.1f);

		if (nX != 0)
		{
			
			this->veclocity.x = 0;
			SetState(STATE_ON_LADDER);
		}
		if (nY != 0)
		{
			this->veclocity.y = 0;
		}

	}

}

void MainCharacter::CheckCollisionWithGround(vector<Object*>* object)
{
	vector<CollisionEvent*> *coEvents = new vector<CollisionEvent*>();
	vector<CollisionEvent*> *coEventsResult = new vector<CollisionEvent*>();

	coEvents->clear();

	this->CalcPotentialCollisions(object, coEvents);

	if (coEvents->size() == 0) {
		this->PlusPosition(this->deltaX, this->deltaY);
		isOnGround = false;
	}
	else {

		float minTx, minTy, nX = 0, nY;

		this->FilterCollision(coEvents, coEventsResult, minTx, minTy, nX, nY);

		this->PlusPosition(minTx*this->deltaX + nX * 0.1f, minTy*this->deltaY + nY * 0.1f);

		if (nX != 0)
		{
			this->veclocity.x = 0;

		}
		if (nY != 0)
		{
			if (GetState() == STATE_ON_LADDER || GetState() == STATE_CLIMBING)
			{
				isOnLadder = false;
				SetState(STATE_IDLE);
			}
			if (nY == -1)
				isOnGround = true;
			this->veclocity.y = 0;

			if (GetState() == STATE_JUMP || GetState() == STATE_JUMP_TO || GetState() == STATE_JUMP_ATTACK || GetState() == STATE_HURT)
			{
				SetState(STATE_IDLE);
			}
		}

	}

}

void MainCharacter::CheckCollisionWithOtherObject(vector<Object*>* object)
{

	
}