#include "Object.h"


Object::Object()
{
	this->isActive = true;
	this->nextObj = NULL;
	this->preObj = NULL;
}

Object::~Object()
{

}

bool Object::checkAABB(Object * obj)
{
	RECT curRect = this->GetBoundingBox();
	RECT otherRect = obj->GetBoundingBox();

	return !(curRect.right < otherRect.left || curRect.left > otherRect.right || curRect.top > otherRect.bottom || curRect.bottom < otherRect.top);
}

void Object::SweptAABB(Object * obj, float dx, float dy, float & collisionTime, float & nx, float &ny)
{
	float dxEntry, dxExit, txEntry, txExit;
	float dyEntry, dyExit, tyEntry, tyExit;

	float entryTime;
	float exitTime;

	RECT movingRect = this->GetBoundingBox();
	float movingTop = movingRect.top;
	float movingBottom = movingRect.bottom;
	float movingLeft = movingRect.left;
	float movingRight = movingRect.right;

	RECT staticRect = obj->GetBoundingBox();
	float staticTop = staticRect.top;
	float staticBottom = staticRect.bottom;
	float staticLeft = staticRect.left;
	float staticRight = staticRect.right;

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

CollisionEvent * Object::GetCollsionObjectsBySweptAABB(Object * obj)
{
	float dx = this->deltaX - obj->GetVeclocity().x*this->deltaTime;
	float dy = this->deltaY - obj->GetVeclocity().y * this->deltaTime;

	float collisionTime, nx, ny;

	this->SweptAABB(obj, dx, dy, collisionTime, nx, ny);
	return new CollisionEvent(collisionTime, nx, ny, obj);
}

void Object::CalcPotentialCollisions(vector<Object*>* objects, vector<CollisionEvent*>* coEvents)
{
	for (UINT i = 0; i < objects->size(); i++) {

		CollisionEvent* coEvent = this->GetCollsionObjectsBySweptAABB(objects->at(i));

		if (coEvent->GetCollisionTime() >= 0 && coEvent->GetCollisionTime() <= 1.0f)
			coEvents->push_back(coEvent);
		else
			delete coEvent;
	}

	sort(coEvents->begin(), coEvents->end(), CollisionEvent::Compare);
}

void Object::FilterCollision(vector<CollisionEvent*>* coEvents, vector<CollisionEvent*>* coEventsResult, float & minTx, float & minTy, float & nx, float & ny)
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

RECT Object::GetBoundingBox()
{
	RECT rect;
	rect.top = this->position.y;
	rect.left = this->position.x;
	rect.right = rect.left + this->objectWidth;
	rect.bottom = rect.top + this->objectHeight;
	return rect;
}

void Object::Update(float deltaTime, std::vector<Object*>* objects)
{
	this->deltaTime = deltaTime;
	this->deltaX = this->veclocity.x * deltaTime;
	this->deltaY= this->veclocity.y * deltaTime;
}

CollisionEvent::CollisionEvent(float collisionTime, float nx, float ny, Object * obj)
{
	this->collisionTime = collisionTime;
	this->nx = nx;
	this->ny = ny;
	this->obj = obj;
}

CollisionEvent::~CollisionEvent()
{
}
