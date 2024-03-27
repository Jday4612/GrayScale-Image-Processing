#pragma once
#include "afxdialogex.h"


// CConstantPositiveDlg 대화 상자

class CConstantPositiveDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantPositiveDlg)

public:
	CConstantPositiveDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantPositiveDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_POSITIVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constantPositive;
	afx_msg void OnBnClickedOk();
};
