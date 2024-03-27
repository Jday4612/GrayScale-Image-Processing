// ConstantPositiveDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessing.h"
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
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_constantPositive);
	DDV_MinMaxInt(pDX, m_constantPositive, 1, INT_MAX);
}


BEGIN_MESSAGE_MAP(CConstantPositiveDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConstantPositiveDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConstantPositiveDlg 메시지 처리기


void CConstantPositiveDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
