// ConstantDoubleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantDoubleDlg.h"


// CConstantDoubleDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantDoubleDlg, CDialog)

CConstantDoubleDlg::CConstantDoubleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_DOUBLE, pParent)
	, m_constantDouble(0)
{

}

CConstantDoubleDlg::~CConstantDoubleDlg()
{
}

void CConstantDoubleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_DOUBLE, m_constantDouble);
	DDV_MinMaxDouble(pDX, m_constantDouble, 0.0, DBL_MAX);
}


BEGIN_MESSAGE_MAP(CConstantDoubleDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConstantDoubleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConstantDoubleDlg 메시지 처리기


void CConstantDoubleDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
