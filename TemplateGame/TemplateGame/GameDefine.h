#pragma once

// ========= START: DEFAULT SetTING =========
#define TRACE_LOG_PATH "Log\\trace.log";
#define DEFAULT_SCREEN_MODE 0
#define DEFAULT_IS_FULL_SCREEN false
#define DEFAULT_FRAME_RATE 30
#define DEFAULT_NAME_OF_GAME L"Game Developer for beginer"
// ========= END: DEFAULT SetTING =========

// ========= START: SCREEN DIMESION =========
#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2
// ========= END: SCREEN DIMESION =========

// ========= START: INPUT HANDLE =========
#define KEYBOARD_BUFFER_SIZE	1024
#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code)&0x8000)?1:0 )
// ========= END: INPUT HANDLE =========

// ========= START: GAME MODE =========
enum GAME_MODE {
	GAME_MODE_INTRO,
	GAME_MODE_START,
	GAME_MODE_RUN,
	GAME_MODE_END
};
// ========= END: GAME MODE =========