#if !defined(AFX_PROGRESSDLG_H__69F3FF3F_DC08_4D54_838E_C26F0C964133__INCLUDED_)
#define AFX_PROGRESSDLG_H__69F3FF3F_DC08_4D54_838E_C26F0C964133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDlg.h : �w�b�_�[ �t�@�C��
//

class CIdicChasenDlg;

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg �_�C�A���O

class CProgressDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CProgressDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESS_DIALOG };
	CProgressCtrl	m_ProgressCtrl1;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	void SetDocument(LPCTSTR lpszDocument);
	void SetRange(int nUpper);
	void StepIt();
	void SetStep(int nStep);
	void Destroy();
	CIdicChasenDlg* m_pIdicChasenDlg;
	LPCTSTR m_lpszDocument;
	BOOL m_bStopReq;
protected:
	CProgressCtrl* m_pProgressCtrl;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CProgressDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PROGRESSDLG_H__69F3FF3F_DC08_4D54_838E_C26F0C964133__INCLUDED_)
