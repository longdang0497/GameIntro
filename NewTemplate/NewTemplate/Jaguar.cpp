#include "Jaguar.h"

Jaguar* Jaguar::_instance = NULL;


Jaguar::Jaguar()
{
	this->jaguar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_JAGUAR);

	this->SetPosition(100, 100);
	this->SetVeclocity(0, 0);
	this->SetObjectType(JAGUAR);
	this->SetState(JAGUARS_LEFT);

	this->direction = 1;
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

}

void Jaguar::Render()
{
	///RenderBoundingBox();
	/*if (this->position.y < 32)
		return;*/
	//RenderBoundingBox();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == 1)
		this->jaguar->DrawSprite(pos, true);
	else
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

