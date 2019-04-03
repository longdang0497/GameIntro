#pragma once
#include "GameObject.h"
#include "Game.h"
#include "debug.h"
#include "Textures.h"
#include "Define.h"
#include "KeyGame.h"
#include "Camera.h"
#include "Sword.h"

class CSimon : public CGameObject
{
	bool isOnGround;

	bool jump;
	bool doneAttack, attacking;
	int untouchable;
	bool doneStage;
	int alpha;

	Sword* sword;




public:
	CSimon();
	~CSimon();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *Ground, vector<LPGAMEOBJECT> *StaticObject, vector<LPGAMEOBJECT> *Item, vector<LPGAMEOBJECT> *Enemy);
	void Render(CCamera *cam);
	void Move();


	void SetState(int state);
	void CreateAnimation();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void KeyBoardHandler();


	void checkCollisionWithGround(vector<LPGAMEOBJECT> *coObjects);
	void checkCollisioWithEnemy(vector<LPGAMEOBJECT>* coObjects);
	void checkCollisioWithStaticObjects(vector<LPGAMEOBJECT>* coObjects);
	void checkCollisionWithItem(vector<LPGAMEOBJECT> *coObjects);

};

