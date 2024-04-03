#pragma once
#include "afxdialogex.h"


// CConstantHeightWidthDlg 대화 상자

class CConstantHeightWidthDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantHeightWidthDlg)

public:
	CConstantHeightWidthDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantHeightWidthDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_HEIGHT_WIDTH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constantHeight;
	int m_constantWidth;
};
