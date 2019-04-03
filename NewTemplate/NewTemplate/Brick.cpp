#include "Brick.h"



CBrick::CBrick(int left, int top, int right, int bottom)
{
	position.x = left;
	position.y = top;
	value.top = top;
	value.right = right;
	value.left = left;
	value.bottom = bottom;
	createAnimation();
}


CBrick::~CBrick()
{
}

void CBrick::createAnimation()
{
}

void CBrick::Render(CCamera *cam)
{
	RenderBoundingBox(cam);
}

void CBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = position.x;
	top = position.y;
	right = value.right;
	bottom = value.bottom;
}
