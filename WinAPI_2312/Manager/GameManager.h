#pragma once

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update();
	void Render();

private:
	void Create();
	void Delete();

private:
	HDC hdc = nullptr;

	HDC backDC = nullptr;
	HBITMAP backBitmap = nullptr;
};