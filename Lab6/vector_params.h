#pragma once

class VectorParams
{
private:
public:
	void OnCreate(HWND hWnd, HINSTANCE hInst);
	BOOL CheckInputText(HWND hdlg);
	BOOL CheckInputValues(HWND hdlg);
	void FindWindows();
};