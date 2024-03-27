#pragma once
#include "afxdialogex.h"


// CConstantDoubleDlg 대화 상자

class CConstantDoubleDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantDoubleDlg)

public:
	CConstantDoubleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDoubleDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_DOUBLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_constantDouble;
	afx_msg void OnBnClickedOk();
};
