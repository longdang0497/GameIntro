#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Camera.h"
#include "Textures.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;


struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

enum ObjectCode
{
	none,
	simon_code,
	whip,
	end_object,
	hunk
};

class CGameObject
{
public:


	D3DXVECTOR2 bdbpos;
	D3DXVECTOR2 position;
	D3DXVECTOR2 dPos;
	D3DXVECTOR2 velocity;

	int ani;
	int hp;
	int direction;
	int state;

	DWORD dt;

	vector<LPANIMATION> animations;

	ObjectCode code;
	ObjectCode item;

	int width, height;


public:


	CGameObject();
	~CGameObject();



	void RenderBoundingBox(CCamera *cam);
	bool AABB(LPGAMEOBJECT coO);
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;

	void AddAnimation(int aniId);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *Ground = NULL, vector<LPGAMEOBJECT> *StaticObject = NULL, vector<LPGAMEOBJECT> *Item = NULL, vector<LPGAMEOBJECT> *Enemy = NULL);
	virtual void Render(CCamera *cam) = 0;

	void SetPosition(D3DXVECTOR2 pos) { position = pos; }
	void SetVelocity(D3DXVECTOR2 vel) { velocity = vel; }
	void SetState(int state) { this->state = state; }
	void setHp(int a) { this->hp = a; }
	void SetItem(ObjectCode a) { this->item = a; }
	void Setwidth(int a) { this->width = a; }
	void Setheight(int a) { this->height = a; }

	D3DXVECTOR2 GetPosition() { return position; }
	D3DXVECTOR2 GetVelcity() { return velocity; }
	int GetState() { return this->state; }
	int getHp() { return hp; }
	ObjectCode GetCode() { return this->code; }
	ObjectCode GetItem() { return this->item; }
	int getwidth() { return this->width; }
	int getheight() { return this->height; }

	int getDirection() { return this->direction; }
	void setDirection(int i) { this->direction = i; }
};

