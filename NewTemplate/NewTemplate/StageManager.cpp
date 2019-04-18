#include "StageManager.h"


StageManager* StageManager::Instance = NULL;

StageManager::StageManager()
{
}


StageManager::~StageManager()
{
}

void StageManager::LoadResources()
{
	currentStage->LoadResource();
}
void StageManager::Update(DWORD dt)
{
	currentStage->Update(dt);
}
void StageManager::Render()
{
	currentStage->Render();
}
