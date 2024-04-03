#pragma once
#include "afxdialogex.h"


// CColorDlg 대화 상자

class CColorDlg : public CDialog
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CColorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedColorRed();
	afx_msg void OnBnClickedColorOrange();
	afx_msg void OnBnClickedColorYellow();
	afx_msg void OnBnClickedColorGreen();
	afx_msg void OnBnClickedColorBlue();
	afx_msg void OnBnClickedColorPurple();
	int m_colorStart = 0;
	int m_colorEnd = 360;
	bool m_checkRed = FALSE;
};
