#include "Camera.h"



CCamera::CCamera()
{
	cameraPosition = { 0,0 };
}


CCamera::~CCamera()
{
}

D3DXVECTOR2 CCamera::transformObjectPosition(D3DXVECTOR2 objectPosition)
{
	D3DXVECTOR2 value = { objectPosition.x - cameraPosition.x,objectPosition.y - cameraPosition.y };
	return value;
}

void CCamera::Update(D3DXVECTOR2 simonPosition)
{
	cameraPosition = { simonPosition.x - SCREEN_WIDTH / 2,cameraPosition.y };
	if (cameraPosition.x < 0)
		cameraPosition = { 0 ,cameraPosition.y };
	if (cameraPosition.x + SCREEN_WIDTH > 2048)
		cameraPosition = { 2048 - SCREEN_WIDTH,cameraPosition.y };
}
