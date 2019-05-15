#pragma once

// ========= GAME
#define GAME_MODE_320_240 0
#define GAME_MODE_640_480 1
#define GAME_MODE_256_256 2
#define GAME_TITLE L"Ninja Gaiden"
enum GAME_STAGE {
	Intro,
	STAGE1,
	STAGE2,
	STAGE3
};



#define STAGE1_WIDTH 2408
#define STAGE1_HEIGHT 176

#define STAGE2_WIDTH 3072
#define STAGE2_HEIGHT 176

#define STAGE3_WIDTH 256
#define STAGE3_HEIGHT 176

// =========== ENIMIES
#define JAGUAR_ID 0
#define SOLDIER_ID 1
#define BUTTERFLY_ID 2
#define EAGLE_ID 3
#define ZOMBIE_ID 4
#define GREEN_SOLDIER_ID 5
#define BAT_ID 6
#define CROW_ID 7

// =========== ITEMS
#define BLUE_R_ID 0
#define ORANGE_R_ID 1
#define SANDGLASS_ID 2
#define BLUE_DART_ID 3
#define ORANGE_DART_ID 4
#define BLUE_POCKET_ID 5
#define ORANGE_POCKET_ID 6
#define BIG_SHURIKEN_ID 7
#define ITEM_FIRE_ID 8
#define ORANGE_JAR_ID 9
#define BLUE_JAR_ID 10

// =========== TEXTURE + SPRITE
#define ID_TEXTURE_MAIN 0
#define PATH_TEXTURE_MAIN L"sprite\\main_character_sprite.png"	//  <===== CÁC SPRITE BÊN DƯỚI SỬ DỤNG TEXTURE NÀY
#define PATH_MAIN_STAND L"sprite\\main\\MAIN_STAND.txt"
#define PATH_MAIN_STAND_KILL L"sprite\\main\\MAIN_STAND_KILL.txt"
#define PATH_MAIN_RUN L"sprite\\main\\MAIN_RUN.txt"
#define PATH_MAIN_SIT L"sprite\\main\\MAIN_SIT.txt"
#define PATH_MAIN_SIT_KILL L"sprite\\main\\MAIN_SIT_KILL.txt"
#define PATH_MAIN_CLIMB L"sprite\\main\\MAIN_CLIMB.txt"
#define PATH_MAIN_ON_LADDER L"sprite\\main\\MAIN_ON_LADDER.txt"
#define PATH_MAIN_JUMP_SCROLL L"sprite\\main\\MAIN_JUMP_SCROLL.txt"
#define PATH_MAIN_JUMP_SCROLL_KILL L"sprite\\main\\MAIN_JUMP_SCROLL_KILL.txt"
#define PATH_MAIN_HURT L"sprite\\main\\MAIN_HURT.txt"

#define ID_TEXTURE_BLACK 1090
#define PATH_TEXTURE_BLACK L"sprite\\black.jpg"	//  <===== CÁC SPRITE BÊN DƯỚI SỬ DỤNG TEXTURE NÀY

#define PATH_MAIN_SWORD L"sprite\\main\\MAIN_SWORD.txt"

#define PATH_SANDGLASS L"sprite\\item\\SANDGLASS.txt"
#define PATH_SHURIKEN L"sprite\\item\\BIG_SHURIKEN.txt"
#define PATH_BLUE_POCKET L"sprite\\item\\BLUE_POCKET.txt"
#define PATH_ORANGE_POCKET L"sprite\\item\\ORANGE_POCKET.txt"
#define PATH_BLUE_DART L"sprite\\item\\ITEM_BLUE_DART.txt"
#define PATH_ORANGE_DART L"sprite\\item\\ITEM_ORANGE_DART.txt"
#define PATH_BLUE_R L"sprite\\item\\ITEM_R_BLUE.txt"
#define PATH_ORANGE_R L"sprite\\item\\ITEM_R_ORANGE.txt"
#define PATH_ITEM_FIRE L"sprite\\item\\ITEM_FIRE.txt"
#define PATH_ORANGE_JAR L"sprite\\item\\ORANGE_JAR.txt"
#define PATH_BLUE_JAR L"sprite\\item\\BLUE_JAR.txt"

#define PATH_BOSS_EXPLODE L"sprite\\boss\\BOSS_EXPLODE.txt"
#define PATH_BUTTERFLY L"sprite\\enemies\\BUTTERFLY.txt"
#define PATH_CROW L"sprite\\enemies\\CROW.txt"
#define PATH_EXPLODE L"sprite\\enemies\\EXPLODE.txt"

#define ID_TEXTURE_ENEMIES 3
#define PATH_TEXTURE_ENEMIES L"sprite\\Enemies_Bosses.png"  //   <===== CÁC SPRITE BÊN DƯỚI SỬ DỤNG TEXTURE NÀY
#define PATH_BOSS_BULLET L"sprite\\boss\\BOSS_BULLET.txt"
#define PATH_BOSS L"sprite\\boss\\BOSS.txt"
#define PATH_BOSS_JUMP L"sprite\\boss\\BOSS_JUMP.txt"

#define PATH_BOXER L"sprite\\enemies\\BOXER.txt"
#define PATH_EAGLE L"sprite\\enemies\\EAGLE.txt"
#define PATH_JAGUAR L"sprite\\enemies\\JAGUAR.txt"
#define PATH_BAT L"sprite\\enemies\\BAT.txt"

#define PATH_GREEN_SOLDIERS_BAZOOKA L"sprite\\enemies\\GREEN_SOLDIERS_BAZOOKA.txt"
#define PATH_BAZOOKA_BULLET L"sprite\\enemies\\BAZOOKA_BULLET.txt"
#define PATH_GREEN_SOLDIERS_WALK L"sprite\\enemies\\GREEN_SOLDIERS_WALK.txt"
#define PATH_GREEN_SOLDIERS_SHOOT L"sprite\\enemies\\GREEN_SOLDIERS_SHOOT.txt"
#define PATH_GREEN_SOLDIERS_BULLET L"sprite\\enemies\\GREEN_SOLDIERS_BULLET.txt"
#define PATH_SOLDIERS_WALK L"sprite\\enemies\\SOLDIERS_WALK.txt"
#define PATH_SOLDIERS_KILL L"sprite\\enemies\\SOLDIERS_KILL.txt"
#define PATH_ZOMBIES_KILL L"sprite\\enemies\\ZOMBIES_KILL.txt"
#define PATH_ZOMBIES_WALK L"sprite\\enemies\\ZOMBIES_WALK.txt"
#define PATH_ZOMBIES_SWORD L"sprite\\enemies\\ZOMBIES_SWORD.txt"


#define ID_TEXTURE_MAP_1 100
#define PATH_TEXTURE_MAP_1 L"sprite\\Stage1\\result.png"
#define PATH_POS_MAP_1 L"sprite\\Stage1\\result.txt"
#define PATH_POS_GROUND_MAP_1 "sprite\\Stage1\\ground.txt"
#define PATH_POS_ENEMIES_MAP_1 L"sprite\\Stage1\\enemies.txt"
#define PATH_POS_HIDE_SATGE_1  "sprite\\Stage1\\HideObject.txt"
#define PATH_POS_ITEMS_MAP_1 L"sprite\\Stage1\\items.txt"

#define ID_TEXTURE_MAP_2 200
#define PATH_TEXTURE_MAP_2 L"sprite\\Stage2\\texture.png"
#define PATH_POS_MAP_2 L"sprite\\Stage2\\map.txt"
#define PATH_POS_GROUND_MAP_2 "sprite\\Stage2\\ground.txt"
#define PATH_POS_LADDER_SATGE_2  "sprite\\Stage2\\ladder.txt"
#define PATH_POS_HIDE_SATGE_2  "sprite\\Stage2\\HideObject.txt"
#define PATH_POS_ENEMIES_MAP_2 L"sprite\\Stage2\\enemies.txt"


#define ID_TEXTURE_MAP_3 300
#define PATH_TEXTURE_MAP_3 L"sprite\\Stage3\\result.png"
#define PATH_POS_MAP_3 L"sprite\\Stage3\\result.txt"
#define PATH_POS_GROUND_MAP_3 "sprite\\Stage3\\ground.txt"


#define ID_BB 1
#define PATH_BB L"sprite\\bb.png"


#define ID_TEX_FONT		2000
#define ID_TEX_HUD_BG	2001
#define ID_TEX_HEALTH	2002

#define PATH_TEX_FONT	L"sprite\\Board\\font.png"
#define PATH_TEX_HUD_BG	L"sprite\\Board\\board.png"
#define PATH_TEX_HEALTH	L"sprite\\Board\\health.png"


#define MAIN_WALK_PACE 0.1f
#define MAIN_JUMP_SPEED_Y 0.3f

// ========= OBJECT =========
enum OBJECT_TYPE {
	BRICK = 3,
	MAIN_CHARACTER,
	BOSS,
	BOSS_EXPLODE,
	BOSS_BULLET,
	CROW,
	EAGLE,
	BUTTERFLY,
	BOXER,
	SOLDIER,
	GREEN_SOLDIER,
	EXPLODE,
	BAZOOKA_BULLET,
	GREEN_SOLDIER_BULLET,
	JAGUAR,
	ZOMBIE,
	ZOMBIE_SWORD,
	ITEM,
	LADDER,
	BAT,
	HIDE_OBJECT
};

enum HIDE_OBJECT_TYPE {
	TOP_LADDER,
	BOTTOM_LADDER,
	END_MAP,
START_MAP
};

// ========== MAIN CHARACTER STATE ==========
enum MAIN_CHARACTER_STATE {
	STATE_IDLE,
	STATE_WALK,
	STATE_ATTACK,
	STATE_SIT,
	STATE_JUMP,
	STATE_SIT_ATTACK,
	STATE_JUMP_TO,
	STATE_HURT,
	STATE_DIE,
	STATE_JUMP_ATTACK,
	STATE_JUMP_ATTACK_TO,
	STATE_ON_LADDER,
	STATE_CLIMBING,
	STATE_FALL
};

// ========== ENEMIES STATE ==========
enum SOLDIER_STATE {
	SOLDIER_WALK_LEFT,
	SOLDIER_WALK_RIGHT,
	SOLDIER_KILL_LEFT,
	SOLDIER_KILL_RIGHT
};

enum ZOMBIES_STATE {
	ZOMBIES_WALK_LEFT,
	ZOMBIES_WALK_RIGHT,
	ZOMBIES_KILL_LEFT,
	ZOMBIES_KILL_RIGHT
};

enum GREEN_SOLDIER_STATE {
	GREEN_SOLDIER_WALK_LEFT,
	GREEN_SOLDIER_WALK_RIGHT,
	GREEN_SOLDIER_SHOOT_LEFT,
	GREEN_SOLDIER_SHOOT_RIGHT,
	GREEN_SOLDIER_BAZOOKA_LEFT,
	GREEN_SOLDIER_BAZOOKA_RIGHT
};

// ========== BOSS ===============
enum BOSS_STATE {
	BOSS_STAND,
	BOSS_JUMP
};

// ========== GRID ===============
#define CELL_SIZE 128
#define BRICK_SIZE 16

#define LEFT -1
#define	RIGHT 1
#define UP 1
#define DOWN -1