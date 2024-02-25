#include "Framework.h"

MapItemManager::~MapItemManager()
{
	for (pair<string, MapItems>	mapItems : totalMapItem)
	{
		for (MapItem* mapItem : mapItems.second)
			delete mapItem;
		mapItems.second.clear();
	}

	totalMapItem.clear();
}

void MapItemManager::Update()
{
	for (pair<string, MapItems> mapItems : totalMapItem)
	{
		for (MapItem* mapItem : mapItems.second)
			mapItem->Update();
	}
}

void MapItemManager::Render(HDC hdc)
{
	for (pair<string, MapItems> mapItems : totalMapItem)
	{
		for (MapItem* mapItem : mapItems.second)
			mapItem->Render(hdc);
	}
}

void MapItemManager::Play(string key, Vector2 pos)
{
	for (MapItem* mapItem : totalMapItem[key])
	{
		if (!mapItem->IsActive())
		{
			mapItem->Play(pos);
			return;
		}
	}
}

void MapItemManager::AllActive( bool isActive)
{
	for (pair<string, MapItems> mapItems : totalMapItem)
	{
		for (MapItem* mapItem : mapItems.second)
			mapItem->SetActive(isActive);
	}
}

void MapItemManager::Add(string key, int poolSize, Texture* texture, float speed, bool isLoop, int imageX, int imageY)
{
	if (totalMapItem.count(key) > 0)
		assert(false);

	MapItems mapItems(poolSize);

	for (MapItem*& mapItem : mapItems)
	{
		if(imageX != -1)
			mapItem = new MapItem(texture, speed, isLoop, imageX, imageY);
		else 
			mapItem = new MapItem(texture, speed, isLoop);
		mapItem->SetActive(false);
	}

	totalMapItem[key] = mapItems;
}

MapItem* MapItemManager::Collision(string key, Rect* rect)
{
	for (MapItem*& mapItem : totalMapItem[key])
	{
		if (mapItem->IsCollision(rect))
			return mapItem;
	}

	return nullptr;

}
