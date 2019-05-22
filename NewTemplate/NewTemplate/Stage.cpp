#include "Stage.h"

Stage::Stage()
{
	this->objects = new vector<Object*>();

	HUD::GetInstance();
}

Stage::~Stage()
{
	//if (item != nullptr) delete item;
}

void Stage::InitStaticObjects(RECT rect, vector<RECT> *staticObjects)
{

	int n = floor(rect.left / CELL_SIZE);
	int tempRight = (n+1) * CELL_SIZE;
	if (tempRight > rect.right) {
		this->InitStaticObjects1(rect, staticObjects);
		return;
	}
	else {
		RECT rect1;
		rect1.top = rect.top;
		rect1.left = rect.left;
		rect1.right = tempRight;
		rect1.bottom = rect.bottom;
		this->InitStaticObjects1(rect1, staticObjects);

		RECT rect2;
		rect2.top = rect.top;
		rect2.left = tempRight;
		rect2.bottom = rect.bottom;
		rect2.right = rect.right;

		this->InitStaticObjects(rect2, staticObjects);
	}

	
}

void Stage::InitStaticObjects1(RECT rect, vector<RECT> *staticObjects)
{
	int n = floor(rect.top / CELL_SIZE);
	int tempBottom = (n + 1) * CELL_SIZE;
	if (tempBottom > rect.bottom) {
		staticObjects->push_back(rect);
		return;
	}
	else {
		RECT rect1;
		rect1.top = rect.top;
		rect1.left = rect.left;
		rect1.right = rect.right;
		rect1.bottom = tempBottom;
		staticObjects->push_back(rect1);

		RECT rect2;
		rect2.top = tempBottom;
		rect2.left = rect.left;
		rect2.bottom = rect.bottom;
		rect2.right = rect.right;

		this->InitStaticObjects1(rect2, staticObjects);
	}
}

void Stage::InitEnemies(LPCWSTR filePath)
{
	fstream fs(filePath);

	vector<ZombieSword*>* S = new vector<ZombieSword*>();
	Zombie *z;

	int numOfObject, left, top, limit1, limit2, objectType, direction, itemId;

	fs >> numOfObject;	

	for (int i = 0; i < numOfObject; i++) {
		fs >> left >> top >> limit1 >> limit2 >> objectType >> direction;
		top += 80;
		D3DXVECTOR3 pos(left, top, 0);

		switch (objectType) {
		case JAGUAR_ID:
			this->objects->push_back(new Jaguar(pos, direction, limit1, limit2));
			break;
		case SOLDIER_ID:
			this->objects->push_back(new Soldier(pos, direction, limit1, limit2));
			break;
		case BUTTERFLY_ID:
		{
			fs >> itemId;			
			this->objects->push_back(new Butterfly(pos, direction, limit1, limit2, itemId));			
			InitItems(pos, itemId);
			break;
		}
		case CROW_ID:
		{
			fs >> itemId;
			this->objects->push_back(new Crow(pos, direction, limit1, limit2));
			InitItems(pos, itemId);
			break;
		}
		case EAGLE_ID:
			//this->objects->push_back(new Eagle(pos, direction, limit1, limit2));
			break;
		case ZOMBIE_ID:
			z = new Zombie(pos, direction, limit1, limit2);
			this->objects->push_back(z);
			S = z->GetSwords();
			for (auto iter : *S)
			{
				this->objects->push_back(iter);
			}
			break;
		case GREEN_SOLDIER_ID:
			this->objects->push_back(new GreenSodier(pos, direction, limit1, limit2));
			break;
		case BAT_ID:
			this->objects->push_back(new Bat(pos, direction, limit1, limit2));
			break;
		default:
			break;
		}
	}	
	fs.close();
}

void Stage::InitItems(D3DXVECTOR3 pos, int objectID)
{
	/*fstream fs(filePath);

	int numOfObject, left, top, objectType;

	fs >> numOfObject;

	for (int i = 0; i < numOfObject; i++) {
		fs >> left >> top >> objectType;
		D3DXVECTOR3 pos(left, top - 50, 0);
*/
		switch (objectID) {
		case BLUE_R_ID:
			this->objects->push_back(new Item(pos, BLUE_R_ID));
			break;
		case ORANGE_R_ID:
			this->objects->push_back(new Item(pos, ORANGE_R_ID));
			break;
		case BLUE_DART_ID:
			this->objects->push_back(new Item(pos, BLUE_DART_ID));
			break;
		case ORANGE_DART_ID:
			this->objects->push_back(new Item(pos, ORANGE_DART_ID));
			break;
		case BLUE_POCKET_ID:
			this->objects->push_back(new Item(pos, BLUE_POCKET_ID));
			break;
		case ORANGE_POCKET_ID:
			this->objects->push_back(new Item(pos, ORANGE_POCKET_ID));
			break;
		case BLUE_JAR_ID:
			this->objects->push_back(new Item(pos, BLUE_JAR_ID));
			break;
		case ORANGE_JAR_ID:
			this->objects->push_back(new Item(pos, ORANGE_JAR_ID));
			break;
		case BIG_SHURIKEN_ID:
			this->objects->push_back(new Item(pos, BIG_SHURIKEN_ID));
			break;
		case SANDGLASS_ID:
			this->objects->push_back(new Item(pos, SANDGLASS_ID));
			break;
		case ITEM_FIRE_ID:
			this->objects->push_back(new Item(pos, ITEM_FIRE_ID));
			break;
		default:
			break;
		}
	/*}

	fs.close();*/
}

void Stage::Update(float deltaTime)
{

	if (fadeIn || fadeOut)
		return;

	if (MainCharacter::GetInstance()->GetPosition().y >= 270)
	{
		//chuyen toi man ket thuc ma chua viet code
		return;
	}


	CKeyGame* k = CKeyGame::getInstance();

	if (k->keyMoveNextPoint)
	{
		MoveNextPoint();
	}



	HUD::GetInstance()->Update(deltaTime);


	for (int i = 0; i < this->objects->size(); i++) {

		float x, y;
		x = this->objects->at(i)->GetPosition().x;
		y = this->objects->at(i)->GetPosition().y;

		if (y >= 270 && this->objects->at(i)->GetObjectType()!=JAGUAR)
		{
				this->objects->at(i)->SetVeclocity(0, 0);
		}
		else if (this->objects->at(i)->GetObjectType() == BOSS || this->objects->at(i)->GetObjectType() == BOSS_BULLET) 
		{
			this->objects->at(i)->Update(deltaTime, new vector<Object*>);
			Grid::GetInstance()->UpdateGrid(this->objects->at(i));

		}
		else if( (this->objects->at(i)->GetObjectType() != BRICK 
			
			/*&& this->objects->at(i)->GetPosition().x >= MainCharacter::GetInstance()->GetPosition().x - 200
			&& this->objects->at(i)->GetPosition().x <= MainCharacter::GetInstance()->GetPosition().x + 150*/
			&& this->objects->at(i)->GetPosition().x >= Camera::GetInstance()->getPosition().x - 100
			&& this->objects->at(i)->GetPosition().x <= Camera::GetInstance()->getPosition().x + Graphic::GetInstance(NULL, NULL, L"", NULL)->GetWidth()
			|| (this->objects->at(i)->GetObjectType() == JAGUAR)
			))
		{
			vector<Object*>* collisionsObject = Grid::GetInstance()->GetCollisionObjects(this->objects->at(i));

			this->objects->at(i)->Update(deltaTime, collisionsObject);

			for (int j = 0; j < collisionsObject->size(); j++) {
				Grid::GetInstance()->UpdateGrid(collisionsObject->at(j));
			}


			Grid::GetInstance()->UpdateGrid(this->objects->at(i));

		}
	}

	Camera::GetInstance()->Update(MainCharacter::GetInstance()->GetPosition());
}

void Stage::Render()
{
	HUD::GetInstance()->Draw(Camera::GetInstance()->getPosition());

	map->drawMap();

	for (int i = 0; i < this->objects->size(); i++) {
		if (this->objects->at(i)->GetObjectType() != BOSS_BULLET) {
			this->objects->at(i)->Render();
		}
		
	}
}

int Stage::Nextpoint()
{
	if (SpecialPoint.size() == 0)
		return -1;
	else
	{
		for (int i = 0; i < SpecialPoint.size() - 1; i++)
		{
			if (MainCharacter::GetInstance()->GetPosition().x >= SpecialPoint.at(i)
				&& MainCharacter::GetInstance()->GetPosition().x <= SpecialPoint.at(i + 1))
				return SpecialPoint.at(i + 1);
		}
		return -1;
	}

}

void Stage::FadeInEffect()
{

}

void Stage::FadeOutEffect()
{

}

void Stage::MoveNextPoint()
{
	int nextpoint = Nextpoint();
	if (nextpoint != -1)
		MainCharacter::GetInstance()->SetPosition(nextpoint, 80);

}


void Stage::AddZombieSword(ZombieSword *Zw)
{
	this->objects->push_back(Zw);
}