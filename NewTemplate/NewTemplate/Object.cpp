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
	return false;
}

void Object::SweptAABB(Object * obj, float dx, float dy, float & collisionTime, float & nx, float &ny)
{

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

		if (c->t <= minTy && c->ny != 0) {
			minTy = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0)
		coEventsResult->push_back(coEvents->at(min_ix));
	if (min_iy >= 0)
		coEventsResult->push_back(coEvents->at(min_iy));
}

void Object::RenderBoundingBox()
{
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);

	D3DXVECTOR3 pos1(left, top, 0);

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(pos1);

	Game::GetInstance()->Draw(pos.x, pos.y, Texture::GetInstance()->Get(ID_BB), left, top, right, bottom);
}

void Object::Update(float deltaTime, std::vector<Object*>* objects)
{
	this->deltaTime = deltaTime;
	this->deltaX = this->veclocity.x * deltaTime;
	this->deltaY = this->veclocity.y * deltaTime;
}

void Object::Render()
{/*
	RenderBoundingBox();*/
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


	D3DXVECTOR2 sdPos = sVel * deltaTime;

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
