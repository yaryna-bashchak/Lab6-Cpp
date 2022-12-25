#include "framework.h"
#include "vector_params.h"
#include "resource1.h"

int n, min, max;
BOOL pn, pmin, pmax;
HWND hWndObject2, hWndObject3;
VectorParams* pVectorDialog;

static INT_PTR CALLBACK FUNC_VectorParams(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            n = GetDlgItemInt(hDlg, IDC_EDIT_N, &pn, FALSE);
            min = GetDlgItemInt(hDlg, IDC_EDIT_MIN, &pmin, FALSE);
            max = GetDlgItemInt(hDlg, IDC_EDIT_MAX, &pmax, FALSE);
            
            if (!pVectorDialog->CheckInputText(hDlg)) break;
            if (!pVectorDialog->CheckInputValues(hDlg)) break;

            pVectorDialog->FindWindows();
            
            EndDialog(hDlg, 1);
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void VectorParams::OnCreate(HWND hWnd, HINSTANCE hInst)
{
    pVectorDialog = this;
    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, FUNC_VectorParams);
}

void VectorParams::FindWindows()
{
    hWndObject2 = FindWindow(L"OBJECT2", NULL);
    if (!hWndObject2)
    {
        WinExec("Object2.exe", SW_SHOW);
        hWndObject2 = FindWindow(L"OBJECT2", NULL);
    }

    hWndObject3 = FindWindow(L"OBJECT3", NULL);
    if (!hWndObject3)
    {
        WinExec("Object3.exe", SW_SHOW);
        hWndObject3 = FindWindow(L"OBJECT3", NULL);
    }
}

BOOL VectorParams::CheckInputText(HWND hdlg)
{
    if (pn == 0 || pmin == 0 || pmax == 0)
    {
        MessageBox(hdlg, L"�� ����� �����, ���� �� ���� ���� ��������������� �� �����, ��� �������� ����� ������.", L"���, �������", MB_OK);
        return FALSE;
    }
    return TRUE;
}

BOOL VectorParams::CheckInputValues(HWND hdlg)
{
    if (n <= 0 || min <= 0 || max <= 0 || max <= min)
    {
        MessageBox(hdlg, L"�� �� ������� ���� ����� � ����������.\n\n������: ����� ����� �� ���� ���� ��'����� � max �� ���� ������, ��� min", L"���, �������", MB_OK);
        return FALSE;
    }
    return TRUE;
}