#pragma once
#include "debug.h"
#include "Game.h"
#include "Texture.h"


class Text
{
	static Text* __instance;

	unordered_map<int, RECT> listChar;

	LPDIRECT3DTEXTURE9 texture;

	int charWidth;
	int charHeight;
	int column;
	int numOfChar;

	Text();

	void DrawChar(char c, D3DXVECTOR2 position);
public:
	~Text();

	static Text* GetInstance();

	void DrawString(char* s, D3DXVECTOR2 position);
};

