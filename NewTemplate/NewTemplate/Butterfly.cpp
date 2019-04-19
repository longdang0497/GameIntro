#include "Butterfly.h"

Butterfly::Butterfly()
{
	this->fly = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BUTTERFLY);
	this->SetObjectType(BUTTERFLY);
	this->HP = 1;

	direction = LEFT;
	currentSprite = fly;
}

Butterfly::~Butterfly()
{
	if (this->fly != NULL) delete this->fly;
}

Butterfly::Butterfly(D3DXVECTOR3 pos, int direction)
{
	this->fly = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BUTTERFLY);
	this->SetObjectType(BUTTERFLY);
	this->HP = 1;
	currentSprite = fly;
	this->position = pos;
	this->direction = direction;

}


void Butterfly::Update(float deltaTime, vector<Object*>* object)
{
	if (HP <= 0)
		return;
	Object::Update(deltaTime, object);


	this->veclocity.y = 0;
	this->veclocity.x = 0;

	this->currentSprite->UpdateSprite();
}

void Butterfly::Render()
{
	if (HP <= 0)
		return;

	Object::Render();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT)
		this->currentSprite->DrawSprite(pos, false);
	else
		this->currentSprite->DrawSprite(pos, true);
}

void Butterfly::HandleCollision(vector<Object*>* objects)
{
}



void Butterfly::GetBoundingBox(float &l, float &t, float &r, float &b)
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


