#pragma once
#include "Object.h"
#include "Sprite.h"
#include "Texture.h"
#include "Define.h"

#define DEFAULT_MAIN_WIDTH 32
#define DEFAULT_MAIN_HEIGHT 32

class MainCharacter : public Object
{ 
private:
	
	static MainCharacter* _instance;
	MAIN_CHARACTER_STATE state;

	Sprite* standSprite;
	Sprite* runSprite;

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
};

