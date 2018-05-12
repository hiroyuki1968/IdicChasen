// DlProgressDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "idicchasen.h"
#include "DlProgressDlg.h"

#include "IdicChasenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlProgressDlg �_�C�A���O


CDlProgressDlg::CDlProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlProgressDlg)
	m_strEdit1 = _T("");
	//}}AFX_DATA_INIT
}


void CDlProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlProgressDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CDlProgressDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlProgressDlg ���b�Z�[�W �n���h��

BOOL CDlProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	// �ϐ��̏�����
	m_bStopReq = FALSE;
	// �}�E�X�J�[�\��
	AfxGetApp()->DoWaitCursor(1);
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDlProgressDlg::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	
//	CDialog::OnCancel();
}

HBRUSH CDlProgressDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: ���̈ʒu�� DC �̃A�g���r���[�g��ύX���Ă�������
	if (! m_pIdicChasenDlg->m_IconButton5.m_hTheme  &&  pWnd->GetDlgCtrlID() == IDC_GROUPBOX1)
		pDC->SetTextColor(RGB(0, 0, 255));
	
	// TODO: �f�t�H���g�̃u���V���]�݂̂��̂łȂ��ꍇ�ɂ́A�Ⴄ�u���V��Ԃ��Ă�������
	return hbr;
}

void CDlProgressDlg::OnButton1() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_bStopReq = TRUE;
}

void CDlProgressDlg::Destroy()
{
	// �}�E�X�J�[�\��
	AfxGetApp()->DoWaitCursor(0);

	EndDialog(IDCANCEL);
	DestroyWindow();
}
