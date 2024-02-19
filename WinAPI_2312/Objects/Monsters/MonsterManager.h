#pragma once

class MonsterManager : public Singleton<MonsterManager>
{
private:
	friend class Singleton;
public:
	MonsterManager();
	MonsterManager(vector<vector<int>> mapData);
	~MonsterManager();

public:
	void Update();
	void Render(HDC hdc);

public:
	void SpawnMonsters(vector<vector<int>> mapData);
	void SetTarget(Character* target);

	static void KillEnemy() { score++; }

	Monster* Collision(Rect* rect);
	
private:
	vector<Monster*> monsters;

	static int score;
};