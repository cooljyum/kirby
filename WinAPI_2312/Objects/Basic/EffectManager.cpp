#include "Framework.h"

EffectManager::~EffectManager()
{
	for (pair<string, Effects> effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			delete effect;
		effects.second.clear();
	}

	totalEffect.clear();
}

void EffectManager::Update()
{
	for (pair<string, Effects> effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Update();
	}
}

void EffectManager::Render(HDC hdc)
{
	for (pair<string, Effects> effects : totalEffect)
	{
		for (Effect* effect : effects.second)
			effect->Render(hdc);
	}
}

void EffectManager::Play(string key, Vector2 pos)
{
	for (Effect* effect : totalEffect[key])
	{
		if (!effect->IsActive())
		{
			effect->Play(pos);
			return;
		}
	}
}

void EffectManager::Add(string key, int poolSize, Texture* texture, float speed, bool isLoop)
{
	if (totalEffect.count(key) > 0)
		assert(false);

	Effects effects(poolSize);

	for (Effect*& effect : effects)
	{
		effect = new Effect(texture, speed, isLoop);
		effect->SetActive(false);
	}

	totalEffect[key] = effects;
}
