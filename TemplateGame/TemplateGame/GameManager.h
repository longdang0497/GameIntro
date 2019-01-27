#pragma once
#include "MetroidGame.h"
#include "World.h"
#include "Grid.h"
#include <time.h>
#include "trace.h"
#include "utils.h"

class GameManager : public MetroidGame
{
protected:
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DTEXTURE9 _texture;
	World * world;
	//CSound * intro;
	//CSound * appear;
	//GameSound *sound;
	Grid *grid;
	DWORD tick_per_frame;
private:
	void _InitBackground();
	void _InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void _InitPositions();

	//Map *map;

	//Texture texture;
public:
	GameManager(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~GameManager();

	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddev);
	// ---------------------------
	virtual void Update(float Delta); 
	// -----------------------------
	virtual void Render(LPDIRECT3DDEVICE9 d3ddv);	
	// ---------------------------
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	DWORD GetTickPerFrame();

	int screenMode;

	LPD3DXSPRITE getSpriteHandler();
	//Map *getMap();
	//Grid* getGrid();
};