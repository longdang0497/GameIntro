#pragma once
#include "trace.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include "Sprite.h"

class DeviceManager;

using namespace std;

class Map {
	struct brick {
		char type;
		int x_pixel;
		int y_pixel;
	};
private:
	string filePath;
	vector<string> stringMap;
	vector<brick> drawBrickArray = vector<brick>();
	int roomID;
	Sprite *sprite;

	//Start coordinate of the camera
	RECT m_boundary = RECT();

	//TODO: 
	int widthLimitation;
	int heightLimitation;

	int m_max_Row;
	int m_max_Column;

	LPDIRECT3DTEXTURE9 texture;
public:
	//Khởi tạo map dạng ô gạch
	Map(LPD3DXSPRITE spriteHandler, LPDIRECT3DTEXTURE9 texture, string filePath, int left, int top);

	//Khởi tạo map dạng hình ảnh background
	Map(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 screen, DeviceManager * device);
	~Map();

	//Vẽ map dạng ô gạch
	void drawMap();
	void drawBrick(brick value);

	//Khởi tạo map dạng hình ảnh background

	void Update(int _roomID);
	void UpdateMap(RECT);

	// Đặt giới hạn load map
	void setLimitation(int x, int y, int width, int height);
	RECT getBoundary();

	// Load map lên
	bool loadMap(string filePath);

	//LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DTEXTURE9 getTexture();
	vector<string> getStringMap();

	static const int count = 0;

	int getRow();
	int getColumn();

	//void inputBrickToGrid(Grid *grid);
};