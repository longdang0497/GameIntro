#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Define.h"

class CCamera
{
	D3DXVECTOR2 cameraPosition;
public:
	CCamera();

	void Update(D3DXVECTOR2 simonPosition);
	D3DXVECTOR2 transformObjectPosition(D3DXVECTOR2 objectPosition);

	D3DXVECTOR2 getPosition() { return cameraPosition; }

	~CCamera();
};

