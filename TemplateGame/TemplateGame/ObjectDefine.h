#pragma once

class World;
class Grid;

#define ANIMATE_RATE 25
#define CHARACTER_SPEED 100.0f

// ========== START: OBJECT ============
#define DEFAULT_OBJECT_WIDTH 42
#define DEFAULT_OBJECT_HEIGHT 64

enum OBJECT_TYPE {
	BRICK,
	MAIN_CHARACTER,
	BOSS,
	BABY_EAGLE,
	BUTTERFLY
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
#define TEXTURE_GAME_CHARACTERS L"sprite\\main_character_sprite.png"

enum MAIN_CHARACTER_STATE{
	STAND_LEFT,
	STAND_RIGHT,
	RUN_LEFT,
	RUN_RIGHT,
	CLIMB_LEFT,
	CLIMB_RIGHT,
	SIT_LEFT,
	SIT_RIGHT,
	STAND_KILL_LEFT,
	STAND_KILL_RIGHT,
	SIT_KILL_LEFT,
	SIT_KILL_RIGHT,
	JUMP_SCROLL_LEFT,
	JUMP_SCROLL_RIGHT,
	JUMP_SCROLL_KILL_LEFT,
	JUMP_SCROLL_KILL_RIGHT
};

#define MAIN_STAND_PATH L"sprite\\main\\MAIN_STAND.txt"
#define MAIN_STAND_COUNT 1
#define MAIN_STAND_WIDTH 17
#define MAIN_STAND_HEIGHT 32

#define MAIN_RUN_PATH L"sprite\\main\\MAIN_RUN.txt"
#define MAIN_RUN_COUNT 3
#define MAIN_RUN_WIDTH 22
#define MAIN_RUN_HEIGHT 31

#define MAIN_CLIMB_PATH L"sprite\\main\\MAIN_RUN.txt"
#define MAIN_CLIMB_COUNT 2
#define MAIN_CLIMB_WIDTH 16
#define MAIN_CLIMB_HEIGHT 31

#define MAIN_SIT_PATH L"sprite\\main\\MAIN_SIT.txt"
#define MAIN_SIT_COUNT 1
#define MAIN_SIT_WIDTH 17
#define MAIN_SIT_HEIGHT 24

#define MAIN_STAND_KILL_PATH L"sprite\\main\\MAIN_STAND_KILL.txt"
#define MAIN_STAND_KILL_COUNT 3
#define MAIN_STAND_KILL_WIDTH 40
#define MAIN_STAND_KILL_HEIGHT 31

#define MAIN_SIT_KILL_PATH L"sprite\\main\\MAIN_SIT_KILL.txt"
#define MAIN_SIT_KILL_COUNT 3
#define MAIN_SIT_KILL_WIDTH 39
#define MAIN_SIT_KILL_HEIGHT 23

#define MAIN_JUMP_SCROLL_PATH L"sprite\\main\\MAIN_JUMP_SCROLL.txt"
#define MAIN_JUMP_SCROLL_COUNT 4
#define MAIN_JUMP_SCROLL_WIDTH 22
#define MAIN_JUMP_SCROLL_HEIGHT 22

#define MAIN_JUMP_SCROLL_KILL_PATH L"sprite\\main\\MAIN_JUMP_SCROLL_KILL.txt"
#define MAIN_JUMP_SCROLL_KILL_COUNT 4
#define MAIN_JUMP_SCROLL_KILL_WIDTH 25
#define MAIN_JUMP_SCROLL_KILL_HEIGHT 25
// ========== END: MAIN CHARACTER ========
// ========== END: MAIN CHARACTER ========

// ========== START: BOSS =============
enum BOSS_STATE {
	JUMP_LEFT,
	JUMP_RIGHT
};

#define TEXTURE_GAME_ENEMIES L"sprite\\Enemies_Bosses.png"

#define MAIN_JUMP_SCROLL_KILL_PATH L"sprite\\boss\\BOSS.txt"
#define MAIN_JUMP_SCROLL_KILL_COUNT 2
#define MAIN_JUMP_SCROLL_KILL_WIDTH 38
#define MAIN_JUMP_SCROLL_KILL_HEIGHT 54
// ========== END: BOSS =============

// ========== START: POSITION ============
#define DEFAULT_POS_X 300
#define DEFAULT_POS_Y 300
// ========== END: POSITION ============

// ========== START: VELOCITY ============
#define DEFAULT_VX 0.0
#define DEFAULT_VY 0.0
// ========== END: VELOCITY ============