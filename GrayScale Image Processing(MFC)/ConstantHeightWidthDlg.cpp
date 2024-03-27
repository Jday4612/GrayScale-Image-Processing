// ConstantHeightWidth.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantHeightWidthDlg.h"


// CConstantHeightWidth 대화 상자

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
	DDX_Text(pDX, IDC_EDIT_CONSTANT_Height, m_constantHeight);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_Width, m_constantWidth);
}


BEGIN_MESSAGE_MAP(CConstantHeightWidthDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConstantHeightWidthDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConstantHeightWidth 메시지 처리기


void CConstantHeightWidthDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
