// Affinity.cpp: CAffinity クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IdicChasen.h"
#include "Affinity.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CAffinity::CAffinity()
{
	Empty();
}

void CAffinity::Empty()
{
	m_strName.Empty();
	m_nGenre = -1;
	m_DtBirth = COleDateTime();
	m_strBloodType.Empty();
	for (int i = 0; i < 8; i ++)
		m_pnAffinity[i] = 0;
}

void CAffinity::Copy(const CAffinity& Src)
{
	m_strName = Src.m_strName;
	m_nGenre = Src.m_nGenre;
	m_DtBirth = Src.m_DtBirth;
	m_strBloodType = Src.m_strBloodType;
	memcpy(m_pnAffinity, Src.m_pnAffinity, sizeof(int) * 8);
}

const CAffinity& CAffinity::operator=(const CAffinity& Src)
{
	Copy(Src);
	return *this;
}
