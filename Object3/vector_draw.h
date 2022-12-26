#pragma once
#include "framework.h"
#include <vector>
#include <string>

using namespace std;

class VectorDraw
{
private:
	int x1 = 100, y1 = 80, x2 = 600, y2 = 460, dArrow = 10;
	HPEN hPen = CreatePen(PS_SOLID, 3, 0);
	char dataFromClipboard[1024];
	vector<double> myVector;
public:
	long GetFromClipboard(HWND hWnd, long maxsize);
	void ParseClipboard();
	void OnPaint(HDC hdc);
	void DrawAxis(HDC hdc);
	void DrawVector(HDC hdc);
};