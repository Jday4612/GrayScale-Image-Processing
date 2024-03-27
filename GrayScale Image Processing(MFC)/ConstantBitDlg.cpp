// ConstantBit.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantBitDlg.h"


// CConstantBit 대화 상자

IMPLEMENT_DYNAMIC(CConstantBitDlg, CDialog)

CConstantBitDlg::CConstantBitDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_BIT, pParent)
	, m_constantBit(0)
{

}

CConstantBitDlg::~CConstantBitDlg()
{
}

void CConstantBitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_BIT, m_constantBit);
	DDV_MinMaxDouble(pDX, m_constantBit, 3, 256);
}


BEGIN_MESSAGE_MAP(CConstantBitDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConstantBitDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConstantBit 메시지 처리기


void CConstantBitDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
