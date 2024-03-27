// Constant2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessing.h"
#include "afxdialogex.h"
#include "Constant2Dlg.h"


// CConstant2Dlg 대화 상자

IMPLEMENT_DYNAMIC(CConstant2Dlg, CDialog)

CConstant2Dlg::CConstant2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT2, pParent)
	, m_constantStart(0)
	, m_constantEnd(0)
{

}

CConstant2Dlg::~CConstant2Dlg()
{
}

void CConstant2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_START, m_constantStart);
	DDV_MinMaxDouble(pDX, m_constantStart, 0, 255);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_END, m_constantEnd);
	DDV_MinMaxDouble(pDX, m_constantEnd, m_constantStart, 255);
}


BEGIN_MESSAGE_MAP(CConstant2Dlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConstant2Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConstant2Dlg 메시지 처리기


void CConstant2Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
