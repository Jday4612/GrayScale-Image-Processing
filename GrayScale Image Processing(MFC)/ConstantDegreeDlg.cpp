// ConstantDegreeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GrayScaleImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantDegreeDlg.h"


// CConstantDegreeDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantDegreeDlg, CDialog)

CConstantDegreeDlg::CConstantDegreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_DEGREE, pParent)
	, m_constantDegree(0)
{

}

CConstantDegreeDlg::~CConstantDegreeDlg()
{
}

void CConstantDegreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_DEGREE, m_constantDegree);
	DDV_MinMaxInt(pDX, m_constantDegree, 0, 360);
}


BEGIN_MESSAGE_MAP(CConstantDegreeDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConstantDegreeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConstantDegreeDlg 메시지 처리기


void CConstantDegreeDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
