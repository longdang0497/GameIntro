#include "CSprites.h"
//#include "MetroidGame.h"

CSprite::CSprite(int id, D3DXVECTOR2 coord, int width, int height, LPDIRECT3DTEXTURE9 tex, LPD3DXSPRITE spriteHandler)
{
	this->id = id;
	//this->srec = rect;
	this->coord = coord;
	this->width = width;
	this->height = height;
	this->texture = tex;
	this->spriteHandler = spriteHandler;
	// Gan he mau trong suot
	transColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(D3DXVECTOR3 position, bool flagRight)
{
	//MetroidGame * world = MetroidGame::GetInstance();
	if (this->spriteHandler == NULL || this->texture == NULL)
		return;
	
	RECT srec;
	srec.top = coord.y;
	srec.left = coord.x;
	srec.bottom = srec.top + this->height;
	srec.right = srec.left + this->width;

	this->spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	// Texture being used is width by height:
	D3DXVECTOR3 spriteCentre = D3DXVECTOR3(width, height, 0);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	// Biến này làm cho object quay theo trục X (trục dọc)
	float tempTurnRight = 2.0f;

	if (!flagRight) {
		tempTurnRight = -2.0f;
	}

	D3DXVECTOR3 scaling(tempTurnRight, 2.0f, 2.0f);

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation(&mat, &D3DXVECTOR3(width / 2, height / 2, 0), NULL, &scaling, &spriteCentre, NULL, &position);

	this->spriteHandler->SetTransform(&mat);
	this->spriteHandler->Draw(texture, &srec, NULL, &position, this->transColor);
	this->spriteHandler->End();


	//world = nullptr;
	//delete(world);
}

void CSprites::Add(int id, D3DXVECTOR2 coord, int width, int height, LPDIRECT3DTEXTURE9 tex, LPD3DXSPRITE spriteHandler)
{
	LPSPRITE s = new CSprite(id, coord, width, height, tex, spriteHandler);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(D3DXVECTOR3 position)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
		
	}

	frames[currentFrame]->GetSprite()->Draw(position, flagRight);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani, bool flagRight)
{
	animations[id] = ani;
	animations[id]->SetFlagDirection(flagRight);
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}