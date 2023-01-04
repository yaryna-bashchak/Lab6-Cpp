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
            n = GetDlgItemInt(hDlg, IDC_EDIT_N, &pn, TRUE);
            min = GetDlgItemInt(hDlg, IDC_EDIT_MIN, &pmin, TRUE);
            max = GetDlgItemInt(hDlg, IDC_EDIT_MAX, &pmax, TRUE);
            
            if (!CheckInputText(hDlg)) break;
            if (!CheckInputValues(hDlg)) break;

            FindMyWindow(2);
            
            int params[3] = { n, min, max };
            CopyData(hWndObject2, GetParent(hDlg), params, sizeof(params));

            FindMyWindow(3);
            PostMessage(hWndObject3, WM_CLIPBOARDUPDATE, NULL, NULL);
            
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

void VectorParams::FindMyWindow(int i)
{
    if (i == 2)
    {
        hWndObject2 = FindWindow(L"OBJECT2", NULL);
        if (!hWndObject2)
        {
            WinExec("Object2.exe", SW_SHOW);
            hWndObject2 = FindWindow(L"OBJECT2", NULL);
        }
    }
    else if (i == 3)
    {
        hWndObject3 = FindWindow(L"OBJECT3", NULL);
        if (!hWndObject3)
        {
            WinExec("Object3.exe", SW_SHOW);
            hWndObject3 = FindWindow(L"OBJECT3", NULL);
        }
    }
}

BOOL VectorParams::CheckInputText(HWND hdlg)
{
    if (pn == 0 || pmin == 0 || pmax == 0)
    {
        MessageBox(hdlg, L"Ви ввели текст, який не може бути інтерпретований як число, або залишили рядок пустим.", L"Упс, помилка", MB_OK);
        return FALSE;
    }
    return TRUE;
}

BOOL VectorParams::CheckInputValues(HWND hdlg)
{
    if (n <= 0 || min <= 0 || max <= 0 || max <= min)
    {
        MessageBox(hdlg, L"Не всі введені вами числа є коректними.\n\nВимоги: жодне число не може бути від'ємним і max має бути більшим, ніж min", L"Упс, помилка", MB_OK);
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
