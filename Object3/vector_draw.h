#pragma once
#include "framework.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class VectorDraw
{
private:
	int x1 = 100, y1 = 80, x2 = 600, y2 = 460, dArrow = 10, dx, dy;
	vector<double>::iterator min, max;
	HPEN hPen = CreatePen(PS_SOLID, 2, 0);
	char dataFromClipboard[1024];
	vector<double> myVector = {10, 3, 12};
public:
	void GetFromClipboard(HWND hWnd, long maxsize);
	void OnPaint(HDC hdc);
	void ParseClipboard();
	void DrawAxis(HDC hdc);
	void DrawNumbers(HDC hdc);
	void DrawVector(HDC hdc);
};