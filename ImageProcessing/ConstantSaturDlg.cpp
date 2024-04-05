// ConstantSaturDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantSaturDlg.h"


// CConstantSaturDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantSaturDlg, CDialog)

CConstantSaturDlg::CConstantSaturDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_SATUR, pParent)
	, m_constantSatur(0)
{

}

CConstantSaturDlg::~CConstantSaturDlg()
{
}

void CConstantSaturDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_SATUR, m_constantSatur);
	DDV_MinMaxDouble(pDX, m_constantSatur, -1.0, 1.0);
}


BEGIN_MESSAGE_MAP(CConstantSaturDlg, CDialog)
END_MESSAGE_MAP()


// CConstantSaturDlg 메시지 처리기
