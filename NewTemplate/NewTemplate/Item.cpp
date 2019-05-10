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
	this->SetPosition(pos.x + 10, pos.y + 40);
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
	if (this->blueR != NULL)
	{
		delete[] this->blueR;
		this->blueR = NULL;
	}

	if (this->orangeR != NULL) {
		delete[] this->orangeR;
		this->orangeR = NULL;
	}

	if (this->blueDart != NULL) {
		delete[] this->blueDart;
		this->blueDart = NULL;
	}

	if (this->orangeDart != NULL) {
		delete[] this->orangeDart;
		this->orangeDart = NULL;
	}

	if (this->blueJar != NULL) {
		delete[] this->blueJar;
		this->blueJar = NULL;
	}

	if (this->orangeJar != NULL) {
		delete[] this->orangeJar;
		this->orangeJar = NULL;
	}

	if (this->bluePocket != NULL) {
		delete[] this->bluePocket;
		this->bluePocket = NULL;
	}

	if (this->orangePocket != NULL) {
		delete[] this->orangePocket;
		this->orangePocket = NULL;
	}

	if (this->bigShuriken != NULL) {
		delete[] this->bigShuriken;
		this->bigShuriken = NULL;
	}

	if (this->itemFire != NULL) {
		delete[] this->itemFire;
		this->itemFire = NULL;
	}

	if (this->sandglass != NULL) {
		delete[] this->sandglass;
		this->sandglass = NULL;
	}
}

void Item::InitItemSprite()
{
	switch (this->objectID) {
	case BLUE_R_ID: // SPIRITUAL STRENGTH 5 POINTS
		this->blueR = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BLUE_R);
		break;
	case ORANGE_R_ID: // SPIRITUAL STRENGTH 10 POINTS
		this->orangeR = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ORANGE_R);
		break;
	case BLUE_DART_ID: // THROWING STAR
		this->blueDart = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BLUE_DART);
		break;
	case ORANGE_DART_ID: // WINDMILL THROWING STAR
		this->orangeDart = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ORANGE_DART);
		break;
	case BLUE_JAR_ID:
		/*this->strength = 5;
		this->SetObjectType(BLUE_JAR);
		this->blueR = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BLUE_R);*/
		break;
	case ORANGE_JAR_ID:	// RESTORE PHYSICAL STRENGTH
		this->orangeJar = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ORANGE_JAR);
		break;
	case BLUE_POCKET_ID:	// BONUS 500 POINTS
		this->bluePocket = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BLUE_POCKET);
		break;
	case ORANGE_POCKET_ID:	 // BONUS 1000 POINTS
		this->orangePocket = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ORANGE_POCKET);
		break;
	case BIG_SHURIKEN_ID:
		this->bigShuriken = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_SHURIKEN);
		break;
	case ITEM_FIRE_ID:	//THE ART OF THE FIRE WHEEL
		this->itemFire = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_ITEM_FIRE);
		break;
	case SANDGLASS_ID: // TIME FREEZE
		this->sandglass = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_SANDGLASS);
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

		this->PlusPosition(this->veclocity.x, this->veclocity.y);
		
		switch (this->objectID) {
		case BLUE_R_ID: // SPIRITUAL STRENGTH 5 POINTS
			this->blueR->UpdateSprite();			
			break;
		case ORANGE_R_ID: // SPIRITUAL STRENGTH 10 POINTS
			this->orangeR->UpdateSprite();
			break;
		case BLUE_DART_ID: // THROWING STAR
			this->blueDart->UpdateSprite();
			break;
		case ORANGE_DART_ID: // WINDMILL THROWING STAR
			this->orangeDart->UpdateSprite();
			break;
		case BLUE_JAR_ID:
			/*this->blueR = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_MAIN), PATH_BLUE_R);*/
			break;
		case ORANGE_JAR_ID:	// RESTORE PHYSICAL STRENGTH
			this->orangeJar->UpdateSprite();
			break;
		case BLUE_POCKET_ID:	// BONUS 500 POINTS
			this->bluePocket->UpdateSprite();
			break;
		case ORANGE_POCKET_ID:	 // BONUS 1000 POINTS
			this->orangePocket->UpdateSprite();
			break;
		case BIG_SHURIKEN_ID:
			this->bigShuriken->UpdateSprite();
			break;
		case ITEM_FIRE_ID:	//THE ART OF THE FIRE WHEEL
			this->itemFire->UpdateSprite();
			break;
		case SANDGLASS_ID: // TIME FREEZE
			this->sandglass->UpdateSprite();
			break;
		}				

		vector<Object*> *ground = new vector<Object*>();
		ground->clear();

		for (auto iter : *objects) {
			if (iter->GetObjectType() == BRICK || iter->GetObjectType() == MAIN_CHARACTER) {
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

		switch (this->objectID) {
		case BLUE_R_ID: // SPIRITUAL STRENGTH 5 POINTS
			this->blueR->DrawSprite(pos, false, alpha);
			break;
		case ORANGE_R_ID: // SPIRITUAL STRENGTH 10 POINTS
			this->orangeR->DrawSprite(pos, false, alpha);
			break;
		case BLUE_DART_ID: // THROWING STAR
			this->blueDart->DrawSprite(pos, false, alpha);
			break;
		case ORANGE_DART_ID: // WINDMILL THROWING STAR
			this->orangeDart->DrawSprite(pos, false, alpha);
			break;
		case BLUE_JAR_ID:
			/*this->blueJar->DrawSprite(pos, false, alpha);*/
			break;
		case ORANGE_JAR_ID:	// RESTORE PHYSICAL STRENGTH
			this->orangeJar->DrawSprite(pos, false, alpha);
			break;
		case BLUE_POCKET_ID:	// BONUS 500 POINTS
			this->bluePocket->DrawSprite(pos, false, alpha);
			break;
		case ORANGE_POCKET_ID:	 // BONUS 1000 POINTS
			this->orangePocket->DrawSprite(pos, false, alpha);
			break;
		case BIG_SHURIKEN_ID:
			this->bigShuriken->DrawSprite(pos, false, alpha);
			break;
		case ITEM_FIRE_ID:	//THE ART OF THE FIRE WHEEL
			this->itemFire->DrawSprite(pos, false, alpha);
			break;
		case SANDGLASS_ID: // TIME FREEZE
			this->sandglass->DrawSprite(pos, false, alpha);
			break;
		}
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

		for (auto iter : *objects)
		{
			if (iter->GetObjectType() == MAIN_CHARACTER)
			{
				if (nY != 0)
					this->veclocity.y = 0;
				if (nX != 0) 
					this->isActive = false;
			}
			else {
				if (nX != 0)
					this->veclocity.x = 0;
				if (nY != 0)
					this->veclocity.y = 0;
				if (nY == -1)
					isOnGround = true;
			}
		}

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

		switch (this->objectID) {
		case BLUE_R_ID: // SPIRITUAL STRENGTH 5 POINTS
			r = l + blueR->GetWidth();
			b = t + blueR->GetHeight();
			break;
		case ORANGE_R_ID: // SPIRITUAL STRENGTH 10 POINTS
			r = l + orangeR->GetWidth();
			b = t + orangeR->GetHeight();
			break;
		case BLUE_DART_ID: // THROWING STAR
			r = l + blueDart->GetWidth();
			b = t + blueDart->GetHeight();
			break;
		case ORANGE_DART_ID: // WINDMILL THROWING STAR
			r = l + orangeDart->GetWidth();
			b = t + orangeDart->GetHeight();
			break;
		case BLUE_JAR_ID:
			/*r = l + blueR->GetWidth();
			b = t + blueR->GetHeight();*/
			break;
		case ORANGE_JAR_ID:	// RESTORE PHYSICAL STRENGTH
			r = l + orangeJar->GetWidth();
			b = t + orangeJar->GetHeight();
			break;
		case BLUE_POCKET_ID:	// BONUS 500 POINTS
			r = l + bluePocket->GetWidth();
			b = t + bluePocket->GetHeight();
			break;
		case ORANGE_POCKET_ID:	 // BONUS 1000 POINTS
			r = l + orangePocket->GetWidth();
			b = t + orangePocket->GetHeight();
			break;
		case BIG_SHURIKEN_ID:
			r = l + bigShuriken->GetWidth();
			b = t + bigShuriken->GetHeight();
			break;
		case ITEM_FIRE_ID:	//THE ART OF THE FIRE WHEEL
			r = l + itemFire->GetWidth();
			b = t + itemFire->GetHeight();
			break;
		case SANDGLASS_ID: // TIME FREEZE
			r = l + sandglass->GetWidth();
			b = t + sandglass->GetHeight();
			break;
		}
	}
}

void Item::Destroy()
{
}
