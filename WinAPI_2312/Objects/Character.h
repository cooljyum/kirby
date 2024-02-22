#pragma once

class Character : public Rect
{
public:
	Character();
	~Character();
	
	bool IsDie() { return (this->hp <= 0) ? true : false; }
	
	int GetHp() { return hp; }
	void SetHp(int hp) { this->hp = hp; UpdateHp(); }

	void DamageHp(int damage) { hp -= damage; UpdateHp();}
	void UpdateHp() { if(hpBar!= nullptr)	hpBar->SetValue((float)this->hp / maxHp); }

public:
	int hp = 100;
	ProgressBar* hpBar;
	float maxHp = hp;
};