// ConstantBitDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantBitDlg.h"


// CConstantBitDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantBitDlg, CDialogEx)

CConstantBitDlg::CConstantBitDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONSTANT_BIT, pParent)
	, m_constantBit(0)
{

}

CConstantBitDlg::~CConstantBitDlg()
{
}

void CConstantBitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_BIT, m_constantBit);
	DDV_MinMaxInt(pDX, m_constantBit, 3, INT_MAX);
}


BEGIN_MESSAGE_MAP(CConstantBitDlg, CDialogEx)
END_MESSAGE_MAP()


// CConstantBitDlg 메시지 처리기
