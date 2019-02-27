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
#include <vector>

using namespace std;

class Sprite {
private:
	LPDIRECT3DTEXTURE9 texture;      // file chua sprite lon
	LPD3DXSPRITE spriteHandler;			  // Dung de xu ly xuat hien sprite dua vao texture
	D3DCOLOR transColor;			  // transparent color
	vector<vector<int>*> * spritePositions; // Dùng để lưu lại vị trí tất cả các sprite thuộc về Stage đang xét

	int width;
	int height;
	int count;						  // So luong sprite trong texture
	int index;
	
	void SetSpritePositions(LPCWSTR filePath);
public:
	Sprite(LPD3DXSPRITE, LPDIRECT3DTEXTURE9, LPCWSTR, int, int, int);
	~Sprite();
	void UpdateSprite();

	void DrawSprite(int x, int y, D3DXVECTOR3 position);	//draw 1 sprite
	void DrawSprite(D3DXVECTOR3 position, bool flagRight);	//draw multi sprites
	RECT* ReadCurrentSpritePosition();
	void Reset();

	void SetWidth(int value);
	int GetWidth();

	void SetHeight(int value);
	int GetHeight();

	int GetIndex();
	int GetCount();
};