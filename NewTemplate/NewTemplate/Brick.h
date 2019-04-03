#pragma once
#include "Define.h"
#include "Textures.h"
#include "GameObject.h"

class CBrick : public CGameObject
{
	RECT value;
public:
	CBrick(int left, int top, int right, int bottom);
	~CBrick();

	void createAnimation();
	virtual void Render(CCamera *cam);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

