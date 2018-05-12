#if !defined(COMMON_H__INCLUDED_)
#define COMMON_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "StringBuffer.h"

CStringBuffer StrFormat(LPCTSTR lpszFormat, ...);
BOOL IsStrQTrim(const CStringBuffer& str);
CStringBuffer StrQTrim(const CStringBuffer& strStr);
CStringBuffer GetDPathFromFPath(LPCTSTR lpszFPath);
CStringBuffer GetFNameFromFPath(LPCTSTR lpszFPath);
int ReStrFile(LPCTSTR lpszFPath, CStringBuffer& str);
int WrStrFile(LPCTSTR lpszFPath, const CStringBuffer& strStr);
CStringBuffer GetLastErrorMessage(DWORD dwLastError = NULL);
CStringBuffer GetExceptionErrorMessage(CException* pEx);

extern int nPumpWaitingMessages;

void PumpWaitingMessages();

CStringBuffer GetShFolderPath(int nFolder);

CStringBuffer IToA(int n);
DWORD GetPrivateProfileStringEx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, CStringBuffer& strReturnedString, LPCTSTR lpFileName);
BOOL WritePrivateProfileStringEx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString, LPCTSTR lpFileName);
void SetPrivateProfileStringEx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString, CStringBuffer& strFile);
BOOL WritePrivateProfile(const CStringBuffer& strNewFile, LPCTSTR lpFileName);
int StrFindOneOf(LPCTSTR lpszStr, LPCTSTR lpszCharSet, int nStart);
int StrFindNotOf(const CStringBuffer& strStr, LPCTSTR lpszCharSet, int nStart = 0);
int StrReverseFindEx(const CStringBuffer& strStr, LPCTSTR lpszTarget, int nIndex, bool bNoCase = false);
CStringBuffer GetShellExecuteErrorText(HINSTANCE hInstance);
CStringBuffer GetHttpStatusText(DWORD dwStatusCode);

void PostWndText(CWnd* pWnd, LPCTSTR lpsz);

/////////////////////////////////////////////////////////////////////////////
// CStringTokenizer

class CStringTokenizer
{
public:
	CStringTokenizer();
	CStringTokenizer(const CStringBuffer& strStr, LPCTSTR lpszSep);

	void SetStrSep(const CStringBuffer& strStr, LPCTSTR lpszSep);
	BOOL StrTok(LPCTSTR lpszSep = NULL);

	CStringBuffer m_strTok;

protected:
	CStringBuffer m_strStr;
	int m_nStrLen;
	CStringBuffer m_strSep;
	int m_nStrPtr;
};

#endif // !defined(COMMON_H__INCLUDED_)
