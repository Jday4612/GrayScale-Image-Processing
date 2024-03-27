
// GrayScaleImageProcessingDoc.cpp: CGrayScaleImageProcessingDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImageProcessing.h"
#endif

#include "GrayScaleImageProcessingDoc.h"

#include <propkey.h>
#include "ConstantDlg.h"
#include "ConstantBitDlg.h"
#include "ConstantDegreeDlg.h"
#include "Constant2Dlg.h"
#include "ConstantDoubleDlg.h"
#include "ConstantHeightWidthDlg.h"
#include "ConstantPositiveDlg.h"
#include "ConstantScaleDegreeDlg.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGrayScaleImageProcessingDoc

IMPLEMENT_DYNCREATE(CGrayScaleImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CGrayScaleImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CGrayScaleImageProcessingDoc 생성/소멸

CGrayScaleImageProcessingDoc::CGrayScaleImageProcessingDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CGrayScaleImageProcessingDoc::~CGrayScaleImageProcessingDoc()
{
}

BOOL CGrayScaleImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGrayScaleImageProcessingDoc serialization

void CGrayScaleImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGrayScaleImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGrayScaleImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGrayScaleImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGrayScaleImageProcessingDoc 진단

#ifdef _DEBUG
void CGrayScaleImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGrayScaleImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGrayScaleImageProcessingDoc 명령


unsigned char** CGrayScaleImageProcessingDoc::OnMalloc2D(int h, int w, int initVal)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** retMemory;

	retMemory = new unsigned char* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new unsigned char [w];

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			retMemory[i][j] = initVal;

	return retMemory;
}


void CGrayScaleImageProcessingDoc::OnFree2D(unsigned char** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;
	
	for (int i = 0; i < h; i++)
		delete memory[i];

	delete [] memory;
}


double** CGrayScaleImageProcessingDoc::OnMalloc2DF(int h, int w, double initVal)
{
	// TODO: 여기에 구현 코드 추가.
	double** retMemory;

	retMemory = new double* [h];
	for (int i = 0; i < h; i++)
		retMemory[i] = new double[w];

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			retMemory[i][j] = initVal;

	return retMemory;
}


void CGrayScaleImageProcessingDoc::OnFree2DF(double** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;

	for (int i = 0; i < h; i++)
		delete memory[i];

	delete[] memory;
}


void CGrayScaleImageProcessingDoc::OnMakeDataImage()
{
	// TODO: 여기에 구현 코드 추가.
	OnFree2D(m_dataImage, m_inH);
	m_dataImage = NULL;
	// 데이터 이미지 메모리 할당
	m_dataImage = OnMalloc2D(m_inH, m_inW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	int num = 1, size = m_inH / 4;

	for (int i = m_inH / 2 - size; i < m_inH / 2; i++) {
		for (int j = m_inW / 2 - num; j < m_inW / 2 + num; j++)
			m_dataImage[i][j] = 255;

		num++;
	}

	num--;

	for (int i = m_inH / 2; i < m_inH / 2 + size; i++) {
		for (int j = m_inW / 2 - num; j < m_inW / 2 + num; j++)
			m_dataImage[i][j] = 255;

		num--;
	}
}


BOOL CGrayScaleImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	// 선택된 파일 열기
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	// 2차원 배열로 사용하기 위함 - 정방형 이미지만 다룸.
	double fLength = (double)File.GetLength();
	double log2Value = log(sqrt(fLength)) / log(2.0);
	if (log2Value != (int)log2Value)
	{
		AfxMessageBox(L"정방향크기의 이미지만 지원함");
		return 0;
	}
	// 기존 메모리 모두 해제하고, 관련 값 초기화
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 입력 이미지 크기 결정 및 메모리 할당
	m_inH = m_inW = (long)sqrt(fLength);
	m_inImage = OnMalloc2D(m_inH, m_inW, 0); // 메모리 할당

	// 파일 --> 메모리
	for (int i = 0; i < m_inH; i++)
		File.Read(m_inImage[i], m_inW);
		
	File.Close();

	return TRUE;
}


BOOL CGrayScaleImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File;
	CFileDialog SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);

		for (int i = 0; i < m_outH; i++)
			File.Write(m_outImage[i], m_outW);
	}

	File.Close();

	return CDocument::OnSaveDocument(lpszPathName);
}


void CGrayScaleImageProcessingDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 기존 메모리 모두 해제하고, 관련 값 초기화
	OnFree2D(m_inImage, m_inH);
	m_inImage = NULL;
	m_inH = m_inW = 0;
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;

	CDocument::OnCloseDocument();
}


void CGrayScaleImageProcessingDoc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++)
			m_outImage[i][j] = m_inImage[i][j];
}


void CGrayScaleImageProcessingDoc::OnAddImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		int value = (int)dlg.m_constant;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				if (m_inImage[i][j] + value < 0)
					m_outImage[i][j] = 0;
				else if (255 < m_inImage[i][j] + value)
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = m_inImage[i][j] + value;
			}
		}
	}
}


void CGrayScaleImageProcessingDoc::OnMulImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDoubleDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double value = dlg.m_constantDouble;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				if (m_inImage[i][j] * value < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < m_inImage[i][j] * value)
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (int)(m_inImage[i][j] * value);
			}
		}
	}
}


void CGrayScaleImageProcessingDoc::OnAndImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	OnMakeDataImage();

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if ((m_inImage[i][j] & m_dataImage[i][j]) < 0)
				m_outImage[i][j] = 0;
			else if (255 < (m_inImage[i][j] & m_dataImage[i][j]))
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (m_inImage[i][j] & m_dataImage[i][j]);
		}
	}
}


void CGrayScaleImageProcessingDoc::OnOrImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	OnMakeDataImage();

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if ((m_inImage[i][j] | m_dataImage[i][j]) < 0)
				m_outImage[i][j] = 0;
			else if (255 < (m_inImage[i][j] | m_dataImage[i][j]))
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (m_inImage[i][j] | m_dataImage[i][j]);
		}
	}
}


void CGrayScaleImageProcessingDoc::OnXorImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	OnMakeDataImage();

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if ((m_inImage[i][j] ^ m_dataImage[i][j]) < 0)
				m_outImage[i][j] = 0;
			else if (255 < (m_inImage[i][j] ^ m_dataImage[i][j]))
				m_outImage[i][j] = 255;
			else
				m_outImage[i][j] = (m_inImage[i][j] ^ m_dataImage[i][j]);
		}
	}
}


void CGrayScaleImageProcessingDoc::OnNotImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++)
			m_outImage[i][j] = 255 - m_inImage[i][j];
}


void CGrayScaleImageProcessingDoc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDoubleDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double gamma = dlg.m_constantDouble;

		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				m_outImage[i][j] = (int)(255 * pow(m_inImage[i][j] / 255.0, gamma));
	}
}


void CGrayScaleImageProcessingDoc::OnCapImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++)
			m_outImage[i][j] = (int)(-255 * pow(m_inImage[i][j] / 127.0 - 1.0, 2) + 255.0);
}


void CGrayScaleImageProcessingDoc::OnCupImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++)
			m_outImage[i][j] = (int)(255.0 * pow(m_inImage[i][j] / 127.0 - 1.0, 2));
}


void CGrayScaleImageProcessingDoc::OnPosterizingImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantBitDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		int value = (int)dlg.m_constantBit;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				for (int k = 1; k < value; k++) {
					if (k == value - 1)
						m_outImage[i][j] = 255;
					else if (m_inImage[i][j] <= 255 / (value - 1) * k) {
						if (k == 1)
							m_outImage[i][j] = 0;
						else
							m_outImage[i][j] = 255 / (value - 2) * (k - 1);

						break;
					}
				}
			}
		}
	}
}


void CGrayScaleImageProcessingDoc::OnStressImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstant2Dlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		int value1 = (int)dlg.m_constantStart, value2 = (int)dlg.m_constantEnd;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				if (value1 <= m_inImage[i][j] && m_inImage[i][j] <= value2)
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = m_inImage[i][j];
			}
		}
	}
}


void CGrayScaleImageProcessingDoc::OnBwImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImage[i][j] < 128)
				m_outImage[i][j] = 0;
			else
				m_outImage[i][j] = 255;
		}
	}
}


void CGrayScaleImageProcessingDoc::OnBwAvgImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	int avg = 0;

	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++)
			avg += m_inImage[i][j];

	avg /= m_inH * m_inW;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImage[i][j] < avg)
				m_outImage[i][j] = 0;
			else
				m_outImage[i][j] = 255;
		}
	}
}


void CGrayScaleImageProcessingDoc::OnBwMedImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 출력 메모리 해제
	OnFree2D(m_outImage, m_outH);
	m_outImage = NULL;
	m_outH = m_outW = 0;
	// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
	m_outH = m_inH;
	m_outW = m_inW;
	// 출력 이미지 메모리 할당
	m_outImage = OnMalloc2D(m_outH, m_outW, 0);
	// *** 진짜 영상 처리 알고리즘 ***
	int med, cnt = 0;

	unsigned char* arr = new unsigned char[m_inH * m_inW];

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			arr[cnt] = m_inImage[i][j];
			cnt++;
		}
	}

	std::sort(arr, arr + cnt);

	med = arr[m_inH * m_inW / 2];

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			if (m_inImage[i][j] < med)
				m_outImage[i][j] = 0;
			else
				m_outImage[i][j] = 255;
		}
	}

	delete[] arr;
}


void CGrayScaleImageProcessingDoc::OnZoomOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantPositiveDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		int scale = dlg.m_constantPositive;
		m_outH = m_inH / scale;
		m_outW = m_inW / scale;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				m_outImage[i / scale][j / scale] = m_inImage[i][j];
	}
}


	void CGrayScaleImageProcessingDoc::OnZoomOutAvgImage()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantPositiveDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			int scale = dlg.m_constantPositive;
			m_outH = m_inH / scale;
			m_outW = m_inW / scale;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			for (int i = 0; i < m_inH; i += scale) {
				for (int j = 0; j < m_inW; j += scale) {
					long long avg = 0;

					for (int n = 0; n < scale; n++)
						for (int m = 0; m < scale; m++)
							avg += m_inImage[i + n][j + m];

					m_outImage[i / scale][j / scale] = avg / (scale * scale);
				}
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnZoomOutMedImage()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantPositiveDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			int scale = dlg.m_constantPositive;
			m_outH = m_inH / scale;
			m_outW = m_inW / scale;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			unsigned char* arr = new unsigned char[scale * scale];

			for (int i = 0; i < m_inH; i += scale) {
				for (int j = 0; j < m_inW; j += scale) {
					int med, cnt = 0;

					for (int n = 0; n < scale; n++) {
						for (int m = 0; m < scale; m++) {
							arr[cnt] = m_inImage[i + n][j + m];
							cnt++;
						}
					}

					std::sort(arr, arr + cnt);
					med = arr[scale * scale / 2];
					m_outImage[i / scale][j / scale] = med;
				}
			}

			delete[] arr;
		}
	}


	void CGrayScaleImageProcessingDoc::OnZoomIn1Image()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantPositiveDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			int scale = dlg.m_constantPositive;
			m_outH = m_inH * scale;
			m_outW = m_inW * scale;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			for (int i = 0; i < m_inH; i++)
				for (int j = 0; j < m_inW; j++)
					m_outImage[i * scale][j * scale] = m_inImage[i][j];
		}
	}


	void CGrayScaleImageProcessingDoc::OnZoomIn2Image()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantPositiveDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			int scale = dlg.m_constantPositive;
			m_outH = m_inH * scale;
			m_outW = m_inW * scale;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			for (int i = 0; i < m_outH; i++)
				for (int j = 0; j < m_outW; j++)
					m_outImage[i][j] = m_inImage[i / scale][j / scale];
		}
	}


	void CGrayScaleImageProcessingDoc::OnZoomInBilinearImage()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantPositiveDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			int scale = dlg.m_constantPositive;
			m_outH = m_inH * scale;
			m_outW = m_inW * scale;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			for (int i = 0; i < m_outH; i++) {
				for (int j = 0; j < m_outW; j++) {
					double rH = (double)i / scale;
					double rW = (double)j / scale;

					int iH = (int)floor(rH);
					int iW = (int)floor(rW);

					double sH = rH - iH;
					double sW = rW - iW;

					if (iH < 0 || m_inH - 1 <= iH || iW < 0 || m_inW - 1 <= iW)
						m_outImage[i][j] = 255;
					else {
						double C1 = (double)m_inImage[iH][iW];
						double C2 = (double)m_inImage[iH][iW + 1];
						double C3 = (double)m_inImage[iH + 1][iW + 1];
						double C4 = (double)m_inImage[iH + 1][iW];

						m_outImage[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);
					}
				}
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnRotate1Image()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantDegreeDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			m_outH = m_inH;
			m_outW = m_inW;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			double degree = dlg.m_constantDegree;
			double radian = -degree * 3.141592 / 180.0;

			for (int i = 0; i < m_inH; i++) {
				for (int j = 0; j < m_inW; j++) {
					int xs = i;
					int ys = j;

					int xd = (int)(cos(radian) * xs - sin(radian) * ys);
					int yd = (int)(sin(radian) * xs + cos(radian) * ys);

					if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW))
						m_outImage[xd][yd] = m_inImage[xs][ys];
				}
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnRotate2Image()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantDegreeDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			m_outH = m_inH;
			m_outW = m_inW;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			double degree = dlg.m_constantDegree;
			double radian = -degree * 3.141592 / 180.0;

			int cx = m_inH / 2;
			int cy = m_inW / 2;

			for (int i = 0; i < m_outH; i++) {
				for (int j = 0; j < m_outW; j++) {
					int xd = i;
					int yd = j;

					int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
					int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));

					xs += cx;
					ys += cy;

					if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
						m_outImage[xd][yd] = m_inImage[xs][ys];
				}
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnRotateZoomInImage()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantScaleDegreeDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			OnFree2D(m_tmpImage, m_tmpH);
			m_tmpImage = NULL;
			m_tmpH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			int scale = dlg.m_constantScale;
			m_outH = m_tmpH = m_inH * scale;
			m_outW = m_tmpW = m_inW * scale;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			m_tmpImage = OnMalloc2D(m_tmpH, m_tmpW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			double degree = dlg.m_constantDegree;
			double radian = -degree * 3.141592 / 180.0;

			// 확대
			for (int i = 0; i < m_outH; i++) {
				for (int j = 0; j < m_outW; j++)
					m_tmpImage[i][j] = m_inImage[i / scale][j / scale];
			}

			// 회전
			int cx = m_tmpH / 2;
			int cy = m_tmpW / 2;

			for (int i = 0; i < m_outH; i++) {
				for (int j = 0; j < m_outW; j++) {
					int xd = i;
					int yd = j;

					int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
					int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));

					xs += cx;
					ys += cy;

					if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
						m_outImage[xd][yd] = m_tmpImage[xs][ys];
				}
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnRotateZoomInBilinearImage()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantScaleDegreeDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			OnFree2D(m_tmpImage, m_tmpH);
			m_tmpImage = NULL;
			m_tmpH = m_tmpW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			int scale = dlg.m_constantScale;
			m_outH = m_tmpH = m_inH * scale;
			m_outW = m_tmpW = m_inW * scale;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			m_tmpImage = OnMalloc2D(m_tmpH, m_tmpW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			double degree = dlg.m_constantDegree;
			double radian = -degree * 3.141592 / 180.0;

			// 확대(양선형 보간)
			for (int i = 0; i < m_outH; i++) {
				for (int j = 0; j < m_outW; j++) {
					double rH = (double)i / scale;
					double rW = (double)j / scale;

					int iH = (int)floor(rH);
					int iW = (int)floor(rW);

					double sH = rH - iH;
					double sW = rW - iW;

					if (iH < 0 || m_inH - 1 <= iH || iW < 0 || m_inW - 1 <= iW)
						m_tmpImage[i][j] = 255;
					else {
						double C1 = (double)m_inImage[iH][iW];
						double C2 = (double)m_inImage[iH][iW + 1];
						double C3 = (double)m_inImage[iH + 1][iW + 1];
						double C4 = (double)m_inImage[iH + 1][iW];

						m_tmpImage[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);
					}
				}
			}

			// 회전
			int cx = m_tmpH / 2;
			int cy = m_tmpW / 2;

			for (int i = 0; i < m_outH; i++) {
				for (int j = 0; j < m_outW; j++) {
					int xd = i;
					int yd = j;

					int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
					int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));

					xs += cx;
					ys += cy;

					if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW))
						m_outImage[xd][yd] = m_tmpImage[xs][ys];
				}
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnMirrorVerImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				m_outImage[i][j] = m_inImage[m_inH - 1 - i][j];
	}


	void CGrayScaleImageProcessingDoc::OnMirrorHorImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				m_outImage[i][j] = m_inImage[i][m_inH - 1 - j];
	}


	void CGrayScaleImageProcessingDoc::OnMoveImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		CConstantHeightWidthDlg dlg;
		if (dlg.DoModal() == IDOK) {
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			m_outH = m_inH;
			m_outW = m_inW;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			int posH = dlg.m_constantHeight, posW = dlg.m_constantWidth;

			for (int i = 0; i < m_inH - posH; i++) {
				for (int j = 0; j < m_inW - posW; j++) {
					int nx = i + posH;
					int ny = j + posW;

					if ((0 <= nx && nx < m_outH) && (0 <= ny && ny < m_outW))
						m_outImage[nx][ny] = m_inImage[i][j];
				}
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnMorphingImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		OnFree2D(m_tmpImage, m_tmpH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		// 모핑할 다른 파일 열기
		CFile File;
		CFileDialog OpenDlg(TRUE, L"raw", NULL, OFN_HIDEREADONLY);

		if (OpenDlg.DoModal() == IDOK) {
			File.Open(OpenDlg.GetPathName(), CFile::modeRead | CFile::typeBinary);

			// 2차원 배열로 사용하기 위함 - 정방형 이미지만 다룸.
			double fLength = (double)File.GetLength();
			double log2Value = log(sqrt(fLength)) / log(2.0);
			if (log2Value != (int)log2Value)
			{
				AfxMessageBox(L"정방향크기의 이미지만 지원함");
				return;
			}

			// (중요!) 입력 이미지 크기 결정 및 메모리 할당
			m_tmpH = m_tmpW = (long)sqrt(fLength);
			m_tmpImage = OnMalloc2D(m_tmpH, m_tmpW, 0); // 메모리 할당

			// 파일 --> 메모리
			for (int i = 0; i < m_tmpH; i++)
				File.Read(m_tmpImage[i], m_tmpW);
		}

		File.Close();
		
		// 모핑
		int tmp;
		double u;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				u = ((i * m_inH) + (j + 1.0)) / (m_inH * m_inW);
				tmp = (int)((1.0 - u) * m_inImage[i][j] + u * m_tmpImage[i][j]);

				if (tmp < 0)
					m_outImage[i][j] = 0;
				else if (255 < tmp)
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmp;
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnHistoStretchImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		int high = m_inImage[0][0], low = m_inImage[0][0];

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				if (m_inImage[i][j] < low)
					low = m_inImage[i][j];

				if (high < m_inImage[i][j])
					high = m_inImage[i][j];
			}
		}

		int px = 0;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				px = (int)((double)(m_inImage[i][j] - low) / (high - low) * 255.0);

				if (px < 0)
					m_outImage[i][j] = 0;
				else if (255 < px)
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = px;
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnEndInImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		int high = m_inImage[0][0], low = m_inImage[0][0];

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				if (m_inImage[i][j] < low)
					low = m_inImage[i][j];

				if (high < m_inImage[i][j])
					high = m_inImage[i][j];
			}
		}

		high -= 50;
		low += 50;

		int px = 0;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				px = (int)((double)(m_inImage[i][j] - low) / (double)(high - low) * 255.0);

				if (px < 0)
					m_outImage[i][j] = 0;
				else if (255 < px)
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = px;
			}
		}
	}


	void CGrayScaleImageProcessingDoc::OnHistoEqualImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		// 1단계 : 빈도 수 세기 (=히스토그램) histo[256]
		int histo[256] = { 0 };

		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				histo[m_inImage[i][j]]++;

		// 2단계 : 누적 히스토그램 생성
		int sumHisto[256] = { 0 };
		sumHisto[0] = histo[0];

		for (int i = 1; i < 256; i++)
			sumHisto[i] = sumHisto[i - 1] + histo[i];

		// 3단계 : 정규화된 히스토그램 생성 normalHisto = sumHisto * (1.0 / (inH * inW)) * 255.0
		double normalHisto[256] = { 0 };

		for (int i = 0; i < 256; i++)
			normalHisto[i] = sumHisto[i] * (1.0 / (m_inH * m_inW)) * 255.0;

		// 입력 배열 --> 출력 배열
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				m_outImage[i][j] = (unsigned char)normalHisto[m_inImage[i][j]];
	}


	void CGrayScaleImageProcessingDoc::OnEmbossImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[3][3] = { { -1.0, 0.0, 0.0}, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } }; // 엠보싱 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++)
					for (int n = 0; n < 3; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 후처리 (마스크 값의 합계에 따라서)
		for (int i = 0; i < m_outH; i++)
			for (int j = 0; j < m_outW; j++)
				tmpOutImage[i][j] += 127.0;

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnBlur1Image()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[3][3] = { { 1.0 / 9, 1.0 / 9, 1.0 / 9 },
			{ 1.0 / 9, 1.0 / 9, 1.0 / 9 },
			{ 1.0 / 9, 1.0 / 9, 1.0 / 9 } }; // 블러링(3x3) 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++)
					for (int n = 0; n < 3; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnBlur2Image()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[9][9]; // 블러링(9x9) 마스크

		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				mask[i][j] = 1.0 / 81;

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 8, m_inW + 8, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 4][j + 4] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(9x9)와 한 점을 중심으로 한 9x9 곱하기
				S = 0.0; // 마스크 818개와 입력값 81개를 각각 곱해서 합한 값

				for (int m = 0; m < 9; m++)
					for (int n = 0; n < 9; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 8);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnSharpImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[3][3] = { { 0.0, -1.0, 0.0 },
			{ -1.0, 5.0, -1.0 },
			{ 0.0, -1.0, 0.0 } }; // 샤프닝 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++)
					for (int n = 0; n < 3; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnSharpHfImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[3][3] = { { -1.0 / 9, -1.0 / 9, -1.0 / 9 },
			{ -1.0 / 9, 8.0 / 9, -1.0 / 9 },
			{ -1.0 / 9, -1.0 / 9, -1.0 / 9 } }; // 샤프닝(고주파) 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++)
					for (int n = 0; n < 3; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n] * 20;

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnSharpLfImage()
	{
		// TODO: 여기에 구현 코드 추가.
		CConstantDoubleDlg dlg;
		if (dlg.DoModal() == IDOK) {
			// 출력 메모리 해제
			OnFree2D(m_outImage, m_outH);
			m_outImage = NULL;
			m_outH = m_outW = 0;
			// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
			m_outH = m_inH;
			m_outW = m_inW;
			// 출력 이미지 메모리 할당
			m_outImage = OnMalloc2D(m_outH, m_outW, 0);
			// *** 진짜 영상 처리 알고리즘 ***
			double alpha = dlg.m_constantDouble;

			double mask[3][3] = { { 1.0 / 9, 1.0 / 9, 1.0 / 9 },
				{ 1.0 / 9, 1.0 / 9, 1.0 / 9 },
				{ 1.0 / 9, 1.0 / 9, 1.0 / 9 } }; // 샤프닝(저주파) 마스크

			// 임시 메모리 할당 (실수형)
			double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
			double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

			// 입력 이미지 -> 임시 입력 이미지
			for (int i = 0; i < m_inH; i++)
				for (int j = 0; j < m_inW; j++)
					tmpInImage[i + 1][j + 1] = m_inImage[i][j];

			// ** 회선 연산
			double S;

			for (int i = 0; i < m_inH; i++) {
				for (int j = 0; j < m_inW; j++) {
					// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
					S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

					for (int m = 0; m < 3; m++)
						for (int n = 0; n < 3; n++)
							S += tmpInImage[i + m][j + n] * mask[m][n];

					tmpOutImage[i][j] = S;
				}
			}

			// 임시 출력 영상 --> 출력 영상
			double unsharp;

			for (int i = 0; i < m_outH; i++) {
				for (int j = 0; j < m_outW; j++) {
					unsharp = alpha * m_inImage[i][j] - tmpOutImage[i][j];

					if (unsharp < 0.0)
						m_outImage[i][j] = 0;
					else if (255.0 < unsharp)
						m_outImage[i][j] = 255;
					else
						m_outImage[i][j] = (unsigned char)unsharp;
				}
			}

			OnFree2DF(tmpInImage, m_inH + 2);
			OnFree2DF(tmpOutImage, m_outH);
		}
	}


	void CGrayScaleImageProcessingDoc::OnGaussianImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[3][3] = { { 1.0 / 16, 1.0 / 8, 1.0 / 16 },
			{ 1.0 / 8, 1.0 / 4, 1.0 / 8 },
			{ 1.0 / 16, 1.0 / 8, 1.0 / 16 } }; // 가우시안 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++)
					for (int n = 0; n < 3; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgeVerImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[3][3] = { { 0.0, 0.0, 0.0 },
			{ -1.0, 1.0, 0.0 },
			{ 0.0, 0.0, 0.0 } }; // 수직 에지 검출 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++)
					for (int n = 0; n < 3; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgeHorImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[3][3] = { { 0.0, -1.0, 0.0 },
				{ 0.0, 1.0, 0.0 },
				{ 0.0, 0.0, 0.0 } }; // 수평 에지 검출 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++)
					for (int n = 0; n < 3; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgeHomogenImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				S = 0.0;

				for (int m = 0; m < 3; m++) {
					for (int n = 0; n < 3; n++) {
						if (S < fabs(tmpInImage[i + 1][j + 1] - tmpInImage[i + m][j + n]))
							S = fabs(tmpInImage[i + 1][j + 1] - tmpInImage[i + m][j + n]);
					}
				}

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgeDiffImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				S = 0.0;

				for (int n = 0; n < 3; n++) {
					if (S < fabs(tmpInImage[i][j + n] - tmpInImage[i + 2][j - n + 2]))
						S = fabs(tmpInImage[i][j + n] - tmpInImage[i + 2][j - n + 2]);
				}

				if (S < fabs(tmpInImage[i + 1][j + 2] - tmpInImage[i + 1][j]))
					S = fabs(tmpInImage[i + 1][j + 2] - tmpInImage[i + 1][j]);

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgeRobertsImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double maskRow[3][3] = { { -1.0, 0.0, 0.0 },
			{ 0.0, 1.0, 0.0 },
			{ 0.0, 0.0, 0.0 } }; // 로버츠 행 에지 검출 마스크

		double maskCol[3][3] = { { 0.0, 0.0, -1.0 },
			{ 0.0, 1.0, 0.0 },
			{ 0.0, 0.0, 0.0 } }; // 로버츠 열 에지 검출 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpRowInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpColInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpRowOutImage = OnMalloc2DF(m_outH, m_outW, 0);
		double** tmpColOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S1, S2;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++) {
					for (int n = 0; n < 3; n++) {
						S1 += tmpRowInImage[i + m][j + n] * maskRow[m][n];
						S2 += tmpColInImage[i + m][j + n] * maskCol[m][n];
					}
				}

				tmpRowOutImage[i][j] = S1;
				tmpColOutImage[i][j] = S2;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				S1 = tmpRowOutImage[i][j];
				S2 = tmpColOutImage[i][j];

				if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));
			}
		}

		OnFree2DF(tmpRowInImage, m_inH + 2);
		OnFree2DF(tmpColInImage, m_inH + 2);
		OnFree2DF(tmpRowOutImage, m_outH);
		OnFree2DF(tmpColOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgePrewittImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double maskRow[3][3] = { { -1.0, -1.0, -1.0 },
			{ 0.0, 0.0, 0.0 },
			{ 1.0, 1.0, 1.0 } }; // 프리윗 행 에지 검출 마스크

		double maskCol[3][3] = { { 1.0, 0.0, -1.0 },
			{ 1.0, 0.0, -1.0 },
			{ 1.0, 0.0, -1.0 } }; // 프리윗 열 에지 검출 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpRowInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpColInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpRowOutImage = OnMalloc2DF(m_outH, m_outW, 0);
		double** tmpColOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S1, S2;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++) {
					for (int n = 0; n < 3; n++) {
						S1 += tmpRowInImage[i + m][j + n] * maskRow[m][n];
						S2 += tmpColInImage[i + m][j + n] * maskCol[m][n];
					}
				}

				tmpRowOutImage[i][j] = S1;
				tmpColOutImage[i][j] = S2;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				S1 = tmpRowOutImage[i][j];
				S2 = tmpColOutImage[i][j];

				if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));
			}
		}

		OnFree2DF(tmpRowInImage, m_inH + 2);
		OnFree2DF(tmpColInImage, m_inH + 2);
		OnFree2DF(tmpRowOutImage, m_outH);
		OnFree2DF(tmpColOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgeSobelImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double maskRow[3][3] = { { -1.0, -2.0, -1.0 },
			{ 0.0, 0.0, 0.0 },
			{ 1.0, 2.0, 1.0 } }; // 소벨 행 에지 검출 마스크

		double maskCol[3][3] = { { 1.0, 0.0, -1.0 },
			{ 2.0, 0.0, -2.0 },
			{ 1.0, 0.0, -1.0 } }; // 소벨 열 에지 검출 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpRowInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpColInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpRowOutImage = OnMalloc2DF(m_outH, m_outW, 0);
		double** tmpColOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpRowInImage[i + 1][j + 1] = tmpColInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S1, S2;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++) {
					for (int n = 0; n < 3; n++) {
						S1 += tmpRowInImage[i + m][j + n] * maskRow[m][n];
						S2 += tmpColInImage[i + m][j + n] * maskCol[m][n];
					}
				}

				tmpRowOutImage[i][j] = S1;
				tmpColOutImage[i][j] = S2;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				S1 = tmpRowOutImage[i][j];
				S2 = tmpColOutImage[i][j];

				if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));
			}
		}

		OnFree2DF(tmpRowInImage, m_inH + 2);
		OnFree2DF(tmpColInImage, m_inH + 2);
		OnFree2DF(tmpRowOutImage, m_outH);
		OnFree2DF(tmpColOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgeLaplacianImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[3][3] = { { 0.0, -1.0, 0.0 },
			{ -1.0, 4.0, -1.0 },
			{ 0.0, -1.0, 0.0 } }; // 라플라시안 에지 검출 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 2, m_inW + 2, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < 3; m++)
					for (int n = 0; n < 3; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 2);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgeLogImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[5][5] = { { 0.0, 0.0, -1.0, 0.0, 0.0 },
			{ 0.0, -1.0, -2.0, -1.0, 0.0 },
			{ -1.0, -2.0, 16.0, -2.0, -1.0 },
			{ 0.0, -1.0, -2.0, -1.0, 0.0 },
			{ 0.0, 0.0, -1.0, 0.0, 0.0 } }; // LoG 에지 검출 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 4, m_inW + 4, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(5x5)와 한 점을 중심으로 한 5x5 곱하기
				S = 0.0; // 마스크 25개와 입력값 25개를 각각 곱해서 합한 값

				for (int m = 0; m < 5; m++)
					for (int n = 0; n < 5; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 4);
		OnFree2DF(tmpOutImage, m_outH);
	}


	void CGrayScaleImageProcessingDoc::OnEdgeDogImage()
	{
		// TODO: 여기에 구현 코드 추가.
		// 출력 메모리 해제
		OnFree2D(m_outImage, m_outH);
		m_outImage = NULL;
		m_outH = m_outW = 0;
		// (중요!) 출력 이미지의 크기를 결정 --> 알고리즘에 의존
		m_outH = m_inH;
		m_outW = m_inW;
		// 출력 이미지 메모리 할당
		m_outImage = OnMalloc2D(m_outH, m_outW, 0);
		// *** 진짜 영상 처리 알고리즘 ***
		double mask[7][7] = { { 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0 },
			{ 0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0 },
			{ -1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0 },
			{ -1.0, -3.0, 5.0, 16.0, 5.0, -3.0, -1.0 },
			{ -1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0 },
			{ 0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0 },
			{ 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0 } }; // DoG 에지 검출 마스크

		// 임시 메모리 할당 (실수형)
		double** tmpInImage = OnMalloc2DF(m_inH + 6, m_inW + 6, 127);
		double** tmpOutImage = OnMalloc2DF(m_outH, m_outW, 0);

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++)
				tmpInImage[i + 1][j + 1] = m_inImage[i][j];

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(7x7)와 한 점을 중심으로 한 7x7 곱하기
				S = 0.0; // 마스크 49개와 입력값 49개를 각각 곱해서 합한 값

				for (int m = 0; m < 7; m++)
					for (int n = 0; n < 7; n++)
						S += tmpInImage[i + m][j + n] * mask[m][n];

				tmpOutImage[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				if (tmpOutImage[i][j] < 0.0)
					m_outImage[i][j] = 0;
				else if (255.0 < tmpOutImage[i][j])
					m_outImage[i][j] = 255;
				else
					m_outImage[i][j] = (unsigned char)tmpOutImage[i][j];
			}
		}

		OnFree2DF(tmpInImage, m_inH + 6);
		OnFree2DF(tmpOutImage, m_outH);
	}
