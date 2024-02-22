#include "Framework.h"

SceneManager::~SceneManager()
{	
	for (pair<string, Scene*> scene : scenes)
		delete scene.second;
}

void SceneManager::Update()
{
	if (curScene == nullptr) return;

	curScene->Update();

	if (KEY->Down(VK_F2))
		ChangeScene("Boss");
}

void SceneManager::Render(HDC hdc)
{
	if (curScene == nullptr) return;

	curScene->Render(hdc);
}

void SceneManager::Add(string key, Scene* scene)
{
	if (scenes.count(key) > 0)
	{
		assert(false);
	}

	//scenes.insert({ key, scene });
	//scenes.insert(make_pair(key, scene));
	//scenes.insert(pair<string, Scene*>(key, scene));
	scenes[key] = scene;
}

void SceneManager::ChangeScene(string key)
{
	if (scenes.count(key) == 0)
	{
		assert(false);
	}

	if (scenes[key] == curScene)
		return;

	if (curScene != nullptr)
		curScene->End();

	curScene = scenes[key];
	curScene->CreateIntroFrame();
}
