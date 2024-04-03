// ConstantPositiveDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantPositiveDlg.h"


// CConstantPositiveDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantPositiveDlg, CDialog)

CConstantPositiveDlg::CConstantPositiveDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_POSITIVE, pParent)
	, m_constantPositive(0)
{

}

CConstantPositiveDlg::~CConstantPositiveDlg()
{
}

void CConstantPositiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_POSITIVE, m_constantPositive);
	DDV_MinMaxInt(pDX, m_constantPositive, 1, INT_MAX);
}


BEGIN_MESSAGE_MAP(CConstantPositiveDlg, CDialog)
END_MESSAGE_MAP()


// CConstantPositiveDlg 메시지 처리기
