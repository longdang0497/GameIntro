#include "Eagle.h"

Eagle::~Eagle()
{
	if (this->sprite != NULL) delete this->sprite;
}

Eagle::Eagle(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_EAGLE);
	this->SetObjectType(EAGLE);
	this->HP = 1;
	this->isActive = false;
	this->flyingToBottom = false;
	this->flyingToRight = false;
	int count = 0;
	this->currentPosition = defaultPosition;
	this->lastPosition = defaultPosition;
	this->SetVeclocity(0.1, 0);
	this->amplitude = DEFAULT_AMPLITUDE;
}

void Eagle::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (this->HP <= 0) {
		return;
	}

	if (MainCharacter::GetInstance()->IsStopWatch())
		return;

	this->sprite->UpdateSprite();

	if (GetTickCount() - this->lastReachTime <= FREEZE_TIME) {
		return;
	}


	// Xét theo camera bên phải
	if (this->enemyAppearanceDirection == 1) {
		if (Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 0)->GetWidth() - this->defaultPosition.x >= -2
			&& Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 0)->GetWidth() - this->defaultPosition.x <= 0) {

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

	if (this->position.x <= Camera::GetInstance()->getPosition().x - 20 || this->position.x >= Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 1)->GetWidth() + 10
		|| this->amplitude == 0) {
		this->Destroy();
		return;
	}

	if (floor(abs(this->position.x - this->currentPosition.x)) <= 1 && floor(abs(this->position.x - this->currentPosition.x)) >= 0
		|| floor(abs(this->position.y - this->currentPosition.y)) <= 1 && floor(abs(this->position.y - this->currentPosition.y) >= 0 && this->isActive)) {

		float left = 0.0f, top = 0.0f;

		this->lastPosition.x = this->currentPosition.x;
		this->lastPosition.y = this->currentPosition.y;


		this->lastReachTime = GetTickCount();




		if (count % 2 == 0) {

			if (MainCharacter::GetInstance()->GetPosition().x < this->position.x) {
				this->flyingToRight = false;
				this->flyingToBottom = true;
				left = MainCharacter::GetInstance()->GetPosition().x - this->amplitude;
			}
			else {
				this->flyingToRight = true;
				this->flyingToBottom = true;
				left = MainCharacter::GetInstance()->GetPosition().x + this->amplitude;
			}
			top = MainCharacter::GetInstance()->GetPosition().y - 15;
			this->amplitude -= 5;

			this->currentPosition = { left, top, 0 };
			this->count++;


		}
		else {
			this->flyingToRight = MainCharacter::GetInstance()->GetPosition().x < this->position.x ? true : false;
			this->flyingToBottom = false;
			left = MainCharacter::GetInstance()->GetPosition().x < this->position.x ? this->position.x + 25 : this->position.x - 25;
			if (count < 6) {
				top = 210;
			}
			else {
				top = 150;
			}

			this->currentPosition = { left, top, 0 };
			this->count++;
		}



	}


	if (this->flyingToRight) {
		this->direction = RIGHT;
	}
	else {
		this->direction = LEFT;
	}

	this->SetVx(0.18*this->direction);

	// current
	float x1 = this->currentPosition.x;
	float y1 = this->currentPosition.y;

	// lastPosition
	float x0 = this->lastPosition.x;
	float y0 = this->lastPosition.y;

	// y = ax + b
	// y0 = ax0 + b
	// y1 = ax1 + b
	// Ra được thông số a, b

	if (x1 - x0 == 0.0)
	{
		this->position.x = this->position.x;
		this->position.y = this->position.y;
	}
	else {
		float a = (y1 - y0) / (x1 - x0);
		float b = y0 - a * x0;
		this->position.x += this->veclocity.x * deltaTime;
		this->position.y = a * this->position.x + b;
	}

}

void Eagle::Render()
{
	if (!this->isActive)
		return;

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
	if (HP > 0) {
		this->objectWidth = this->sprite->GetWidth();
		this->objectHeight = this->sprite->GetHeight();
		l = position.x;
		t = position.y;
		r = l + this->objectWidth;
		b = t + this->objectHeight;
	}
	else {
		l = t = r = b = 0;
	}
}

void Eagle::Destroy()
{
	this->position = defaultPosition;
	this->HP = 1;
	this->isActive = false;
	this->flyingToBottom = false;
	this->flyingToRight = false;
	this->count = 0;
	this->currentPosition = defaultPosition;
	this->lastPosition = defaultPosition;
	this->amplitude = DEFAULT_AMPLITUDE;
}
