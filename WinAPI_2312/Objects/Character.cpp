#include "Framework.h"

Character::Character()
{
	
}

Character::~Character()
{
}

void Character::CreateHpBar(Texture* frontTexture, Texture* backTexture ,Vector2 pos, bool isActive )
{
	if (frontTexture == nullptr || backTexture == nullptr) return; // null Ã³¸®
	
	hpBar = new ProgressBar(frontTexture, backTexture);

	hpBar->SetPos(pos);
	hpBar->SetActive(isActive);
	UpdateHp();
}
