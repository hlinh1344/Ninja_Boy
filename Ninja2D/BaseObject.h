#pragma once
#include <windows.h>
#include <WindowsX.h>
#include <math.h>

class BaseObject
{
protected:
	int posX;
	int posY;
	int formX;
	int formY;
	bool isDead;
	HBITMAP hBitmap, hbmMask;
	HINSTANCE hInst;
	//HDC hdcMem;
	HGDIOBJ oldBitmap;
	BITMAP bitmap;

public:

	BaseObject();
	~BaseObject();

	virtual int GetPosX();
	virtual int GetPosY();
	void SetPosX(int a_posX);
	void SetPosY(int a_posY);
	void IncresePosX(int a);
	void IncresePosY(int a);
	virtual void Draw(HWND hwnd, HDC hdc, HDC hdcMem);
	HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent);
	virtual int GetWidth();
	virtual int GetHeight();
	virtual void SetDeath(bool a_isDead);

	static int mapSlider;
	static int clousDrifting;
};

