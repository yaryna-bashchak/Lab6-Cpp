#pragma once
#include "framework.h"
#include <vector>
#include <string>

using namespace std;

class VectorGenerator
{
private:
	int n, min, max;
	vector<double> myVector;
	void Generate();
	char* ConvertVectorToChars();
	int PutToClipboard(HWND hWnd, char *src);
public:
	void OnCopyData(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void ShowVector(HWND hWnd, HDC hdc);
};