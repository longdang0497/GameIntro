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

using namespace std;

class Sprite {
private:
	LPDIRECT3DTEXTURE9 texture;      // file chua sprite lon
	LPD3DXSPRITE spriteHandler;			  // Dung de xu ly xuat hien sprite dua vao texture
	D3DCOLOR transColor;			  // transparent color
	LPWSTR _Coord;

	int width;
	int height;
	int x;
	int y;	
	int count;						  // So luong sprite trong texture
	int _Index;
	RECT srect;
public:
	Sprite(LPD3DXSPRITE, LPDIRECT3DTEXTURE9, LPWSTR, int);
	~Sprite();
	void updateSprite();

	//Ex: player->drawSprite(0, 0, 16, 32, D3DXVECTOR3(10, 10, 0));
	void drawSprite(int x, int y, int width, int height, D3DXVECTOR3 position);	//draw 1 sprite
	void drawSprite(int width, int height, D3DXVECTOR3 position);	//draw multi sprites
	RECT ReadCoord();
	void ReSet();

	void SetWidth(int value);
	int GetWidth();

	void SetHeight(int value);
	int GetHeight();

	int GetIndex();
	int GetCount();
};