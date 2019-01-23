#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "trace.h"

LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPCWSTR FilePath);