#pragma once
#include "afxdialogex.h"


// CConstantInterval 대화 상자

class CConstantIntervalDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantIntervalDlg)

public:
	CConstantIntervalDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantIntervalDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_INTERVAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constantStart;
	int m_constantEnd;
};
