#pragma once

class Animation
{
private:
	const float FRAME_PER_SECOND = 10.0f;

public:
	Animation(POINT imageFrame, float speed = 1.0f);
	~Animation() = default;

	void Update();

	void SetDefault(bool loop = false, bool pingpong = false);
	void SetPart(int start, int end, bool loop = false, bool pingpong = false);
	void SetArray(int* arr, int size, bool loop = false, bool pingpong = false);

	void SetPingpong();

	void Play() { isPlay = true, curFrameNum = 0; }
	void Stop();

	void SetSpeed(float speed) { this->speed = speed; }
	void SetEndEvent(function<void()> event) { endEvent = event; }

	POINT GetFrame() { return frames[action[curFrameNum]]; }
	bool IsPlay() { return isPlay; }

private:
	vector<POINT> frames;
	vector<int> action;
		
	POINT imageFrame;
	int curFrameNum = 0;
	bool isPlay = true, isLoop = false;
	float playTime = 0.0f, intervalTime = 0.0f, speed;

	function<void()> endEvent = nullptr;
};