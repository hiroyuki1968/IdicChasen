#if !defined(AFX_DLPROGRESSDLG_H__B3C840E3_3A64_40BB_960A_15F85AE2739A__INCLUDED_)
#define AFX_DLPROGRESSDLG_H__B3C840E3_3A64_40BB_960A_15F85AE2739A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlProgressDlg.h : �w�b�_�[ �t�@�C��
//

class CIdicChasenDlg;

/////////////////////////////////////////////////////////////////////////////
// CDlProgressDlg �_�C�A���O

class CDlProgressDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CDlProgressDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlProgressDlg)
	enum { IDD = IDD_DLPROGRESS_DIALOG };
	CString	m_strEdit1;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void Destroy();
	CIdicChasenDlg* m_pIdicChasenDlg;
	BOOL m_bStopReq;
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlProgressDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLPROGRESSDLG_H__B3C840E3_3A64_40BB_960A_15F85AE2739A__INCLUDED_)
