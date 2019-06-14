#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"
#include "Define.h"
#include "KeyGame.h"
#include "Sword.h"
#include "Explode.h"
#include "Camera.h"
#include "Enemy.h"
#include "Item.h"
#include "HideObject.h"
#include "Flames.h"
#include "Windmill.h"
#include "Text.h"
#include "Shuriken.h"


#define MAIN_RATE 50

#define DEFAULT_MAIN_WIDTH 32
#define DEFAULT_MAIN_HEIGHT 32

enum SecondaryWeapon {
	SW_none,
	SW_shuriken,
	SW_windmill,
	SW_jump_Scroll_Kill,
	SW_Flames
};


class MainCharacter : public Object
{
private:

	bool Demo = true;

	static MainCharacter* _instance;
	MAIN_CHARACTER_STATE state;

	bool isOnGround;

	Sprite* standSprite;
	Sprite* runSprite;
	Sprite* sitSprite;
	Sprite* jumpScrollSprite;
	Sprite* hitSprite;
	Sprite* jumpHitSprite;
	Sprite* sitHitSprite;
	Sprite* hurtSprite;
	Sprite* onLadder;
	Sprite* climbing;

	bool isInTheEndOfMap  = false;
	int score = 0;

	bool isHurting = false;
	DWORD startHurting;

	bool allowJump = false;
	DWORD startStanding;

	int alpha = 255; // dùng để vẽ nhân vật khi bị làm tổn thương

	
	bool StopWatch;
	DWORD StartStopWatch;

	int Lives;

	bool IsRepawn;

	int Energy;

	SecondaryWeapon SubWeapon;

	Explode *explode;
	bool alreadyGotItem = false;
public:
	MainCharacter();
	~MainCharacter();


	MAIN_CHARACTER_STATE GetState();
	void SetState(MAIN_CHARACTER_STATE value);

	void ResetAllSprites();
	bool GetStateActive();

	void Reset(float  x, float y);
	void Update(float t, vector<Object*> *object = NULL);
	void Render();

	static MainCharacter* GetInstance() {
		if (_instance == NULL) _instance = new MainCharacter();
		return _instance;
	}

	void HandleCollision(vector<Object*> *objects);
	void HandleCollisionWithStaticObject(vector<Object*> *objects);
	void HandleCollisionWithMovingObject(vector<Object*> *objects);



	void KeyBoardHandle();

	void GetBoundingBox(float &l, float &t, float &r, float &b);

	int GetScore() { return this->score; }
	void Score() { this->score += 10; }

	bool GetIsInTheEndOfMap() {
		return isInTheEndOfMap;
	}

	void SetIsInTheEndOfMap(bool value) { this->isInTheEndOfMap = value; }

	bool IsStopWatch() { return this->StopWatch; }

	int GetLives() { return this->Lives; }

	void LoseLive() { Lives--; }

	bool GetRepawn() { return this->IsRepawn; }
	void SetRepawn(bool s) { this->IsRepawn = s; }

	void SubtractScore(int a) { this->score = this->score - a; }

	int GetEnergy() { return this->Energy; }
	void SetEnergy(int a) { this->Energy = a; }

	bool GetGotItem() { return this->alreadyGotItem; }
	void SetGotItem(bool value) { this->alreadyGotItem = value; }

	SecondaryWeapon GetSubWeapon() { return this->SubWeapon; }
};

