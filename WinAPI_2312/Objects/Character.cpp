#include "Framework.h"

Character::Character()
{
	
}

Character::~Character()
{
}

void Character::DamageHp(int damage)
{
	if (IsDie()) return;

	HitAudio();
	hp -= damage;
	UpdateHp();
}

void Character::CreateHpBar(Texture* frontTexture, Texture* backTexture ,Vector2 pos, bool isActive )
{
	if (frontTexture == nullptr || backTexture == nullptr) return; // null Ã³¸®
	
	this->hpBar = new ProgressBar(frontTexture, backTexture, true);

	this->hpBar->SetPos(pos);
	this->hpBar->SetActive(isActive);
	UpdateHp();
}
