#if !defined(UXTHEME_H__INCLUDED_)
#define UXTHEME_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef	HTHEME
#define	HTHEME	HANDLE
#endif

void LoadUxThemeDll();
void FreeUxThemeDll();
BOOL IsThemeActive();
HTHEME OpenThemeData(HWND hwnd, LPCWSTR pszClassList);
HRESULT CloseThemeData(HTHEME hTheme);
HRESULT GetThemeBackgroundContentRect(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pBoundingRect, RECT *pContentRect);
HRESULT DrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT* pRect, const RECT* pClipRect);
HRESULT DrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex);

#endif // !defined(UXTHEME_H__INCLUDED_)
