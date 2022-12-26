#include "framework.h"
#include "vector_params.h"
#include "resource1.h"
#include <stdio.h>

VectorParams* pVectorDialog;

static INT_PTR CALLBACK FUNC_VectorParams(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (pVectorDialog) return pVectorDialog->DlgWndProc(hDlg, message, wParam, lParam);
    return (INT_PTR)FALSE;
}

INT_PTR VectorParams::DlgWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
            
            if (!CheckInputText(hDlg)) break;
            if (!CheckInputValues(hDlg)) break;

            FindWindows();
            
            int params[3] = { n, min, max };
            CopyData(hWndObject2, GetParent(hDlg), params, sizeof(params));
            //PostMessage(hWndObject2, WM_COMMAND, 10000, (LPARAM)hWnd);

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

void VectorParams::OnCreate(HWND hwnd, HINSTANCE hInst)
{
    pVectorDialog = this;
    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, FUNC_VectorParams);
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
        MessageBox(hdlg, L"�� �� ������ ���� ����� � ����������.\n\n������: ����� ����� �� ���� ���� ��'����� � max �� ���� ������, �� min", L"���, �������", MB_OK);
        return FALSE;
    }
    return TRUE;
}

void VectorParams::CopyData(HWND hWndDest, HWND hWndSrc, void* lp, long cb)
{
    COPYDATASTRUCT cds;

    cds.dwData = 1;
    cds.cbData = cb;
    cds.lpData = lp;

    SendMessage(hWndDest, WM_COPYDATA, (WPARAM)hWndSrc, (LPARAM)&cds);
}
