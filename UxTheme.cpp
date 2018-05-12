#include "stdafx.h"
#include "UxTheme.h"

HMODULE hUxThemeDll;

void LoadUxThemeDll()
{
	hUxThemeDll = LoadLibrary(_T("UxTheme.dll"));
}

void FreeUxThemeDll()
{
	if (hUxThemeDll)
		FreeLibrary(hUxThemeDll);
	hUxThemeDll = NULL;
}

BOOL IsThemeActive()
{
	BOOL bRet = FALSE;
	if (hUxThemeDll)
		bRet = ((BOOL(__stdcall *)())*GetProcAddress(hUxThemeDll, _T("IsThemeActive")))();
	return bRet;
}

HTHEME OpenThemeData(HWND hwnd, LPCWSTR pszClassList)
{
	return ((HTHEME(__stdcall *)(HWND, LPCWSTR))*GetProcAddress(hUxThemeDll, _T("OpenThemeData")))(hwnd, pszClassList);
}

HRESULT CloseThemeData(HTHEME hTheme)
{
	return ((HRESULT(__stdcall *)(HTHEME))*GetProcAddress(hUxThemeDll, _T("CloseThemeData")))(hTheme);
}

HRESULT GetThemeBackgroundContentRect(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pBoundingRect, RECT *pContentRect)
{
	return ((HRESULT(__stdcall *)(HTHEME, HDC, int, int, const RECT *, RECT *))*GetProcAddress(hUxThemeDll, _T("GetThemeBackgroundContentRect")))(hTheme, hdc, iPartId, iStateId, pBoundingRect, pContentRect);
}

HRESULT DrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT* pRect, const RECT* pClipRect)
{
	return ((HRESULT(__stdcall *)(HTHEME, HDC, int, int, const RECT*, const RECT*))*GetProcAddress(hUxThemeDll, _T("DrawThemeBackground")))(hTheme, hdc, iPartId, iStateId, pRect, pClipRect);
}

HRESULT DrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex)
{
	return ((HRESULT(__stdcall *)(HTHEME, HDC, int, int, const RECT *, HIMAGELIST, int))*GetProcAddress(hUxThemeDll, _T("DrawThemeIcon")))(hTheme, hdc, iPartId, iStateId, pRect, himl, iImageIndex);
}
