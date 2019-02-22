#pragma once

class World;
class Grid;

#define ANIMATE_RATE 30
#define TEXTURE_GAME_CHARACTERS L"sprite\\samus_sprites.png"

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
};
// ========== END: OBJECT ============

// ========== START: MAIN CHARACTER =============
#define STANDRIGHT_PATH L"sprite\\STANDING_RIGHT.txt"
#define STANDLEFT_PATH L"sprite\\STANDING_LEFT.txt"
// ========== END: MAIN CHARACTER ========

// ========== START: POSITION ============
#define DEFAULT_POS_X 1.0
#define DEFAULT_POS_Y 1.0
// ========== END: POSITION ============

// ========== START: VELOCITY ============
#define DEFAULT_VX 0.0
#define DEFAULT_VY 0.0
// ========== END: VELOCITY ============