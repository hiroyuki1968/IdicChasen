// IdicChasen.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "IdicChasen.h"
#include "IdicChasenDlg.h"

#include "IdicChasenDef.h"
#include "htmlhelp.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenApp

BEGIN_MESSAGE_MAP(CIdicChasenApp, CWinApp)
	//{{AFX_MSG_MAP(CIdicChasenApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenApp �N���X�̍\�z

CIdicChasenApp::CIdicChasenApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
	m_hExeCheckMutex = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CIdicChasenApp �I�u�W�F�N�g

CIdicChasenApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIdicChasenApp �N���X�̏�����

BOOL CIdicChasenApp::InitInstance()
{
	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
#endif

	LoadUxThemeDll();

	// Exe �t�H���_
	m_strDir = GetDPathFromFPath(m_pszHelpFilePath);

	// �R�}���h ���C������
	BOOL bUninstall = _tcsicmp(m_lpCmdLine, _T("/Uninstall")) == 0;

	// �A���C���X�g�[��
	if (bUninstall) {
		CStringBuffer strProductCode;
		if (ReadProductCode(strProductCode))
			return FALSE;

		HINSTANCE hShellExecute;
		if ((int)(hShellExecute = ShellExecute(NULL, _T("open"), _T("msiexec"), _T("/x ") + strProductCode, NULL, SW_SHOWNORMAL)) <= 32)
			AfxMessageBox(_T("�A���C���X�g�[���[���s�G���[: ") + GetShellExecuteErrorText(hShellExecute), MB_ICONSTOP);
		return FALSE;
	}

	// �v���O�����̕����N���}�~
	// �����A�I�[�v���ł���ΈȑO�̃A�v���P�[�V�������N�����Ă���
	CString strMutex(MUTEX_INSTANCE);
	HANDLE hPrevMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, strMutex);
	if (hPrevMutex) {
		AfxMessageBox("���ɋN�����Ă��܂��B", MB_ICONSTOP);
		// �N���[�Y
		CloseHandle(hPrevMutex);
		return FALSE; 
	}
	// �����N���m�F�p�~���[�e�b�N�X�쐬
	m_hExeCheckMutex = CreateMutex(FALSE, 0, strMutex);

	CIdicChasenDlg dlg;
	m_pMainWnd = &dlg;
	m_pIdicChasenDlg = &dlg;
	dlg.m_strDir = m_strDir;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <��ݾ�> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}

int CIdicChasenApp::ExitInstance() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	if (m_hExeCheckMutex)
		ReleaseMutex(m_hExeCheckMutex);
	FreeUxThemeDll();
	
	return CWinApp::ExitInstance();
}

void CIdicChasenApp::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	//������OS���̃`�F�b�N���s���Ƃ悢
	//OSVERSIONINFO os_info;
	//os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	//GetVersionEx(&os_info);

	//����͍쐬����HtmlHelp�ɂ��قȂ�
	//dwData��ϊ�����R�[�h���K�v
	char* szFileName = "IdicChasen.htm";

	CString strHelpPath = m_pszHelpFilePath;
	strHelpPath = strHelpPath.Left(strHelpPath.ReverseFind('.') + 1) + "chm";

	HtmlHelp(NULL, strHelpPath, HH_DISPLAY_TOPIC, (DWORD)szFileName);

// ��{�N���X�̃����o�֐��͌Ă΂Ȃ�
//	CWinApp::WinHelp(dwData, nCmd);
}

int CIdicChasenApp::ReadProductCode(CStringBuffer& strProductCode)
{
	int nRv = 0;

	if (ReStrFile(m_strDir + _T("\\") FNAME_PRODUCTCODE, strProductCode))
		nRv = -1;
	else
		strProductCode.TrimRight();

	return nRv;
}

int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CIdicChasenDlg* pIdicChasenDlg = theApp.m_pIdicChasenDlg;

	int nRv = 0;
	COleDateTime Dt0;
	COleDateTime Dt1;
	int n0;
	int n1;

	switch (lParamSort) {
	case 0:
		nRv = pIdicChasenDlg->m_AffinityArray[lParam1].m_strName.Compare(pIdicChasenDlg->m_AffinityArray[lParam2].m_strName);
		break;
	case 1:
		Dt0 = pIdicChasenDlg->m_AffinityArray[lParam1].m_DtBirth;
		Dt1 = pIdicChasenDlg->m_AffinityArray[lParam2].m_DtBirth;
		if (Dt0 < Dt1)
			nRv = -1;
		else if (Dt0 > Dt1)
			nRv = 1;
		break;
	case 2:
		nRv = pIdicChasenDlg->m_AffinityArray[lParam1].m_strBloodType.Compare(pIdicChasenDlg->m_AffinityArray[lParam2].m_strBloodType);
		break;
	default:
		n0 = pIdicChasenDlg->m_AffinityArray[lParam1].m_pnAffinity[lParamSort - 3];
		n1 = pIdicChasenDlg->m_AffinityArray[lParam2].m_pnAffinity[lParamSort - 3];
		if (n0 < n1)
			nRv = 1;
		else if (n0 > n1)
			nRv = -1;
	}

	return nRv * pIdicChasenDlg->m_nLastSortDir;
}

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CIdicChasenDlg* pIdicChasenDlg = theApp.m_pIdicChasenDlg;

	LPMSG lpMsg = (LPMSG) lParam;

	if ( nCode >= 0 && PM_REMOVE == wParam )
	{
		if (lpMsg->message == WM_KEYDOWN)
		{
			HWND hwnd = lpMsg->hwnd;
			HWND hwndParent;
			HWND hwndIdicChasenDlg = pIdicChasenDlg->m_hWnd;
			while ((hwndParent = GetParent(hwnd)) != NULL) {
				if (hwndParent == hwndIdicChasenDlg)
					break;
				hwnd = hwndParent;
			}
			
			int nID = 0;
			if (hwndParent)
				nID = GetDlgCtrlID(lpMsg->hwnd);

			BOOL bNull = FALSE;

			switch (lpMsg->message) {
			case WM_KEYDOWN:
				if (hwndParent == hwndIdicChasenDlg  ||  hwndParent == NULL  &&  hwnd == hwndIdicChasenDlg)
					if (lpMsg->wParam == VK_RETURN)
						if (nID == IDC_EDIT15  ||  nID == IDC_EDIT16) {
							pIdicChasenDlg->UpdateList();
							bNull = TRUE;
						}
			}

			if (bNull) {
				lpMsg->message = WM_NULL;
				lpMsg->lParam  = 0;
				lpMsg->wParam  = 0;
			}
		}
	}

	return CallNextHookEx(pIdicChasenDlg->m_hHook, nCode, wParam, lParam);
}
