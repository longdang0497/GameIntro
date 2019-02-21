#pragma once
#include <DirectXMath.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DeviceManager.h"
#include "Object.h"
#include "GameDefine.h"

class Camera
{
private:
	float angle;    // này dịch ra tiếng Việt là góc á
	DirectX::XMFLOAT3 scaleFactors;
	D3DXMATRIX orthographicMatrix;	//ma trận tầm nhìn
	D3DXMATRIX identityMatrix;	//ma trận vật
	D3DXMATRIX viewMatrix;	//ma trận trong world

	int cameraWidth;
	int cameraHeight;

	RECT *mapBoundary;
	Object* followingObject;
	RECT *cameraBound;

	// Vị trí bắt đầu và kết thúc
	float startPosX;
	float endPosX;
public:
	Camera();
	Camera(int cameraWidth, int cameraHeight, float angle, DirectX::XMFLOAT3 scaleFactors);
	~Camera();

	void UpdateCamera();
	void SetTransform(DeviceManager *device);
	void Follow(Object * object);

	void SetMapBoundary(RECT* rect);
	RECT* GetMapBoundary();
	void SetCameraBoundary(RECT* rect);
	RECT* GetCameraBoundary();
	void SetAngle(float angle);
	float GetAngle();
	void SetCameraWidth(int cameraWidth);
	int GetCameraWidth();
	void SetCameraHeight(int cameraHeight);
	int GetCameraHeight();
	void SetStartPosX(float startPosX);
	float GetStartPosX();
	void SetEndPosX(float endPosX);
	float GetEndPosX();

};

