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

	void AllActive(bool isActive);

	void Spawn(int x, int y);
	void SpawnMonsters(vector<vector<int>> mapData);

	void SetTarget(Character* target);
	void SetLandTexture(Texture* texture);
	void SetHitAudioKey(string key);
	
	void SetOffAllHpBar();

	//static
	static void KillEnemy() { score++; }

	//Return Monster
	Monster* Collision(Rect* rect);
	
private:
	vector<Monster*> monsters;

	static int score;
};