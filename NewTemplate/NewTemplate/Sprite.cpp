#include "Sprite.h"


Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, LPCWSTR filePath)
{
	if (texture == NULL) {
		return;
	}

	this->texture = texture;
	this->index = 0;

	this->spritePositions = new vector<vector<int>*>();

	this->SetSpritePositions(filePath);
	isDone = false;
}

Sprite::~Sprite()
{
	for (int i = 0; i < this->spritePositions->size(); i++) {
		delete this->spritePositions->at(i);
	}

	delete this->spritePositions;
}

void Sprite::SetSpritePositions(LPCWSTR filePath)
{
	// Đọc thông tin file
	fstream f;
	try
	{
		f.open(filePath);
	}
	catch (fstream::failure e)
	{
		trace(L"Error when Init Sprite %s", filePath);
	}

	string line;
	while (!f.eof()) {
		getline(f, line);

		string splitString;

		istringstream iss(line);

		vector<int> * tempVector = new vector<int>();

		while (getline(iss, splitString, '\t'))
		{
			tempVector->push_back(stoi(splitString));
		}

		this->spritePositions->push_back(tempVector);
	}

	trace(L"Done Init Sprite %s", filePath);
	f.close();
}

void Sprite::UpdateSprite()
{
	DWORD now = GetTickCount();
	if (this->index == -1)
	{
		this->index = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t =this->GetTime();
		if (now - lastFrameTime > 100)
		{
			lastFrameTime = now;
			if (this->index == this->spritePositions->size()-1)
			{
				isDone = true;
				this->index = 0;
			}
			else this->index = (this->index + 1) % this->spritePositions->size();
		}
	}
	
}

void Sprite::DrawSprite(D3DXVECTOR3 position, bool flagRight)
{
	if (this->texture == NULL)
		return;

	RECT rect = ReadCurrentSpritePosition();	//đọc tọa độ của sprite trong file txt

	// Texture being used is width by height:
	D3DXVECTOR3 spriteCentre = D3DXVECTOR3((float)this->width, (float)this->height, 0);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	// Biến này làm cho object quay theo trục X (trục dọc)
	float tempTurnRight = 1.0f;

	if (!flagRight) {
		tempTurnRight = -1.0f;
	}

	D3DXVECTOR3 scaling(tempTurnRight, 1.0f, 1.0f);

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation(&mat, &D3DXVECTOR3(width / 2, height / 2, 0), NULL, &scaling, &spriteCentre, NULL, &position);

	Game::GetInstance()->GetSpriteHandler()->SetTransform(&mat);

	Game::GetInstance()->GetSpriteHandler()->Draw(this->texture, &rect, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

RECT Sprite::ReadCurrentSpritePosition()
{
	RECT rect;
	vector<int>* tempVector = this->spritePositions->at(this->index);

	// Giá trị đầu tiên là x, giá trị thứ 2 là y, giá trị thứ 3 là width, giá trị thứ 4 là height
	rect.left = tempVector->at(0);
	rect.top = tempVector->at(1);
	rect.right = rect.left + tempVector->at(2);
	rect.bottom = rect.top + tempVector->at(3);

	this->width = tempVector->at(2);
	this->height = tempVector->at(3);
	return rect;
}

void Sprite::Reset()
{
	this->index = 0;
}
