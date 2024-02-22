#pragma once

//Character->Rect 
//Character primarily manages the HP (Health Points).
class Character : public Rect
{
public:
	//Set
	Character();
	~Character();
	
	//Die check to hp
	bool IsDie() { return (this->hp <= 0) ? true : false; }
	
	//Hp Control
	int GetHp() { return hp; }

	void SetHp(int hp) { this->hp = hp; maxHp = hp; UpdateHp();	}

	void HealHp(int heal) { hp -= heal; UpdateHp(); }
	void DamageHp(int damage) { hp -= damage; UpdateHp(); }
	
	//HpBar Control
	void CreateHpBar(Texture* frontTexture, Texture* backTexture, Vector2 pos, bool isActive = false);
	void UpdateHp() { if(hpBar!= nullptr)	hpBar->SetValue((float)this->hp / maxHp); }

public:
	int hp = 100;
	float maxHp = hp;

	ProgressBar* hpBar = nullptr;
};