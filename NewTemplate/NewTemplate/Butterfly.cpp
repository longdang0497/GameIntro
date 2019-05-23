#include "Butterfly.h"

Butterfly::Butterfly(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
//Butterfly::Butterfly(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2, Item * item) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->fly = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BUTTERFLY);
	this->SetObjectType(BUTTERFLY);
	this->SetPosition(pos.x, pos.y);
	this->HP = 1;
	//this->item = item;	
}

Butterfly::~Butterfly()
{
	if (this->item != nullptr && this->GetHP() <= 0) {
		delete item;
		item = NULL;
	}

	if (this->fly != nullptr) {
		delete(fly); 
		fly = NULL;
	}
}

void Butterfly::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (HP <= 0)
	{	
		return;
	}

	Object::Update(deltaTime, objects);


	this->veclocity.y = 0;
	this->veclocity.x = 0;

	this->fly->UpdateSprite();
}

void Butterfly::Render()
{
	if (HP <= 0)
	{
		//this->item->Render();
		return;
	}

	Object::Render();
	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (direction == RIGHT)
		this->fly->DrawSprite(pos, false);
	else
		this->fly->DrawSprite(pos, true);
}

void Butterfly::HandleCollision(vector<Object*>* objects)
{
}

void Butterfly::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (HP > 0)
	{
		l = position.x;
		t = position.y;
		r = l + fly->GetWidth();
		b = t + fly->GetHeight();
	}
	else l = r = b = t = 0;
}

void Butterfly::Destroy()
{
}

void Butterfly::ActivateItem()
{
	//this->item = new Item(this->GetPosition(), this->itemId);
	////this->item->InitItemSprite();
	//this->item->InitItemSprite();
	//this->item->SetPosition(this->GetPosition().x, this->GetPosition().y);
	//this->item->SetObjID(this->itemId);
	//this->item->SetActive(true);
}
