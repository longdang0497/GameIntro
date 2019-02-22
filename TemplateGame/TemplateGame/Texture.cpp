#include "Texture.h"

Texture::Texture() {
	this->transColor = D3DCOLOR_ARGB(255, 255, 255, 255);
}

Texture::~Texture() {

}

LPDIRECT3DTEXTURE9 Texture::LoadTexture(LPDIRECT3DDEVICE9 d3ddev, LPCWSTR fileName) {
	HRESULT result;
	LPDIRECT3DTEXTURE9 texture = NULL;
	this->textureFilePath = fileName;
	
	// Doc thong tin file anh de tao texture
	D3DXIMAGE_INFO infoOfTexture;

	result = D3DXGetImageInfoFromFile(this->textureFilePath, &infoOfTexture);
	if (result != D3D_OK)
		return NULL;

	result = D3DXCreateTextureFromFileEx(d3ddev,
		this->textureFilePath,
		infoOfTexture.Width,
		infoOfTexture.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transColor,
		&infoOfTexture,
		NULL,
		&texture);

	if (result != D3D_OK)
		return NULL;
	return texture;
}