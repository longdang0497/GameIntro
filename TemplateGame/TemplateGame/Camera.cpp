#include "Camera.h"

Camera::Camera()
{
	this->cameraWidth = DEFAULT_CAMERA_WIDTH;
	this->cameraHeight = DEFAULT_CAMERA_HEIGHT;
	this->angle = DEFAULT_CAMERA_ANGLE;
	this->startPosX = DEFAULT_CAMERA_START_POS_X;
	this->endPosX = DEFAULT_CAMERA_END_POS_X;
	this->mapBoundary = new RECT();
	this->cameraBound = new RECT();
	this->followingObject = nullptr;
}

Camera::Camera(int cameraWidth, int cameraHeight, float angle, DirectX::XMFLOAT3 scaleFactors)
{
	Camera::Camera();
	this->cameraWidth = cameraWidth;
	this->cameraHeight = cameraHeight;
	this->angle = angle;
	this->scaleFactors = scaleFactors;

	// Cái khúc phía dưới này là mặc định òi, còn vì sao có số đó thì trong hàm UPDATE ~~
	float left = -this->cameraWidth * CAMERA_FOLLOW_POINT_LEFT_RATIO;
	float right = this->cameraWidth * CAMERA_FOLLOW_POINT_RIGHT_RATIO;
	float top = this->cameraHeight * CAMERA_FOLLOW_POINT_TOP_RATIO;
	float bottom = -this->cameraHeight * CAMERA_FOLLOW_POINT_BOTTOM_RATIO;
	D3DXMatrixOrthoOffCenterLH(&orthographicMatrix, left, right, bottom, top, 0.0f, 1.0f);
	//D3DXMatrixIdentity(&identityMatrix);

}

Camera::~Camera()
{
	this->mapBoundary = nullptr;
	delete this->mapBoundary;

	this->cameraBound = nullptr;
	delete this->cameraBound;

	this->followingObject = nullptr;
	delete this->followingObject;
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
	eye.x = this->followingObject->GetCurPos()->GetPosX();
	eye.y = this->followingObject->GetCurPos()->GetPosY();

	// Điều chỉnh boundary cho camera (cái khúc này tính tay từ từ nó ra ~~ )
	this->cameraBound->top = this->mapBoundary->top - (long long) CAMERA_FOLLOW_POINT_TOP_RATIO * this->cameraHeight;
	this->cameraBound->bottom = this->mapBoundary->bottom + (long long)CAMERA_FOLLOW_POINT_BOTTOM_RATIO * this->cameraHeight;
	this->cameraBound->left = this->followingObject->GetCurPos()->GetPosX() - (long long)CAMERA_FOLLOW_POINT_LEFT_RATIO * this->cameraWidth;
	this->cameraBound->right = this->followingObject->GetCurPos()->GetPosX() + (long long)CAMERA_FOLLOW_POINT_RIGHT_RATIO * this->cameraWidth;

	// Kiểm tra cái camera vs cái map của mình, có tách dụng để giới hạn lại sự xuất hiện lên màn hình
	if (this->cameraBound->left < this->mapBoundary->left)
		eye.x = this->mapBoundary->left + CAMERA_FOLLOW_POINT_LEFT_RATIO * this->cameraWidth;
	else if (this->cameraBound->right > this->mapBoundary->right)
		eye.x = this->mapBoundary->right - CAMERA_FOLLOW_POINT_RIGHT_RATIO * this->cameraWidth;

	if (this->cameraBound->top < this->mapBoundary->top)
		eye.y = this->mapBoundary->top + CAMERA_FOLLOW_POINT_TOP_RATIO * this->cameraHeight;
	else if (this->cameraBound->bottom > this->mapBoundary->bottom)
		eye.y = this->mapBoundary->bottom - CAMERA_FOLLOW_POINT_BOTTOM_RATIO * this->cameraHeight;

	//update camera bound
	this->cameraBound->top = eye.y - (long long)(CAMERA_FOLLOW_POINT_TOP_RATIO * this->cameraHeight);
	this->cameraBound->bottom = eye.y + (long long)(CAMERA_FOLLOW_POINT_BOTTOM_RATIO * this->cameraHeight);
	this->cameraBound->left = eye.x - (long long)(CAMERA_FOLLOW_POINT_LEFT_RATIO * this->cameraWidth);
	this->cameraBound->right = eye.x + (long long)(CAMERA_FOLLOW_POINT_RIGHT_RATIO * this->cameraWidth);
}

void Camera::SetTransform(DeviceManager * device)
{
	device->GetDevice()->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	device->GetDevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
}

// Cài đặt camera cần phải theo dõi đối tượng nào
void Camera::Follow(Object * object)
{
	this->followingObject = object;
}

// Các phương thức GET/SET
void Camera::SetMapBoundary(RECT* rect)
{
	this->mapBoundary = rect;
	this->mapBoundary->right = this->cameraWidth;
}

RECT* Camera::GetMapBoundary()
{
	return this->mapBoundary;
}

void Camera::SetCameraBoundary(RECT* rect)
{
	this->cameraBound = rect;
}

RECT* Camera::GetCameraBoundary()
{
	return this->cameraBound;
}
void Camera::SetAngle(float angle)
{
	this->angle = angle;
}

float Camera::GetAngle()
{
	return this->angle;
}

void Camera::SetCameraWidth(int cameraWidth)
{
	this->cameraWidth = cameraWidth;
}

int Camera::GetCameraWidth()
{
	return this->cameraWidth;
}

void Camera::SetCameraHeight(int cameraHeight)
{
	this->cameraHeight = cameraHeight;
}

int Camera::GetCameraHeight()
{
	return this->cameraHeight;
}

void Camera::SetStartPosX(float startPosX)
{
	this->startPosX = startPosX;
}

float Camera::GetStartPosX()
{
	return this->startPosX;
}

void Camera::SetEndPosX(float endPosX)
{
	this->endPosX = endPosX;
}

float Camera::GetEndPosX()
{
	return this->endPosX;
}
