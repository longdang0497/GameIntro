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
	/*RECT curRect = this->GetBoundingBox();
	RECT otherRect = obj->GetBoundingBox();

	return !(curRect.right < otherRect.left || curRect.left > otherRect.right || curRect.top > otherRect.bottom || curRect.bottom < otherRect.top);*/

	return false;
}

void Object::SweptAABB(Object * obj, float dx, float dy, float & collisionTime, float & nx, float &ny)
{
	//float dxEntry, dxExit, txEntry, txExit;
	//float dyEntry, dyExit, tyEntry, tyExit;

	//float entryTime;
	//float exitTime;

	//RECT movingRect = this->GetBoundingBox();
	//float movingTop = movingRect.top;
	//float movingBottom = movingRect.bottom;
	//float movingLeft = movingRect.left;
	//float movingRight = movingRect.right;

	//RECT staticRect = obj->GetBoundingBox();
	//float staticTop = staticRect.top;
	//float staticBottom = staticRect.bottom;
	//float staticLeft = staticRect.left;
	//float staticRight = staticRect.right;

	//collisionTime = -1.0f; // Không có va chạm
	//nx = ny = 0;

	//// Broad-phase test
	//float bl = dx > 0 ? movingLeft : movingLeft + dx;
	//float bt = dy > 0 ? movingTop : movingTop + dy;
	//float br = dx > 0 ? movingRight + dx : movingRight;
	//float bb = dy > 0 ? movingBottom + dy : movingBottom;

	//// Nếu không nằm trong vùng va chạm với nhau thì không cần xét
	//if (br < staticLeft || bl >  staticRight
	//	|| bb < staticTop || bt > staticBottom)
	//	return;

	//if (dx == 0 && dy == 0) return; // Không di chuyển cũng thoát ra

	//// đi qua phải
	//if (dx > 0) {
	//	dxEntry = staticLeft - movingRight;
	//	dxExit = staticRight - movingLeft;
	//}
	//else if (dx < 0) {
	//	dxEntry = staticRight - movingLeft;
	//	dxExit = staticLeft - movingRight;
	//}

	//// đi xuống
	//if (dy > 0) {
	//	dyEntry = staticTop - movingBottom;
	//	dyExit = staticBottom - movingTop;
	//}
	//else if (dy < 0) {
	//	dyEntry = staticBottom - movingTop;
	//	dyExit = staticTop - movingBottom;
	//}

	//if (dx == 0) {
	//	txEntry = -std::numeric_limits<float>::infinity();
	//	txExit = std::numeric_limits<float>::infinity();
	//}
	//else {
	//	txEntry = dxEntry / dx;
	//	txExit = dxExit / dx;
	//}

	//if (dy == 0) {
	//	tyEntry = -std::numeric_limits<float>::infinity();
	//	tyExit = std::numeric_limits<float>::infinity();
	//}
	//else {
	//	tyEntry = dyEntry / dy;
	//	tyExit = dyExit / dy;
	//}

	//if ((txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f) return;

	//entryTime = max(txEntry, tyEntry);
	//exitTime = min(txExit, tyExit);

	//if (entryTime > exitTime) return;
	//collisionTime = entryTime;

	//if (txEntry > tyEntry) {
	//	ny = 0.0f;
	//	dx > 0 ? nx = -1.0f : nx = 1.0f;
	//}
	//else {
	//	nx = 0.0f;
	//	dy > 0 ? ny = -1.0f : ny = 1.0f;
	//}
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
	for (UINT i = 0; i < objects->size(); i++)
	{
		CollisionEvent* e = SweptAABBEx(objects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents->push_back(e);
		else
			delete e;
	}

	std::sort(coEvents->begin(), coEvents->end(), CollisionEvent::compare);
}

void Object::FilterCollision(vector<CollisionEvent*>* coEvents, vector<CollisionEvent*>* coEventsResult, float & minTx, float & minTy, float & nx, float & ny)
{
	minTx = 1.0f;
	minTy = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult->clear();

	for (UINT i = 0; i < coEvents->size(); i++)
	{
		CollisionEvent* c = coEvents->at(i);

		if (c->t <= minTx && c->nx != 0) {
			minTx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t <= minTy  && c->ny != 0) {
			minTy = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult->push_back(coEvents->at(min_ix));
	if (min_iy >= 0) coEventsResult->push_back(coEvents->at(min_iy));
}

void Object::RenderBoundingBox()
{


	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);


	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	Game::GetInstance()->Draw(pos.x,pos.y,Texture::GetInstance()->Get(ID_BB),left,top,right,bottom);
}

void Object::Update(float deltaTime, std::vector<Object*>* objects)
{
	this->deltaTime = deltaTime;
	this->deltaX = this->veclocity.x * deltaTime;
	this->deltaY= this->veclocity.y * deltaTime;
}


CollisionEvent* Object::SweptAABBEx(Object* coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	D3DXVECTOR2 sVel;
	sVel.x = coO->GetVeclocity().x;
	sVel.y = coO->GetVeclocity().y;


	D3DXVECTOR2 sdPos = sVel*deltaTime;

	D3DXVECTOR2 ndPos;
	ndPos.x = this->deltaX - sdPos.x;
	ndPos.y = this->deltaY - sdPos.y;

	GetBoundingBox(ml, mt, mr, mb);

	Game::SweptAABB(
		ml, mt, mr, mb,
		ndPos.x, ndPos.y,
		sl, st, sr, sb,
		t, nx, ny
		);

	CollisionEvent * e = new CollisionEvent(t, nx, ny, coO);
	return e;
}
