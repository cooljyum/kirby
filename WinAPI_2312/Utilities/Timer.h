#pragma once

class Timer : public Singleton<Timer>
{
private:
	friend class Singleton;

	const float EPSILON = 0.01f;

private:
	Timer();
	~Timer();

public:
	void Update();
	void Render(HDC hdc);

	float GetElapsedTime() { return elpasedTime > EPSILON ? EPSILON : elpasedTime; }

private:
	float timeScale = 0.0f;
	float elpasedTime = 0.0f;
	float oneSecCount = 0.0f;
	float deltaScale = 1.0f;

	__int64 curTime = 0;
	__int64 lastTime = 0;
	__int64 periodFrequency = 0;

	int frameRate = 0;
	int frameCount = 0;
};