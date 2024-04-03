// ColorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "ColorDlg.h"


// CColorDlg 대화 상자

IMPLEMENT_DYNAMIC(CColorDlg, CDialog)

CColorDlg::CColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_COLOR, pParent)
{

}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	ON_BN_CLICKED(IDC_COLOR_RED, &CColorDlg::OnBnClickedColorRed)
	ON_BN_CLICKED(IDC_COLOR_ORANGE, &CColorDlg::OnBnClickedColorOrange)
	ON_BN_CLICKED(IDC_COLOR_YELLOW, &CColorDlg::OnBnClickedColorYellow)
	ON_BN_CLICKED(IDC_COLOR_GREEN, &CColorDlg::OnBnClickedColorGreen)
	ON_BN_CLICKED(IDC_COLOR_BLUE, &CColorDlg::OnBnClickedColorBlue)
	ON_BN_CLICKED(IDC_COLOR_PURPLE, &CColorDlg::OnBnClickedColorPurple)
END_MESSAGE_MAP()


// CColorDlg 메시지 처리기


void CColorDlg::OnBnClickedColorRed()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_colorStart = 13;
	m_colorEnd = 330;
	m_checkRed = TRUE;
	EndDialog(IDOK);
}


void CColorDlg::OnBnClickedColorOrange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_colorStart = 8;
	m_colorEnd = 20;
	EndDialog(IDOK);
}


void CColorDlg::OnBnClickedColorYellow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_colorStart = 20;
	m_colorEnd = 60;
	EndDialog(IDOK);
}


void CColorDlg::OnBnClickedColorGreen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_colorStart = 60;
	m_colorEnd = 150;
	EndDialog(IDOK);
}


void CColorDlg::OnBnClickedColorBlue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_colorStart = 150;
	m_colorEnd = 270;
	EndDialog(IDOK);
}


void CColorDlg::OnBnClickedColorPurple()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_colorStart = 270;
	m_colorEnd = 330;
	EndDialog(IDOK);
}
