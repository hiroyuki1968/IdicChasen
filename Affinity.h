// Affinity.h: CAffinity クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AFFINITY_H__D8986442_BCA6_4C46_B3E5_3B12A8F8E167__INCLUDED_)
#define AFX_AFFINITY_H__D8986442_BCA6_4C46_B3E5_3B12A8F8E167__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CAffinity  
{
public:
	CAffinity();

	void Empty();
	void Copy(const CAffinity& Src);
	const CAffinity& operator=(const CAffinity& Src);

	CString m_strName;
	int m_nGenre;
	COleDateTime m_DtBirth;
	CString m_strBloodType;
	int m_pnAffinity[8];
};

/////////////////////////////////////////////////////////////////////////////
// CAffinityArray : CAffinity 配列クラス

typedef CArray<CAffinity, const CAffinity&> CAffinityArray;

#endif // !defined(AFX_AFFINITY_H__D8986442_BCA6_4C46_B3E5_3B12A8F8E167__INCLUDED_)
