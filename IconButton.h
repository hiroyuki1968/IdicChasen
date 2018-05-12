#if !defined(AFX_ICONBUTTON_H__F3C057CB_A771_4844_AEFA_654494271022__INCLUDED_)
#define AFX_ICONBUTTON_H__F3C057CB_A771_4844_AEFA_654494271022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IconButton.h : �w�b�_�[ �t�@�C��
//

#include "UxTheme.h"

/////////////////////////////////////////////////////////////////////////////
// CIconButton �E�B���h�E

class CIconButton : public CButton
{
// �R���X�g���N�V����
public:
	CIconButton();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CIconButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CIconButton();
	HTHEME m_hTheme;
protected:
	BOOL m_bDrawItem;
	BOOL m_bInWindow;
	HICON m_hIcon;
	CImageList m_ImageList;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CIconButton)
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ICONBUTTON_H__F3C057CB_A771_4844_AEFA_654494271022__INCLUDED_)
