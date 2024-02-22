#pragma once

class EffectManager : public Singleton<EffectManager>
{
private:
	friend class Singleton;

	EffectManager() = default;
	~EffectManager();

public:
	void Update();
	void Render(HDC hdc);

	void Play(string key, Vector2 pos);

	void Add(string key, int poolSize, Texture* texture, float speed = 1.0f, bool isLoop = true);

private:
	typedef vector<Effect*> Effects;
	map<string, Effects> totalEffect;
};