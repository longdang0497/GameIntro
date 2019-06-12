
#include "MainCharacter.h"

MainCharacter* MainCharacter::_instance = NULL;

MainCharacter::MainCharacter()
{
	this->standSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_STAND, MAIN_RATE);
	this->runSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_RUN, MAIN_RATE);
	this->sitSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_SIT, MAIN_RATE);
	this->jumpScrollSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_JUMP_SCROLL, MAIN_RATE);
	this->hitSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_STAND_KILL, MAIN_RATE);
	this->jumpHitSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_JUMP_SCROLL_KILL, MAIN_RATE);
	this->sitHitSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_SIT_KILL, MAIN_RATE);
	this->hurtSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_HURT, MAIN_RATE);
	this->onLadder = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_ON_LADDER, MAIN_RATE);
	this->climbing = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_CLIMB, MAIN_RATE);

	this->SetObjectType(MAIN_CHARACTER);
	this->SetState(STATE_IDLE);

	this->objectWidth = 20;
	this->objectHeight = 31;

	this->SetPosition(100, 120);
	this->SetVeclocity(0, 0);
	this->SetDirection(RIGHT); //Right
	this->isOnGround = false;
	this->HP = 16;

	this->allowJump = false;

	StartStopWatch = GetTickCount();

	Lives = 2;


	IsRepawn = false;

	Energy = 100;

	SubWeapon = SW_shuriken;

	this->explode = new Explode();

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
	if (this->hurtSprite != NULL) delete this->hurtSprite;
	if (this->onLadder != NULL) delete this->sitHitSprite;
	if (this->climbing != NULL) delete this->hurtSprite;
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
	case STATE_FALL:
		veclocity.x += -0.08 * direction;
		veclocity.y = -0.08;
		//veclocity.x = 0;
		//veclocity.y = 0;
		currentSprite = standSprite;
		break;
	case STATE_IDLE:
		SetVx(0);
		currentSprite = standSprite;
		break;
	case STATE_WALK:
		SetVx(MAIN_WALK_PACE * direction);
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
		SetVx(0.1 * direction);
		break;
	case STATE_ATTACK:
		Sword::GetInstance()->setIsActive(true);
		Sword::GetInstance()->SetDirection(direction);
		if (direction == RIGHT)
			Sword::GetInstance()->SetPosition(position.x + 18, position.y + 3);
		else
			Sword::GetInstance()->SetPosition(position.x - 25, position.y + 3);
		Sword::GetInstance()->CalCulatePosition();
		SetVx(0);
		currentSprite = hitSprite;
		break;
	case STATE_JUMP_SCROLL_HIT:
		SetVeclocity(0, -MAIN_JUMP_SPEED_Y);
		currentSprite = jumpHitSprite;
		break;
	case STATE_SIT_ATTACK:
		Sword::GetInstance()->setIsActive(true);
		Sword::GetInstance()->SetDirection(direction);
		if (direction == RIGHT)
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
		if (direction == RIGHT)
			Sword::GetInstance()->SetPosition(position.x + 18, position.y + 3);
		else
			Sword::GetInstance()->SetPosition(position.x - 25, position.y + 3);
		break;
	case STATE_JUMP_ATTACK_TO:
		SetVx(0.1 * direction);
		currentSprite = hitSprite;
		Sword::GetInstance()->setIsActive(true);
		Sword::GetInstance()->SetDirection(direction);
		if (direction == RIGHT)
			Sword::GetInstance()->SetPosition(position.x + 18, position.y + 3);
		else
			Sword::GetInstance()->SetPosition(position.x - 25, position.y + 3);
		break;
	case STATE_HURT:
		currentSprite = hurtSprite;
		this->Hurt();
		SetVeclocity(-0.15 * direction, -0.2);
		isOnGround = false;
		startHurting = GetTickCount();
		isHurting = true;
		break;
	case STATE_ON_LADDER:
		currentSprite = onLadder;
		SetVx(0);
		SetVy(0);
		break;
	case STATE_CLIMBING:
		currentSprite = climbing;
		SetVx(0);
		SetVy(0);
		break;
	default:
		break;
	}
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

void MainCharacter::Update(float t, vector<Object*> * object)
{
	if (HP == 0)
		return;

	if (isInTheEndOfMap)
		return;

	this->explode->Update(deltaTime, object);

	if (StopWatch && GetTickCount() - StartStopWatch >= 6000)
	{
		StopWatch = false;
	}


	alpha = 255;

	if (isHurting || IsRepawn)
	{
		alpha = 128;
	}

	Object::Update(t);

	Sword::GetInstance()->Update(t, object);

	Shuriken::GetInstance()->Update(t, object);

	Windmill::GetInstance()->Update(t, object);

	Flames::GetInstance()->Update(t, object);

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
		if (direction == RIGHT)
			Sword::GetInstance()->SetPosition(position.x + 18, position.y + 3);
		else
			Sword::GetInstance()->SetPosition(position.x - 25, position.y + 3);
	}

	if (GetTickCount() - startStanding >= 300 && isOnGround)
	{
		allowJump = true;
	}


	this->veclocity.y += 0.0012f * t;
	KeyBoardHandle();
	currentSprite->UpdateSprite();

	HandleCollision(object);

	if (GetTickCount() - startHurting >= 1000)
		isHurting = false;
}

void MainCharacter::Render()
{
	if (HP == 0)
		return;

	this->explode->Render();

	// Cách này chỉ là đang fix tạm thôi nha <3
	if (Game::GetInstance()->GetGameStage() == STAGE1 && this->position.x > 883 && this->position.x < 960
		&& this->position.y + 31 > 154) {
		this->position.y = 154 - 32;
	}
	else if (Game::GetInstance()->GetGameStage() == STAGE2) {
		if (this->position.x >= 416 && this->position.x <= 576 && this->position.y + 31 > 151) {
			this->position.y = 151 - 32;
		}
		else if (this->position.x >= 1309 && this->position.x <= 1600 && this->position.y + 31 > 152
			|| this->position.x >= 2720 && this->position.x <= 2875 && this->position.y + 31 > 152) {
			this->position.y = 152 - 32;
		}
	}

	Object::Render();

	this->position.z = 0;



	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT)
		this->currentSprite->DrawSprite(pos, true, alpha);
	else
		this->currentSprite->DrawSprite(pos, false, alpha);

	Sword::GetInstance()->Render();
	Shuriken::GetInstance()->Render();
	Flames::GetInstance()->Render();
	Windmill::GetInstance()->Render();

}

void MainCharacter::KeyBoardHandle()
{
	CKeyGame* k = CKeyGame::getInstance();

	if (GetState() == STATE_ON_LADDER || GetState() == STATE_CLIMBING)
	{
		if (k->keyDown)
		{
			position.y += 0.5;
			if (GetState() == STATE_ON_LADDER)
				SetState(STATE_CLIMBING);
		}
		else if (k->keyUp) {
			position.y -= 0.5;
			if (GetState() == STATE_ON_LADDER)
				SetState(STATE_CLIMBING);
		}
		else if (k->keyJump)
		{
			currentSprite = jumpScrollSprite;
			direction *= -1;
			SetVy(-0.3f);
			SetState(STATE_JUMP_TO);
		}
		else
			SetState(STATE_ON_LADDER);
	}
	else if (isOnGround)
	{
		if (k->keyChangeGameMode && Energy > 0)
		{
			if (SubWeapon == SW_jump_Scroll_Kill && allowJump && Energy>=5)
			{
				allowJump = false;
				Energy -= 5;
				SetState(STATE_JUMP_SCROLL_HIT);
				isOnGround = false;
			}
			else if (SubWeapon == SW_shuriken && Shuriken::GetInstance()->GetIsActive() == false && Energy >= 5)
			{
				Shuriken::GetInstance()->SetPosition(this->position.x, this->position.y);
				Shuriken::GetInstance()->SetDirection(this->direction);
				Shuriken::GetInstance()->Reset();
				Shuriken::GetInstance()->SetIsActive(true);
				Energy -= 5;
			}
			else if (SubWeapon == SW_windmill && Windmill::GetInstance()->GetIsActive() == false && Energy >= 3)
			{
				Windmill::GetInstance()->SetPosition(this->position.x, this->position.y+5);
				Windmill::GetInstance()->SetDirection(this->direction);
				Windmill::GetInstance()->Reset();
				Windmill::GetInstance()->SetIsActive(true);
				Energy -= 3;
			}
			else if (SubWeapon == SW_Flames && Flames::GetInstance()->GetIsActive() == false && Energy >= 5)
			{
				Flames::GetInstance()->SetPosition(this->position.x, this->position.y);
				Flames::GetInstance()->SetDirection(this->direction);
				Flames::GetInstance()->Reset();
				Flames::GetInstance()->SetIsActive(true);
				Energy -= 5;
			}
		}

		else if (k->keyJump && allowJump) //(GetState() != STATE_JUMP || GetState() != STATE_JUMP_TO))
		{
			allowJump = false;
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
				direction = LEFT;
			else if (k->keyRight)
				direction = RIGHT;
		}
		else if (k->keyRight && GetState() != STATE_SIT && GetState() != STATE_SIT_ATTACK && GetState() != STATE_ATTACK && GetState() != STATE_HURT)
		{
			direction = RIGHT;
			SetState(STATE_WALK);
		}
		else if (k->keyLeft && GetState() != STATE_SIT && GetState() != STATE_SIT_ATTACK && GetState() != STATE_ATTACK && GetState() != STATE_HURT)
		{
			direction = LEFT;
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
				direction = LEFT;
			else if (k->keyRight)
				direction = RIGHT;
		}
		else if (GetState() != STATE_ATTACK && GetState() != STATE_SIT_ATTACK && GetState() != STATE_HURT)
		{
			SetState(STATE_IDLE);
			isOnGround = true;
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

		if ((GetState() == STATE_JUMP || GetState() == STATE_JUMP_TO || GetState() == STATE_JUMP_ATTACK || GetState() == STATE_JUMP_ATTACK || GetState() == STATE_JUMP_SCROLL_HIT))
		{
			/*direction = LEFT;
			if (GetState() == STATE_JUMP)
				SetState(STATE_JUMP_TO);
			else if (GetState() == STATE_JUMP_ATTACK)
				SetState(STATE_JUMP_ATTACK_TO);*/


			if (k->keyLeft)
			{
				direction = LEFT;
				if (GetState() == STATE_JUMP || GetState()==STATE_JUMP_SCROLL_HIT)
					SetState(STATE_JUMP_TO);
				else if (GetState() == STATE_JUMP_ATTACK)
					SetState(STATE_JUMP_ATTACK_TO);
				else if (GetState() == STATE_JUMP_ATTACK_TO)
					SetState(STATE_JUMP_ATTACK_TO);
				else if (GetState() == STATE_JUMP_TO)
					SetState(STATE_JUMP_TO);
			}
			else if (k->keyRight)
			{
				direction = RIGHT;
				if (GetState() == STATE_JUMP || GetState() == STATE_JUMP_SCROLL_HIT)
					SetState(STATE_JUMP_TO);
				else if (GetState() == STATE_JUMP_ATTACK)
					SetState(STATE_JUMP_ATTACK_TO);
				else if (GetState() == STATE_JUMP_ATTACK_TO)
					SetState(STATE_JUMP_ATTACK_TO);
				else if (GetState() == STATE_JUMP_TO)
					SetState(STATE_JUMP_TO);
			}
			else
			{
				SetVx(0);
			}


		}
		//if (k->keyRight && (GetState() == STATE_JUMP || GetState() == STATE_JUMP_TO || GetState() == STATE_JUMP_ATTACK || GetState() == STATE_JUMP_ATTACK))
		//{
		//	/*direction = RIGHT;
		//	if (GetState() == STATE_JUMP)
		//		SetState(STATE_JUMP_TO);
		//	else if (GetState() == STATE_JUMP_ATTACK)
		//		SetState(STATE_JUMP_ATTACK_TO);*/

		//	direction = RIGHT;
		//	if (GetState() == STATE_JUMP)
		//		SetState(STATE_JUMP_TO);
		//	else if (GetState() == STATE_JUMP_ATTACK)
		//		SetState(STATE_JUMP_ATTACK_TO);
		//	else if (GetState() == STATE_JUMP_ATTACK_TO)
		//		SetState(STATE_JUMP_ATTACK_TO);
		//	else if (GetState() == STATE_JUMP_TO)
		//		SetState(STATE_JUMP_TO);
		//}
	}



}

void MainCharacter::HandleCollision(vector<Object*> * objects)
{
	vector<Object*>* staticObject = new vector<Object*>();
	vector<Object*>* movingObject = new vector<Object*>();
	staticObject->clear();
	movingObject->clear();


	for (auto iter : *objects)
	{
		if (iter->GetObjectType() == BRICK)
			staticObject->push_back(iter);
		else if (iter->GetHP() >= 0 || iter->GetActive() == true || iter->GetObjectType() == ITEM)
			movingObject->push_back(iter);
	}

	if (GetState() != STATE_ON_LADDER && GetState() != STATE_CLIMBING)
		this->HandleCollisionWithStaticObject(staticObject);
	if (!isHurting)
		this->HandleCollisionWithMovingObject(movingObject);


}

void MainCharacter::HandleCollisionWithStaticObject(vector<Object*> * objects)
{
	vector<CollisionEvent*>* coEvents = new vector<CollisionEvent*>();
	vector<CollisionEvent*>* coEventsResult = new vector<CollisionEvent*>();

	coEvents->clear();

	this->CalcPotentialCollisions(objects, coEvents);

	if (coEvents->size() == 0) {

		this->PlusPosition(this->deltaX, this->deltaY);
		isOnGround = false;

	}
	else {
		float minTx, minTy, nX = 0, nY;

		this->FilterCollision(coEvents, coEventsResult, minTx, minTy, nX, nY);

		if (nY == 1)
			this->PlusPosition(minTx * this->deltaX + nX * 0.1f, this->deltaY);
		else
			this->PlusPosition(minTx * this->deltaX + nX * 0.1f, minTy * this->deltaY + nY * 0.225f);

		for (auto iter : *coEventsResult)
		{
			switch (iter->obj->GetObjectType())
			{
			case BRICK:
			{
				if (nX != 0)
				{
					this->veclocity.x = 0;
				}
				if (nY != 0)
				{
					if (nY == -1)
					{
						this->veclocity.y = 0;
						isOnGround = true;
						if (GetState() == STATE_JUMP || GetState() == STATE_JUMP_TO || GetState() == STATE_HURT )
						{
							position.y -= 10;
							startStanding = GetTickCount();
							SetState(STATE_IDLE);
						}
						else if (GetState() == STATE_JUMP_ATTACK || GetState() == STATE_JUMP_SCROLL_HIT)
						{
							startStanding = GetTickCount();
							SetState(STATE_IDLE);
						}

					}
				}
				break;
			}
			
			default:
			{
				break;
			}

			}
		}
	}

	for (int i = 0; i < coEvents->size(); i++)
		delete coEvents->at(i);
	delete coEvents;

	delete coEventsResult;
}

void MainCharacter::HandleCollisionWithMovingObject(vector<Object*> * objects)
{
	for (auto iter : *objects)
	{
		if (iter->GetIsActive())
		{
			switch (iter->GetObjectType())
			{
			case JAGUAR:
			case GREEN_SOLDIER:
			case BAZOOKA_BULLET:
			case SOLDIER:
			case BOSS:
			case BOSS_BULLET:
			case ZOMBIE:
			case BAT:
			case EAGLE:
			case ZOMBIE_SWORD:
			{
				if (Demo)
				{
					float al, at, ar, ab, bl, bt, br, bb;
					GetBoundingBox(al, at, ar, ab);
					iter->GetBoundingBox(bl, bt, br, bb);
					if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
					{
						{
							if (!StopWatch)
							{
								if (GetState() == STATE_JUMP_SCROLL_HIT)
								{
									this->explode->SetActive(iter->GetPosition());
									iter->SetHP(iter->GetHP() - 1);
								}
								else
								{
									if(Demo)
										SetState(STATE_HURT);
								}
							}
						}

						break;
					}   
				}
				break;
			}
			case HIDE_OBJECT:
			{
				float al, at, ar, ab, bl, bt, br, bb;
				GetBoundingBox(al, at, ar, ab);
				iter->GetBoundingBox(bl, bt, br, bb);
				if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
				{
					HideObject* h = dynamic_cast<HideObject*> (iter);
					if ((h->getType() == TOP_LADDER || h->getType() == BOTTOM_LADDER) && (GetState() == STATE_ON_LADDER || GetState() == STATE_CLIMBING))
					{
						//SetVy(0);
						SetState(STATE_FALL);
					}
					else if (h->getType() == END_MAP)
					{
						isInTheEndOfMap = true;
					}
				}

				break;
			}
			case LADDER:
			{
				float al, at, ar, ab, bl, bt, br, bb;
				GetBoundingBox(al, at, ar, ab);
				iter->GetBoundingBox(bl, bt, br, bb);
				if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
				{
					if(state!= STATE_ON_LADDER && state != STATE_CLIMBING)
						SetState(STATE_ON_LADDER);
					break;
				}
			}
			case ITEM:
			{
				float al, at, ar, ab, bl, bt, br, bb;
				GetBoundingBox(al, at, ar, ab);
				iter->GetBoundingBox(bl, bt, br, bb);
				if (Game::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
				{
					if (iter->GetActive())
					{
						iter->SetActive(false);
						Item* it = dynamic_cast<Item*>(iter);
						switch (it->GetObjID())
						{
						case 0: //enery + 5
						{
							this->Energy += it->GetValue();
							it->SetValue(0);
							it->SetActive(false);
							break;
						}
						case 1: //enery + 10
						{
							this->Energy += it->GetValue();
							it->SetValue(0);
							it->SetActive(false);
							break;
						}
						case 2:
						{
							this->StopWatch = true;
							this->StartStopWatch = GetTickCount();
							break;
						}

						case 3:
						{
							SubWeapon = SW_windmill;
							break;
							break;
						}
						case 4: //Restore
						{
							SubWeapon = SW_shuriken;
							break;
						}
						case 5:
						{
							this->score += 500;
							break;
						}
						case 6:
						{
							this->score += 1000;
							break;
						}
						case 8: //taoj vong lua
						{
							break;
						}
						case 11://jump Scroll
						{
							SubWeapon = SW_jump_Scroll_Kill;
							break;
						}
						case 9://jump Scroll
						{
							this->HP += 16;
							if (this->HP > 16)
								this->HP = 16;

							break;
						}
						case 12:
						{
							this->Lives += 1;
							break;
						}
						case 13:
						{
							this->SubWeapon = SW_Flames;
							break;
						}
						default:
						{
							break;
						}
						}
					}
					this->alreadyGotItem = true;
				}
				break;
			}
			
			default:
			{
				break;
			}
			
			}
		}
	}

	// sweptAABB colision
	vector<CollisionEvent*>* coEvents = new vector<CollisionEvent*>();
	coEvents->clear();

	CalcPotentialCollisions(objects, coEvents);

	for (auto iter : *coEvents)
	{
		if (iter->obj->GetIsActive()) {
			switch (iter->obj->GetObjectType())
			{
			case JAGUAR:
			case SOLDIER:
			case BAT:
			case EAGLE:
			case ZOMBIE:
			case ZOMBIE_SWORD:
			{	
				if (!StopWatch)
				{
					if (GetState() == STATE_JUMP_SCROLL_HIT)
					{
						this->explode->SetActive(iter->obj->GetPosition());
						iter->obj->SetHP(0);
					}
					else
					{
						if(Demo)
							SetState(STATE_HURT);
					}
				}
				
			break;
			}
			case HIDE_OBJECT:
			{
				HideObject* h = dynamic_cast<HideObject*> (iter->obj);
				if ((h->getType() == TOP_LADDER || h->getType() == BOTTOM_LADDER) && (GetState() == STATE_ON_LADDER || GetState() == STATE_CLIMBING))
				{
					
					SetState(STATE_FALL);
				}
				else if (h->getType() == END_MAP)
				{
					isInTheEndOfMap = true;
				}
				break;
			}
			case LADDER:
			{
				if (state != STATE_ON_LADDER && state != STATE_CLIMBING)
					SetState(STATE_ON_LADDER);
				break;
			}
			case ITEM:
			{
				if (iter->obj->GetActive())
				{
					iter->obj->SetActive(false);
					Item* it = dynamic_cast<Item*>(iter->obj);
					switch (it->GetObjID())
					{
					case 0: //enery + 5
					{
						this->Energy += it->GetValue();
						it->SetValue(0);
						it->SetActive(false);
						break;
					}
					case 1: //enery + 10
					{
						this->Energy += it->GetValue();
						it->SetValue(0);
						it->SetActive(false);
						break;
					}
					case 2:
					{
						this->StopWatch = true;
						this->StartStopWatch = GetTickCount();
						break;
					}

					case 3:
					{
						SubWeapon =  SW_windmill;
						break;
						break;
					}
					case 4: //Restore
					{
						SubWeapon = SW_shuriken;
						break;
					}
					case 9://jump Scroll
					{
						this->HP += 16;
						if (this->HP > 16)
							this->HP = 16;
						
						break;
					}
					case 5:
					{
						this->score += 500;
						break;
					}
					case 6:
					{
						this->score += 1000;
						break;
					}
					case 11: 
					{
						SubWeapon = SW_jump_Scroll_Kill;
						break;
					}
					case 12:
					{
						this->Lives += 1;
						break;
					}
					case 13:
					{
						this->SubWeapon = SW_Flames;
						break;
					}
					default:
						break;
					}
				}
				break;
			}
			default:
				break;

			}
		}
	}
	for (auto iter : *coEvents) delete iter;
	coEvents->clear();
	delete coEvents;
}

void MainCharacter::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x + 2;
	r = l + 18;
	//t = position.y;
	//b = t + 31;


	if (state == STATE_SIT)
	{
		//l = position.x;
		t = position.y + 7;
		//r = position.x + 17;
		b = position.y + 31;
	}
	else if (state == STATE_JUMP || state == STATE_JUMP_TO)
	{
		//l = position.x;
		t = position.y;
		//r = position.x + 21;
		b = position.y + 21;
	}
	else if (state == STATE_SIT_ATTACK)
	{
		//l = position.x;
		t = position.y + 8;
		//r = position.x + 17;
		b = position.y + 31;
	}
	else
	{
		//l = position.x;
		t = position.y;
		//r = position.x + 17;
		b = position.y + 31;
	}
}