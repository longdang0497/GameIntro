#include "Crow.h"

Crow::Crow(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
//Butterfly::Butterfly(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2, Item * item) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->fly = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_CROW);
	this->SetObjectType(CROW);
	this->SetPosition(pos.x, pos.y);
	this->HP = 1;
	//this->item = item;	
}

Crow::~Crow()
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

void Crow::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (HP <= 0)
	{
		/*if (firstCreate == false)
		{
			this->ActivateItem();
			firstCreate = true;
			this->item->SetActive(true);
			this->item->Update(deltaTime);
		}	*/
		return;
	}

	if (MainCharacter::GetInstance()->IsStopWatch())
		return;

	Object::Update(deltaTime, objects);


	this->veclocity.y = 0;
	this->veclocity.x = 0;

	this->fly->UpdateSprite();
}

void Crow::Render()
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

void Crow::HandleCollision(vector<Object*>* objects)
{
}

void Crow::GetBoundingBox(float & l, float & t, float & r, float & b)
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

void Crow::Destroy()
{
}

void Crow::ActivateItem()
{
	//this->item = new Item(this->GetPosition(), this->itemId);
	////this->item->InitItemSprite();
	//this->item->InitItemSprite();
	//this->item->SetPosition(this->GetPosition().x, this->GetPosition().y);
	//this->item->SetObjID(this->itemId);
	//this->item->SetActive(true);
}
