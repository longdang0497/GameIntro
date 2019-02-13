#pragma once
#include "MetroidGame.h"
#include "Grid.h"
#include <time.h>
#include "trace.h"
#include "utils.h"

class GameManager : public MetroidGame
{
protected:
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DTEXTURE9 texture;
	//CSound * intro;
	//CSound * appear;
	//GameSound *sound;
	Grid *grid;
	DWORD tickPerFrame;
	int screenMode;
private:
	void InitBackground();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void InitPositions();

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

	LPD3DXSPRITE GetSpriteHandler();
	//Map *getMap();
	//Grid* getGrid();
};