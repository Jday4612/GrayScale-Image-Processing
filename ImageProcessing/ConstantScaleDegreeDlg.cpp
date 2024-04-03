// ConstantScaleDegreeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageProcessing.h"
#include "afxdialogex.h"
#include "ConstantScaleDegreeDlg.h"


// CConstantScaleDegreeDlg 대화 상자

IMPLEMENT_DYNAMIC(CConstantScaleDegreeDlg, CDialog)

CConstantScaleDegreeDlg::CConstantScaleDegreeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CONSTANT_SCALE_DEGREE, pParent)
	, m_constantScale(0)
	, m_constantDegree(0)
{

}

CConstantScaleDegreeDlg::~CConstantScaleDegreeDlg()
{
}

void CConstantScaleDegreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_SCALE, m_constantScale);
	DDV_MinMaxInt(pDX, m_constantScale, 1, INT_MAX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_DEGREE, m_constantDegree);
	DDV_MinMaxInt(pDX, m_constantDegree, 0, 360);
}


BEGIN_MESSAGE_MAP(CConstantScaleDegreeDlg, CDialog)
END_MESSAGE_MAP()


// CConstantScaleDegreeDlg 메시지 처리기
