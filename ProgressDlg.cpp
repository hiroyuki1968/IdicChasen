// ProgressDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "IdicChasen.h"
#include "ProgressDlg.h"

#include "Common.h"
#include "IdicChasenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg �_�C�A���O


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg ���b�Z�[�W �n���h��

BOOL CProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	// �ϐ��̏�����
	m_bStopReq = FALSE;
	// �������e
	GetDlgItem(IDC_TEXT1)->SetWindowText(m_lpszDocument);
	// �}�E�X�J�[�\��
	AfxGetApp()->DoWaitCursor(1);
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CProgressDlg::OnCancel()
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	
//	CDialog::OnCancel();
}

HBRUSH CProgressDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: ���̈ʒu�� DC �̃A�g���r���[�g��ύX���Ă�������
	if (! m_pIdicChasenDlg->m_IconButton5.m_hTheme  &&  pWnd->GetDlgCtrlID() == IDC_GROUPBOX1)
		pDC->SetTextColor(RGB(0, 0, 255));
	
	// TODO: �f�t�H���g�̃u���V���]�݂̂��̂łȂ��ꍇ�ɂ́A�Ⴄ�u���V��Ԃ��Ă�������
	return hbr;
}

void CProgressDlg::OnButton1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_bStopReq = TRUE;
}

void CProgressDlg::SetDocument(LPCTSTR lpszDocument)
{
	GetDlgItem(IDC_TEXT1)->SetWindowText(lpszDocument);
}

void CProgressDlg::SetRange(int nUpper)
{
	m_ProgressCtrl1.SetRange32(0, nUpper);
}

void CProgressDlg::StepIt()
{
	m_ProgressCtrl1.StepIt();
	PumpWaitingMessages();
}

void CProgressDlg::SetStep(int nStep)
{
	m_ProgressCtrl1.SetStep(nStep);
}

void CProgressDlg::Destroy()
{
	// �}�E�X�J�[�\��
	AfxGetApp()->DoWaitCursor(0);

	EndDialog(IDCANCEL);
	DestroyWindow();
}
