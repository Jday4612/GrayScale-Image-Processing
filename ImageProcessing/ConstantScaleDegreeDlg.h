#pragma once
#include "afxdialogex.h"


// CConstantScaleDegreeDlg 대화 상자

class CConstantScaleDegreeDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantScaleDegreeDlg)

public:
	CConstantScaleDegreeDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantScaleDegreeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_SCALE_DEGREE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constantScale;
	int m_constantDegree;
};
