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

void MonsterManager::SpawnMonsters(vector<vector<int>> mapData)
{
	for (int y = 0; y < mapData.size(); y++)
	{
		vector<int> rowData = mapData[y];
		//0�� ��������
		//1�� ���� x
		//2�� ���� y
		//3�� ���� ü��

		monsters.push_back(new Monster(mapData[y][0], mapData[y][1], mapData[y][2], mapData[y][3]));
	}
}

void MonsterManager::SetTarget(Rect* target)
{
	for (Monster*& monster : monsters)
		monster->SetTarget(target);
}
