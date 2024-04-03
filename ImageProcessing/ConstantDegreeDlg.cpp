// ConstantDegreeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantDegreeDlg.h"


// CConstantDegreeDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantDegreeDlg, CDialogEx)

CConstantDegreeDlg::CConstantDegreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONSTANT_DEGREE, pParent)
	, m_constantDegree(0)
{

}

CConstantDegreeDlg::~CConstantDegreeDlg()
{
}

void CConstantDegreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_DEGREE, m_constantDegree);
	DDV_MinMaxInt(pDX, m_constantDegree, 0, 360);
}


BEGIN_MESSAGE_MAP(CConstantDegreeDlg, CDialogEx)
END_MESSAGE_MAP()


// CConstantDegreeDlg 메시지 처리기
