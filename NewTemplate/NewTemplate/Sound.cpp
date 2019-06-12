#include "Sound.h"

bool GameSound::m_isSoundOff = false;
GameSound* GameSound::_instance = NULL;

GameSound::GameSound()
{
	//create DirectSound manager object
	dsound = new CSoundManager();
}

bool GameSound::InitializeDirectSound(HWND hWnd)
{
	bool isInit_Audio = true;
	HRESULT result;

	//initialize DirectSound
	result = dsound->Initialize(hWnd, DSSCL_PRIORITY);
	if (result != DS_OK)
		isInit_Audio = false;

	//set the primary buffer format
	result = dsound->SetPrimaryBufferFormat(2, 22050, 16);
	if (result != DS_OK)
		isInit_Audio = false;

	//return success
	return isInit_Audio;
}

bool GameSound::Init(HWND hwnd)
{
	bool result;
	// Initialize direct sound and the primary sound buffer.
	result = InitializeDirectSound(hwnd);
	if (!result)
	{
		return false;
	}
}

CSound* GameSound::LoadSound(LPTSTR filename)
{
	HRESULT res;

	//create local reference to wave data
	CSound *wave;

	//attempt to load the wave file
	res = dsound->Create(&wave, filename);
	if (res != DS_OK)
		return NULL;

	//return the wave
	return wave;
}

void GameSound::Playsound(CSound *sound)
{
	sound->Play();
}

void GameSound::Loopsound(CSound *sound)
{
	sound->Play(0, DSBPLAY_LOOPING);
}

void GameSound::Stopsound(CSound *sound)
{
	sound->Stop();
}