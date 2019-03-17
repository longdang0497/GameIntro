#pragma once
#include <DirectXMath.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"
#include "Game.h"

#define CAMERA_FOLLOW_POINT_LEFT_RATIO   2.0/4
#define CAMERA_FOLLOW_POINT_RIGHT_RATIO  2.0/4
#define CAMERA_FOLLOW_POINT_BOTTOM_RATIO 1.0/4
#define CAMERA_FOLLOW_POINT_TOP_RATIO    3.0/4

class Camera
{
private:

	static Camera* _instance;

	float angle;
	DirectX::XMFLOAT3 scaleFactors;

	D3DXMATRIX orthographicMatrix;	//ma trận tầm nhìn
	D3DXMATRIX identityMatrix;	//ma trận vật
	D3DXMATRIX viewMatrix;	//ma trận trong world

	int cameraWidth;
	int cameraHeight;

	RECT mapBoundary;
	Object* followingObject;
	RECT cameraBound;

	// Vị trí bắt đầu và kết thúc
	float startPosX;
	float endPosX;

public:
	Camera(int cameraWidth, int cameraHeight, float angle, DirectX::XMFLOAT3 scaleFactors);
	~Camera();

	void UpdateCamera();
	void SetTransform();
	void Follow(Object* obj) { this->followingObject = obj; }

	void SetMapBoundary(RECT rect) { this->mapBoundary = rect; this->mapBoundary.right = this->cameraWidth; }
	RECT GetMapBoundary() { return this->mapBoundary; }

	void SetCameraBoundary(RECT rect) { this->cameraBound = rect; }
	RECT GetCameraBoundary() { return this->cameraBound; }

	static Camera* GetInstance(int cameraWidth, int cameraHeight, float angle, DirectX::XMFLOAT3 scaleFactors) {
		if (_instance == NULL) _instance = new Camera(cameraWidth, cameraHeight, angle, scaleFactors);
		return _instance;
	}
};

