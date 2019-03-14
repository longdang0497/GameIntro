#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	D3DXVECTOR2 coord;
	int width;
	int height;

	D3DCOLOR transColor;			  // transparent color
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE spriteHandler;
public: 
	CSprite(int id, D3DXVECTOR2 coord, int width, int height, LPDIRECT3DTEXTURE9 tex, LPD3DXSPRITE spriteHandler);

	void Draw(D3DXVECTOR3 position, bool flagRight);

	void SetWidth(int value) { this->width = value; }
	int GetWidth() { return this->width; }

	void SetHeight(int value) { this->height = value; }
	int GetHeight() { return this->height; }
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, D3DXVECTOR2 coord, int width, int height, LPDIRECT3DTEXTURE9 tex, LPD3DXSPRITE spriteHandler);
	LPSPRITE Get(int id);

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	bool flagRight;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(D3DXVECTOR3 position);
	void SetFlagDirection(bool value) { this->flagRight = value; }
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani, bool flagRight);
	LPANIMATION Get(int id);

	static CAnimations * GetInstance();
};

