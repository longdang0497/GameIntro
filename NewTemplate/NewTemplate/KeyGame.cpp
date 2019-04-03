#include "KeyGame.h"


CKeyGame* CKeyGame::instance = 0;
CKeyGame * CKeyGame::getInstance()
{
	if (instance == 0)
		instance = new CKeyGame();

	return instance;
}

void CKeyGame::update()
{
	keyAttack = key->IsKeyDown(DIK_C) || key->IsKeyDown(DIK_L);
	keyAttackPress = keyAttack && !isKeyAttackDownPrevious;
	isKeyAttackDownPrevious = keyAttack;

	keyJump = key->IsKeyDown(DIK_SPACE);
	keyJumpPress = keyJump && !isKeyJumpDownPrevious;
	isKeyJumpDownPrevious = keyJump;

	keyChangeScene = key->IsKeyDown(DIK_RETURN);
	keyChangeScenePress = keyChangeScene && !isKeyChangeSceneDownPrevious;
	isKeyChangeSceneDownPrevious = keyChangeScene;

	keyUp = key->IsKeyDown(DIK_UP) || key->IsKeyDown(DIK_W);
	keyDown = key->IsKeyDown(DIK_DOWN) || key->IsKeyDown(DIK_S);
	keyLeft = key->IsKeyDown(DIK_LEFT) || key->IsKeyDown(DIK_A);
	keyRight = key->IsKeyDown(DIK_RIGHT) || key->IsKeyDown(DIK_D);
	keyMove = keyLeft || keyRight;
	keyStair = keyUp || keyDown || keyLeft || keyRight;
	keyBeginStair = keyUp;
	keyRangeAttack = keyUp && keyAttackPress;
	keySitDownAttack = keyDown && keyAttackPress;
}

CKeyGame::CKeyGame()
{
	key = CKeyBoard::getInstance();
	isKeyJumpDownPrevious = false;
	isKeyAttackDownPrevious = false;
	isKeyChangeSceneDownPrevious = false;
}


CKeyGame::~CKeyGame()
{
}
