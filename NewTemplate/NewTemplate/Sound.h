#pragma once
#include <dsound.h>
#include "SDKsound.h"
#include "SDKwavefile.h"
using namespace std;

//function prototypes
class GameSound
{
	//primary DirectSound object
	CSoundManager *dsound;
	static GameSound* _instance;
public:
	GameSound();

	static GameSound* GetInstance() {
		if (_instance == NULL) _instance = new GameSound();
		return _instance;
	}

	bool InitializeDirectSound(HWND);
	bool Init(HWND);
	CSound *LoadSound(LPTSTR);
	void Playsound(CSound *);
	void Loopsound(CSound *);
	void Stopsound(CSound *);
	static bool m_isSoundOff;
};