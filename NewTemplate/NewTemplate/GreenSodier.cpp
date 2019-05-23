#include "GreenSodier.h"

GreenSodier::GreenSodier(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2, int state) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->HP = 1;
	this->SetObjectType(GREEN_SOLDIER);
	this->SetPosition(pos.x, pos.y);
	this->isActive = false;
	this->state = state;
	if (this->state == 0) // GREEN SOLDIER CHẠY
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_GREEN_SOLDIERS_WALK);
	else if (this->state == 1) // GREEN SOLDIER BẮN
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_GREEN_SOLDIERS_BAZOOKA);
	else if (this->state == 2) // GREEN PLAYER CHẠY
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_GREEN_PLAYER);

	this->bullets = new vector<BazookaBullet*>();
	BazookaBullet *S1 = new BazookaBullet();

	bullets->push_back(S1);

	WaitTime = GetTickCount();
	isShooting = false;
	count = 0;
}

GreenSodier::~GreenSodier()
{
	if (this->currentSprite != nullptr) {
		delete(currentSprite);
		currentSprite = NULL;
	}

	for (auto iter : *bullets)
	{
		delete(iter);
		iter = NULL;
	}
}

void GreenSodier::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (this->HP <= 0 && limitX1 == limitX2) 
		return;
	
	for (auto iter : *bullets)
	{
		iter->Update(deltaTime, objects);
	}

	if (this->position.y >= Graphic::GetInstance(NULL, NULL, L"", 1)->GetHeight()) {
		this->Destroy();
		return;
	}

	// Xét theo camera bên phải
	if (this->enemyAppearanceDirection == 1) {
		int temp = Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 1)->GetWidth();
		if (temp - this->position.x <= 3.0 && temp - this->position.x >= 0.0) {
			this->isActive = true;
			this->direction = -1;
		}
	}
	// Xét theo camera bên trái
	else {
		if (Camera::GetInstance()->getPosition().x - this->position.x <= 5.0 && Camera::GetInstance()->getPosition().x - this->position.x >= 0.0) {
			this->isActive = true;
			this->direction = 1;
		}
	}

	if (!this->isActive) return;

	if (this->enemyAppearanceDirection == 0 && this->position.x < Camera::GetInstance()->getPosition().x - 3.0
		|| this->position.x > Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 1)->GetWidth()) {
		this->Destroy();
		return;
	}

	if (position.x >= limitX2 && direction == RIGHT)
		direction = LEFT;

	if (position.x <= limitX1 && direction == LEFT)
		direction = RIGHT;

	if (GetTickCount() - WaitTime > 1200 && !isShooting && state == 1)
	{
		count = 0;
		isShooting = true;
		WaitNext = GetTickCount();
		Shoot();
	}

	if (isShooting)
		Shoot();

	Object::Update(deltaTime, objects);

	this->veclocity.y += 0.0018f * deltaTime;

	if (isOnGround) {
		if (this->state == 0 || this->state == 2)
			this->veclocity.x = 0.08 * direction;
		else
			this->veclocity.x = 0;
		this->currentSprite->UpdateSprite();
	}

	vector<Object*> *ground = new vector<Object*>();
	ground->clear();

	for (auto iter : *objects) {
		if (iter->GetObjectType() == BRICK) {
			ground->push_back(iter);
		}
	}

	this->HandleCollision(ground);

	delete ground;
}

void GreenSodier::Render()
{
	if (this->isActive == true)
	{
		if (HP <= 0) {
			return;
		}

		Object::Render();	
				
		this->position.z = 0;

		D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

		for (auto iter : *bullets)
		{
			iter->Render();
		}

		if (direction == RIGHT) {
			this->currentSprite->DrawSprite(pos, true);
		}
		else {
			this->currentSprite->DrawSprite(pos, false);
		}
	}
}

void GreenSodier::HandleCollision(vector<Object*>* objects)
{
	vector<CollisionEvent*> *coEvents = new vector<CollisionEvent*>();
	vector<CollisionEvent*> *coEventsResult = new vector<CollisionEvent*>();

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
			this->PlusPosition(minTx * this->deltaX + nX * 0.1f, minTy * this->deltaY + nY * 0.1f);

		if (nX != 0)
			this->veclocity.x = 0;
		if (nY != 0)
		{
			if (nY == -1)
			{
				this->veclocity.y = 0;
				isOnGround = true;
			}
		}
	}

	for (int i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void GreenSodier::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (HP > 0)
	{
		l = position.x;
		t = position.y;
		r = l + currentSprite->GetWidth();
		b = t + currentSprite->GetHeight();
	}
	else l = r = b = t = 0;
}

void GreenSodier::Destroy()
{
	this->position = defaultPosition;
	//this->position.y -= 2;
	this->HP = 1;
	this->isActive = false;
}

void GreenSodier::Shoot()
{
	if (count != this->bullets->size())
	{
		if (GetTickCount() - WaitNext >= 400)
		{
			bullets->at(count)->SetPosition(this->position.x - 8, this->position.y);
			bullets->at(count)->SetVeclocity(0.1*this->direction, 0);
			bullets->at(count)->SetHP(1);
			bullets->at(count)->SetIsActive(true);
			bullets->at(count)->SetDirection(this->direction);
			count++;
			WaitNext = GetTickCount();
		}
	}
	else
	{
		isShooting = false;
		WaitTime = GetTickCount();
		count = 0;
	}
}

vector<BazookaBullet*>* GreenSodier::GetBullets()
{
	return this->bullets;
}
