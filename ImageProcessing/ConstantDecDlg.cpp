// ConstantDec.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantDecDlg.h"


// CConstantDec 대화 상자

IMPLEMENT_DYNAMIC(CConstantDecDlg, CDialog)

CConstantDecDlg::CConstantDecDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_DEC, pParent)
	, m_constantDec(0)
{

}

CConstantDecDlg::~CConstantDecDlg()
{
}

void CConstantDecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_DEC, m_constantDec);
	DDV_MinMaxDouble(pDX, m_constantDec, 0.0, DBL_MAX);
}


BEGIN_MESSAGE_MAP(CConstantDecDlg, CDialog)
END_MESSAGE_MAP()


// CConstantDec 메시지 처리기
