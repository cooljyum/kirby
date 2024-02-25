#pragma once

class MapItemManager : public Singleton<MapItemManager>
{
private:
	friend class Singleton;

	MapItemManager() = default;
	~MapItemManager();

public:
	void Update();
	void Render(HDC hdc);

	void AllActive(bool isActive);
	void Add(string key, int poolSize, Texture* texture, float speed = 1.0f, bool isLoop = true, int imageX = -1, int imageY = -1);

	void Play(string key, Vector2 pos);

	MapItem* Collision(string key, Rect* rect);

private:
	typedef vector<MapItem*> MapItems;
	map<string, MapItems> totalMapItem;
};