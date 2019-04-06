#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Define.h"

class Camera
{
	D3DXVECTOR2 cameraPosition;
public:
	Camera();

	void Update(D3DXVECTOR2 simonPosition);
	D3DXVECTOR2 transformObjectPosition(D3DXVECTOR2 objectPosition);

	D3DXVECTOR2 getPosition() { return cameraPosition; }

	~Camera();
};

