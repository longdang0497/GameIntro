#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <iostream>
#include "trace.h"
#include "ObjectPosition.h"

using namespace std;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	ObjectPosition *position = new ObjectPosition(1.0f, 1.0f);
	
	cout << position->GetObjectWidth() << endl;
	cout << position->GetObjectHeight() << endl;

	system("pause");

	trace(L"Start game");
	return 0;
}