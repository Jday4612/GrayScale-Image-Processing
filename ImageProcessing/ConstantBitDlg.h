#pragma once
#include "afxdialogex.h"


// CConstantBitDlg 대화 상자

class CConstantBitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConstantBitDlg)

public:
	CConstantBitDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConstantBitDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSTANT_BIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_constantBit;
};
