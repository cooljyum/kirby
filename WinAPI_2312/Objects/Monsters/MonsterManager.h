#pragma once

class MonsterManager 
{
public:
	MonsterManager();
	MonsterManager(vector<vector<int>> mapData);
	~MonsterManager();

public:
	void Update();
	void Render(HDC hdc);

	void SpawnMonsters(vector<vector<int>> mapData);
	void SetTarget(Character* target);

	static void KillEnemy() { score++; }

private:
	vector<Monster*> monsters;

	static int score;
};