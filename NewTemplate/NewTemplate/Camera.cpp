#include "Camera.h"

Camera * Camera::_instance = NULL;


Camera::Camera(int cameraWidth, int cameraHeight, float angle, DirectX::XMFLOAT3 scaleFactors)
{
	this->cameraWidth = cameraWidth;
	this->cameraHeight = cameraHeight;
	this->angle = angle;
	this->scaleFactors = scaleFactors;
	this->startPosX = 0.0f;
	this->endPosX = 0.0f;
	this->followingObject = NULL;
}


Camera::~Camera()
{
}

void Camera::UpdateCamera()
{
	D3DXVECTOR3 eye(320, 352, 1);	// x,y not important, camera've been following m_following
	D3DXVECTOR3 direction(0, 0, -1);
	D3DXVECTOR3 up(0, -1, 0);

	D3DXMatrixLookAtLH(&viewMatrix, &eye, &(eye + direction), &up);

	if (this->followingObject == nullptr)
		return;

	// Điều chỉnh camera đi theo object
	eye.x = this->followingObject->GetPosition().x;
	eye.y = this->followingObject->GetPosition().y;

	// Điều chỉnh boundary cho camera (cái khúc này tính tay từ từ nó ra ~~ )
	this->cameraBound.top = this->mapBoundary.top - CAMERA_FOLLOW_POINT_TOP_RATIO * this->cameraHeight;
	this->cameraBound.bottom = this->mapBoundary.bottom + CAMERA_FOLLOW_POINT_BOTTOM_RATIO * this->cameraHeight;
	this->cameraBound.left = this->followingObject->GetPosition().x - CAMERA_FOLLOW_POINT_LEFT_RATIO * this->cameraWidth;
	this->cameraBound.right = this->followingObject->GetPosition().x + CAMERA_FOLLOW_POINT_RIGHT_RATIO * this->cameraWidth;

	// Kiểm tra cái camera vs cái map của mình, có tách dụng để giới hạn lại sự xuất hiện lên màn hình
	if (this->cameraBound.left < this->mapBoundary.left)
		eye.x = this->mapBoundary.left + CAMERA_FOLLOW_POINT_LEFT_RATIO * this->cameraWidth;
	else if (this->cameraBound.right > this->mapBoundary.right)
		eye.x = this->mapBoundary.right - CAMERA_FOLLOW_POINT_RIGHT_RATIO * this->cameraWidth;

	if (this->cameraBound.top < this->mapBoundary.top)
		eye.y = this->mapBoundary.top + CAMERA_FOLLOW_POINT_TOP_RATIO * this->cameraHeight;
	else if (this->cameraBound.bottom > this->mapBoundary.bottom)
		eye.y = this->mapBoundary.bottom - CAMERA_FOLLOW_POINT_BOTTOM_RATIO * this->cameraHeight;

	//update camera bound
	this->cameraBound.top = eye.y - (CAMERA_FOLLOW_POINT_TOP_RATIO * this->cameraHeight);
	this->cameraBound.bottom = eye.y + (CAMERA_FOLLOW_POINT_BOTTOM_RATIO * this->cameraHeight);
	this->cameraBound.left = eye.x - (CAMERA_FOLLOW_POINT_LEFT_RATIO * this->cameraWidth);
	this->cameraBound.right = eye.x + (CAMERA_FOLLOW_POINT_RIGHT_RATIO * this->cameraWidth);
}

void Camera::SetTransform()
{
	Game::GetInstance()->GetDirect3DDevice()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	Game::GetInstance()->GetDirect3DDevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
}

