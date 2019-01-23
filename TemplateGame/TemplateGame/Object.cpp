#include "Object.h"



Object::Object()
{
	this->curPos = new ObjectPosition();
	this->lastPos = new ObjectPosition();
	this->curVec = new ObjectVelocity();
	this->lastVec = new ObjectVelocity();
}

Object::~Object()
{
	curPos = nullptr;
	lastPos = nullptr;
	curVec = nullptr;
	lastVec = nullptr;
	nextObject = nullptr;
	preObject = nullptr;

	delete curPos;
	delete lastPos;
	delete curVec;
	delete lastVec;
	delete nextObject;
	delete preObject;
}


// Xử lý va chạm giữa 2 vật thể với nhau
// Giải thuật sử dụng là: sweptAABB
// Trục x, y với y hướng xuống
// Nháp lại khúc này xem thử giải thuật chạy đúng chưa
// Cái ý nghĩa của delta time là với vận vận tốc V thì trong 1s mình sẽ di được V quãng đường
// Nhưng thực tế trong game thì deltaTime là thời gian mà frame chạy và đó là thời gian thực của object. Tức 1s mình đang xét là deltaTime trong game
float Object::GetCollisionTime(Object * otherObject, COLLISION_DIRECTION & collisionDirection, float deltaTime)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	float vX = this->curVec->getVx() * deltaTime;
	float vY = this->curVec->getVy() * deltaTime;

	// Tìm khoảng cách giữa 2 vật thể
	// Object đang đi qua phải
	if (vX > 0.0f) {
		xInvEntry = otherObject->GetCurPos()->getPosX() - (this->GetCurPos()->getPosX() + this->objectWidth);
		xInvExit = (otherObject->objectWidth + otherObject->GetCurPos()->getPosX()) - this->curPos->getPosX();
	}

	// Object đang đi qua bên trái
	else {
		xInvEntry = (otherObject->curPos->getPosX() + otherObject->GetObjectWidth()) - this->curPos->getPosX();
		xInvExit = otherObject->GetCurPos()->getPosX() - (this->curPos->getPosX() + this->objectWidth);
	}

	// Vật thể đang đi xuống
	if (vY > 0.0f) {
		yInvEntry = otherObject->GetCurPos()->getPosY() - (this->curPos->getPosY() + this->objectHeight);
		yInvExit = otherObject->curPos->getPosY() + otherObject->objectHeight - this->curPos->getPosY();
	}

	// Vật thể đang đi lên
	else {
		yInvEntry = (otherObject->curPos->getPosY() + otherObject->objectHeight) - this->curPos->getPosY();
		yInvExit = otherObject->curPos->getPosY() - (this->curPos->getPosY() + this->objectHeight);
	}

	// Tính khoảng thời gian va chạm và thời gian hết va chạm
	float xEntry, yEntry;
	float xExit, yExit;
	if (vX == 0.0f) {
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else {
		xEntry = xInvEntry / vX;
		xExit = xInvExit / vX;
	}

	if (vY == 0.0f) {
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else {
		yEntry = yInvEntry / vY;
		yExit = yInvExit / vY;
	}

	// Xac dinh truc nao bi va cham dau tien
	float entryTime = max(xEntry, yEntry);      // Cho biet thoi gian bat dau va cham
	float exitTime = min(xExit, yExit);			// Cho biet thoi gian ket thuc va cham

	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) {
		collisionDirection = NONE;
		return deltaTime;
	}
	else {
		if (xEntry > yEntry) { // này là đã va chạm ở trục Y rồi
			if (xInvEntry >= 0.0f) {
				if (this->curPos->getPosY() + this->objectHeight <= otherObject->curPos->getPosY() 
					|| this->curPos->getPosY() >= otherObject->curPos->getPosY() + otherObject->objectHeight)

					collisionDirection = NONE;
				else
					collisionDirection = RIGHT;
			}
			else {
				if (this->curPos->getPosY() >= otherObject->curPos->getPosY() + otherObject->objectHeight
					|| this->curPos->getPosY() + this->objectHeight <= otherObject->curPos->getPosY())

					collisionDirection = NONE;
				else
					collisionDirection = LEFT;
			}
		}
		else {			// Này là va chạm với trục X rồi nè
			if (yInvEntry >= 0.0f) {
				if (this->curPos->getPosX() + this->objectWidth<= otherObject->curPos->getPosX()
					|| this->curPos->getPosX() >= otherObject->curPos->getPosX() + otherObject->objectWidth)
					collisionDirection = NONE;
				else
					collisionDirection = BOTTOM;
			}
			else {
				if (this->curPos->getPosX() + this->objectWidth <= otherObject->curPos->getPosX()
					|| this->curPos->getPosX() >= otherObject->curPos->getPosX() + otherObject->objectWidth)
					collisionDirection = NONE;
				else
					collisionDirection = TOP;
			}
		}
	}

	// Trả về thời gian va chạm
	return entryTime;
}

// Đám này là hàm ảo, để mấy con sau kế thừa rồi xài
void Object::InitSprites()
{
}

void Object::Update(float deltaTime)
{
}

void Object::Render()
{
}

void Object::Init(float posX, float posY)
{
	this->curPos->setPosX(posX);
	this->curPos->setPosY(posY);
	this->isActive = true;
}

void Object::Destroy()
{
}

// Get/set methods
void Object::SetObjectType(OBJECT_TYPE objectType)
{
	this->objectType = objectType;
}

void Object::SetIsActive(bool isActive)
{
	this->isActive = isActive;
}

void Object::SetCurPosition(ObjectPosition * curPos)
{

	this->curPos = curPos;
}

void Object::SetLastPosition(ObjectPosition * lastPos)
{

	this->lastPos = lastPos;
}

void Object::SetCurVec(ObjectVelocity * curVec)
{

	this->curVec = curVec;
}

void Object::SetLastVec(ObjectVelocity * lastVec)
{
	this->lastVec = lastVec;
}

void Object::SetNextObject(Object * nextObject)
{
	this->nextObject = nextObject;
}

void Object::SetPreObject(Object * preObject)
{
	this->preObject = preObject;
}

void Object::SetObjectWidth(int width)
{
	this->objectWidth = width;
}

void Object::SetObjectHeight(int height)
{
	this->objectHeight = height;
}

void Object::SetGravity(float gravity)
{
	this->gravity = gravity;
}

void Object::SetSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	this->spriteHandler = spriteHandler;
}

OBJECT_TYPE Object::GetObjectType()
{
	return this->objectType;
}

bool Object::GetIsActive()
{
	return this->isActive;
}

ObjectPosition * Object::GetCurPos()
{
	return this->curPos;
}

ObjectPosition * Object::GetLastPos()
{
	return this->lastPos;
}

ObjectVelocity * Object::GetCurVec()
{
	return this->curVec;
}

ObjectVelocity * Object::GetLastVec()
{
	return this->lastVec;
}

Object * Object::GetNextObject()
{
	return this->nextObject;
}

Object * Object::GetPreObject()
{
	return this->preObject;
}

int Object::GetObjectWidth()
{
	return this->objectWidth;
}

int Object::GetObjectHeight()
{
	return this->objectHeight;
}

float Object::GetGravity()
{
	return this->gravity;
}

LPD3DXSPRITE Object::GetSpriteHandler()
{
	return this->spriteHandler;
}
