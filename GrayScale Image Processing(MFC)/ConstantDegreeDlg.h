#pragma once
#include "afxdialogex.h"


// CConstantDegreeDlg 대화 상자

class CConstantDegreeDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantDegreeDlg)

public:
	CConstantDegreeDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantDegreeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_DEGREE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constantDegree;
	afx_msg void OnBnClickedOk();
};
