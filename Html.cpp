#include "stdafx.h"
#include "Html.h"

#include "Common.h"

/////////////////////////////////////////////////////////////////////////////
// CHtmlTokenizer

CHtmlTokenizer::CHtmlTokenizer()
{
}

CHtmlTokenizer::CHtmlTokenizer(const CStringBuffer& strHtml, BOOL bPreTag)
{
	SetHtml(strHtml, bPreTag);
}

void CHtmlTokenizer::SetHtml(const CStringBuffer& strHtml, BOOL bPreTag)
{
	if (bPreTag)
		m_strHtml = m_strPreTag;
	else
		m_strHtml.Empty();
	m_strPreTag.Empty();
	m_strHtml += strHtml;
	m_nHtmlLen = m_strHtml.GetLength();
	m_nHtmlPtr = 0;
}

void CHtmlTokenizer::AddHtml(const CStringBuffer& strHtml)
{
	m_strHtml += strHtml;
	m_nHtmlLen = m_strHtml.GetLength();
}

BOOL CHtmlTokenizer::HtmlTok()
{
	int nTmpPtr;
	int nStrLen;

	if (m_nHtmlPtr >= m_nHtmlLen)
		return FALSE;
	
	if (m_nHtmlPtr + 4 < m_nHtmlLen  &&  m_strHtml.Mid(m_nHtmlPtr, 4) == _T("<!--"))
		if (m_nHtmlPtr + 4 == m_nHtmlLen  ||  (nTmpPtr = m_strHtml.Find(_T("-->"), m_nHtmlPtr + 2)) == -1)
			nStrLen = m_nHtmlLen - m_nHtmlPtr;
		else
			nStrLen = nTmpPtr + 3 - m_nHtmlPtr;
	else if (m_nHtmlPtr + 1 < m_nHtmlLen  &&  m_strHtml[m_nHtmlPtr] == _T('<')) {
		if ((nTmpPtr = m_strHtml.Find(_T('>'), m_nHtmlPtr + 1)) == -1)
			nStrLen = m_nHtmlLen - m_nHtmlPtr;
		else
			nStrLen = nTmpPtr + 1 - m_nHtmlPtr;
	} else
		if ((nTmpPtr = m_strHtml.Find(_T('<'), m_nHtmlPtr)) == -1)
			nStrLen = m_nHtmlLen - m_nHtmlPtr;
		else
			nStrLen = nTmpPtr - m_nHtmlPtr;

	nTmpPtr = m_nHtmlPtr;

	m_nHtmlPtr += nStrLen;
	
	m_strTag = m_strHtml.Mid(nTmpPtr, nStrLen);
	if (m_nHtmlPtr >= m_nHtmlLen  &&  IsTagCmd()  &&  m_strTag.Right(1) != _T(">")) {
		m_strPreTag = m_strTag;
		m_strTag.Empty();
	}
	SetTagParm();

	return TRUE;
}

BOOL CHtmlTokenizer::HtmlReverseTok()
{
	int nTmpPtr;
	int nStrLen;

	if (m_nHtmlPtr <= 0)
		return FALSE;
	
	if (m_nHtmlPtr - 3 >= 0  &&  m_strHtml.Mid(m_nHtmlPtr - 3, 3) == _T("-->"))
		if (m_nHtmlPtr - 3 == 0  ||  (nTmpPtr = StrReverseFindEx(m_strHtml, _T("<!--"), m_nHtmlPtr - 1)) == -1)
			nStrLen = m_nHtmlPtr;
		else
			nStrLen = m_nHtmlPtr - nTmpPtr;
	else if (m_nHtmlPtr - 1 >= 0  &&  m_strHtml[m_nHtmlPtr - 1] == _T('>')) {
		if ((nTmpPtr = StrReverseFindEx(m_strHtml, _T("<"), m_nHtmlPtr - 1)) == -1)
			nStrLen = m_nHtmlPtr;
		else
			nStrLen = m_nHtmlPtr - nTmpPtr;
	} else
		if ((nTmpPtr = StrReverseFindEx(m_strHtml, _T(">"), m_nHtmlPtr)) == -1)
			nStrLen = m_nHtmlPtr;
		else
			nStrLen = m_nHtmlPtr - nTmpPtr - 1;

	m_nHtmlPtr -= nStrLen;
	
	m_strTag = m_strHtml.Mid(m_nHtmlPtr, nStrLen);
	SetTagParm();

	return TRUE;
}

void CHtmlTokenizer::SetTagParm()
{
	m_nTagLen = m_strTag.GetLength();
	m_nTagPtr = 0;
}

BOOL CHtmlTokenizer::IsTagCmd() const
{
	return m_strTag[0] == _T('<');
}

CStringBuffer CHtmlTokenizer::GetTagCmd() const
{
	CStringTokenizer StringTokenizer(m_strTag, _T("\n <>"));
	StringTokenizer.StrTok();

	return StringTokenizer.m_strTok;
}

int CHtmlTokenizer::TagAttrTok(CStringBuffer& strKey, CStringBuffer& strValue)
{
	if (m_nTagPtr >= m_nTagLen)
		return -1;
	
	int nTmpPtr;
	if (m_nTagPtr == 0) {
		if ((nTmpPtr = m_strTag.FindOneOf(_T(" =\'\">"))) == -1) {
			m_nTagPtr = -1;
			return -1;
		}
		switch (m_strTag[nTmpPtr]) {
		case _T(' '):
			break;
		case _T('>'):
			m_nTagPtr = -1;
			return 0;
		default:
			m_nTagPtr = -1;
			return -1;
		}
	} else
		nTmpPtr = m_nTagPtr;

	int nStr0Ptr = StrFindNotOf(m_strTag, _T(" "), nTmpPtr);
	switch (m_strTag[nStr0Ptr]) {
	case _T('='):
	case _T('\''):
	case _T('\"'):
		m_nTagPtr = -1;
		return -1;
	case _T('>'):
		m_nTagPtr = -1;
		return 0;
	}
	if ((nTmpPtr = StrFindOneOf(m_strTag, _T(" =\'\">"), nStr0Ptr)) == -1) {
		m_nTagPtr = -1;
		return -1;
	}
	switch (m_strTag[nTmpPtr]) {
	case _T('\''):
	case _T('\"'):
		m_nTagPtr = -1;
		return -1;
	}
	int nStr0Len = nTmpPtr - nStr0Ptr;
	
	int nStr1Ptr = StrFindNotOf(m_strTag, _T(" "), nTmpPtr);
	switch (m_strTag[nStr1Ptr]) {
	case _T('\''):
	case _T('\"'):
		m_nTagPtr = -1;
		return -1;
	}
	int nStr1Len = 0;
	int nRv;
	if (m_strTag[nStr1Ptr] == _T('=')) {
		if (nStr1Ptr + 1 >= m_nTagLen) {
			m_nTagPtr = -1;
			return -1;
		}

		nStr1Ptr = StrFindNotOf(m_strTag, _T(" "), nStr1Ptr + 1);
		TCHAR chSep;
		switch (chSep = m_strTag[nStr1Ptr]) {
		case _T('='):
			m_nTagPtr = -1;
			return -1;
		case _T('\''):
		case _T('\"'):
			if (nStr1Ptr + 1 >= m_nTagLen) {
				m_nTagPtr = -1;
				return -1;
			}
			if ((nTmpPtr = m_strTag.Find(chSep, nStr1Ptr + 1)) == -1) {
				m_nTagPtr = -1;
				return -1;
			}
			nTmpPtr ++;
			break;
		case _T('>'):
			nTmpPtr = nStr1Len;
			break;
		default:
			if ((nTmpPtr = StrFindOneOf(m_strTag, _T(" \'\">"), nStr1Ptr)) == -1) {
				m_nTagPtr = -1;
				return -1;
			}
			switch (m_strTag[nTmpPtr]) {
			case _T(' '):
			case _T('>'):
				break;
			default:
				m_nTagPtr = -1;
				return -1;
			}
		}
		nStr1Len = nTmpPtr - nStr1Ptr;

		nRv = 2;
	} else
		nRv = 1;

	strKey = m_strKey = m_strTag.Mid(nStr0Ptr, nStr0Len);
	strValue = m_strTag.Mid(nStr1Ptr, nStr1Len);

	m_nAttrPtr = nStr0Ptr;
	m_nAttrLen = nStr1Ptr + nStr1Len - nStr0Ptr;

	m_nTagPtr = nTmpPtr;
	
	return nRv;
}

int CHtmlTokenizer::FindTagAttr(LPCTSTR lpszKey, CStringBuffer& strValue)
{
	CStringBuffer strKey;
	CStringBuffer strTmpValue;
	int nRv;

	m_nTagPtr = 0;
	while (1) {
		if ((nRv = TagAttrTok(strKey, strTmpValue)) <= 0)
			return -1;
		if (strKey.CompareNoCase(lpszKey) == 0) {
			strValue = strTmpValue;
			break;
		}
	}

	return nRv;
}

/*
int CHtmlTokenizer::ChangeTagAttr(LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	CStringBuffer strTmpValue;

	if (FindTagAttr(lpszKey, strTmpValue) <= 0)
		return -1;
	ChangeTagAttr(lpszValue);

	return 0;
}
*/

void CHtmlTokenizer::ChangeTagAttr(LPCTSTR lpszValue)
{
	CStringBuffer strAttr(m_strKey);
	if (lpszValue)
		strAttr += (CStringBuffer)_T('=') + lpszValue;
	m_strTag.Update(m_nAttrPtr, m_nAttrLen, strAttr);
	SetTagParm();
}

void CHtmlTokenizer::AddTagAttr(LPCTSTR lpszKey, LPCTSTR lpszValue)
{
	m_strTag.Insert(m_nTagLen - 1, (CStringBuffer)_T(' ') + lpszKey + _T('=') + lpszValue);
	SetTagParm();
}

int CHtmlTokenizer::DelTagAttr(LPCTSTR lpszKey)
{
	CStringBuffer strTag;
	CStringBuffer strKey;
	CStringBuffer strTmpValue;
	int nRv;

	strTag = _T('<') + GetTagCmd();
	m_nTagPtr = 0;
	while (1) {
		if ((nRv = TagAttrTok(strKey, strTmpValue)) < 0)
			return -1;
		if (nRv == 0)
			break;
		if (strKey.CompareNoCase(lpszKey))
			if (nRv == 1)
				strTag += _T(' ') + strKey;
			else
				strTag += _T(' ') + strKey + _T('=') + strTmpValue;
	}
	strTag += _T(">");
	m_strTag = strTag;
	SetTagParm();

	return 0;
}

void CHtmlTokenizer::DelTagAttr()
{
	m_strTag.Delete(m_nAttrPtr - 1, m_nAttrLen + 1);
	SetTagParm();
}
