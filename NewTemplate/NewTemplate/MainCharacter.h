#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"
#include "Define.h"
#include "KeyGame.h"
#include "Sword.h"
#include "Camera.h"
#include "Enemy.h"
#include "Item.h"
#include "HideObject.h"
#include "Shuriken.h"



#define DEFAULT_MAIN_WIDTH 32
#define DEFAULT_MAIN_HEIGHT 32

class MainCharacter : public Object
{
private:

	bool Demo = false;

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

	int PlusScore;
	DWORD StartDoubleScore;

	bool StopWatch;
	DWORD StartStopWatch;

	bool HasShuriken;
	DWORD StartHasShuriken;

	int Lives;

	bool IsRepawn;

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
	void Score() { this->score += 10*PlusScore; }

	bool GetIsInTheEndOfMap() {
		return isInTheEndOfMap;
	}

	void SetIsInTheEndOfMap(bool value) { this->isInTheEndOfMap = value; }

	bool IsStopWatch() { return this->StopWatch; }

	bool GetHasShuriken() { return this->HasShuriken; }

	int GetPlusScore() { return this->PlusScore; }


	int GetLives() { return this->Lives; }

	void LoseLive() { Lives--; }

	bool GetRepawn() { return this->IsRepawn; }
	void SetRepawn(bool s) { this->IsRepawn = s; }

	void SubtractScore(int a) { this->score = this->score - a; }
};

