#include "Eagle.h"

bool Eagle::CheckCurrentPosAndPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float min, float max)
{
	float distanceX = floor(abs(pos1.x - pos2.x));
	float distanceY = floor(abs(pos1.y - pos2.y));
	return distanceX <= max && distanceX >= min || distanceY <= max && distanceY >= min;
}

Eagle::~Eagle()
{
	if (this->sprite != NULL) delete this->sprite;
}

// limitX1 dung de di chuyen dai bang o phia tren, limitX2 dung de di chuyen dai bang o phia duoi
Eagle::Eagle(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_EAGLE);
	this->HP = 1;
	this->SetObjectType(EAGLE);
	this->isActive = false;
	this->count = 0;
	this->canAppearAgain = true;
	this->lastReachTime = GetTickCount();
	this->currentPos = this->defaultPosition;
	this->lastPos = this->defaultPosition;
	this->SetVeclocity(EAGLE_VEC_X, 0);
}

void Eagle::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (this->HP <= 0)
		return;

	if (MainCharacter::GetInstance()->IsStopWatch())
		return;

	this->sprite->UpdateSprite();

	// Xét theo camera bên phải
	if (this->enemyAppearanceDirection == 1) {
		if (Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", NULL)->GetWidth() - this->defaultPosition.x >= -2
			&& Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", NULL)->GetWidth() - this->defaultPosition.x <= 0) {

			if (this->canAppearAgain) {
				this->isActive = true;
				this->flyingToRight = false;
				this->flyingToBottom = true;
			}

			this->canAppearAgain = !this->canAppearAgain;

		}
	}
	// Xét theo camera bên trái
	else {
		if (Camera::GetInstance()->getPosition().x - this->defaultPosition.x <= 2
			&& Camera::GetInstance()->getPosition().x - this->defaultPosition.x >= 0) {
			if (this->canAppearAgain) {
				this->isActive = true;
				this->flyingToRight = true;
				this->flyingToBottom = true;
			}

			this->canAppearAgain = !this->canAppearAgain;
		}
	}

	if (!this->isActive) return;

	if (GetTickCount() - this->lastReachTime <= EAGLE_FREEZE_TIME)
		return;

	if (this->CheckCurrentPosAndPos(this->position, this->currentPos, 0.0f, 1.0f)) {

		float left = 0.0f ,top = 0.0f;

		this->lastPos.x = this->currentPos.x;
		this->lastPos.y = this->currentPos.y;
		this->lastReachTime = GetTickCount();

		if (count % 2 == 0) {
			top = EAGLE_HIGHTEST_POS_Y;
			
			if (this->position.x >= MainCharacter::GetInstance()->GetPosition().x) {
				left = MainCharacter::GetInstance()->GetPosition().x - this->limitX1;
				this->flyingToRight = false;
			}
			else {
				left = MainCharacter::GetInstance()->GetPosition().x + this->limitX1;
				this->flyingToRight = true;
			}
		}
		else {
			top = EAGLE_LOWEST_POS_Y;

			if (this->position.x >= MainCharacter::GetInstance()->GetPosition().x) {
				left = this->lastPos.x + (this->limitX2 - this->limitX1);
				this->flyingToRight = true;
			}
			else {
				left = this->lastPos.x - (this->limitX2 - this->limitX1);
				this->flyingToRight = false;
			}
		}

 		this->currentPos = { left, top, 0.0f };
		this->count++;
	}
	
	CKeyGame* k = CKeyGame::getInstance();

	if (k->keyRight)
	{
		this->currentPos.x += 2.0f;
	}
	else if(k->keyLeft) {
		this->currentPos.x -= 2.0f;
	}

	if (this->flyingToRight)
		this->direction = RIGHT;
	else
		this->direction = LEFT;

	this->SetVx(EAGLE_VEC_X * this->direction);

	// current Pos
	float x1 = this->currentPos.x;
	float y1 = this->currentPos.y;

	// last Pos
	float x0 = this->lastPos.x;
	float y0 = this->lastPos.y;


	// y = ax + b
	// y0 = ax0 + b
	// y1 = ax1 + b
	// Ra được thông số a, b 

	if (x1 - x0 == 0) {
		this->position.x = this->position.x;
		this->position.y = this->position.y;
	}
	else {
		float a = (y1 - y0) / (x1 - x0);
		float b = y0 - a * x0;

		this->position.x += this->veclocity.x * deltaTime;
		this->position.y = a * this->position.x + b;
	}

	if (this->position.y < 150.0f && this->count >=2) {
 		int i = 1;
	}

}

void Eagle::Render()
{
	if (!this->isActive || this->HP<=0)
		return;

	Object::Render();

	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT) {
		this->sprite->DrawSprite(pos, true);
	}
	else {
		this->sprite->DrawSprite(pos, false);
	}
}

void Eagle::HandleCollision(vector<Object*>* objects)
{
}

void Eagle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (this->HP > 0 && this->isActive) {
		this->objectWidth = this->sprite->GetWidth();
		this->objectHeight = this->sprite->GetHeight();

		l = this->position.x;
		t = this->position.y;
		b = t + this->objectHeight;
		r = l + this->objectWidth;
	}
}

void Eagle::Destroy()
{
	this->HP = 1;
	this->isActive = false;
	this->position = this->defaultPosition;
	this->currentPos = this->defaultPosition;
	this->lastPos = this->defaultPosition;
	this->count = 0;
	this->canAppearAgain = true;
}
