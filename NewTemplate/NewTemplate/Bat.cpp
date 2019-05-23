#include "Bat.h"



Bat::Bat(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->sprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_BAT);
	this->HP = 1;
	this->SetObjectType(BAT);
	this->isActive = false;
}

void Bat::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (this->HP <= 0 ) {
		return;
	}

	if (MainCharacter::GetInstance()->IsStopWatch())
		return;


	//Xuát hiện bên phải
	if (this->enemyAppearanceDirection == 1) {
		if (Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 0)->GetWidth() - this->defaultPosition.x >= -2
			&& Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", 0)->GetWidth() - this->defaultPosition.x <= 0) {
			this->isActive = true;
			this->direction = LEFT;
		}
	}

	// Xuất hiện bên trái
	else {
		if (Camera::GetInstance()->getPosition().x - this->defaultPosition.x <= 2
			&& Camera::GetInstance()->getPosition().x - this->defaultPosition.x >= 0) {
			this->isActive = true;
			this->direction = RIGHT;
		}
	}

	if (!this->isActive) return;

	if (!(this->position.x >= MainCharacter::GetInstance()->GetPosition().x - 128
		&& this->position.x <= MainCharacter::GetInstance()->GetPosition().x + 128)) {
		this->Destroy();
		return;
	}

	//y = 50 * sin(2 * PI * x / 180) + 200
	this->position.x += 0.05 * direction * deltaTime;
	this->position.y = 20 * sin(10 * 3.1415926535 * this->position.x / 180) + this->defaultPosition.y;
	this->sprite->UpdateSprite();
}

void Bat::Render()
{
	if (!this->isActive) {
		return;
	}

	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT) {
		this->sprite->DrawSprite(pos, true);
	}
	else {
		this->sprite->DrawSprite(pos, false);
	}
}

void Bat::HandleCollision(vector<Object*>* objects)
{
}

void Bat::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void Bat::Destroy()
{
	this->position = defaultPosition;
	this->HP = 1;
	this->isActive = false;
}
