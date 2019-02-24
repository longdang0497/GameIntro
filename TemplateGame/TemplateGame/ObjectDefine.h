#pragma once

class World;
class Grid;

#define ANIMATE_RATE 30
#define TEXTURE_GAME_CHARACTERS L"sprite\\samus_sprites.png"
#define CHARACTER_SPEED 200.0f

// ========== START: OBJECT ============
#define DEFAULT_OBJECT_WIDTH 42
#define DEFAULT_OBJECT_HEIGHT 64

enum OBJECT_TYPE {
	BRICK,
	MAIN_CHARACTER
};

enum COLLISION_DIRECTION {
	NONE,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

enum MAIN_CHARACTER_MOVEMENT {
	STAND_LEFT,
	STAND_RIGHT,
	RUN_LEFT,
	RUN_RIGHT
};
// ========== END: OBJECT ============

// ========== START: MAIN CHARACTER =============
#define STANDRIGHT_PATH L"sprite\\STANDING_RIGHT.txt"
#define STANDLEFT_PATH L"sprite\\STANDING_LEFT.txt"
#define STAND_WIDTH 42
#define STAND_HEIGHT 64

#define RUNRIGHT_PATH L"sprite\\RUNNING_RIGHT.txt"
#define RUNLEFT_PATH L"sprite\\RUNNING_LEFT.txt"
#define RUN_WIDTH 40
#define RUN_HEIGHT 64
// ========== END: MAIN CHARACTER ========

// ========== START: POSITION ============
#define DEFAULT_POS_X 1.0
#define DEFAULT_POS_Y 1.0
// ========== END: POSITION ============

// ========== START: VELOCITY ============
#define DEFAULT_VX 0.0
#define DEFAULT_VY 0.0
// ========== END: VELOCITY ============