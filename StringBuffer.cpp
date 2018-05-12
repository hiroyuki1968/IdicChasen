#include "stdafx.h"
#include "StringBuffer.h"

/////////////////////////////////////////////////////////////////////////////
// CStringBufferObject

CStringBufferObject::CStringBufferObject(int nBufLen)
{
	m_nRefCount = 1;
	m_nLength = 0;
	m_nBufLen = nBufLen;
	if ((m_lpszBuf = (TCHAR *)malloc(sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
		AfxThrowMemoryException();
	m_lpszBuf[0] = _T('\0');
}

CStringBufferObject::CStringBufferObject(CStringBufferObject& Sbo)
{
	m_nRefCount = 1;
	m_nLength = Sbo.m_nLength;
	m_nBufLen = Sbo.m_nBufLen;
	if ((m_lpszBuf = (TCHAR *)malloc(sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
		AfxThrowMemoryException();
	memcpy(m_lpszBuf, Sbo.m_lpszBuf, sizeof(TCHAR) * (m_nLength + 1));
}

CStringBufferObject::CStringBufferObject(TCHAR ch, int nRepeat)
{
	m_nRefCount = 1;
	m_nLength = nRepeat;
	m_nBufLen = STRBUF_INITBUFLEN * (m_nLength / STRBUF_INITBUFLEN + 1);
	if ((m_lpszBuf = (TCHAR *)malloc(sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
		AfxThrowMemoryException();
	for (int i = 0; i < nRepeat; i ++)
		m_lpszBuf[i] = ch;
	m_lpszBuf[nRepeat] = _T('\0');
}

CStringBufferObject::CStringBufferObject(LPCTSTR lpsz)
{
	m_nRefCount = 1;
	m_nLength = _tcslen(lpsz);
	m_nBufLen = STRBUF_INITBUFLEN * (m_nLength / STRBUF_INITBUFLEN + 1);
	if ((m_lpszBuf = (TCHAR *)malloc(sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
		AfxThrowMemoryException();
	memcpy(m_lpszBuf, lpsz, sizeof(TCHAR) * (m_nLength + 1));
}

CStringBufferObject::CStringBufferObject(LPCTSTR lpsz, int nLength)
{
	m_nRefCount = 1;
	m_nLength = nLength;
	m_nBufLen = STRBUF_INITBUFLEN * (m_nLength / STRBUF_INITBUFLEN + 1);
	if ((m_lpszBuf = (TCHAR *)malloc(sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
		AfxThrowMemoryException();
	memcpy(m_lpszBuf, lpsz, sizeof(TCHAR) * nLength);
	m_lpszBuf[nLength] = _T('\0');
}

CStringBufferObject::~CStringBufferObject()
{
	free(m_lpszBuf);
}

void CStringBufferObject::operator=(const CStringBufferObject& SboSrc)
{
	int nDstLen = SboSrc.m_nLength;
	memcpy(m_lpszBuf, SboSrc.m_lpszBuf, sizeof(TCHAR) * (nDstLen + 1));
	m_nLength = nDstLen;
}

void CStringBufferObject::operator=(LPCTSTR lpsz)
{
	int nDstLen = _tcslen(lpsz);
	if (nDstLen > m_nBufLen) {
		if (m_nBufLen == 0)
			m_nBufLen = STRBUF_INITBUFLEN;
		m_nBufLen *= (nDstLen / m_nBufLen + 1);
		if ((m_lpszBuf = (TCHAR *)realloc(m_lpszBuf, sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
			AfxThrowMemoryException();
	}
	memcpy(m_lpszBuf, lpsz, sizeof(TCHAR) * (nDstLen + 1));
	m_nLength = nDstLen;
}

void CStringBufferObject::operator+=(const CStringBufferObject& SboSrc)
{
	int nSrcLen = SboSrc.m_nLength;
	int nDstLen = m_nLength + nSrcLen;
	if (nDstLen > m_nBufLen) {
		if (m_nBufLen == 0)
			m_nBufLen = STRBUF_INITBUFLEN;
		m_nBufLen *= (nDstLen / m_nBufLen + 1);
		if ((m_lpszBuf = (TCHAR *)realloc(m_lpszBuf, sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
			AfxThrowMemoryException();
	}
	memcpy(m_lpszBuf + m_nLength, SboSrc.m_lpszBuf, sizeof(TCHAR) * (nSrcLen + 1));
	m_nLength = nDstLen;
}

void CStringBufferObject::operator+=(TCHAR ch)
{
	int nDstLen = m_nLength + 1;
	if (nDstLen > m_nBufLen) {
		if (m_nBufLen == 0)
			m_nBufLen = STRBUF_INITBUFLEN;
		m_nBufLen *= (nDstLen / m_nBufLen + 1);
		if ((m_lpszBuf = (TCHAR *)realloc(m_lpszBuf, sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
			AfxThrowMemoryException();
	}
	m_lpszBuf[m_nLength] = ch;
	m_lpszBuf[m_nLength + 1] = _T('\0');
	m_nLength = nDstLen;
}

void CStringBufferObject::operator+=(LPCTSTR lpsz)
{
	int nSrcLen =  _tcslen(lpsz);
	int nDstLen = m_nLength + nSrcLen;
	if (nDstLen > m_nBufLen) {
		if (m_nBufLen == 0)
			m_nBufLen = STRBUF_INITBUFLEN;
		m_nBufLen *= (nDstLen / m_nBufLen + 1);
		if ((m_lpszBuf = (TCHAR *)realloc(m_lpszBuf, sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
			AfxThrowMemoryException();
	}
	memcpy(m_lpszBuf + m_nLength, lpsz, sizeof(TCHAR) * (nSrcLen + 1));
	m_nLength = nDstLen;
}

int CStringBufferObject::Replace(TCHAR chOld, TCHAR chNew)
{
	TCHAR* pch = m_lpszBuf;
	int nCount = 0;
	while ((pch = _tcschr(pch, chOld)) != NULL) {
		*(pch ++) = chNew;
		nCount ++;
	}

	return nCount;
}

int CStringBufferObject::Insert(int nIndex, LPCTSTR lpsz)
{
	int nSrcLen = _tcslen(lpsz);
	int nDstLen = m_nLength + nSrcLen;
	if (nDstLen > m_nBufLen) {
		if (m_nBufLen == 0)
			m_nBufLen = STRBUF_INITBUFLEN;
		m_nBufLen *= (nDstLen / m_nBufLen + 1);
		if ((m_lpszBuf = (TCHAR *)realloc(m_lpszBuf, sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
			AfxThrowMemoryException();
	}
	memmove(m_lpszBuf + nIndex + nSrcLen, m_lpszBuf + nIndex, sizeof(TCHAR) * (m_nLength - nIndex + 1));
	memcpy(m_lpszBuf + nIndex, lpsz, sizeof(TCHAR) * nSrcLen);
	m_nLength = nDstLen;

	return m_nLength;
}

int CStringBufferObject::Delete(int nIndex, int nCount)
{
	int nMoveIdx = nIndex + nCount;
	if (nMoveIdx > m_nLength)
		nMoveIdx = m_nLength;
	int nMoveLen = m_nLength - nMoveIdx;
	memmove(m_lpszBuf + nIndex, m_lpszBuf + nMoveIdx, sizeof(TCHAR) * (nMoveLen + 1));
	m_nLength = nIndex + nMoveLen;

	return m_nLength;
}

int CStringBufferObject::Update(int nIndex, int nCount, LPCTSTR lpsz)
{
	int nSrcLen = _tcslen(lpsz);
	int nDstLen = m_nLength - nCount + nSrcLen;
	if (nDstLen > m_nBufLen) {
		if (m_nBufLen == 0)
			m_nBufLen = STRBUF_INITBUFLEN;
		m_nBufLen *= (nDstLen / m_nBufLen + 1);
		if ((m_lpszBuf = (TCHAR *)realloc(m_lpszBuf, sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
			AfxThrowMemoryException();
	}
	int nMoveIdx = nIndex + nCount;
	memmove(m_lpszBuf + nIndex + nSrcLen, m_lpszBuf + nMoveIdx, sizeof(TCHAR) * (m_nLength - nMoveIdx + 1));
	memcpy(m_lpszBuf + nIndex, lpsz, sizeof(TCHAR) * nSrcLen);
	m_nLength = nDstLen;

	return m_nLength;
}

void CStringBufferObject::FormatV(LPCTSTR lpszFormat, va_list vl)
{
	int nDstLen;
	while ((nDstLen = _vsntprintf(m_lpszBuf, m_nBufLen, lpszFormat, vl)) == -1) {
		if (m_nBufLen == 0)
			m_nBufLen = STRBUF_INITBUFLEN;
		m_nBufLen *= 2;
		if ((m_lpszBuf = (TCHAR *)realloc(m_lpszBuf, sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
			AfxThrowMemoryException();
	}
	m_lpszBuf[m_nBufLen] = _T('\0');
	m_nLength = nDstLen;
}

void CStringBufferObject::TrimLeft(LPCTSTR lpszTargets)
{
	static const TCHAR pszDefaultTargets[] = _T("\r\n \t");
	if (lpszTargets == NULL)
		lpszTargets = pszDefaultTargets;
	int nTargetsIdx;
	int nTargetsLen = _tcslen(lpszTargets);
	BOOL bNotTargets;
	int nIdx;
	TCHAR ch;
	for (nIdx = 0; nIdx < m_nLength; nIdx ++) {
		ch = m_lpszBuf[nIdx];
		bNotTargets = TRUE;
		for (nTargetsIdx = 0; nTargetsIdx < nTargetsLen; nTargetsIdx ++)
			if (ch == lpszTargets[nTargetsIdx]) {
				bNotTargets = FALSE;
				break;
			}
		if (bNotTargets)
			break;
	}
	m_nLength -= nIdx;
	memmove(m_lpszBuf, m_lpszBuf + nIdx, sizeof(TCHAR) * (m_nLength + 1));

	return;
}

void CStringBufferObject::TrimRight(LPCTSTR lpszTargets)
{
	static const TCHAR pszDefaultTargets[] = _T("\r\n \t");
	if (lpszTargets == NULL)
		lpszTargets = pszDefaultTargets;
	int nTargetsIdx;
	int nTargetsLen = _tcslen(lpszTargets);
	BOOL bNotTargets;
	int nIdx;
	TCHAR ch;
	for (nIdx = m_nLength - 1; nIdx >= 0; nIdx --) {
		ch = m_lpszBuf[nIdx];
		bNotTargets = TRUE;
		for (nTargetsIdx = 0; nTargetsIdx < nTargetsLen; nTargetsIdx ++)
			if (ch == lpszTargets[nTargetsIdx]) {
				bNotTargets = FALSE;
				break;
			}
		if (bNotTargets)
			break;
	}
	m_nLength = nIdx + 1;
	m_lpszBuf[m_nLength] = _T('\0');

	return;
}

void CStringBufferObject::SetBufferLength(int nNewLength)
{
	if (nNewLength < m_nLength)
		m_nLength = nNewLength;
	m_nBufLen = nNewLength;
	if ((m_lpszBuf = (TCHAR *)realloc(m_lpszBuf, sizeof(TCHAR) * (m_nBufLen + 1))) == 0)
		AfxThrowMemoryException();
	m_lpszBuf[m_nLength] = _T('\0');
}

/////////////////////////////////////////////////////////////////////////////
// CStringBuffer

CStringBuffer::CStringBuffer(int nLength)
{
	m_pSbo = new CStringBufferObject(nLength);
}

CStringBuffer::CStringBuffer(const CStringBuffer& SbSrc)
{
	m_pSbo = SbSrc.m_pSbo;
	m_pSbo->m_nRefCount ++;
}

CStringBuffer::CStringBuffer(TCHAR ch, int nRepeat)
{
	m_pSbo = new CStringBufferObject(ch, nRepeat);
}

CStringBuffer::CStringBuffer(LPCTSTR lpsz)
{
	m_pSbo = new CStringBufferObject(lpsz);
}

CStringBuffer::CStringBuffer(LPCTSTR lpsz, int nLength)
{
	m_pSbo = new CStringBufferObject(lpsz, nLength);
}

CStringBuffer::~CStringBuffer()
{
	if (-- m_pSbo->m_nRefCount == 0)
		delete m_pSbo;
}

int CStringBuffer::GetLength() const
{
	return m_pSbo->m_nLength;
}

BOOL CStringBuffer::IsEmpty() const
{
	return 	m_pSbo->m_lpszBuf[0] == _T('\0');
}

void CStringBuffer::Empty()
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(m_pSbo->m_nBufLen);
	} else {
		m_pSbo->m_lpszBuf[0] = _T('\0');
		m_pSbo->m_nLength = 0;
	}
}

TCHAR CStringBuffer::operator[](int nIndex) const
{
	return m_pSbo->m_lpszBuf[nIndex];
}

void CStringBuffer::SetAt(int nIndex, TCHAR ch)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	m_pSbo->m_lpszBuf[nIndex] = ch;
}

CStringBuffer::operator LPCTSTR() const
{
	return m_pSbo->m_lpszBuf;
}

const CStringBuffer& CStringBuffer::operator=(const CStringBuffer& SbSrc)
{
	if (m_pSbo->m_nBufLen >= SbSrc.m_pSbo->m_nLength) {
		if (m_pSbo->m_nRefCount > 1) {
			m_pSbo->m_nRefCount --;
			m_pSbo = new CStringBufferObject(m_pSbo->m_nBufLen);
		}
		*m_pSbo = *SbSrc.m_pSbo;
	} else {
		if (m_pSbo->m_nRefCount > 1)
			m_pSbo->m_nRefCount --;
		else
			delete m_pSbo;
		m_pSbo = SbSrc.m_pSbo;
		m_pSbo->m_nRefCount ++;
	}

	return *this;
}

const CStringBuffer& CStringBuffer::operator=(LPCTSTR lpsz)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(m_pSbo->m_nBufLen);
	}
	*m_pSbo = lpsz;

	return *this;
}

const CStringBuffer& CStringBuffer::operator+=(const CStringBuffer& SbSrc)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	*m_pSbo += *SbSrc.m_pSbo;

	return *this;
}

const CStringBuffer& CStringBuffer::operator+=(TCHAR ch)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	*m_pSbo += ch;

	return *this;
}

const CStringBuffer& CStringBuffer::operator+=(LPCTSTR lpsz)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	*m_pSbo += lpsz;

	return *this;
}

BOOL CStringBuffer::CompareNoCase(LPCTSTR lpsz) const
{
	return _tcsicmp(m_pSbo->m_lpszBuf, lpsz);
}

CStringBuffer CStringBuffer::Mid(int nFirst) const
{
	if (nFirst > m_pSbo->m_nLength) {
		CStringBuffer Sb;
		return Sb;
	}
	CStringBuffer Sb(m_pSbo->m_lpszBuf + nFirst);

	return Sb;
}

CStringBuffer CStringBuffer::Mid(int nFirst, int nCount) const
{
	if (nFirst > m_pSbo->m_nLength) {
		CStringBuffer Sb;
		return Sb;
	}
	if (nFirst + nCount > m_pSbo->m_nLength) {
		CStringBuffer Sb(m_pSbo->m_lpszBuf + nFirst, m_pSbo->m_nLength - nFirst);
		return Sb;
	}
	CStringBuffer Sb(m_pSbo->m_lpszBuf + nFirst, nCount);
	return Sb;
}

CStringBuffer CStringBuffer::Left(int nCount) const
{
	if (nCount > m_pSbo->m_nLength)
		return *this;
	CStringBuffer Sb(m_pSbo->m_lpszBuf, nCount);
	return Sb;
}

CStringBuffer CStringBuffer::Right(int nCount) const
{
	if (nCount > m_pSbo->m_nLength)
		return *this;
	CStringBuffer Sb(m_pSbo->m_lpszBuf + m_pSbo->m_nLength - nCount, nCount);
	return Sb;
}

void CStringBuffer::MakeUpper()
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	_tcsupr(m_pSbo->m_lpszBuf);
}

void CStringBuffer::MakeLower()
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	_tcslwr(m_pSbo->m_lpszBuf);
}

int CStringBuffer::Replace(TCHAR chOld, TCHAR chNew)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	return m_pSbo->Replace(chOld, chNew);
}

int CStringBuffer::Replace(LPCTSTR lpszOld, LPCTSTR lpszNew)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	int nOldLen = _tcslen(lpszOld);
	int nNewLen = _tcslen(lpszNew);
	int nCount = 0;
	int nIndex;
	TCHAR* pch = m_pSbo->m_lpszBuf;
	while ((pch = _tcsstr(pch, lpszOld)) != NULL) {
		nIndex = pch - m_pSbo->m_lpszBuf;
		m_pSbo->Update(nIndex, nOldLen, lpszNew);
		pch = m_pSbo->m_lpszBuf + nIndex + nNewLen;
		nCount ++;
	}

	return nCount;
}

int CStringBuffer::Update(int nIndex, int nCount, LPCTSTR lpsz)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	return m_pSbo->Update(nIndex, nCount, lpsz);
}

int CStringBuffer::Insert(int nIndex, LPCTSTR lpsz)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	return m_pSbo->Insert(nIndex, lpsz);
}

int CStringBuffer::Delete(int nIndex, int nCount)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	return m_pSbo->Delete(nIndex, nCount);
}

void CStringBuffer::Format(LPCTSTR lpszFormat, ...)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(m_pSbo->m_nBufLen);
	}
	va_list vl;
	va_start(vl, lpszFormat);
	m_pSbo->FormatV(lpszFormat, vl);
	va_end(vl);
}

void CStringBuffer::FormatV(LPCTSTR lpszFormat, va_list vl)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(m_pSbo->m_nBufLen);
	}
	m_pSbo->FormatV(lpszFormat, vl);
}

void CStringBuffer::TrimLeft(LPCTSTR lpszTargets)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	m_pSbo->TrimLeft(lpszTargets);
	return;
}

void CStringBuffer::TrimRight(LPCTSTR lpszTargets)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	m_pSbo->TrimRight(lpszTargets);
	return;
}

int CStringBuffer::Find(TCHAR ch) const
{
	TCHAR* pch;
	if ((pch = _tcschr(m_pSbo->m_lpszBuf, (int)ch)) == NULL)
		return -1;

	return pch - m_pSbo->m_lpszBuf;
}

int CStringBuffer::Find(LPCTSTR lpszSub) const
{
	TCHAR* pch;
	if ((pch = _tcsstr(m_pSbo->m_lpszBuf, lpszSub)) == NULL)
		return -1;

	return pch - m_pSbo->m_lpszBuf;
}

int CStringBuffer::Find(TCHAR ch, int nStart) const
{
	TCHAR* pch;
	if ((pch = _tcschr(m_pSbo->m_lpszBuf + nStart, (int)ch)) == NULL)
		return -1;

	return pch - m_pSbo->m_lpszBuf;
}

int CStringBuffer::Find(LPCTSTR pstr, int nStart) const
{
	TCHAR* pch;
	if ((pch = _tcsstr(m_pSbo->m_lpszBuf + nStart, pstr)) == NULL)
		return -1;

	return pch - m_pSbo->m_lpszBuf;
}

int CStringBuffer::ReverseFind(TCHAR ch) const
{
	TCHAR* pch;
	if ((pch = _tcsrchr(m_pSbo->m_lpszBuf, (int)ch)) == NULL)
		return -1;

	return pch - m_pSbo->m_lpszBuf;
}

int CStringBuffer::FindOneOf(LPCTSTR lpszCharSet) const
{
	TCHAR* pch;
	if ((pch = _tcspbrk(m_pSbo->m_lpszBuf, lpszCharSet)) == NULL)
		return -1;

	return pch - m_pSbo->m_lpszBuf;
}

LPTSTR CStringBuffer::GetBuffer(int nMinBufLength)
{
	if (nMinBufLength > m_pSbo->m_nBufLen)
		SetBufferLength(nMinBufLength);

	return m_pSbo->m_lpszBuf;
}

LPTSTR CStringBuffer::GetBufferSetLength(int nNewLength)
{
	SetBufferLength(nNewLength);
	return m_pSbo->m_lpszBuf;
}

void CStringBuffer::ReleaseBuffer(int nNewLength)
{
	if (nNewLength == -1)
		m_pSbo->m_nLength = _tcslen(m_pSbo->m_lpszBuf);
	else {
		m_pSbo->m_nLength = nNewLength;
		m_pSbo->m_lpszBuf[nNewLength] = _T('\0');
	}
}

void CStringBuffer::SetBufferLength(int nNewLength)
{
	if (m_pSbo->m_nRefCount > 1) {
		m_pSbo->m_nRefCount --;
		m_pSbo = new CStringBufferObject(*m_pSbo);
	}
	m_pSbo->SetBufferLength(nNewLength);
}

BOOL operator==(const CStringBuffer& Sb1, const CStringBuffer& Sb2)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, Sb2.m_pSbo->m_lpszBuf) == 0;
}

BOOL operator==(const CStringBuffer& Sb1, LPCTSTR lpsz)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, lpsz) == 0;
}

BOOL operator==(LPCTSTR lpsz, const CStringBuffer& Sb2)
{
	return _tcscmp(lpsz, Sb2.m_pSbo->m_lpszBuf) == 0;
}

BOOL operator!=(const CStringBuffer& Sb1, const CStringBuffer& Sb2)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, Sb2.m_pSbo->m_lpszBuf) != 0;
}

BOOL operator!=(const CStringBuffer& Sb1, LPCTSTR lpsz)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, lpsz) != 0;
}

BOOL operator!=(LPCTSTR lpsz, const CStringBuffer& Sb2)
{
	return _tcscmp(lpsz, Sb2.m_pSbo->m_lpszBuf) != 0;
}

BOOL operator<(const CStringBuffer& Sb1, const CStringBuffer& Sb2)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, Sb2.m_pSbo->m_lpszBuf) < 0;
}

BOOL operator<(const CStringBuffer& Sb1, LPCTSTR lpsz)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, lpsz) < 0;
}

BOOL operator<(LPCTSTR lpsz, const CStringBuffer& Sb2)
{
	return _tcscmp(lpsz, Sb2.m_pSbo->m_lpszBuf) < 0;
}

BOOL operator>(const CStringBuffer& Sb1, const CStringBuffer& Sb2)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, Sb2.m_pSbo->m_lpszBuf) > 0;
}

BOOL operator>(const CStringBuffer& Sb1, LPCTSTR lpsz)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, lpsz) > 0;
}

BOOL operator>(LPCTSTR lpsz, const CStringBuffer& Sb2)
{
	return _tcscmp(lpsz, Sb2.m_pSbo->m_lpszBuf) > 0;
}

BOOL operator<=(const CStringBuffer& Sb1, const CStringBuffer& Sb2)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, Sb2.m_pSbo->m_lpszBuf) <= 0;
}

BOOL operator<=(const CStringBuffer& Sb1, LPCTSTR lpsz)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, lpsz) <= 0;
}

BOOL operator<=(LPCTSTR lpsz, const CStringBuffer& Sb2)
{
	return _tcscmp(lpsz, Sb2.m_pSbo->m_lpszBuf) <= 0;
}

BOOL operator>=(const CStringBuffer& Sb1, const CStringBuffer& Sb2)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, Sb2.m_pSbo->m_lpszBuf) >= 0;
}

BOOL operator>=(const CStringBuffer& Sb1, LPCTSTR lpsz)
{
	return _tcscmp(Sb1.m_pSbo->m_lpszBuf, lpsz) >= 0;
}

BOOL operator>=(LPCTSTR lpsz, const CStringBuffer& Sb2)
{
	return _tcscmp(lpsz, Sb2.m_pSbo->m_lpszBuf) >= 0;
}

CStringBuffer operator+(const CStringBuffer& Sb1, const CStringBuffer& Sb2)
{
	CStringBuffer Sb(Sb1);
	Sb += Sb2;

	return Sb;
}

CStringBuffer operator+(const CStringBuffer& Sb1, TCHAR ch)
{
	CStringBuffer Sb(Sb1);
	Sb += ch;

	return Sb;
}

CStringBuffer operator+(TCHAR ch, const CStringBuffer& Sb2)
{
	CStringBuffer Sb(ch);
	Sb += Sb2;

	return Sb;
}
CStringBuffer operator+(const CStringBuffer& Sb1, LPCTSTR lpsz)
{
	CStringBuffer Sb(Sb1);
	Sb += lpsz;

	return Sb;
}

CStringBuffer operator+(LPCTSTR lpsz, const CStringBuffer& Sb2)
{
	CStringBuffer Sb(lpsz);
	Sb += Sb2;

	return Sb;
}
