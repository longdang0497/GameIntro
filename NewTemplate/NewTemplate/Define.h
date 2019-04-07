#pragma once

// ========= GAME
#define GAME_MODE_320_240 0
#define GAME_MODE_640_480 1
#define GAME_TITLE L"Ninja Gaiden"
enum GAME_STAGE {
	STAGE1,
	STAGE2,
	STAGE3
};

#define STAGE1_WIDTH 2408
#define STAGE1_HEIGHT 176

// =========== TEXTURE + SPRITE
#define ID_TEXTURE_MAIN 0
#define PATH_TEXTURE_MAIN L"sprite\\main_character_sprite.png"
#define PATH_POS_MAIN_STAND L"sprite\\main\\MAIN_STAND.txt"
#define PATH_POS_MAIN_RUN L"sprite\\main\\MAIN_RUN.txt"
#define PATH_POS_MAIN_SIT L"sprite\\main\\MAIN_SIT.txt"
#define PATH_POS_MAIN_JUMP_SCROLL L"sprite\\main\\MAIN_JUMP_SCROLL.txt"

#define ID_TEXTURE_MAP_1 100
#define PATH_TEXTURE_MAP_1 L"sprite\\Stage1\\texture.png"
#define PATH_POS_MAP_1 L"sprite\\Stage1\\map.txt"
#define PATH_POS_GROUND_MAP_1 "sprite\\Stage1\\ground.txt"

// ========= OBJECT =========
enum OBJECT_TYPE {
	BRICK,
	MAIN_CHARACTER
};

// ========== MAIN CHARACTER STATE ==========
enum MAIN_CHARACTER_STATE {
	STAND_RIGHT,
	STAND_LEFT,
	RUN_RIGHT,
	RUN_LEFT,
	SIT_RIGHT,
	SIT_LEFT,
	JUMP_SCROLL_RIGHT,
	JUMP_SCROLL_LEFT
};

// ========== GRID ===============
#define CELL_SIZE 128
#define BRICK_SIZE 16