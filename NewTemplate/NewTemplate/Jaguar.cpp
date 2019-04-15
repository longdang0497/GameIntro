#include "Jaguar.h"

Jaguar* Jaguar::_instance = NULL;

Jaguar::Jaguar()
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);

	this->SetPosition(200, 200);
	this->SetVeclocity(0, 0);
	this->SetObjectType(JAGUAR);
	this->SetState(JAGUARS_LEFT);

	//this->direction = 1;
	this->score = 0;
}

Jaguar::~Jaguar()
{
	if (this->jaguar != NULL) delete this->jaguar;
}

JAGUARS_STATE Jaguar::GetState()
{
	return this->state;
}

void Jaguar::SetState(JAGUARS_STATE value)
{
	this->state = value;
}

void Jaguar::Update(float deltaTime, vector<Object*>* object)
{
	this->SetVx(0.05f);
	if (this->GetState() == JAGUARS_LEFT)
		this->SetPosition((this->GetVeclocity().x * deltaTime) + this->GetPosition().x, this->GetPosition().y);
	else if (this->GetState() == JAGUARS_RIGHT)
		this->SetPosition((-this->GetVeclocity().x * deltaTime) + this->GetPosition().x, this->GetPosition().y);

	this->jaguar->UpdateSprite();
}

void Jaguar::Render()
{
	///RenderBoundingBox();
	/*if (this->position.y < 32)
		return;*/
	//RenderBoundingBox();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (this->GetState() == JAGUARS_LEFT)
		this->jaguar->DrawSprite(pos, true);
	else if (this->GetState() == JAGUARS_RIGHT)
		this->jaguar->DrawSprite(pos, false);
}

void Jaguar::HandleCollision(vector<Object*>* objects)
{
}

void Jaguar::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = position.x;
	t = position.y;
	r = l + objectWidth;
	b = t + objectHeight;
}

