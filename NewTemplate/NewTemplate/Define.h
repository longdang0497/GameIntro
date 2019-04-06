#pragma once

// ========= GAME
#define GAME_MODE_320_240 0
#define GAME_MODE_640_480 1
#define GAME_TITLE L"Ninja Gaiden"

// =========== TEXTURE + SPRITE
#define ID_TEXTURE_MAIN 0
#define PATH_TEXTURE_MAIN L"sprite\\main_character_sprite.png"
#define PATH_POS_MAIN_STAND L"sprite\\main\\MAIN_STAND.txt"
#define PATH_POS_MAIN_RUN L"sprite\\main\\MAIN_RUN.txt"

#define ID_TEXTURE_MAP_1 100
#define PATH_TEXTURE_MAP_1 L"sprite\\background.png"

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
	RUN_LEFT
};