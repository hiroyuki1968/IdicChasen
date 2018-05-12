// IdicChasen.h : IDICCHASEN �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_IDICCHASEN_H__99B66FE4_1E3E_448D_82DC_4E2FEA0E812A__INCLUDED_)
#define AFX_IDICCHASEN_H__99B66FE4_1E3E_448D_82DC_4E2FEA0E812A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

#include "IdicChasenDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� IdicChasen.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CIdicChasenApp : public CWinApp
{
public:
	CIdicChasenApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CIdicChasenApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	CIdicChasenDlg* m_pIdicChasenDlg;
protected:
	int ReadProductCode(CStringBuffer& strProductCode);
	CString m_strDir;
	HANDLE m_hExeCheckMutex;

	//{{AFX_MSG(CIdicChasenApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);
int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_IDICCHASEN_H__99B66FE4_1E3E_448D_82DC_4E2FEA0E812A__INCLUDED_)
