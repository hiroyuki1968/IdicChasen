#if !defined(HTML_H__INCLUDED_)
#define HTML_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CHtmlTokenizer

class CHtmlTokenizer
{
public:
	CHtmlTokenizer();
	CHtmlTokenizer(const CStringBuffer& strHtml, BOOL bPreTag = FALSE);

	void SetHtml(const CStringBuffer& strHtml, BOOL bPreTag = FALSE);
	void AddHtml(const CStringBuffer& strHtml);
	BOOL HtmlTok();
	BOOL HtmlReverseTok();
	BOOL IsTagCmd() const;
	CStringBuffer GetTagCmd() const;

	int TagAttrTok(CStringBuffer& strKey, CStringBuffer& strValue);
	int FindTagAttr(LPCTSTR lpszKey, CStringBuffer& strValue);
//	int ChangeTagAttr(LPCTSTR lpszKey, LPCTSTR lpszValue);
	void ChangeTagAttr(LPCTSTR lpszValue);
	void AddTagAttr(LPCTSTR lpszKey, LPCTSTR lpszValue);
	int DelTagAttr(LPCTSTR lpszKey);
	void DelTagAttr();

	CStringBuffer m_strHtml;
	int m_nHtmlPtr;

	CStringBuffer m_strTag;
	int m_nTagLen;

protected:
	void SetTagParm();

	int m_nHtmlLen;
	CStringBuffer m_strPreTag;

	CStringBuffer m_strKey;
	int m_nTagPtr;
	int m_nAttrPtr;
	int m_nAttrLen;
};

#endif // !defined(HTML_H__INCLUDED_)
