#pragma once
#include "Keyboard.h"

class CKeyGame
{
private:
	CKeyBoard* key;

	static CKeyGame* instance;
public:
	static CKeyGame* getInstance();

	bool keyUp;
	bool keyDown;
	bool keyLeft;
	bool keyRight;
	bool keyMove;
	bool keyStair;
	bool keyBeginStair;
	bool keyRangeAttack;
	bool keySitDownAttack;

	bool keyChangeScene;
	bool keyChangeScenePress, isKeyChangeSceneDownPrevious;

	bool keyAttack;
	bool keyAttackPress, isKeyAttackDownPrevious;

	bool keyJump;
	bool keyJumpPress, isKeyJumpDownPrevious;

	void update();
	CKeyGame();
	~CKeyGame();
};

