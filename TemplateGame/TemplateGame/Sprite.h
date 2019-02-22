#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "DeviceManager.h"
#include "DXGraphics.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "trace.h"
#include "Camera.h"

using namespace std;

class Sprite {
private:
	Camera * camera;
	LPDIRECT3DTEXTURE9 texture;      // file chua sprite lon
	LPD3DXSPRITE spriteHandler;			  // Dung de xu ly xuat hien sprite dua vao texture
	D3DCOLOR transColor;			  // transparent color
	LPWSTR coord;

	int width;
	int height;
	int count;						  // So luong sprite trong texture
	int index;
	RECT srect;
public:
	Sprite(LPD3DXSPRITE, LPDIRECT3DTEXTURE9, LPWSTR, int, int, int);
	~Sprite();
	void UpdateSprite();

	void DrawSprite(int x, int y, D3DXVECTOR3 position);	//draw 1 sprite
	void DrawSprite(D3DXVECTOR3 position);	//draw multi sprites
	RECT ReadCoord();
	void Reset();

	void SetWidth(int value);
	int GetWidth();

	void SetHeight(int value);
	int GetHeight();

	int GetIndex();
	int GetCount();
};