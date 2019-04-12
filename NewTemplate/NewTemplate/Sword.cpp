#include "Sword.h"

Sword* Sword::_instance = NULL;

Sword::Sword()
{
	isActive = false;
	direction = 1;
	swordSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_MAIN_SWORD);

	currentSprite = swordSprite;
}


Sword::~Sword()
{

}

void Sword::Update(float t, vector<Object*> *object)
{
	//position = MainCharacter::GetInstance()->GetPosition();
	if(isActive)
		currentSprite->UpdateSprite();
	if (isActive && currentSprite->getDone())
	{
		isActive = false;
		currentSprite->setDone(false);
	}
}
void Sword::Render()
{
	//RenderBoundingBox();
	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (isActive)
	{

		if (direction == 1)
		{
			currentSprite->DrawSprite(pos, true); 
		}
		else
		{
			currentSprite->DrawSprite(pos, false);
		}

	}
}

void Sword::HandleCollision(vector<Object*>* objects)
{
}

void Sword::CalCulatePosition()
{
	
}

void Sword::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (isActive)
	{
		switch (currentSprite->GetIndex())
		{
		case 0:
			l = position.x;
			t = position.y;
			b = t;
			r = l;
			break;
		case 1:
			l = position.x;
			t = position.y + 5;
			b = t + 10;
			r = l + 27;
			break;
		case 2:
			if (direction == 1)
				l = position.x;
			else
				l = position.x+16;
			t = position.y;
			b = t + 5;
			r = l + 9;
			break;
		}
	}
	else
	{
		l = position.x;
		t = position.y;
		b = t;
		r = l;
	}
}

void Sword::checkCollisioWithEnemy(vector<Object*> *coObjects)
{

}
