#include "Boss.h"

Boss::Boss(D3DXVECTOR3 pos, int appearanceDirection, int limitX1, int limitX2) : Enemy(pos, appearanceDirection, limitX1, limitX2)
{
	this->HP = 10;
	this->boss = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_BOSS);
	this->bossJump = new Sprite(Texture::GetInstance()->Get(ID_TEXTURE_ENEMIES), PATH_BOSS_JUMP);
	this->SetObjectType(BOSS);
	this->isActive = true;
	this->direction = LEFT;
	this->objectWidth = BOSS_WIDTH;
	this->objectHeight = BOSS_HEIGHT;
	this->veclocity.x = 0.15;
	this->freezeTime = GetTickCount();
	this->bossState = BOSS_STAND;
	this->countToShoot = 3;

	this->bullets = new vector<BossBullet*>();
	BossBullet *bullet1 = new BossBullet();
	BossBullet *bullet2 = new BossBullet();
	BossBullet *bullet3 = new BossBullet();

	this->bullets->push_back(bullet1);
	this->bullets->push_back(bullet2);
	this->bullets->push_back(bullet3);

}

// 513 y = 4 x2 - 868 x + 111178
void Boss::Update(float deltaTime, std::vector<Object*>* objects)
{
	if (this->HP <= 0) {
		this->Destroy();
		return;
	}

	if (!this->isActive || GetTickCount() - this->freezeTime < FREEZE_TIME) {
		return;
	}

	//std::wstringstream s;
	//s << L"position " << this->position.x << "\n";
	//std::wstring ws = s.str();
	//OutputDebugString(ws.c_str());

	if (this->position.x <= 26) {
		this->veclocity.x = 0.1;
		this->freezeTime = GetTickCount();
		this->bossState = BOSS_STAND;
		this->direction = RIGHT;
		if (this->countToShoot % 3 == 0) {
			int y = 174;
			int x = 46;

			for (auto it : *this->bullets) {
				it->SetStart(D3DXVECTOR3(x, y, 0), D3DXVECTOR3(0.13, 0, 0));
				y += 20;
				x -= 10;
			}
		}
		this->countToShoot++;
	}
	else if(this->position.x >= 191){
		this->veclocity.x = -0.1;
		this->freezeTime = GetTickCount();
		this->bossState = BOSS_STAND;
		this->direction = LEFT;
		if (this->countToShoot % 3 == 0) {
			int y = 168;
			int x = 194;

			for (auto it : *this->bullets) {
				it->SetStart(D3DXVECTOR3(x, y, 0), D3DXVECTOR3(-0.13, 0, 0));
				y += 20;
				x += 10;
			}
		}
		this->countToShoot++;
	}
	else {
		this->bossState = BOSS_JUMP;
	}

	this->position.x += this->veclocity.x * deltaTime;
	float y = (4 * pow(this->position.x, 2) - this->position.x * 868 + 111178) / 513;    
	this->position.y =  y;
	
	switch (this->bossState) {
	case BOSS_STAND:
		this->boss->UpdateSprite();
		break;
	case BOSS_JUMP:
		this->bossJump->UpdateSprite();
		break;
	default:
		break;
	}

}

void Boss::Render()
{
	if (!this->isActive) {
		return;
	}

	this->position.z = 0;

	D3DXVECTOR3 pos = Camera::GetInstance()->transformObjectPosition(position);

	if (GetTickCount() - this->freezeTime > FREEZE_TIME) {
		for (auto it : *this->bullets) {
			if (it->GetStart()) {
				it->SetIsActive(true);
			}
			it->Render();
		}
	}

	switch (this->bossState) {
	case BOSS_STAND:
		if (direction == RIGHT) {
			this->boss->DrawSprite(pos, true);
		}
		else {
			this->boss->DrawSprite(pos, false);
		}
		break;
	case BOSS_JUMP:
		if (direction == RIGHT) {
			this->bossJump->DrawSprite(pos, true);
		}
		else {
			this->bossJump->DrawSprite(pos, false);
		}
		break;
	default:
		break;
	}


}

void Boss::HandleCollision(vector<Object*>* objects)
{
}

void Boss::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (this->HP > 0) {
		l = position.x;
		t = position.y;
		r = l + objectWidth;
		b = t + objectHeight;
	}
	else
		l = t = r = b = 0;
}

void Boss::Destroy()
{
}

vector<BossBullet*>* Boss::GetBullets()
{
	return this->bullets;
}
