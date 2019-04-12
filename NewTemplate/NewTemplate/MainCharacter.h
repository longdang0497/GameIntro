#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"
#include "Define.h"
#include "KeyGame.h"
#include "Sword.h"
#include "Camera.h"
#include "Brick.h"
#include "Ladder.h"

#define DEFAULT_MAIN_WIDTH 32
#define DEFAULT_MAIN_HEIGHT 32

class MainCharacter : public Object
{ 
private:
	
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
	Sprite* climb;

	bool isOnLadder;
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
	void HandleCollision(vector<Object*> *objects);

	static MainCharacter* GetInstance() {
		if (_instance == NULL) _instance = new MainCharacter();
		return _instance;
	}

	void KeyBoardHandle();

	void GetBoundingBox(float &l, float &t, float &r, float &b);

	void CheckCollisionWithGround(Brick *brick);
	void CheckCollisionWithOtherObject(vector<Object*>* object = NULL);
	void CheckCollisionWithLadder(Ladder *ladder);

};

