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

	float vX = this->curVec->GetVx() * deltaTime;
	float vY = this->curVec->GetVy() * deltaTime;

	// Tìm khoảng cách giữa 2 vật thể
	// Object đang đi qua phải
	if (vX > 0.0f) {
		xInvEntry = otherObject->GetCurPos()->GetPosX() - (this->GetCurPos()->GetPosX() + this->objectWidth);
		xInvExit = (otherObject->objectWidth + otherObject->GetCurPos()->GetPosX()) - this->curPos->GetPosX();
	}

	// Object đang đi qua bên trái
	else {
		xInvEntry = (otherObject->curPos->GetPosX() + otherObject->GetObjectWidth()) - this->curPos->GetPosX();
		xInvExit = otherObject->GetCurPos()->GetPosX() - (this->curPos->GetPosX() + this->objectWidth);
	}

	// Vật thể đang đi xuống
	if (vY > 0.0f) {
		yInvEntry = otherObject->GetCurPos()->GetPosY() - (this->curPos->GetPosY() + this->objectHeight);
		yInvExit = otherObject->curPos->GetPosY() + otherObject->objectHeight - this->curPos->GetPosY();
	}

	// Vật thể đang đi lên
	else {
		yInvEntry = (otherObject->curPos->GetPosY() + otherObject->objectHeight) - this->curPos->GetPosY();
		yInvExit = otherObject->curPos->GetPosY() - (this->curPos->GetPosY() + this->objectHeight);
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
				if (this->curPos->GetPosY() + this->objectHeight <= otherObject->curPos->GetPosY() 
					|| this->curPos->GetPosY() >= otherObject->curPos->GetPosY() + otherObject->objectHeight)

					collisionDirection = NONE;
				else
					collisionDirection = RIGHT;
			}
			else {
				if (this->curPos->GetPosY() >= otherObject->curPos->GetPosY() + otherObject->objectHeight
					|| this->curPos->GetPosY() + this->objectHeight <= otherObject->curPos->GetPosY())

					collisionDirection = NONE;
				else
					collisionDirection = LEFT;
			}
		}
		else {			// Này là va chạm với trục X rồi nè
			if (yInvEntry >= 0.0f) {
				if (this->curPos->GetPosX() + this->objectWidth<= otherObject->curPos->GetPosX()
					|| this->curPos->GetPosX() >= otherObject->curPos->GetPosX() + otherObject->objectWidth)
					collisionDirection = NONE;
				else
					collisionDirection = BOTTOM;
			}
			else {
				if (this->curPos->GetPosX() + this->objectWidth <= otherObject->curPos->GetPosX()
					|| this->curPos->GetPosX() >= otherObject->curPos->GetPosX() + otherObject->objectWidth)
					collisionDirection = NONE;
				else
					collisionDirection = TOP;
			}
		}
	}

	// Trả về thời gian va chạm
	return entryTime;
}

void Object::SweptAABB(Object * otherObject, float dx, float dy, float & collisionTime, float & nx, float & ny)
{
	float dxEntry, dxExit, txEntry, txExit;
	float dyEntry, dyExit, tyEntry, tyExit;

	float entryTime;
	float exitTime;

	float movingTop = this->curPos->GetPosY();
	float movingBottom = this->curPos->GetPosY() + this->objectHeight;
	float movingLeft = this->curPos->GetPosX();
	float movingRight = this->curPos->GetPosX() + this->objectWidth;

	float staticTop = otherObject->GetCurPos()->GetPosY();
	float staticBottom = otherObject->GetCurPos()->GetPosY() + otherObject->GetObjectHeight();
	float staticLeft = otherObject->GetCurPos()->GetPosX();
	float staticRight = otherObject->GetCurPos()->GetPosX() + otherObject->GetObjectWidth();

	collisionTime = -1.0f; // Không có va chạm
	nx = ny = 0;

	// Broad-phase test
	float bl = dx > 0 ? movingLeft : movingLeft + dx;
	float bt = dy > 0 ? movingTop : movingTop + dy;
	float br = dx > 0 ? movingRight + dx : movingRight;
	float bb = dy > 0 ? movingBottom + dy : movingBottom;

	// Nếu không nằm trong vùng va chạm với nhau thì không cần xét
	if (br < staticLeft || bl >  staticRight
		|| bb < staticTop || bt > staticBottom)
		return;

	if (dx == 0 && dy == 0) return; // Không di chuyển cũng thoát ra

	// đi qua phải
	if (dx > 0) {
		dxEntry = staticLeft - movingRight;
		dxExit = staticRight - movingLeft;
	}
	else if (dx < 0) {
		dxEntry = staticRight - movingLeft;
		dxExit = staticLeft - movingRight;
	}

	// đi xuống
	if (dy > 0) {
		dyEntry = staticTop - movingBottom;
		dyExit = staticBottom - movingTop;
	}
	else if (dy < 0) {
		dyEntry = staticBottom - movingTop;
		dyExit = staticTop - movingBottom;
	}

	if (dx == 0) {
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else {
		txEntry = dxEntry / dx;
		txExit = dxExit / dx;
	}

	if (dy == 0) {
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else {
		tyEntry = dyEntry / dy;
		tyExit = dyExit / dy;
	}

	if ((txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f) return;

	entryTime = max(txEntry, tyEntry);
	exitTime = min(txExit, tyExit);

	if (entryTime > exitTime) return;
	collisionTime = entryTime;

	if (txEntry > tyEntry) {
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else {
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}

CollisionEvent* Object::GetCollsionObjectsBySweptAABB(Object* obj)
{
	ObjectVelocity* otherObjectVec = obj->GetCurVec();
	float dx = this->deltaPosX - otherObjectVec->GetVx()*this->deltaTime;
	float dy = this->deltaPosY - otherObjectVec->GetVy() * this->deltaTime;

	float collisionTime, nx, ny;

	this->SweptAABB(obj, dx, dy, collisionTime, nx, ny);
	return new CollisionEvent(collisionTime, nx, ny, obj);
}

void Object::CalcPotentialCollisions(vector<Object*>* objects, vector<CollisionEvent*>* coEvents)
{
	for (UINT i = 0; i < objects->size(); i++) {
		CollisionEvent* coEvent = this->GetCollsionObjectsBySweptAABB(objects->at(i));

		if (coEvent->GetCollisionTime() > 0 && coEvent->GetCollisionTime() <= 1.0f)
			coEvents->push_back(coEvent);
		else
			delete coEvent;
	}

	sort(coEvents->begin(), coEvents->end(), CollisionEvent::Compare);
}

void Object::FilterCollision(vector<CollisionEvent*> *coEvents, vector<CollisionEvent*> *coEventsResult, float & minTx, float & minTy, float & nx, float & ny)
{
	minTx = 1.0f;
	minTy = 1.0f;
	int minIx = -1; // Index của object có khả năng va chạm gần nhất theo X (chiều ngang)
	int minIy = -1; // index của Object có khả năng va chạm gần nhất theo Y (chiều dọc)

	ny = 0.0f;
	nx = 0.0f;

	coEventsResult->clear();

	for (UINT i = 0; i < coEvents->size(); i++) {
		CollisionEvent* c = coEvents->at(i);

		if (c->GetCollisionTime() < minTx && c->GetNx() != 0) {
			minTx = c->GetCollisionTime();
			nx = c->GetNx();
			minIx = i;
		}

		if (c->GetCollisionTime() < minTy && c->GetNy() != 0) {
			minTy = c->GetCollisionTime();
			ny = c->GetNy();
			minIy = i;
		}
	}

	if (minIx >= 0) coEventsResult->push_back(coEvents->at(minIx));
	if (minIy >= 0) coEventsResult->push_back(coEvents->at(minIy));
}

// Lấy giá trị BoudingBox của Object và trả về dạng RECT*
RECT * Object::GetBoundingBox()
{
	return this->curPos->GetBoudingBox();
}

void Object::Init(float posX, float posY)
{
	this->curPos->SetPosX(posX);
	this->curPos->SetPosY(posY);
	this->isActive = true;
}

void Object::Update(float deltaTime, std::vector<Object*>* objects)
{
	this->deltaTime = deltaTime;
	this->deltaPosX = this->curVec->GetVx() * deltaTime;
	this->deltaPosY = this->curVec->GetVy() * deltaTime;
}

void Object::SetPosition(float posX, float posY)
{
	this->lastPos->SetPosX(this->curPos->GetPosX());
	this->lastPos->SetPosY(this->curPos->GetPosY());
	this->curPos->SetPosX(posX);
	this->curPos->SetPosY(posY);
}

void Object::SetVeclocity(float vX, float vY)
{
	this->lastVec->SetVx(this->curVec->GetVx());
	this->lastVec->SetVy(this->curVec->GetVy());
	this->curVec->SetVx(vX);
	this->curVec->SetVy(vY);
}

// Get/Set methods
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

CollisionEvent::CollisionEvent(float collisionTime, float nx, float ny, Object* obj)
{
	this->collisionTime = collisionTime;
	this->nx = nx;
	this->ny = ny;
	this->obj = obj;
}


CollisionEvent::~CollisionEvent()
{
}
