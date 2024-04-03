// ConstantInterval.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantIntervalDlg.h"


// CConstantInterval 대화 상자

IMPLEMENT_DYNAMIC(CConstantIntervalDlg, CDialog)

CConstantIntervalDlg::CConstantIntervalDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_INTERVAL, pParent)
	, m_constantStart(0)
	, m_constantEnd(0)
{

}

CConstantIntervalDlg::~CConstantIntervalDlg()
{
}

void CConstantIntervalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_START, m_constantStart);
	DDV_MinMaxInt(pDX, m_constantStart, 0, 255);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_END, m_constantEnd);
	DDV_MinMaxInt(pDX, m_constantEnd, m_constantStart, 255);
}


BEGIN_MESSAGE_MAP(CConstantIntervalDlg, CDialog)
END_MESSAGE_MAP()


// CConstantInterval 메시지 처리기
