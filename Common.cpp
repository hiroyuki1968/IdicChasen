#include "stdafx.h"
#include "Common.h"

#include <afxinet.h>
#include <shfolder.h>

CStringBuffer StrFormat(LPCTSTR lpszFormat, ...)
{
	CStringBuffer str;

	va_list vl;
	va_start(vl, lpszFormat);
	str.FormatV(lpszFormat, vl);
	va_end(vl);

	return str;
}

BOOL IsStrQTrim(const CStringBuffer& str)
{
	_TCHAR chQ = str[0];
	return (chQ == _T('\'')  ||  chQ == _T('\"'))  &&  str[str.GetLength() - 1] == chQ;
}

CStringBuffer StrQTrim(const CStringBuffer& str)
{
	if (IsStrQTrim(str))
		return str.Mid(1, str.GetLength() - 2);

	return str;
}

CStringBuffer GetDPathFromFPath(LPCTSTR lpszFPath)
{
	CStringBuffer strFPath(lpszFPath);
	return strFPath.Left(strFPath.ReverseFind(_T('\\')));
}

CStringBuffer GetFNameFromFPath(LPCTSTR lpszFPath)
{
	CStringBuffer strFPath(lpszFPath);
	return strFPath.Mid(strFPath.ReverseFind(_T('\\')) + 1);
}

int ReStrFile(LPCTSTR lpszFPath, CStringBuffer& str)
{
	int nRv = 0;

	try {
		CStdioFile StdioFile(lpszFPath, CFile::modeRead);
		CString strLine;
		str.Empty();
		while (StdioFile.ReadString(strLine)) {
			str += strLine;
			str += _T('\n');
		}
		StdioFile.Close();
	}
	catch (CException* pEx) {
		AfxMessageBox((CStringBuffer)lpszFPath + _T(" ファイル読み込みエラー: ") + GetExceptionErrorMessage(pEx), MB_ICONSTOP);
		nRv = -1;
		pEx->Delete();
	}

	return nRv;
}

int WrStrFile(LPCTSTR lpszFPath, const CStringBuffer& str)
{
	int nRv = 0;

	CFileStatus FileStatus;
	for (int i = 0; i < 20000 / 250  &&  CFile::GetStatus(lpszFPath, FileStatus); i ++) {
		if (DeleteFile(lpszFPath))
			break;
		Sleep(250);
	}

	try {
		CStdioFile StdioFile(lpszFPath, CFile::modeCreate | CFile::modeWrite);
		StdioFile.WriteString(str);
		StdioFile.Close();
	}
	catch (CException* pEx) {
		AfxMessageBox((CStringBuffer)lpszFPath + _T(" ファイル書き出しエラー: ") + GetExceptionErrorMessage(pEx), MB_ICONSTOP);
		nRv = -1;
		pEx->Delete();
	}

	return nRv;
}

CStringBuffer GetLastErrorMessage(DWORD dwLastError)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwLastError ? dwLastError : GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	// Process any inserts in lpMsgBuf.
	CStringBuffer strMsg((LPCTSTR)lpMsgBuf);
	// Free the buffer.
	LocalFree( lpMsgBuf );

	return strMsg;
}

CStringBuffer GetExceptionErrorMessage(CException* pEx)
{
	TCHAR   szCause[255];

	pEx->GetErrorMessage(szCause, 255);
	return szCause;
}

int nPumpWaitingMessages = 0;

// 時間の掛かる処理をしている間に他のメッセージを処理する。
void PumpWaitingMessages()
{
	nPumpWaitingMessages ++;

	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (msg.message == WM_QUIT)
			break;
		::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		::TranslateMessage(&msg);
		::DispatchMessage (&msg);
	}

	nPumpWaitingMessages --;
}

CStringBuffer GetShFolderPath(int nFolder)
{
	CStringBuffer strRv;

	TCHAR szFolderPath[MAX_PATH];
	if(SUCCEEDED(SHGetFolderPath(NULL, nFolder, NULL, 0, szFolderPath)))
		strRv = szFolderPath;

	return strRv;
}

CStringBuffer IToA(int n)
{
	static _TCHAR psz[12];
	_itoa(n, psz, 10);

	return psz;
}

DWORD GetPrivateProfileStringEx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpDefault, CStringBuffer& strReturnedString, LPCTSTR lpFileName)
{
	strReturnedString = lpDefault;

	CFileStatus FileStatus;
	if (CFile::GetStatus(lpFileName, FileStatus))
		try {

			CString strLine;
			BOOL bApp = FALSE;
			CString strAppName((CString)_T('[') + lpAppName + _T(']'));
			CString strKeyName((CString)lpKeyName + _T('='));
			int nKeyName = strKeyName.GetLength();

			CStdioFile StdioFile(lpFileName, CFile::modeRead);
			while (StdioFile.ReadString(strLine)) {
				if (bApp) {
					if (strLine.Left(nKeyName) == strKeyName) {
						strReturnedString = strLine.Mid(nKeyName);
						break;
					} else if (strLine.GetLength()  &&  strLine[0] == _T('['))
						break;
				} else
					if (strLine == strAppName)
						bApp = TRUE;
			}
			StdioFile.Close();
		}
		catch (CException* pEx) {
			pEx->Delete();
		}

	return strReturnedString.GetLength();
}

BOOL WritePrivateProfileStringEx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString, LPCTSTR lpFileName)
{
	CFileStatus FileStatus;
	CStringBuffer strFile;
	if (CFile::GetStatus(lpFileName, FileStatus))
		if (ReStrFile(lpFileName, strFile))
			return FALSE;

	CStringBuffer strNewFile = strFile;
	SetPrivateProfileStringEx(lpAppName, lpKeyName, lpString, strNewFile);

	if (strNewFile != strFile)
		if (WrStrFile(lpFileName, strNewFile))
			return FALSE;

	return TRUE;
}

void SetPrivateProfileStringEx(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString, CStringBuffer& strFile)
{
	CStringBuffer strLine;
	BOOL bApp = FALSE;
	CStringBuffer strAppName((CStringBuffer)_T('[') + lpAppName + _T(']'));
	CStringBuffer strKeyName((CStringBuffer)lpKeyName + _T('='));
	int nKeyName = strKeyName.GetLength();
	int nFileLen = strFile.GetLength();
	int nIndex0 = 0;
	int nIndex1;
	int nIndex2 = 0;

	while (nIndex0 < nFileLen) {
		if ((nIndex1 = strFile.Find(_T('\n'), nIndex0)) == -1)
			nIndex1 = nFileLen;
		strLine = strFile.Mid(nIndex0, nIndex1 - nIndex0);

		if (bApp) {
			if (strLine.Left(nKeyName) == strKeyName) {
				nIndex2 = nIndex0 + nKeyName;
				break;
			} else if (strLine.GetLength()  &&  strLine[0] == _T('[')) {
				while (-- nIndex0  &&  strFile[nIndex0] == _T('\n'))
					;
				nIndex0 ++;
				break;
			}
		} else
			if (strLine == strAppName)
				bApp = TRUE;

		nIndex0 = nIndex1 + 1;
	}
	if (nIndex2)
		if (lpString)
			strFile.Update(nIndex2, nIndex1 - nIndex2, lpString);
		else
			strFile.Delete(nIndex0, nIndex1 - nIndex0 + (nIndex1 == nFileLen ? 0 : 1));
	else
		if (lpString) {
			if (! bApp) {
				if (strFile.GetLength())
					strFile += _T('\n');
				strFile += strAppName + _T('\n');
			}
			strFile += strKeyName + lpString + _T('\n');
		}
}

BOOL WritePrivateProfile(const CStringBuffer& strNewFile, LPCTSTR lpFileName)
{
	CFileStatus FileStatus;
	CStringBuffer strFile;
	if (CFile::GetStatus(lpFileName, FileStatus))
		if (ReStrFile(lpFileName, strFile))
			return FALSE;

	if (strNewFile != strFile)
		if (WrStrFile(lpFileName, strNewFile))
			return FALSE;

	return TRUE;
}

int StrFindOneOf(LPCTSTR lpszStr, LPCTSTR lpszCharSet, int nStart)
{
	_TCHAR* pch;
	if ((pch = _tcspbrk(lpszStr + nStart, lpszCharSet)) == NULL)
		return -1;

	return pch - lpszStr;
}

int StrFindNotOf(const CStringBuffer& str, LPCTSTR lpszCharSet, int nStart)
{
	int nStrPtr = nStart + _tcsspn((LPCTSTR)str + nStart, lpszCharSet);
	if (nStrPtr >= str.GetLength())
		return -1;

	return nStrPtr;
}

int StrReverseFindEx(const CStringBuffer& str, LPCTSTR lpszTarget, int nIndex, bool bNoCase) {
	int i;
	int j;
	CString strTarget(lpszTarget);
	int nTargetLen = strTarget.GetLength();
	BOOL bNotFound;
	BOOL bFound = FALSE;

	if (bNoCase)
		strTarget.MakeUpper();

	if (nIndex < 0)
		return -1;
	if (nIndex > str.GetLength() - nTargetLen)
		nIndex = str.GetLength() - nTargetLen;

	for (i = nIndex; i >= 0; i --) {
		bNotFound = FALSE;
		for (j = 0; j < nTargetLen; j ++)
			if (((bNoCase ? toupper(str[i + j]) : str[i + j])) != strTarget[j]) {
				bNotFound = TRUE;
				break;
			}
		if (! bNotFound) {
			bFound = TRUE;
			break;
		}
	}
	if (! bFound)
		return -1;

	return i;
}

CStringBuffer GetShellExecuteErrorText(HINSTANCE hInstance)
{
	CStringBuffer strText;

	switch ((int)hInstance) {
	case 0:
		strText = _T("メモリまたはリソースが不足しています。");
		break;
/*
	case ERROR_FILE_NOT_FOUND:
		strText = _T("指定されたファイルが見つかりませんでした。");
		break;
	case ERROR_PATH_NOT_FOUND:
		strText = _T("指定されたパスが見つかりませんでした。");
		break;
*/
	case ERROR_BAD_FORMAT:
		strText = _T(".exe ファイルが無効です。Win32 の .exe ではないか、.exe イメージ内にエラーがあります。");
		break;
	case SE_ERR_ACCESSDENIED:
		strText = _T("オペレーティングシステムが、指定されたファイルへのアクセスを拒否しました。");
		break;
	case SE_ERR_ASSOCINCOMPLETE:
		strText = _T("ファイル名の関連付けが不完全または無効です。");
		break;
	case SE_ERR_DDEBUSY:
		strText = _T("ほかの DDE トランザクションが現在処理中なので、DDE トランザクションを完了できませんでした。");
		break;
	case SE_ERR_DDEFAIL:
		strText = _T("DDE トランザクションが失敗しました。");
		break;
	case SE_ERR_DDETIMEOUT:
		strText = _T("要求がタイムアウトしたので、DDE トランザクションを完了できませんでした。");
		break;
	case SE_ERR_DLLNOTFOUND:
		strText = _T("指定されたダイナミックリンクライブラリ（DLL）が見つかりませんでした。");
		break;
	case SE_ERR_FNF:
		strText = _T("指定されたファイルが見つかりませんでした。");
		break;
	case SE_ERR_NOASSOC:
		strText = _T("指定されたファイル拡張子に関連付けられたアプリケーションがありません。印刷可能ではないファイルを印刷しようとした場合も、このエラーが返ります。");
		break;
	case SE_ERR_OOM:
		strText = _T("操作を完了するのに十分なメモリがありません。");
		break;
	case SE_ERR_PNF:
		strText = _T("指定されたパスが、見つかりませんでした。");
		break;
	case SE_ERR_SHARE:
		strText = _T("共有違反が発生しました。");
	}

	return strText;
}

CStringBuffer GetHttpStatusText(DWORD dwStatusCode)
{
	CStringBuffer strText;

	switch (dwStatusCode) {
	case HTTP_STATUS_CONTINUE:
		strText = _T("OK to continue with request");
		break;
	case HTTP_STATUS_SWITCH_PROTOCOLS:
		strText = _T("server has switched protocols in upgrade header");
		break;

	case HTTP_STATUS_CREATED:
		strText = _T("object created, reason = new URI");
		break;
	case HTTP_STATUS_ACCEPTED:
		strText = _T("async completion (TBS)");
		break;
	case HTTP_STATUS_PARTIAL:
		strText = _T("partial completion");
		break;
	case HTTP_STATUS_NO_CONTENT:
		strText = _T("no info to return");
		break;
	case HTTP_STATUS_RESET_CONTENT:
		strText = _T("request completed, but clear form");
		break;
	case HTTP_STATUS_PARTIAL_CONTENT:
		strText = _T("partial GET furfilled");
		break;

	case HTTP_STATUS_AMBIGUOUS:
		strText = _T("server couldn't decide what to return");
		break;
	case HTTP_STATUS_MOVED:
		strText = _T("object permanently moved");
		break;
	case HTTP_STATUS_REDIRECT:
		strText = _T("object temporarily moved");
		break;
	case HTTP_STATUS_REDIRECT_METHOD:
		strText = _T("redirection w/ new access method");
		break;
	case HTTP_STATUS_NOT_MODIFIED:
		strText = _T("if-modified-since was not modified");
		break;
	case HTTP_STATUS_USE_PROXY:
		strText = _T("redirection to proxy, location header specifies proxy to use");
		break;
	case HTTP_STATUS_REDIRECT_KEEP_VERB:
		strText = _T("HTTP/1.1: keep same verb");
		break;

	case HTTP_STATUS_BAD_REQUEST:
		strText = _T("不適切な要求です");
		break;
	case HTTP_STATUS_DENIED:
		strText = _T("access denied");
		break;
	case HTTP_STATUS_PAYMENT_REQ:
		strText = _T("payment required");
		break;
	case HTTP_STATUS_FORBIDDEN:
		strText = _T("request forbidden");
		break;
	case HTTP_STATUS_NOT_FOUND:
		strText = _T("要求された URL が見つかりません");
		break;
	case HTTP_STATUS_BAD_METHOD:
		strText = _T("サーバーは要求された方式をサポートしていません");
		break;
	case HTTP_STATUS_NONE_ACCEPTABLE:
		strText = _T("no response acceptable to client found");
		break;
	case HTTP_STATUS_PROXY_AUTH_REQ:
		strText = _T("proxy authentication required");
		break;
	case HTTP_STATUS_REQUEST_TIMEOUT:
		strText = _T("server timed out waiting for request");
		break;
	case HTTP_STATUS_CONFLICT:
		strText = _T("user should resubmit with more info");
		break;
	case HTTP_STATUS_GONE:
		strText = _T("the resource is no longer available");
		break;
	case HTTP_STATUS_LENGTH_REQUIRED:
		strText = _T("the server refused to accept request w/o a length");
		break;
	case HTTP_STATUS_PRECOND_FAILED:
		strText = _T("precondition given in request failed");
		break;
	case HTTP_STATUS_REQUEST_TOO_LARGE:
		strText = _T("request entity was too large");
		break;
	case HTTP_STATUS_URI_TOO_LONG:
		strText = _T("request URI too long");
		break;
	case HTTP_STATUS_UNSUPPORTED_MEDIA:
		strText = _T("unsupported media type");
		break;

	case HTTP_STATUS_SERVER_ERROR:
		strText = _T("原因不明のサーバー エラー");
		break;
	case HTTP_STATUS_NOT_SUPPORTED:
		strText = _T("required not supported");
		break;
	case HTTP_STATUS_BAD_GATEWAY:
		strText = _T("error response received from gateway");
		break;
	case HTTP_STATUS_SERVICE_UNAVAIL:
		strText = _T("サーバー容量の限界です");
		break;
	case HTTP_STATUS_GATEWAY_TIMEOUT:
		strText = _T("timed out waiting for gateway");
		break;
	case HTTP_STATUS_VERSION_NOT_SUP:
		strText = _T("HTTP version not supported");
	}

	return strText;
}

void PostWndText(CWnd* pWnd, LPCTSTR lpsz)
{
	int nLen = _tcslen(lpsz);
	UINT uCh;
	BOOL bMbBLead;
	BOOL bPreMbBLead = FALSE;
	UINT uScanCode;
	for (int i = 0; i < nLen; i ++) {
		uCh = (unsigned char)lpsz[i];
		if (bPreMbBLead)
			bMbBLead = FALSE;
		else
			bMbBLead = _ismbblead(uCh);
		if (bPreMbBLead || bMbBLead)
			uScanCode = 0;
		else
			uScanCode = MapVirtualKey(uCh, 0);
		pWnd->PostMessage(WM_CHAR, uCh, uScanCode << 16 | 0x0001);
		bPreMbBLead = bMbBLead;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStringTokenizer

CStringTokenizer::CStringTokenizer()
{
}

CStringTokenizer::CStringTokenizer(const CStringBuffer& str, LPCTSTR lpszSep)
{
	SetStrSep(str, lpszSep);
}

void CStringTokenizer::SetStrSep(const CStringBuffer& str, LPCTSTR lpszSep)
{
	m_strStr = str;
	m_nStrLen = m_strStr.GetLength();
	m_strSep = lpszSep;
	m_nStrPtr = 0;
}

BOOL CStringTokenizer::StrTok(LPCTSTR lpszSep)
{
	if (lpszSep)
		m_strSep = lpszSep;

	if (m_nStrPtr >= m_nStrLen)
		return FALSE;

	int nTmpPtr;
	int nStrLen = 0;

	do {
		if ((nTmpPtr = StrFindOneOf(m_strStr, m_strSep, m_nStrPtr)) == -1) {
			nStrLen = m_nStrLen - m_nStrPtr;
			break;
		}
		if (nTmpPtr != m_nStrPtr) {
			nStrLen = nTmpPtr - m_nStrPtr;
			break;
		}
		m_nStrPtr = nTmpPtr + 1;
	} while (m_nStrPtr < m_nStrLen);

	nTmpPtr = m_nStrPtr;

	m_nStrPtr += nStrLen + 1;

	m_strTok = m_strStr.Mid(nTmpPtr, nStrLen);

	return TRUE;
}
