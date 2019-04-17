#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "trace.h"
#include <vector>
#include "Game.h"

using namespace std;

class Sprite
{
private:
	LPDIRECT3DTEXTURE9 texture;      // file chua sprite lon

	vector<vector<int>*> * spritePositions; // Dùng để lưu lại vị trí tất cả các sprite thuộc về Stage đang xét

	int width;
	int height;
	int index;

	bool isDone;

	DWORD time;
	DWORD lastFrameTime;

	void SetSpritePositions(LPCWSTR filePath);

public:
	Sprite(LPDIRECT3DTEXTURE9, LPCWSTR); // Phương thức mới dùng để khỏi tạo sprite và dựa hoàn toàn vào file
	~Sprite();

	void UpdateSprite();
	void DrawSprite(D3DXVECTOR3 position, bool flagRight);	//draw multi sprites
	RECT ReadCurrentSpritePosition();
	void Reset();

	DWORD GetTime() { return time; }

	bool getDone() { return this->isDone; }
	void setDone(bool a) { this->isDone = a; }

	int GetHeight() { return this->height; }
	void SetHeight(int a) { this->height = a; }
	int GetWidth() { return this->width; }
	void SetWidth(int a) { this->width = a; }

	int GetIndex() { return this->index; }

	void GetBoundingBox(int &width, int &height) { width = this->width; height = this->height; }
};

