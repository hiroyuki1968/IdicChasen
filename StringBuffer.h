#if !defined(STRINGBUFFER_H__INCLUDED_)
#define STRINGBUFFER_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRBUF_INITBUFLEN	16

class CStringBufferObject
{
public:
	CStringBufferObject(int nBufLen = STRBUF_INITBUFLEN);
	CStringBufferObject(CStringBufferObject &Sbo);
	CStringBufferObject(TCHAR ch, int nRepeat = 1);
	CStringBufferObject(LPCTSTR lpsz);
	CStringBufferObject(LPCTSTR lpsz, int nLength);
	~CStringBufferObject();
	void operator=(const CStringBufferObject &SboSrc);
	void operator=(LPCTSTR lpsz);
	void operator+=(const CStringBufferObject &SboSrc);
	void operator+=(TCHAR ch);
	void operator+=(LPCTSTR lpsz);
	int Replace(TCHAR chOld, TCHAR chNew);
	int Insert(int nIndex, LPCTSTR lpsz);
	int Delete(int nIndex, int nCount);
	int Update(int nIndex, int nCount, LPCTSTR lpsz);
	void FormatV(LPCTSTR lpszFormat, va_list vl);
	void TrimLeft(LPCTSTR lpszTargets);
	void TrimRight(LPCTSTR lpszTargets);
	void SetBufferLength(int nNewLength = STRBUF_INITBUFLEN);
	TCHAR* m_lpszBuf;
	int m_nLength;
	int m_nBufLen;
	int m_nRefCount;
};

class CStringBuffer
{
public:
	CStringBuffer(int nLength = STRBUF_INITBUFLEN);
	CStringBuffer(const CStringBuffer& SbSrc);
	CStringBuffer(TCHAR ch, int nRepeat = 1);
	CStringBuffer(LPCTSTR lpsz);
	CStringBuffer(LPCTSTR lpsz, int nLength);
	~CStringBuffer();
	int GetLength() const;
	BOOL IsEmpty() const;
	void Empty();
	TCHAR operator[](int nIndex) const;
	void SetAt(int nIndex, TCHAR ch);
	operator LPCTSTR() const;
	const CStringBuffer& operator=(const CStringBuffer& SbSrc);
	const CStringBuffer& operator=(LPCTSTR lpsz);
	friend CStringBuffer operator+(const CStringBuffer& Sb1, const CStringBuffer& Sb2);
	friend CStringBuffer operator+(const CStringBuffer& Sb1, TCHAR ch);
	friend CStringBuffer operator+(TCHAR ch, const CStringBuffer& Sb2);
	friend CStringBuffer operator+(const CStringBuffer& Sb1, TCHAR lpsz);
	friend CStringBuffer operator+(LPCTSTR lpsz, const CStringBuffer& Sb2);
	const CStringBuffer& operator+=(const CStringBuffer& SbSrc);
	const CStringBuffer& operator+=(TCHAR ch);
	const CStringBuffer& operator+=(LPCTSTR lpsz);
	friend BOOL operator==(const CStringBuffer& Sb1, const CStringBuffer& Sb2);
	friend BOOL operator==(const CStringBuffer& Sb1, LPCTSTR lpsz);
	friend BOOL operator==(LPCTSTR lpsz, const CStringBuffer &Sb2);
	friend BOOL operator!=(const CStringBuffer& Sb1, const CStringBuffer& Sb2);
	friend BOOL operator!=(const CStringBuffer& Sb1, LPCTSTR lpsz);
	friend BOOL operator!=(LPCTSTR lpsz, const CStringBuffer& Sb2);
	friend BOOL operator<(const CStringBuffer& Sb1, const CStringBuffer& Sb2);
	friend BOOL operator<(const CStringBuffer& Sb1, LPCTSTR lpsz);
	friend BOOL operator<(LPCTSTR lpsz, const CStringBuffer& Sb2);
	friend BOOL operator>(const CStringBuffer& Sb1, const CStringBuffer& Sb2);
	friend BOOL operator>(const CStringBuffer& Sb1, LPCTSTR lpsz);
	friend BOOL operator>(LPCTSTR lpsz, const CStringBuffer& Sb2);
	friend BOOL operator<=(const CStringBuffer& Sb1, const CStringBuffer& Sb2);
	friend BOOL operator<=(const CStringBuffer& Sb1, LPCTSTR lpsz);
	friend BOOL operator<=(LPCTSTR lpsz, const CStringBuffer& Sb2);
	friend BOOL operator>=(const CStringBuffer& Sb1, const CStringBuffer& Sb2);
	friend BOOL operator>=(const CStringBuffer& Sb1, LPCTSTR lpsz);
	friend BOOL operator>=(LPCTSTR lpsz, const CStringBuffer& Sb2);
	BOOL CompareNoCase(LPCTSTR lpsz) const;
	CStringBuffer Mid(int nFirst) const;
	CStringBuffer Mid(int nFirst, int nCount) const;
	CStringBuffer Left(int nCount) const;
	CStringBuffer Right(int nCount) const;
	void MakeUpper();
	void MakeLower();
	int Replace(TCHAR chOld, TCHAR chNew);
	int Replace(LPCTSTR lpszOld, LPCTSTR lpszNew);
	int Insert(int nIndex, LPCTSTR lpsz);
	int Delete(int nIndex, int nCount = 1);
	int Update(int nIndex, int nCount, LPCTSTR lpsz);
	void Format(LPCTSTR lpszFormat, ...);
	void FormatV(LPCTSTR lpszFormat, va_list argList);
	void TrimLeft(LPCTSTR lpszTargets = NULL);
	void TrimRight(LPCTSTR lpszTargets = NULL);
	int Find(TCHAR ch) const;
	int Find(LPCTSTR lpszSub) const;
	int Find(TCHAR ch, int nStart) const;
	int Find(LPCTSTR pstr, int nStart) const;
	int ReverseFind(TCHAR ch) const;
	int FindOneOf(LPCTSTR lpszCharSet) const;
	LPTSTR GetBuffer(int nMinBufLength = STRBUF_INITBUFLEN);
	LPTSTR GetBufferSetLength(int nNewLength = STRBUF_INITBUFLEN);
	void ReleaseBuffer(int nNewLength = -1);
	void SetBufferLength(int nNewLength = STRBUF_INITBUFLEN);

public:
	CStringBufferObject* m_pSbo;
};

#endif // !defined(STRINGBUFFER_H__INCLUDED_)
