#pragma once

class Character : public Rect
{
public:
	Character();
	~Character();
	
	bool IsDie() { if (this->hp <= 0) return true; else return false; }
	
	int GetHp() { return hp; }
	void SetHp(int hp) { this->hp = hp; }

	void DamageHp(int damage) { hp -= damage; }

public:
	int hp = 100;
};