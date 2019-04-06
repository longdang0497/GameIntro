#include "Camera.h"



Camera::Camera()
{
	cameraPosition = { 0,0 };
}


Camera::~Camera()
{
}

D3DXVECTOR2 Camera::transformObjectPosition(D3DXVECTOR2 objectPosition)
{
	D3DXVECTOR2 value = { objectPosition.x - cameraPosition.x,objectPosition.y - cameraPosition.y };
	return value;
}

void Camera::Update(D3DXVECTOR2 simonPosition)
{
	cameraPosition = { simonPosition.x - 640 / 2,cameraPosition.y };
	if (cameraPosition.x < 0)
		cameraPosition = { 0 ,cameraPosition.y };
	if (cameraPosition.x + 640 > 2048)
		cameraPosition = { 2048 - 640,cameraPosition.y };
}
