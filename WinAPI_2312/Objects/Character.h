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

	void SetHp(int hp, bool isMax = true) { this->hp = hp; if (isMax) { maxHp = hp; } UpdateHp(); }

	void HealHp(int heal) { hp -= heal; UpdateHp(); }
	void DamageHp(int damage);
	
	//HpBar Control
	void CreateHpBar(Texture* frontTexture, Texture* backTexture, Vector2 pos, bool isActive = true);
	void SetActiveHpBar(bool isActive) { hpBar->SetActive(isActive); }
	void UpdateHp() { if(hpBar!= nullptr)	hpBar->SetValue((float)this->hp / maxHp); }

	void SetHitAudioKey(string hitAudioKey) { this->hitAudioKey = hitAudioKey; }
	void HitAudio() { if(hitAudioKey != "") SOUND->Play(hitAudioKey, 0.5f); }

public:
	int hp = 100;
	float maxHp = hp;

	string hitAudioKey = "";

	ProgressBar* hpBar = nullptr;

};