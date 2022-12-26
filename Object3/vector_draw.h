#pragma once
#include "framework.h"
#include <vector>
#include <string>

using namespace std;

class VectorDraw
{
private:
	char dataFromClipboard[1024];
	vector<double> myVector;
public:
	long GetFromClipboard(HWND hWnd, long maxsize);
	void ParseClipboard();
};