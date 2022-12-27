#pragma once

class VectorParams
{
private:
	int n, min, max;
	BOOL pn, pmin, pmax;
	HWND hWndObject2, hWndObject3;
	BOOL CheckInputText(HWND hdlg);
	BOOL CheckInputValues(HWND hdlg);
	void FindWindows();
	void CopyData(HWND hWndDest, HWND hWndSrc, void* lp, long cb);
public:
	INT_PTR CALLBACK DlgWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void OnCreate(HWND hwnd, HINSTANCE hInst);
};