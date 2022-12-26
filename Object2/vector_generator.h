#pragma once
#include "framework.h"
#include <vector>
#include <string>

using namespace std;

class VectorGenerator
{
private:
	int n, min, max;
	vector<double> myVector = {12, 15, 17};
public:
	void OnCopyData(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void Generate();
	void ShowVector(HWND hWnd, HDC hdc);
};