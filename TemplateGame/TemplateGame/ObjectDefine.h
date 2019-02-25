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


// ========== END: OBJECT ============

// ========== START: MAIN CHARACTER =============
enum MAIN_CHARACTER_STATE{
	STAND_LEFT,
	STAND_RIGHT,
	RUN_LEFT,
	RUN_RIGHT
};

#define MAIN_STAND_PATH L"sprite\\main\\MAIN_STAND.txt"
#define MAIN_STAND_COUNT 1
#define MAIN_STAND_WIDTH 42
#define MAIN_STAND_HEIGHT 64

#define MAIN_RUN_PATH L"sprite\\main\\MAIN_RUN.txt"
#define MAIN_RUN_COUNT 3
#define MAIN_RUN_WIDTH 40
#define MAIN_RUN_HEIGHT 64
// ========== END: MAIN CHARACTER ========

// ========== START: POSITION ============
#define DEFAULT_POS_X 1.0
#define DEFAULT_POS_Y 1.0
// ========== END: POSITION ============

// ========== START: VELOCITY ============
#define DEFAULT_VX 0.0
#define DEFAULT_VY 0.0
// ========== END: VELOCITY ============