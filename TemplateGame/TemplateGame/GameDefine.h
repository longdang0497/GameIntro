#pragma once

// ========= START: DEFAULT SETTING =========
#define TRACE_LOG_PATH "Log\\trace.log"
#define DEFAULT_SCREEN_MODE 0
#define DEFAULT_IS_FULL_SCREEN false
#define DEFAULT_FRAME_RATE 30
#define DEFAULT_NAME_OF_GAME L"Game Developer for beginer"
#define DEFAULT_CAMERA_WIDTH 1
#define DEFAULT_CAMERA_HEIGHT 1
#define DEFAULT_CAMERA_ANGLE 0.0F
#define DEFAULT_CAMERA_START_POS_X 0.0f
#define DEFAULT_CAMERA_END_POS_X 0.0f
// ========= END: DEFAULT SETTING =========

// ========= START: SCREEN DIMESION =========
#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2
// ========= END: SCREEN DIMESION =========

// ========= START: INPUT HANDLE =========
#define KEYBOARD_BUFFER_SIZE	1024
#define KEY_DOWN(code) ( IsKeyDown(code) )
//#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code)&0x8000)?1:0 )
// ========= END: INPUT HANDLE =========

// ========= START: GAME MODE =========
enum GAME_MODE {
	GAME_MODE_INTRO,
	GAME_MODE_START,
	GAME_MODE_RUN,
	GAME_MODE_END
};
// ========= END: GAME MODE =========

// ========= START: CAMERA =========
#define CAMERA_FOLLOW_POINT_LEFT_RATIO   2.0/4
#define CAMERA_FOLLOW_POINT_RIGHT_RATIO  2.0/4
#define CAMERA_FOLLOW_POINT_BOTTOM_RATIO 1.0/4
#define CAMERA_FOLLOW_POINT_TOP_RATIO    3.0/4
// ========= END: CAMERA =========

// ========= START: MAP =========
#define TEST_MAP_PATH L"sprite\\testmap.txt"
// ========= END: MAP=========