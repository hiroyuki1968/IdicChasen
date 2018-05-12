// FindDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "idicchasen.h"
#include "FindDlg.h"

#include "IdicChasenDef.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindDlg �_�C�A���O


CFindDlg::CFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindDlg ���b�Z�[�W �n���h��

BOOL CFindDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	// �����L�[
	CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO1);
	for (int i = 0, imax = m_pSaFindKey->GetSize(); i < imax; i ++)
		pComboBox->AddString(m_pSaFindKey->GetAt(i));
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CFindDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	const static char* pszFuncName = "CFindDlg.OnOK";
	try {
		// �����L�[
		CComboBox* pComboBox = (CComboBox *)GetDlgItem(IDC_COMBO1);
		int nFindKey;
		if ((nFindKey = pComboBox->GetCurSel()) == CB_ERR)
			pComboBox->GetWindowText(m_strFindKey);
		else
			pComboBox->GetLBText(nFindKey, m_strFindKey);
		// �����L�[����
		if (nFindKey != CB_ERR  ||  (nFindKey = pComboBox->FindStringExact(-1, m_strFindKey)) != CB_ERR)
			m_pSaFindKey->RemoveAt(nFindKey);
		m_pSaFindKey->InsertAt(0, m_strFindKey);
		if (m_pSaFindKey->GetSize() > HISTORY_COUNT)
			m_pSaFindKey->SetSize(HISTORY_COUNT);
	}
	catch (CMemoryException* pEx) {
		MessageBox(StrFormat(ERRMSG_MEMEX, pszFuncName, (LPCTSTR)GetExceptionErrorMessage(pEx)), NULL, MB_ICONSTOP);
		pEx->Delete();
	}
	
	CDialog::OnOK();
}
