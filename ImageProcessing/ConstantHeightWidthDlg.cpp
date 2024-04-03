// ConstantHeightWidthDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantHeightWidthDlg.h"


// CConstantHeightWidthDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantHeightWidthDlg, CDialog)

CConstantHeightWidthDlg::CConstantHeightWidthDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_HEIGHT_WIDTH, pParent)
	, m_constantHeight(0)
	, m_constantWidth(0)
{

}

CConstantHeightWidthDlg::~CConstantHeightWidthDlg()
{
}

void CConstantHeightWidthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_HEIGHT, m_constantHeight);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_WIDTH, m_constantWidth);
}


BEGIN_MESSAGE_MAP(CConstantHeightWidthDlg, CDialog)
END_MESSAGE_MAP()


// CConstantHeightWidthDlg 메시지 처리기
