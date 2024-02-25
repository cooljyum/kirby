#include "Framework.h"

MonsterManager::MonsterManager()
{

}

MonsterManager::MonsterManager(vector<vector<int>> mapData)
{
	SpawnMonsters(mapData);
}

MonsterManager::~MonsterManager()
{
	for (Monster*& monster : monsters)
		delete monster;
}

void MonsterManager::Update()
{
	for (Monster*& monster : monsters)
		monster->Update();
}

void MonsterManager::Render(HDC hdc)
{
	for (Monster*& monster : monsters)
		monster->Render(hdc);
}

void MonsterManager::AllActive(bool isActive)
{
	for (Monster*& monster : monsters)
	{
		monster->SetAllActive(isActive);
	}
}

void MonsterManager::Spawn(int x, int y)
{
	monsters.push_back(new Monster(x, y));
}

void MonsterManager::SpawnMonsters(vector<vector<int>> mapData)
{
	for (int y = 0; y < mapData.size(); y++)
	{
		vector<int> rowData = mapData[y];
		//0은 몬스터종류
		//1은 몬스터 x
		//2는 몬스터 y
		//3은 몬스터 체력

		int type = mapData[y][0];
		monsters.push_back(new Monster(mapData[y][1], mapData[y][2], mapData[y][3]));
	}
}

void MonsterManager::SetTarget(Character* target)
{
	for (Monster*& monster : monsters)
		monster->SetTarget(target);
}

void MonsterManager::SetLandTexture(Texture* texture)
{
	for (Monster*& monster : monsters)
		monster->SetLandTexture(texture);
}

void MonsterManager::SetHitAudioKey(string key)
{
	for (Monster*& monster : monsters)
		monster->SetHitAudioKey(key);
}

void MonsterManager::SetOffAllHpBar()
{
	for (Monster*& monster : monsters)
		monster->SetActiveHpBar(false);
}

Monster* MonsterManager::Collision(Rect* rect)
{
	for (Monster*& monster : monsters)
	{
		if (monster->IsCollision(rect))
			return monster;
	}

	return nullptr;

}
