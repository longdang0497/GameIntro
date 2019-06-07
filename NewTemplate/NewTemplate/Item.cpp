#include "Item.h"

Item* Item::_instance = NULL;

Item::Item()
{
	//this->objectID = objectID;
	//this->defaultPosition = pos;
	//this->position = pos;
	this->veclocity = { 0,0,0 };
	this->isActive = false;
	this->SetObjectType(ITEM);
	this->SetHP(1);
	this->isOnGround = false;
	this->timeAppear = 5000;
}

Item::Item(D3DXVECTOR3 pos, int objectID)
{
	this->objectID = objectID;
	//this->defaultPosition = pos;
	this->SetPosition(pos.x, pos.y);
	this->SetObjectType(ITEM);
	this->veclocity = { 0,0,0 };
	this->isActive = false;
	this->SetHP(1);
	this->InitItemSprite();
	this->isOnGround = false;
	this->timeAppear = 5000;
}

Item::~Item()
{
	
	if (this->currentSprite != NULL) {
		delete[] this->currentSprite;
		this->currentSprite = NULL;
	}
}

void Item::InitItemSprite()
{
	switch (this->objectID) {
	case BLUE_R_ID: // SPIRITUAL STRENGTH 5 POINTS
		this->value = 5;
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BLUE_R);
		break;
	case ORANGE_R_ID: // SPIRITUAL STRENGTH 10 POINTS
		this->value = 10;
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ORANGE_R);
		break;
	case BLUE_DART_ID: // THROWING STAR
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BLUE_DART);
		break;
	case ORANGE_DART_ID: // WINDMILL THROWING STAR
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ORANGE_DART);
		break;
	case BLUE_JAR_ID:
		/*this->strength = 5;
		this->SetObjectType(BLUE_JAR);
		this->blueR = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BLUE_R);*/
		break;
	case ORANGE_JAR_ID:	// RESTORE PHYSICAL STRENGTH
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ORANGE_JAR);
		break;
	case BLUE_POCKET_ID:	// BONUS 500 POINTS
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BLUE_POCKET);
		break;
	case ORANGE_POCKET_ID:	 // BONUS 1000 POINTS
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ORANGE_POCKET);
		break;
	case BIG_SHURIKEN_ID:
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_SHURIKEN);
		break;
	case ITEM_FIRE_ID:	//THE ART OF THE FIRE WHEEL
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ITEM_FIRE);
		break;
	case SANDGLASS_ID: // TIME FREEZE
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_SANDGLASS);
		break;
	case JUMP_SCROLL: // ALLOW JUMP_SCROLL
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_JUMP_SCROLL);
		break;
	case PLUS_LIVE_ID: 
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_PLUS_LIVE);
		break;
	case FLAMES_ID:
		this->currentSprite = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_FLAMES);
		break;
	}
}

void Item::SetObjID(int value)
{
	this->objectID = value;
}

void Item::Update(float deltaTime, std::vector<Object*>* objects)
{	
	if (this->isActive == true)
	{
		if (HP <= 0)
			return;
		alpha = 255;

		Object::Update(deltaTime, objects);

		this->veclocity.y += 0.0015f*deltaTime;
		this->veclocity.x = 0;		

		this->currentSprite->UpdateSprite();

		vector<Object*> *ground = new vector<Object*>();
		ground->clear();

		for (auto iter : *objects) {
			if (iter->GetObjectType() == BRICK ) {
				ground->push_back(iter);
			}
		}

		this->HandleCollision(ground);		

		// Tính thời gian hiển thị
		timeAppear -= deltaTime;
		// Nếu hết thời gian thì nổ
		if (timeAppear > 0 && timeAppear <= 800) 
			this->alpha = 128;
		if (timeAppear <= 0)
			this->isActive = false;

		delete ground;
	}
}

void Item::Render()
{
	if (this->isActive == true)
	{
		if (HP <= 0)
			return;

		Object::Render();
		this->position.z = 0;

		D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);
		this->currentSprite->DrawSprite(pos, false, alpha);
	}
}

void Item::HandleCollision(vector<Object*>* objects)
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

		this->PlusPosition(minTx*this->deltaX + nX * 0.1f, minTy*this->deltaY + nY * 0.1f);
		if (nX != 0)
				this->veclocity.x = 0;
		if (nY != 0)
				this->veclocity.y = 0;
		if (nY == -1)
			isOnGround = true;
		}

	

	for (int i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}

	delete coEvents;
	delete coEventsResult;
}

void Item::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (this->isActive == true)
	{
		l = position.x;
		t = position.y;
		r = l + currentSprite->GetWidth();
		b = t + currentSprite->GetHeight();
	}
	else l = t = r = b = 0;
}

void Item::Destroy()
{
}
