#include "Text.h"

Text* Text::__instance;

Text::Text()
{
	this->texture = Texture::GetInstance()->Get(ID_TEX_FONT);

	charWidth = 8;
	charHeight = 8;
	column = 18;
	numOfChar = 38;
	int listID[48] = { 65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,48,49,50,51,52,53,54,55,56,57,45,32 };

	for (int i = 0; i < numOfChar; i++)
	{
		
		int top = 3 + (i / column) * charHeight;
		int left = 3 + (i % column) * charWidth;
		RECT tmpRect = { left, top, left + charWidth, top + charHeight };
		listChar.insert(pair<int, RECT>(listID[i], tmpRect));
	}
}

Text::~Text()
{
}

Text* Text::GetInstance()
{
	if (__instance == NULL) __instance = new Text();
	return __instance;
}

void Text::DrawChar(char c, D3DXVECTOR2 position)
{
	RECT sourceRect = listChar[c];
	Game::GetInstance()->Draw(position.x, position.y, texture, sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom);
}

void Text::DrawChar(char c, D3DXVECTOR2 position, int alpha)
{
	RECT sourceRect = listChar[c];
	Game::GetInstance()->Draw(position.x, position.y, texture, sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom, 0);
}

void Text::DrawString(char* s, D3DXVECTOR2 position)
{
	for (int i = 0; i < strlen(s); i++)
		DrawChar(s[i], { position.x + i * charWidth, position.y });
}
void Text::DrawString(char* s, D3DXVECTOR2 position, int alpha)
{
	for (int i = 0; i < strlen(s); i++)
		DrawChar(s[i], { position.x + i * charWidth, position.y }, alpha);
}