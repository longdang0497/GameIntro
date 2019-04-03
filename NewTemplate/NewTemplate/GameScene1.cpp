#include "GameScene1.h"

GameScene1::GameScene1()
{

}

GameScene1::GameScene1(LPCWSTR filePath, CSimon *simon)
{

	CTextures *textures = CTextures::GetInstance();

	textures->Add(ID_TEX_BBOX, L"bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	ground = new vector<LPGAMEOBJECT>();
	item = new vector<LPGAMEOBJECT>();
	enemy = new vector<LPGAMEOBJECT>();
	staticObjects = new vector<LPGAMEOBJECT>();

	fstream fs(filePath);

	fs >> startOfWorldX >> endOfWorldX >> startOfWorldY >> endOfWorldY;


	fs >> numOfGround;

	int a, b, c, d;

	for (int i = 0; i < numOfGround; i++)
	{
		fs >> a >> b >> c >> d;

		CBrick*g = new CBrick(a, b, c, d);
		ground->push_back(g);
	}

	fs >> numOfStaticObjects;

	//for (int i = 0; i < numOfStaticObjects; i++)
	//{
	//	fs >> a >> b >> c;
	//	if (a == 2)
	//	{
	//		EndObject *e = new EndObject();
	//		e->SetPosition(D3DXVECTOR2(b, c));
	//		staticObjects->push_back(e);
	//	}
	//}

	Hunk *h = new Hunk(100, 50, 1);
	enemy->push_back(h);

	a = 0;
	b = 0;
	simon->SetPosition(D3DXVECTOR2(a, b));

	map = new Map(STATE1_TXT, STATE1_PNG, 100);
}


GameScene1::~GameScene1()
{
}


void GameScene1::update(DWORD dt, CSimon *simon)
{
	simon->Update(dt, ground, staticObjects, item, enemy);


	for (int i = 0; i < staticObjects->size(); i++)
	{
		staticObjects->at(i)->Update(dt, ground, staticObjects, item, enemy);
	}

	for (int i = 0; i < item->size(); i++)
	{
		item->at(i)->Update(dt, ground, staticObjects, item, enemy);
	}

	for (int i = 0; i < enemy->size(); i++)
	{
		enemy->at(i)->Update(dt, ground, staticObjects, item, enemy);
	}
}

void GameScene1::render(CCamera *cam, CSimon *simon)
{
	map->drawMap(cam);
	for (int i = 0; i < staticObjects->size(); i++)
	{
		staticObjects->at(i)->Render(cam);
	}

	for (int i = 0; i < item->size(); i++)
	{
		item->at(i)->Render(cam);
	}


	for (int i = 0; i < enemy->size(); i++)
	{
		enemy->at(i)->Render(cam);
	}
	for (int i = 0; i < ground->size(); i++)
	{
		ground->at(i)->Render(cam);
	}
	simon->Render(cam);
}