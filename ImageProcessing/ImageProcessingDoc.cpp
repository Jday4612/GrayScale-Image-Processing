
// ImageProcessingDoc.cpp: CImageProcessingDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"

#include <propkey.h>

#include <algorithm>
#include "ConstantDlg.h"
#include "ConstantDecDlg.h"
#include "ConstantBitDlg.h"
#include "ConstantIntervalDlg.h"
#include "ConstantPositiveDlg.h"
#include "ConstantDegreeDlg.h"
#include "ConstantScaleDegreeDlg.h"
#include "ConstantHeightWidthDlg.h"
#include "ColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CImageProcessingDoc 생성/소멸

CImageProcessingDoc::CImageProcessingDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
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
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
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

// CImageProcessingDoc 진단

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc 명령


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// 기존 메모리 해제
	if (m_inImageR != NULL) {
		OnFree2D(m_inImageR, m_inH);
		OnFree2D(m_inImageG, m_inH);
		OnFree2D(m_inImageB, m_inH);

		m_inImageR = m_inImageG = m_inImageB = NULL;
		m_inH = m_inW = 0;

		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);

		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CImage image;
	image.Load(lpszPathName);
	// (중요!) 입력 영상 크기 알아내기~
	m_inH = image.GetHeight();
	m_inW = image.GetWidth();
	// 메모리 할당
	m_inImageR = OnMalloc2D(m_inH, m_inW);
	m_inImageG = OnMalloc2D(m_inH, m_inW);
	m_inImageB = OnMalloc2D(m_inH, m_inW);
	// CImage의 객체값 --> 메모리
	COLORREF  px;

	for (int i=0; i<m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			px = image.GetPixel(j, i);
			m_inImageR[i][j] = GetRValue(px);
			m_inImageG[i][j] = GetGValue(px);
			m_inImageB[i][j] = GetBValue(px);
		}

	return TRUE;
}


unsigned char** CImageProcessingDoc::OnMalloc2D(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	unsigned char** memory;
	memory = new unsigned char* [h];

	for (int i = 0; i < h; i++)
		memory[i] = new unsigned char[w];

	return memory;
}


double** CImageProcessingDoc::OnMalloc2D_double(int h, int w)
{
	// TODO: 여기에 구현 코드 추가.
	double** memory;
	memory = new double* [h];

	for (int i = 0; i < h; i++)
		memory[i] = new double[w];

	return memory;
}


template <typename T>
void CImageProcessingDoc::OnFree2D(T** memory, int h)
{
	// TODO: 여기에 구현 코드 추가.
	if (memory == NULL)
		return;

	for (int i = 0; i < h; i++)
		delete[] memory[i];

	delete[] memory;
}


void CImageProcessingDoc::OnFreeOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_outImageR != NULL) {
		OnFree2D(m_outImageR, m_outH);
		OnFree2D(m_outImageG, m_outH);
		OnFree2D(m_outImageB, m_outH);

		m_outImageR = m_outImageG = m_outImageB = NULL;
		m_outH = m_outW = 0;
	}
}


void CImageProcessingDoc::OnMakeDataImage()
{
	// TODO: 여기에 구현 코드 추가.
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


void CImageProcessingDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	OnFree2D(m_inImageR, m_inH);
	OnFree2D(m_inImageG, m_inH);
	OnFree2D(m_inImageB, m_inH);

	OnFree2D(m_outImageR, m_outH);
	OnFree2D(m_outImageG, m_outH);
	OnFree2D(m_outImageB, m_outH);

	OnFree2D(m_dataImage, m_dataH);

	CDocument::OnCloseDocument();
}


BOOL CImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_outImageR == NULL)
		return FALSE;

	CImage image;
	image.Create(m_outW, m_outH, 32);

	unsigned char R, G, B;
	COLORREF px;

	for(int i=0; i<m_outW; i++) 
		for (int j = 0; j < m_outH; j++) {
			R = m_outImageR[j][i];
			G = m_outImageG[j][i];
			B = m_outImageB[j][i];
			px = RGB(R, G, B);
			image.SetPixel(i, j, px);
		}

	image.Save(lpszPathName, Gdiplus::ImageFormatPNG);
	MessageBox(NULL, L"저장", L"성공", NULL);

	return TRUE;
}


void CImageProcessingDoc::OnEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = m_inImageR[i][j];
			m_outImageG[i][j] = m_inImageG[i][j];
			m_outImageB[i][j] = m_inImageB[i][j];
		}
	}
}


void CImageProcessingDoc::OnGrayScale()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	double avg;
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			avg = (m_inImageR[i][j] + m_inImageG[i][j] + m_inImageB[i][j]) / 3.0;
			m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)avg;
		}
	}
}


void CImageProcessingDoc::OnAddImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		int value = (int)dlg.m_constant, px = 0;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// R
				px = m_inImageR[i][j] + value;

				if (px < 0)
					m_outImageR[i][j] = 0;
				else if (255 < px)
					m_outImageR[i][j] = 255;
				else
					m_outImageR[i][j] = px;

				// G
				px = m_inImageG[i][j] + value;

				if (px < 0)
					m_outImageG[i][j] = 0;
				else if (255 < px)
					m_outImageG[i][j] = 255;
				else
					m_outImageG[i][j] = px;

				// B
				px = m_inImageB[i][j] + value;

				if (px < 0)
					m_outImageB[i][j] = 0;
				else if (255 < px)
					m_outImageB[i][j] = 255;
				else
					m_outImageB[i][j] = px;
			}
		}
	}
}


void CImageProcessingDoc::OnMulImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDecDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		double value = (double)dlg.m_constantDec, px = 0.0;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// R
				px = m_inImageR[i][j] * value;

				if (px < 0.0)
					m_outImageR[i][j] = 0;
				else if (255.0 < px)
					m_outImageR[i][j] = 255;
				else
					m_outImageR[i][j] = (unsigned char)px;

				// G
				px = m_inImageG[i][j] * value;

				if (px < 0.0)
					m_outImageG[i][j] = 0;
				else if (255.0 < px)
					m_outImageG[i][j] = 255;
				else
					m_outImageG[i][j] = (unsigned char)px;

				// B
				px = m_inImageB[i][j] * value;

				if (px < 0.0)
					m_outImageB[i][j] = 0;
				else if (255.0 < px)
					m_outImageB[i][j] = 255;
				else
					m_outImageB[i][j] = (unsigned char)px;
			}
		}
	}
}


void CImageProcessingDoc::OnAndImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	OnFree2D(m_dataImage, m_inH);
	m_dataImage = NULL;
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_dataH = m_inH;
	m_outW = m_dataW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	m_dataImage = OnMalloc2D(m_inH, m_inW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_dataH; i++)
		for (int j = 0; j < m_dataW; j++)
			m_dataImage[i][j] = 0;

	OnMakeDataImage();
	int px = 0;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			px = (m_inImageR[i][j] & m_dataImage[i][j]);

			if (px < 0)
				m_outImageR[i][j] = 0;
			else if (255 < px)
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = px;

			// G
			px = (m_inImageG[i][j] & m_dataImage[i][j]);

			if (px < 0)
				m_outImageG[i][j] = 0;
			else if (255 < px)
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = px;

			// B
			px = (m_inImageB[i][j] & m_dataImage[i][j]);

			if (px < 0)
				m_outImageB[i][j] = 0;
			else if (255 < px)
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = px;
		}
	}
}


void CImageProcessingDoc::OnOrImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	OnFree2D(m_dataImage, m_inH);
	m_dataImage = NULL;
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_dataH = m_inH;
	m_outW = m_dataW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	m_dataImage = OnMalloc2D(m_inH, m_inW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_dataH; i++)
		for (int j = 0; j < m_dataW; j++)
			m_dataImage[i][j] = 0;

	OnMakeDataImage();
	int px = 0;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			px = (m_inImageR[i][j] | m_dataImage[i][j]);

			if (px < 0)
				m_outImageR[i][j] = 0;
			else if (255 < px)
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = px;

			// G
			px = (m_inImageG[i][j] | m_dataImage[i][j]);

			if (px < 0)
				m_outImageG[i][j] = 0;
			else if (255 < px)
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = px;

			// B
			px = (m_inImageB[i][j] | m_dataImage[i][j]);

			if (px < 0)
				m_outImageB[i][j] = 0;
			else if (255 < px)
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = px;
		}
	}
}


void CImageProcessingDoc::OnXorImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	OnFree2D(m_dataImage, m_inH);
	m_dataImage = NULL;
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_dataH = m_inH;
	m_outW = m_dataW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	m_dataImage = OnMalloc2D(m_inH, m_inW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_dataH; i++)
		for (int j = 0; j < m_dataW; j++)
			m_dataImage[i][j] = 0;

	OnMakeDataImage();
	int px = 0;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			px = (m_inImageR[i][j] ^ m_dataImage[i][j]);

			if (px < 0)
				m_outImageR[i][j] = 0;
			else if (255 < px)
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = px;

			// G
			px = (m_inImageG[i][j] ^ m_dataImage[i][j]);

			if (px < 0)
				m_outImageG[i][j] = 0;
			else if (255 < px)
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = px;

			// B
			px = (m_inImageB[i][j] ^ m_dataImage[i][j]);

			if (px < 0)
				m_outImageB[i][j] = 0;
			else if (255 < px)
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = px;
		}
	}
}


void CImageProcessingDoc::OnNotImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = 255 - m_inImageR[i][j];
			m_outImageG[i][j] = 255 - m_inImageG[i][j];
			m_outImageB[i][j] = 255 - m_inImageB[i][j];
		}
	}
}


void CImageProcessingDoc::OnGammaImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDecDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		double gamma = (double)dlg.m_constantDec, px = 0.0;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// R
				px = 255 * pow(m_inImageR[i][j] / 255.0, gamma);

				if (px < 0.0)
					m_outImageR[i][j] = 0;
				else if (255.0 < px)
					m_outImageR[i][j] = 255;
				else
					m_outImageR[i][j] = (unsigned char)px;

				// G
				px = 255 * pow(m_inImageG[i][j] / 255.0, gamma);

				if (px < 0.0)
					m_outImageG[i][j] = 0;
				else if (255.0 < px)
					m_outImageG[i][j] = 255;
				else
					m_outImageG[i][j] = (unsigned char)px;

				// B
				px = 255 * pow(m_inImageB[i][j] / 255.0, gamma);

				if (px < 0.0)
					m_outImageB[i][j] = 0;
				else if (255.0 < px)
					m_outImageB[i][j] = 255;
				else
					m_outImageB[i][j] = (unsigned char)px;
			}
		}
	}
}


void CImageProcessingDoc::OnCapImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = (int)(-255 * pow(m_inImageR[i][j] / 127.0 - 1.0, 2) + 255.0);
			m_outImageG[i][j] = (int)(-255 * pow(m_inImageG[i][j] / 127.0 - 1.0, 2) + 255.0);
			m_outImageB[i][j] = (int)(-255 * pow(m_inImageB[i][j] / 127.0 - 1.0, 2) + 255.0);
		}
	}
}


void CImageProcessingDoc::OnCupImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = (int)(255.0 * pow(m_inImageR[i][j] / 127.0 - 1.0, 2));
			m_outImageG[i][j] = (int)(255.0 * pow(m_inImageG[i][j] / 127.0 - 1.0, 2));
			m_outImageB[i][j] = (int)(255.0 * pow(m_inImageB[i][j] / 127.0 - 1.0, 2));
		}
	}
}


void CImageProcessingDoc::OnPosterizingImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantBitDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		int bit = (int)dlg.m_constantBit;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// R
				for (int k = 1; k < bit; k++) {
					if (k == (bit - 1))
						m_outImageR[i][j] = 255;
					else if (m_inImageR[i][j] <= 255 / (bit - 1) * k) {
						if (k == 1)
							m_outImageR[i][j] = 0;
						else
							m_outImageR[i][j] = 255 / (bit - 2) * (k - 1);

						break;
					}
				}

				//G
				for (int k = 1; k < bit; k++) {
					if (k == (bit - 1))
						m_outImageG[i][j] = 255;
					else if (m_inImageG[i][j] <= 255 / (bit - 1) * k) {
						if (k == 1)
							m_outImageG[i][j] = 0;
						else
							m_outImageG[i][j] = 255 / (bit - 2) * (k - 1);

						break;
					}
				}

				//B
				for (int k = 1; k < bit; k++) {
					if (k == (bit - 1))
						m_outImageB[i][j] = 255;
					else if (m_inImageB[i][j] <= 255 / (bit - 1) * k) {
						if (k == 1)
							m_outImageB[i][j] = 0;
						else
							m_outImageB[i][j] = 255 / (bit - 2) * (k - 1);

						break;
					}
				}
			}
		}
	}
}


void CImageProcessingDoc::OnStressImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantIntervalDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		int start = (int)dlg.m_constantStart, end = (int)dlg.m_constantEnd, px = 0;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// R
				if (start <= m_inImageR[i][j] && m_inImageR[i][j] <= end)
					m_outImageR[i][j] = 255;
				else
					m_outImageR[i][j] = m_inImageR[i][j];

				// G
				if (start <= m_inImageG[i][j] && m_inImageG[i][j] <= end)
					m_outImageG[i][j] = 255;
				else
					m_outImageG[i][j] = m_inImageG[i][j];

				// B
				if (start <= m_inImageB[i][j] && m_inImageB[i][j] <= end)
					m_outImageB[i][j] = 255;
				else
					m_outImageB[i][j] = m_inImageB[i][j];
			}
		}
	}
}


void CImageProcessingDoc::OnBwImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			if (m_inImageR[i][j] < 128)
				m_outImageR[i][j] = 0;
			else
				m_outImageR[i][j] = 255;

			// G
			if (m_inImageG[i][j] < 128)
				m_outImageG[i][j] = 0;
			else
				m_outImageG[i][j] = 255;

			// B
			if (m_inImageB[i][j] < 128)
				m_outImageB[i][j] = 0;
			else
				m_outImageB[i][j] = 255;
		}
	}
}


void CImageProcessingDoc::OnBwAvgImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	long long avgR = 0, avgG = 0, avgB = 0;

	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			avgR += m_inImageR[i][j];
			avgG += m_inImageG[i][j];
			avgB += m_inImageB[i][j];
		}

	avgR /= m_inH * m_inW;
	avgG /= m_inH * m_inW;
	avgB /= m_inH * m_inW;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			if (m_inImageR[i][j] < avgR)
				m_outImageR[i][j] = 0;
			else
				m_outImageR[i][j] = 255;

			// G
			if (m_inImageG[i][j] < avgG)
				m_outImageG[i][j] = 0;
			else
				m_outImageG[i][j] = 255;

			// B
			if (m_inImageB[i][j] < avgB)
				m_outImageB[i][j] = 0;
			else
				m_outImageB[i][j] = 255;
		}
	}
}


void CImageProcessingDoc::OnBwMedImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int medR, medG, medB, cnt = 0;

	unsigned char* arrR = new unsigned char[m_inH * m_inW];
	unsigned char* arrG = new unsigned char[m_inH * m_inW];
	unsigned char* arrB = new unsigned char[m_inH * m_inW];

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			arrR[cnt] = m_inImageR[i][j];
			arrG[cnt] = m_inImageG[i][j];
			arrB[cnt] = m_inImageB[i][j];
			cnt++;
		}
	}

	std::sort(arrR, arrR + cnt);
	std::sort(arrG, arrG + cnt);
	std::sort(arrB, arrB + cnt);

	medR = arrR[(int)(m_inH * m_inW / 2)];
	medG = arrG[(int)(m_inH * m_inW / 2)];
	medB = arrB[(int)(m_inH * m_inW / 2)];

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			if (m_inImageR[i][j] < medR)
				m_outImageR[i][j] = 0;
			else
				m_outImageR[i][j] = 255;

			// G
			if (m_inImageG[i][j] < medG)
				m_outImageG[i][j] = 0;
			else
				m_outImageG[i][j] = 255;

			// B
			if (m_inImageB[i][j] < medB)
				m_outImageB[i][j] = 0;
			else
				m_outImageB[i][j] = 255;
		}
	}

	delete[] arrR;
	delete[] arrG;
	delete[] arrB;
}


void CImageProcessingDoc::OnZoomOutImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantPositiveDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		int scale = dlg.m_constantPositive;
		m_outH = m_inH / scale;
		m_outW = m_inW / scale;

		if (m_inH % 2 == 1)
			m_outH++;
		if (m_inW % 2 == 1)
			m_outW++;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				m_outImageR[i / scale][j / scale] = m_inImageR[i][j];
				m_outImageG[i / scale][j / scale] = m_inImageG[i][j];
				m_outImageB[i / scale][j / scale] = m_inImageB[i][j];
			}
		}
	}
}


void CImageProcessingDoc::OnZoomOutAvgImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantPositiveDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		int scale = dlg.m_constantPositive;
		m_outH = m_inH / scale;
		m_outW = m_inW / scale;

		if (m_inH % 2 == 1)
			m_outH++;
		if (m_inW % 2 == 1)
			m_outW++;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		for (int i = 0; i < m_inH; i += scale) {
			for (int j = 0; j < m_inW; j += scale) {
				int avgR = 0, avgG = 0, avgB = 0, cnt = 0;

				for (int n = 0; n < scale; n++) {
					if (m_inH <= i + n)
						break;

					for (int m = 0; m < scale; m++) {
						if (m_inW <= j + m)
							break;

						avgR += m_inImageR[i + n][j + m];
						avgG += m_inImageG[i + n][j + m];
						avgB += m_inImageB[i + n][j + m];
						cnt++;
					}
				}

				m_outImageR[i / scale][j / scale] = avgR / cnt;
				m_outImageG[i / scale][j / scale] = avgG / cnt;
				m_outImageB[i / scale][j / scale] = avgB / cnt;
			}
		}
	}
}


void CImageProcessingDoc::OnZoomOutMedImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantPositiveDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		int scale = dlg.m_constantPositive;
		m_outH = m_inH / scale;
		m_outW = m_inW / scale;

		if (m_inH % 2 == 1)
			m_outH++;
		if (m_inW % 2 == 1)
			m_outW++;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		unsigned char* arrR = new unsigned char[scale * scale];
		unsigned char* arrG = new unsigned char[scale * scale];
		unsigned char* arrB = new unsigned char[scale * scale];

		for (int i = 0; i < m_inH; i += scale) {
			for (int j = 0; j < m_inW; j += scale) {
				int medR, medG, medB, cnt = 0;

				for (int n = 0; n < scale; n++) {
					if (m_inH <= i + n)
						break;

					for (int m = 0; m < scale; m++) {
						if (m_inW <= j + m)
							break;

						arrR[cnt] = m_inImageR[i + n][j + m];
						arrG[cnt] = m_inImageG[i + n][j + m];
						arrB[cnt] = m_inImageB[i + n][j + m];
						cnt++;
					}
				}

				std::sort(arrR, arrR + cnt);
				std::sort(arrG, arrG + cnt);
				std::sort(arrB, arrB + cnt);

				medR = arrR[cnt / 2];
				medG = arrG[cnt / 2];
				medB = arrB[cnt / 2];

				m_outImageR[i / scale][j / scale] = medR;
				m_outImageG[i / scale][j / scale] = medG;
				m_outImageB[i / scale][j / scale] = medB;
			}
		}

		delete[] arrR;
		delete[] arrG;
		delete[] arrB;
	}
}


void CImageProcessingDoc::OnZoomIn1Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantPositiveDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		int scale = dlg.m_constantPositive;
		m_outH = m_inH * scale;
		m_outW = m_inW * scale;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				m_outImageR[i * scale][j * scale] = m_inImageR[i][j];
				m_outImageG[i * scale][j * scale] = m_inImageG[i][j];
				m_outImageB[i * scale][j * scale] = m_inImageB[i][j];
			}
		}
	}
}


void CImageProcessingDoc::OnZoomIn2Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantPositiveDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		int scale = dlg.m_constantPositive;
		m_outH = m_inH * scale;
		m_outW = m_inW * scale;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				m_outImageR[i][j] = m_inImageR[i / scale][j / scale];
				m_outImageG[i][j] = m_inImageG[i / scale][j / scale];
				m_outImageB[i][j] = m_inImageB[i / scale][j / scale];
			}
		}
	}
}


void CImageProcessingDoc::OnZoomInBilinearImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantPositiveDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		int scale = dlg.m_constantPositive;
		m_outH = m_inH * scale;
		m_outW = m_inW * scale;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				double rH = (double)i / scale;
				double rW = (double)j / scale;

				int iH = (int)floor(rH);
				int iW = (int)floor(rW);

				double sH = rH - iH;
				double sW = rW - iW;

				if (iH < 0 || m_inH - 1 <= iH || iW < 0 || m_inW - 1 <= iW)
					m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = 255;
				else {
					// R
					double C1 = (double)m_inImageR[iH][iW];
					double C2 = (double)m_inImageR[iH][iW + 1];
					double C3 = (double)m_inImageR[iH + 1][iW + 1];
					double C4 = (double)m_inImageR[iH + 1][iW];

					m_outImageR[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);

					// G
					C1 = (double)m_inImageG[iH][iW];
					C2 = (double)m_inImageG[iH][iW + 1];
					C3 = (double)m_inImageG[iH + 1][iW + 1];
					C4 = (double)m_inImageG[iH + 1][iW];

					m_outImageG[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);

					// B
					C1 = (double)m_inImageB[iH][iW];
					C2 = (double)m_inImageB[iH][iW + 1];
					C3 = (double)m_inImageB[iH + 1][iW + 1];
					C4 = (double)m_inImageB[iH + 1][iW];

					m_outImageB[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);
				}
			}
		}
	}
}


void CImageProcessingDoc::OnRotate1Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDegreeDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		double degree = dlg.m_constantDegree;
		double radian = -degree * 3.141592 / 180.0;

		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++) {
				m_outImageR[i][j] = 0;
				m_outImageG[i][j] = 0;
				m_outImageB[i][j] = 0;
			}

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				int xs = i;
				int ys = j;

				int xd = (int)(cos(radian) * xs - sin(radian) * ys);
				int yd = (int)(sin(radian) * xs + cos(radian) * ys);

				if ((0 <= xd && xd < m_outH) && (0 <= yd && yd < m_outW)) {
					m_outImageR[xd][yd] = m_inImageR[xs][ys];
					m_outImageG[xd][yd] = m_inImageG[xs][ys];
					m_outImageB[xd][yd] = m_inImageB[xs][ys];
				}
			}
		}
	}
}


void CImageProcessingDoc::OnRotate2Image()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDegreeDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		double degree = dlg.m_constantDegree;
		double radian = -degree * 3.141592 / 180.0;

		int cx = m_inH / 2;
		int cy = m_inW / 2;

		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++) {
				m_outImageR[i][j] = 0;
				m_outImageG[i][j] = 0;
				m_outImageB[i][j] = 0;
			}

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				int xd = i;
				int yd = j;

				int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
				int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));

				xs += cx;
				ys += cy;

				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW)) {
					m_outImageR[xd][yd] = m_inImageR[xs][ys];
					m_outImageG[xd][yd] = m_inImageG[xs][ys];
					m_outImageB[xd][yd] = m_inImageB[xs][ys];
				}
			}
		}
	}
}


void CImageProcessingDoc::OnRotateZoomInImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantScaleDegreeDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		int scale = dlg.m_constantScale;
		int tmpH, tmpW;

		m_outH = tmpH = m_inH * scale;
		m_outW = tmpW = m_inW * scale;
		// 메모리 할당
		unsigned char** tmpImageR = NULL, ** tmpImageG = NULL, ** tmpImageB = NULL;

		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		tmpImageR = OnMalloc2D(tmpH, tmpW);
		tmpImageG = OnMalloc2D(tmpH, tmpW);
		tmpImageB = OnMalloc2D(tmpH, tmpW);
		// ** 진짜 영상처리 알고리즘 **
		double degree = dlg.m_constantDegree;
		double radian = -degree * 3.141592 / 180.0;

		// 확대
		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				tmpImageR[i][j] = m_inImageR[i / scale][j / scale];
				tmpImageG[i][j] = m_inImageG[i / scale][j / scale];
				tmpImageB[i][j] = m_inImageB[i / scale][j / scale];
			}
		}

		// 회전
		int cx = tmpH / 2;
		int cy = tmpW / 2;

		for (int i = 0; i < m_outH; i++)
			for (int j = 0; j < m_outW; j++) {
				m_outImageR[i][j] = 0;
				m_outImageG[i][j] = 0;
				m_outImageB[i][j] = 0;
			}

		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				int xd = i;
				int yd = j;

				int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
				int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));

				xs += cx;
				ys += cy;

				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW)) {
					m_outImageR[xd][yd] = tmpImageR[xs][ys];
					m_outImageG[xd][yd] = tmpImageG[xs][ys];
					m_outImageB[xd][yd] = tmpImageB[xs][ys];
				}
			}
		}

		for (int i = 0; i < tmpH; i++) {
			delete[] tmpImageR[i];
			delete[] tmpImageG[i];
			delete[] tmpImageB[i];
		}

		delete[] tmpImageR;
		delete[] tmpImageG;
		delete[] tmpImageB;
	}
}


void CImageProcessingDoc::OnRotateZoomInBilinearImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantScaleDegreeDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		int scale = dlg.m_constantScale;
		int tmpH, tmpW;

		m_outH = tmpH = m_inH * scale;
		m_outW = tmpW = m_inW * scale;
		// 메모리 할당
		unsigned char** tmpImageR = NULL, ** tmpImageG = NULL, ** tmpImageB = NULL;

		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);

		tmpImageR = OnMalloc2D(tmpH, tmpW);
		tmpImageG = OnMalloc2D(tmpH, tmpW);
		tmpImageB = OnMalloc2D(tmpH, tmpW);
		// ** 진짜 영상처리 알고리즘 **
		double degree = dlg.m_constantDegree;
		double radian = -degree * 3.141592 / 180.0;

		// 확대(양선형 보간)
		for (int i = 0; i < tmpH; i++) {
			for (int j = 0; j < tmpW; j++) {
				double rH = (double)i / scale;
				double rW = (double)j / scale;

				int iH = (int)floor(rH);
				int iW = (int)floor(rW);

				double sH = rH - iH;
				double sW = rW - iW;

				if (iH < 0 || m_inH - 1 <= iH || iW < 0 || m_inW - 1 <= iW)
					tmpImageR[i][j] = tmpImageG[i][j] = tmpImageB[i][j] = 255;
				else {
					// R
					double C1 = (double)m_inImageR[iH][iW];
					double C2 = (double)m_inImageR[iH][iW + 1];
					double C3 = (double)m_inImageR[iH + 1][iW + 1];
					double C4 = (double)m_inImageR[iH + 1][iW];

					tmpImageR[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);

					// G
					C1 = (double)m_inImageG[iH][iW];
					C2 = (double)m_inImageG[iH][iW + 1];
					C3 = (double)m_inImageG[iH + 1][iW + 1];
					C4 = (double)m_inImageG[iH + 1][iW];

					tmpImageG[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);

					// B
					C1 = (double)m_inImageB[iH][iW];
					C2 = (double)m_inImageB[iH][iW + 1];
					C3 = (double)m_inImageB[iH + 1][iW + 1];
					C4 = (double)m_inImageB[iH + 1][iW];

					tmpImageB[i][j] = (unsigned char)(C1 * (1 - sH) * (1 - sW) + C2 * sW * (1 - sH) + C3 * sW * sH + C4 * (1 - sW) * sH);
				}
			}
		}

		// 회전
		int cx = tmpH / 2;
		int cy = tmpW / 2;

		for (int i = 0; i < m_outH; i++)
			for (int j = 0; j < m_outW; j++) {
				m_outImageR[i][j] = 0;
				m_outImageG[i][j] = 0;
				m_outImageB[i][j] = 0;
			}

		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				int xd = i;
				int yd = j;

				int xs = (int)(cos(radian) * (xd - cx) + sin(radian) * (yd - cy));
				int ys = (int)(-sin(radian) * (xd - cx) + cos(radian) * (yd - cy));

				xs += cx;
				ys += cy;

				if ((0 <= xs && xs < m_outH) && (0 <= ys && ys < m_outW)) {
					m_outImageR[xd][yd] = tmpImageR[xs][ys];
					m_outImageG[xd][yd] = tmpImageG[xs][ys];
					m_outImageB[xd][yd] = tmpImageB[xs][ys];
				}
			}
		}

		for (int i = 0; i < tmpH; i++) {
			delete[] tmpImageR[i];
			delete[] tmpImageG[i];
			delete[] tmpImageB[i];
		}

		delete[] tmpImageR;
		delete[] tmpImageG;
		delete[] tmpImageB;
	}
}


void CImageProcessingDoc::OnMirrorVerImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = m_inImageR[m_inH - 1 - i][j];
			m_outImageG[i][j] = m_inImageG[m_inH - 1 - i][j];
			m_outImageB[i][j] = m_inImageB[m_inH - 1 - i][j];
		}
	}
}


void CImageProcessingDoc::OnMirrorHorImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = m_inImageR[i][m_inW - 1 - j];
			m_outImageG[i][j] = m_inImageG[i][m_inW - 1 - j];
			m_outImageB[i][j] = m_inImageB[i][m_inW - 1 - j];
		}
	}
}


void CImageProcessingDoc::OnMoveImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantHeightWidthDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		int posH = dlg.m_constantHeight, posW = dlg.m_constantWidth;

		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++) {
				m_outImageR[i][j] = 0;
				m_outImageG[i][j] = 0;
				m_outImageB[i][j] = 0;
			}

		for (int i = 0; i < m_inH - posH; i++) {
			for (int j = 0; j < m_inW - posW; j++) {
				int nx = i + posH;
				int ny = j + posW;

				if ((0 <= nx && nx < m_outH) && (0 <= ny && ny < m_outW)) {
					m_outImageR[nx][ny] = m_inImageR[i][j];
					m_outImageG[nx][ny] = m_inImageG[i][j];
					m_outImageB[nx][ny] = m_inImageB[i][j];
				}
			}
		}
	}
}


void CImageProcessingDoc::OnMorphingImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	int tmpH, tmpW;

	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	unsigned char** tmpImageR = NULL, ** tmpImageG = NULL, ** tmpImageB = NULL;
	// ** 진짜 영상처리 알고리즘 **
	// 모핑할 다른 파일 열기
	CImage image;
	CFileDialog OpenDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY);

	if (OpenDlg.DoModal() == IDOK) {
		image.Load(OpenDlg.GetPathName());

		// (중요!) 입력 영상 크기 알아내기~
		tmpH = image.GetHeight();
		tmpW = image.GetWidth();

		// 메모리 할당
		tmpImageR = OnMalloc2D(tmpH, tmpW);
		tmpImageG = OnMalloc2D(tmpH, tmpW);
		tmpImageB = OnMalloc2D(tmpH, tmpW);
		// CImage의 객체값 --> 메모리
		COLORREF  px;

		for (int i = 0; i < tmpH; i++)
			for (int j = 0; j < tmpW; j++) {
				px = image.GetPixel(j, i);
				tmpImageR[i][j] = GetRValue(px);
				tmpImageG[i][j] = GetGValue(px);
				tmpImageB[i][j] = GetBValue(px);
			}

		// 모핑
		int tmp;
		double u;

		if (tmpH < m_inH)
			m_outH = tmpH;

		if (tmpW < m_inW)
			m_outW = tmpW;

		// 출력 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
			

		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				u = ((i * m_inH) + (j + 1.0)) / (m_inH * m_inW);
				// R
				tmp = (int)((1.0 - u) * m_inImageR[i][j] + u * tmpImageR[i][j]);

				if (tmp < 0)
					m_outImageR[i][j] = 0;
				else if (255 < tmp)
					m_outImageR[i][j] = 255;
				else
					m_outImageR[i][j] = (unsigned char)tmp;

				// G
				tmp = (int)((1.0 - u) * m_inImageG[i][j] + u * tmpImageG[i][j]);

				if (tmp < 0)
					m_outImageG[i][j] = 0;
				else if (255 < tmp)
					m_outImageG[i][j] = 255;
				else
					m_outImageG[i][j] = (unsigned char)tmp;

				// B
				tmp = (int)((1.0 - u) * m_inImageB[i][j] + u * tmpImageB[i][j]);

				if (tmp < 0)
					m_outImageB[i][j] = 0;
				else if (255 < tmp)
					m_outImageB[i][j] = 255;
				else
					m_outImageB[i][j] = (unsigned char)tmp;
			}
		}
	}
}


void CImageProcessingDoc::OnHistoStretchImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int highR = m_inImageR[0][0], lowR = m_inImageR[0][0];
	int highG = m_inImageG[0][0], lowG = m_inImageG[0][0];
	int highB = m_inImageB[0][0], lowB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			if (m_inImageR[i][j] < lowR)
				lowR = m_inImageR[i][j];

			if (highR < m_inImageR[i][j])
				highR = m_inImageR[i][j];

			// G
			if (m_inImageG[i][j] < lowG)
				lowG = m_inImageG[i][j];

			if (highG < m_inImageG[i][j])
				highG = m_inImageG[i][j];

			// B
			if (m_inImageB[i][j] < lowB)
				lowB = m_inImageB[i][j];

			if (highB < m_inImageB[i][j])
				highB = m_inImageB[i][j];
		}
	}

	int px = 0;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			px = (int)((double)(m_inImageR[i][j] - lowR) / (highR - lowR) * 255.0);

			if (px < 0)
				m_outImageR[i][j] = 0;
			else if (255 < px)
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = px;

			// G
			px = (int)((double)(m_inImageG[i][j] - lowG) / (highG - lowG) * 255.0);

			if (px < 0)
				m_outImageG[i][j] = 0;
			else if (255 < px)
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = px;

			// B
			px = (int)((double)(m_inImageB[i][j] - lowB) / (highB - lowB) * 255.0);

			if (px < 0)
				m_outImageB[i][j] = 0;
			else if (255 < px)
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = px;
		}
	}
}


void CImageProcessingDoc::OnHistoEndInImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	int highR = m_inImageR[0][0], lowR = m_inImageR[0][0];
	int highG = m_inImageG[0][0], lowG = m_inImageG[0][0];
	int highB = m_inImageB[0][0], lowB = m_inImageB[0][0];

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			if (m_inImageR[i][j] < lowR)
				lowR = m_inImageR[i][j];

			if (highR < m_inImageR[i][j])
				highR = m_inImageR[i][j];

			// G
			if (m_inImageG[i][j] < lowG)
				lowG = m_inImageG[i][j];

			if (highG < m_inImageG[i][j])
				highG = m_inImageG[i][j];

			// B
			if (m_inImageB[i][j] < lowB)
				lowB = m_inImageB[i][j];

			if (highB < m_inImageB[i][j])
				highB = m_inImageB[i][j];
		}
	}

	// R
	highR -= 50;
	lowR += 50;
	// G
	highG -= 50;
	lowG += 50;
	// B
	highB -= 50;
	lowB += 50;

	int px = 0;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			px = (int)((double)(m_inImageR[i][j] - lowR) / (double)(highR - lowR) * 255.0);

			if (px < 0)
				m_outImageR[i][j] = 0;
			else if (255 < px)
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = px;

			// G
			px = (int)((double)(m_inImageG[i][j] - lowG) / (double)(highG - lowG) * 255.0);

			if (px < 0)
				m_outImageG[i][j] = 0;
			else if (255 < px)
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = px;

			// B
			px = (int)((double)(m_inImageB[i][j] - lowB) / (double)(highB - lowB) * 255.0);

			if (px < 0)
				m_outImageB[i][j] = 0;
			else if (255 < px)
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = px;
		}
	}
}


void CImageProcessingDoc::OnHistoEqualImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	// 1단계 : 빈도 수 세기 (=히스토그램) histo[256]
	int histoR[256] = { 0 }, histoG[256] = { 0 }, histoB[256] = { 0 };

	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			histoR[m_inImageR[i][j]]++;
			histoG[m_inImageG[i][j]]++;
			histoB[m_inImageB[i][j]]++;
		}

	// 2단계 : 누적 히스토그램 생성
	int sumHistoR[256] = { 0 }, sumHistoG[256] = { 0 }, sumHistoB[256] = { 0 };
	sumHistoR[0] = histoR[0];
	sumHistoG[0] = histoG[0];
	sumHistoB[0] = histoB[0];

	for (int i = 1; i < 256; i++) {
		sumHistoR[i] = sumHistoR[i - 1] + histoR[i];
		sumHistoG[i] = sumHistoG[i - 1] + histoG[i];
		sumHistoB[i] = sumHistoB[i - 1] + histoB[i];
	}

	// 3단계 : 정규화된 히스토그램 생성 normalHisto = sumHisto * (1.0 / (inH * inW)) * 255.0
	double normalHistoR[256] = { 0 }, normalHistoG[256] = { 0 }, normalHistoB[256] = { 0 };

	for (int i = 0; i < 256; i++) {
		normalHistoR[i] = sumHistoR[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoG[i] = sumHistoG[i] * (1.0 / (m_inH * m_inW)) * 255.0;
		normalHistoB[i] = sumHistoB[i] * (1.0 / (m_inH * m_inW)) * 255.0;
	}

	// 입력 배열 --> 출력 배열
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			m_outImageR[i][j] = (unsigned char)normalHistoR[m_inImageR[i][j]];
			m_outImageG[i][j] = (unsigned char)normalHistoG[m_inImageG[i][j]];
			m_outImageB[i][j] = (unsigned char)normalHistoB[m_inImageB[i][j]];
		}
}


void CImageProcessingDoc::OnEmbossImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {
		{ -1.0, 0.0, 0.0 },
		{  0.0, 0.0, 0.0 },
		{  0.0, 0.0, 1.0 } }; // 엠보싱 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;
	
	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 후처리 (마스크 값의 합계에 따라서)
	for (int i = 0; i < m_outH; i++)
		for (int j = 0; j < m_outW; j++) {
			tmpOutImageR[i][j] += 127.0;
			tmpOutImageG[i][j] += 127.0;
			tmpOutImageB[i][j] += 127.0;
		}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnEmbossHsiImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {
		{ -1.0, 0.0, 0.0 },
		{  0.0, 0.0, 0.0 },
		{  0.0, 0.0, 1.0 } }; // 엠보싱 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;
	double** tmpInImageH = NULL, ** tmpInImageS = NULL, ** tmpInImageI = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpInImageH = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageS = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageI = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	///////// RGB 모델 --> HSI 모델 ///////////////
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			double* hsi;
			unsigned char R, G, B;

			R = tmpInImageR[i][j]; G = tmpInImageG[i][j]; B = tmpInImageB[i][j];
			hsi = RGB2HSI(R, G, B);

			double H, S, I;

			H = hsi[0]; S = hsi[1]; I = hsi[2];
			tmpInImageH[i][j] = H; tmpInImageS[i][j] = S; tmpInImageI[i][j] = I;
		}
	}

	// ** 회선 연산
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			double S_VALUE = 0.0;

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S_VALUE += tmpInImageI[i + m][j + n] * mask[m][n];

			tmpInImageI[i][j] = S_VALUE;
		}
	}

	// 후처리 (마스크 값의 합계에 따라서)
	for (int i = 0; i < m_outH; i++)
		for (int j = 0; j < m_outW; j++)
			tmpInImageI[i][j] += 127;

	////// HSI --> RGB ////////
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			unsigned char* rgb;
			double H, S, I;

			H = tmpInImageH[i][j]; S = tmpInImageS[i][j]; I = tmpInImageI[i][j];

			rgb = HSI2RGB(H, S, I);
			tmpOutImageR[i][j] = rgb[0]; tmpOutImageG[i][j] = rgb[1]; tmpOutImageB[i][j] = rgb[2];
		}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpInImageH, m_inH + 2);
	OnFree2D(tmpInImageS, m_inH + 2);
	OnFree2D(tmpInImageI, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnBlur1Image()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 },
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 },
		{ 1.0 / 9, 1.0 / 9, 1.0 / 9 } }; // 블러링(3x3) 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnBlur2Image()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 9;
	double mask[MSIZE][MSIZE]; // 블러링(9x9) 마스크

	for (int i = 0; i < MSIZE; i++)
		for (int j = 0; j < MSIZE; j++)
			mask[i][j] = 1.0 / 81;

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 8, m_inW + 8);
	tmpInImageG = OnMalloc2D_double(m_inH + 8, m_inW + 8);
	tmpInImageB = OnMalloc2D_double(m_inH + 8, m_inW + 8);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 8; i++)
		for (int j = 0; j < m_inW + 8; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 4][j + 4] = m_inImageR[i][j];
			tmpInImageG[i + 4][j + 4] = m_inImageG[i][j];
			tmpInImageB[i + 4][j + 4] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(9x9)와 한 점을 중심으로 한 9x9 곱하기
			// R
			S = 0.0; // 마스크 81개와 입력값 81개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 81개와 입력값 81개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 81개와 입력값 81개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 8);
	OnFree2D(tmpInImageG, m_inH + 8);
	OnFree2D(tmpInImageB, m_inH + 8);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnSharpImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {
		{ 0.0, -1.0, 0.0 },
		{ -1.0, 5.0, -1.0 },
		{ 0.0, -1.0, 0.0 } }; // 샤프닝 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnSharpHfImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {
		{ -1.0 / 9, -1.0 / 9, -1.0 / 9 },
		{ -1.0 / 9, 8.0 / 9, -1.0 / 9 },
		{ -1.0 / 9, -1.0 / 9, -1.0 / 9 } }; // 샤프닝(고주파) 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n] * 20;

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n] * 20;

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n] * 20;

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnSharpLfImage()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDecDlg dlg;
	if (dlg.DoModal() == IDOK) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		double alpha = dlg.m_constantDec;

		const int MSIZE = 3;
		double mask[MSIZE][MSIZE] = {
			{ 1.0 / 9, 1.0 / 9, 1.0 / 9 },
			{ 1.0 / 9, 1.0 / 9, 1.0 / 9 },
			{ 1.0 / 9, 1.0 / 9, 1.0 / 9 } }; // 샤프닝(저주파) 마스크

		// 임시 메모리 할당
		double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

		tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
		tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
		tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

		tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
		tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
		tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

		// 임시 메모리 초기화 (127)
		for (int i = 0; i < m_inH + 2; i++)
			for (int j = 0; j < m_inW + 2; j++)
				tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

		// 입력 이미지 -> 임시 입력 이미지
		for (int i = 0; i < m_inH; i++)
			for (int j = 0; j < m_inW; j++) {
				tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
				tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
				tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
			}

		// ** 회선 연산
		double S;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
				// R
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < MSIZE; m++)
					for (int n = 0; n < MSIZE; n++)
						S += tmpInImageR[i + m][j + n] * mask[m][n];

				tmpOutImageR[i][j] = S;

				// G
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < MSIZE; m++)
					for (int n = 0; n < MSIZE; n++)
						S += tmpInImageG[i + m][j + n] * mask[m][n];

				tmpOutImageG[i][j] = S;

				// B
				S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

				for (int m = 0; m < MSIZE; m++)
					for (int n = 0; n < MSIZE; n++)
						S += tmpInImageB[i + m][j + n] * mask[m][n];

				tmpOutImageB[i][j] = S;
			}
		}

		// 임시 출력 영상 --> 출력 영상
		double unsharp;

		for (int i = 0; i < m_outH; i++) {
			for (int j = 0; j < m_outW; j++) {
				// R
				unsharp = alpha * m_inImageR[i][j] - tmpOutImageR[i][j];

				if (unsharp < 0.0)
					m_outImageR[i][j] = 0;
				else if (255.0 < unsharp)
					m_outImageR[i][j] = 255;
				else
					m_outImageR[i][j] = (unsigned char)unsharp;

				// G
				unsharp = alpha * m_inImageG[i][j] - tmpOutImageG[i][j];

				if (unsharp < 0.0)
					m_outImageG[i][j] = 0;
				else if (255.0 < unsharp)
					m_outImageG[i][j] = 255;
				else
					m_outImageG[i][j] = (unsigned char)unsharp;

				// B
				unsharp = alpha * m_inImageB[i][j] - tmpOutImageB[i][j];

				if (unsharp < 0.0)
					m_outImageB[i][j] = 0;
				else if (255.0 < unsharp)
					m_outImageB[i][j] = 255;
				else
					m_outImageB[i][j] = (unsigned char)unsharp;
			}
		}

		// 임시 메모리 해제
		OnFree2D(tmpInImageR, m_inH + 2);
		OnFree2D(tmpInImageG, m_inH + 2);
		OnFree2D(tmpInImageB, m_inH + 2);
		OnFree2D(tmpOutImageR, m_outH);
		OnFree2D(tmpOutImageG, m_outH);
		OnFree2D(tmpOutImageB, m_outH);
	}
}


void CImageProcessingDoc::OnGaussianImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {
		{ 1.0 / 16, 1.0 / 8, 1.0 / 16 },
		{ 1.0 / 8, 1.0 / 4, 1.0 / 8 },
		{ 1.0 / 16, 1.0 / 8, 1.0 / 16 } }; // 가우시안 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgeVerImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {
		{ 0.0, 0.0, 0.0 },
		{ -1.0, 1.0, 0.0 },
		{ 0.0, 0.0, 0.0 } }; // 수직 에지 검출 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgeHorImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {
		{ 0.0, -1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 0.0 } }; // 수평 에지 검출 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgeHomogenImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			S = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					if (S < fabs(tmpInImageR[i + 1][j + 1] - tmpInImageR[i + m][j + n]))
						S = fabs(tmpInImageR[i + 1][j + 1] - tmpInImageR[i + m][j + n]);
				}
			}

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					if (S < fabs(tmpInImageG[i + 1][j + 1] - tmpInImageG[i + m][j + n]))
						S = fabs(tmpInImageG[i + 1][j + 1] - tmpInImageG[i + m][j + n]);
				}
			}

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0;

			for (int m = 0; m < MSIZE; m++) {
				for (int n = 0; n < MSIZE; n++) {
					if (S < fabs(tmpInImageB[i + 1][j + 1] - tmpInImageB[i + m][j + n]))
						S = fabs(tmpInImageB[i + 1][j + 1] - tmpInImageB[i + m][j + n]);
				}
			}

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgeDiffImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// R
			S = 0.0;

			for (int n = 0; n < MSIZE; n++) {
				if (S < fabs(tmpInImageR[i][j + n] - tmpInImageR[i + 2][j - n + 2]))
					S = fabs(tmpInImageR[i][j + n] - tmpInImageR[i + 2][j - n + 2]);
			}

			if (S < fabs(tmpInImageR[i + 1][j + 2] - tmpInImageR[i + 1][j]))
				S = fabs(tmpInImageR[i + 1][j + 2] - tmpInImageR[i + 1][j]);

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0;

			for (int n = 0; n < MSIZE; n++) {
				if (S < fabs(tmpInImageG[i][j + n] - tmpInImageG[i + 2][j - n + 2]))
					S = fabs(tmpInImageG[i][j + n] - tmpInImageG[i + 2][j - n + 2]);
			}

			if (S < fabs(tmpInImageG[i + 1][j + 2] - tmpInImageG[i + 1][j]))
				S = fabs(tmpInImageG[i + 1][j + 2] - tmpInImageG[i + 1][j]);

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0;

			for (int n = 0; n < MSIZE; n++) {
				if (S < fabs(tmpInImageB[i][j + n] - tmpInImageB[i + 2][j - n + 2]))
					S = fabs(tmpInImageB[i][j + n] - tmpInImageB[i + 2][j - n + 2]);
			}

			if (S < fabs(tmpInImageB[i + 1][j + 2] - tmpInImageB[i + 1][j]))
				S = fabs(tmpInImageB[i + 1][j + 2] - tmpInImageB[i + 1][j]);

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgeRobertsImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double maskRow[MSIZE][MSIZE] = {
		{ -1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 0.0 } }; // 로버츠 행 에지 검출 마스크

	double maskCol[MSIZE][MSIZE] = {
		{ 0.0, 0.0, -1.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 0.0 } }; // 로버츠 열 에지 검출 마스크

	// 임시 메모리 할당
	double** tmpRowInImageR = NULL, ** tmpRowInImageG = NULL, ** tmpRowInImageB = NULL, ** tmpRowOutImageR = NULL, ** tmpRowOutImageG = NULL, ** tmpRowOutImageB = NULL;
	double** tmpColInImageR = NULL, ** tmpColInImageG = NULL, ** tmpColInImageB = NULL, ** tmpColOutImageR = NULL, ** tmpColOutImageG = NULL, ** tmpColOutImageB = NULL;

	tmpRowInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpRowInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpRowInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpColInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpColInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpColInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpRowOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpRowOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpRowOutImageB = OnMalloc2D_double(m_outH, m_outW);
	tmpColOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpColOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpColOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++) {
			tmpRowInImageR[i][j] = tmpRowInImageG[i][j] = tmpRowInImageB[i][j] = 127.0;
			tmpColInImageR[i][j] = tmpColInImageG[i][j] = tmpColInImageB[i][j] = 127.0;
		}

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpRowInImageR[i + 1][j + 1] = tmpColInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpRowInImageG[i + 1][j + 1] = tmpColInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpRowInImageB[i + 1][j + 1] = tmpColInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S1, S2;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					S1 += tmpRowInImageR[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImageR[i + m][j + n] * maskCol[m][n];
				}

			tmpRowOutImageR[i][j] = S1;
			tmpColOutImageR[i][j] = S2;

			// G
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					S1 += tmpRowInImageG[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImageG[i + m][j + n] * maskCol[m][n];
				}

			tmpRowOutImageG[i][j] = S1;
			tmpColOutImageG[i][j] = S2;

			// B
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					S1 += tmpRowInImageB[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImageB[i + m][j + n] * maskCol[m][n];
				}

			tmpRowOutImageB[i][j] = S1;
			tmpColOutImageB[i][j] = S2;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			S1 = tmpRowOutImageR[i][j];
			S2 = tmpColOutImageR[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));

			// G
			S1 = tmpRowOutImageG[i][j];
			S2 = tmpColOutImageG[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));

			// B
			S1 = tmpRowOutImageB[i][j];
			S2 = tmpColOutImageB[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpRowInImageR, m_inH + 2);
	OnFree2D(tmpRowInImageG, m_inH + 2);
	OnFree2D(tmpRowInImageB, m_inH + 2);
	OnFree2D(tmpColInImageR, m_inH + 2);
	OnFree2D(tmpColInImageG, m_inH + 2);
	OnFree2D(tmpColInImageB, m_inH + 2);

	OnFree2D(tmpRowOutImageR, m_outH);
	OnFree2D(tmpRowOutImageG, m_outH);
	OnFree2D(tmpRowOutImageB, m_outH);
	OnFree2D(tmpColOutImageR, m_outH);
	OnFree2D(tmpColOutImageG, m_outH);
	OnFree2D(tmpColOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgePrewittImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double maskRow[MSIZE][MSIZE] = {
		{ -1.0, -1.0, -1.0 },
		{ 0.0, 0.0, 0.0 },
		{ 1.0, 1.0, 1.0 } }; // 프리윗 행 에지 검출 마스크

	double maskCol[MSIZE][MSIZE] = {
		{ 1.0, 0.0, -1.0 },
		{ 1.0, 0.0, -1.0 },
		{ 1.0, 0.0, -1.0 } }; // 프리윗 열 에지 검출 마스크

	// 임시 메모리 할당
	double** tmpRowInImageR = NULL, ** tmpRowInImageG = NULL, ** tmpRowInImageB = NULL, ** tmpRowOutImageR = NULL, ** tmpRowOutImageG = NULL, ** tmpRowOutImageB = NULL;
	double** tmpColInImageR = NULL, ** tmpColInImageG = NULL, ** tmpColInImageB = NULL, ** tmpColOutImageR = NULL, ** tmpColOutImageG = NULL, ** tmpColOutImageB = NULL;

	tmpRowInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpRowInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpRowInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpColInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpColInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpColInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpRowOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpRowOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpRowOutImageB = OnMalloc2D_double(m_outH, m_outW);
	tmpColOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpColOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpColOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++) {
			tmpRowInImageR[i][j] = tmpRowInImageG[i][j] = tmpRowInImageB[i][j] = 127.0;
			tmpColInImageR[i][j] = tmpColInImageG[i][j] = tmpColInImageB[i][j] = 127.0;
		}

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpRowInImageR[i + 1][j + 1] = tmpColInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpRowInImageG[i + 1][j + 1] = tmpColInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpRowInImageB[i + 1][j + 1] = tmpColInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S1, S2;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					S1 += tmpRowInImageR[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImageR[i + m][j + n] * maskCol[m][n];
				}

			tmpRowOutImageR[i][j] = S1;
			tmpColOutImageR[i][j] = S2;

			// G
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					S1 += tmpRowInImageG[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImageG[i + m][j + n] * maskCol[m][n];
				}

			tmpRowOutImageG[i][j] = S1;
			tmpColOutImageG[i][j] = S2;

			// B
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					S1 += tmpRowInImageB[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImageB[i + m][j + n] * maskCol[m][n];
				}

			tmpRowOutImageB[i][j] = S1;
			tmpColOutImageB[i][j] = S2;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			S1 = tmpRowOutImageR[i][j];
			S2 = tmpColOutImageR[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));

			// G
			S1 = tmpRowOutImageG[i][j];
			S2 = tmpColOutImageG[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));

			// B
			S1 = tmpRowOutImageB[i][j];
			S2 = tmpColOutImageB[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpRowInImageR, m_inH + 2);
	OnFree2D(tmpRowInImageG, m_inH + 2);
	OnFree2D(tmpRowInImageB, m_inH + 2);
	OnFree2D(tmpColInImageR, m_inH + 2);
	OnFree2D(tmpColInImageG, m_inH + 2);
	OnFree2D(tmpColInImageB, m_inH + 2);

	OnFree2D(tmpRowOutImageR, m_outH);
	OnFree2D(tmpRowOutImageG, m_outH);
	OnFree2D(tmpRowOutImageB, m_outH);
	OnFree2D(tmpColOutImageR, m_outH);
	OnFree2D(tmpColOutImageG, m_outH);
	OnFree2D(tmpColOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgeSobelImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double maskRow[MSIZE][MSIZE] = {
		{ -1.0, -2.0, -1.0 },
		{ 0.0, 0.0, 0.0 },
		{ 1.0, 2.0, 1.0 } }; // 소벨 행 에지 검출 마스크

	double maskCol[MSIZE][MSIZE] = {
		{ 1.0, 0.0, -1.0 },
		{ 2.0, 0.0, -2.0 },
		{ 1.0, 0.0, -1.0 } }; // 소벨 열 에지 검출 마스크

	// 임시 메모리 할당
	double** tmpRowInImageR = NULL, ** tmpRowInImageG = NULL, ** tmpRowInImageB = NULL, ** tmpRowOutImageR = NULL, ** tmpRowOutImageG = NULL, ** tmpRowOutImageB = NULL;
	double** tmpColInImageR = NULL, ** tmpColInImageG = NULL, ** tmpColInImageB = NULL, ** tmpColOutImageR = NULL, ** tmpColOutImageG = NULL, ** tmpColOutImageB = NULL;

	tmpRowInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpRowInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpRowInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpColInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpColInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpColInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpRowOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpRowOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpRowOutImageB = OnMalloc2D_double(m_outH, m_outW);
	tmpColOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpColOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpColOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++) {
			tmpRowInImageR[i][j] = tmpRowInImageG[i][j] = tmpRowInImageB[i][j] = 127.0;
			tmpColInImageR[i][j] = tmpColInImageG[i][j] = tmpColInImageB[i][j] = 127.0;
		}

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpRowInImageR[i + 1][j + 1] = tmpColInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpRowInImageG[i + 1][j + 1] = tmpColInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpRowInImageB[i + 1][j + 1] = tmpColInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S1, S2;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					S1 += tmpRowInImageR[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImageR[i + m][j + n] * maskCol[m][n];
				}

			tmpRowOutImageR[i][j] = S1;
			tmpColOutImageR[i][j] = S2;

			// G
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					S1 += tmpRowInImageG[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImageG[i + m][j + n] * maskCol[m][n];
				}

			tmpRowOutImageG[i][j] = S1;
			tmpColOutImageG[i][j] = S2;

			// B
			S1 = S2 = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++) {
					S1 += tmpRowInImageB[i + m][j + n] * maskRow[m][n];
					S2 += tmpColInImageB[i + m][j + n] * maskCol[m][n];
				}

			tmpRowOutImageB[i][j] = S1;
			tmpColOutImageB[i][j] = S2;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			S1 = tmpRowOutImageR[i][j];
			S2 = tmpColOutImageR[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));

			// G
			S1 = tmpRowOutImageG[i][j];
			S2 = tmpColOutImageG[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));

			// B
			S1 = tmpRowOutImageB[i][j];
			S2 = tmpColOutImageB[i][j];

			if (sqrt((double)(S1 * S1 + S2 * S2)) < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < sqrt((double)(S1 * S1 + S2 * S2)))
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)sqrt((double)(S1 * S1 + S2 * S2));
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpRowInImageR, m_inH + 2);
	OnFree2D(tmpRowInImageG, m_inH + 2);
	OnFree2D(tmpRowInImageB, m_inH + 2);
	OnFree2D(tmpColInImageR, m_inH + 2);
	OnFree2D(tmpColInImageG, m_inH + 2);
	OnFree2D(tmpColInImageB, m_inH + 2);

	OnFree2D(tmpRowOutImageR, m_outH);
	OnFree2D(tmpRowOutImageG, m_outH);
	OnFree2D(tmpRowOutImageB, m_outH);
	OnFree2D(tmpColOutImageR, m_outH);
	OnFree2D(tmpColOutImageG, m_outH);
	OnFree2D(tmpColOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgeLaplacianImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 3;
	double mask[MSIZE][MSIZE] = {
		{ 0.0, -1.0, 0.0 },
		{ -1.0, 4.0, -1.0 },
		{ 0.0, -1.0, 0.0 } }; // 라플라시안 에지 검출 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageG = OnMalloc2D_double(m_inH + 2, m_inW + 2);
	tmpInImageB = OnMalloc2D_double(m_inH + 2, m_inW + 2);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 2; i++)
		for (int j = 0; j < m_inW + 2; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 1][j + 1] = m_inImageR[i][j];
			tmpInImageG[i + 1][j + 1] = m_inImageG[i][j];
			tmpInImageB[i + 1][j + 1] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(3x3)와 한 점을 중심으로 한 3x3 곱하기
			// R
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 9개와 입력값 9개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 2);
	OnFree2D(tmpInImageG, m_inH + 2);
	OnFree2D(tmpInImageB, m_inH + 2);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgeLogImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 5;
	double mask[MSIZE][MSIZE] = {
		{ 0.0, 0.0, -1.0, 0.0, 0.0 },
		{ 0.0, -1.0, -2.0, -1.0, 0.0 },
		{ -1.0, -2.0, 16.0, -2.0, -1.0 },
		{ 0.0, -1.0, -2.0, -1.0, 0.0 },
		{ 0.0, 0.0, -1.0, 0.0, 0.0 } }; // LoG 에지 검출 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 4, m_inW + 4);
	tmpInImageG = OnMalloc2D_double(m_inH + 4, m_inW + 4);
	tmpInImageB = OnMalloc2D_double(m_inH + 4, m_inW + 4);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 4; i++)
		for (int j = 0; j < m_inW + 4; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 2][j + 2] = m_inImageR[i][j];
			tmpInImageG[i + 2][j + 2] = m_inImageG[i][j];
			tmpInImageB[i + 2][j + 2] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(5x5)와 한 점을 중심으로 한 5x5 곱하기
			// R
			S = 0.0; // 마스크 25개와 입력값 25개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 25개와 입력값 25개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 25개와 입력값 25개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 4);
	OnFree2D(tmpInImageG, m_inH + 4);
	OnFree2D(tmpInImageB, m_inH + 4);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnEdgeDogImage()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	const int MSIZE = 7;
	double mask[MSIZE][MSIZE] = {
		{ 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0 },
		{ 0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0 },
		{ -1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0 },
		{ -1.0, -3.0, 5.0, 16.0, 5.0, -3.0, -1.0 },
		{ -1.0, -3.0, 5.0, 5.0, 5.0, -3.0, -1.0 },
		{ 0.0, -2.0, -3.0, -3.0, -3.0, -2.0, 0.0 },
		{ 0.0, 0.0, -1.0, -1.0, -1.0, 0.0, 0.0 } }; // DoG 에지 검출 마스크

	// 임시 메모리 할당
	double** tmpInImageR = NULL, ** tmpInImageG = NULL, ** tmpInImageB = NULL, ** tmpOutImageR = NULL, ** tmpOutImageG = NULL, ** tmpOutImageB = NULL;

	tmpInImageR = OnMalloc2D_double(m_inH + 6, m_inW + 6);
	tmpInImageG = OnMalloc2D_double(m_inH + 6, m_inW + 6);
	tmpInImageB = OnMalloc2D_double(m_inH + 6, m_inW + 6);

	tmpOutImageR = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageG = OnMalloc2D_double(m_outH, m_outW);
	tmpOutImageB = OnMalloc2D_double(m_outH, m_outW);

	// 임시 메모리 초기화 (127)
	for (int i = 0; i < m_inH + 6; i++)
		for (int j = 0; j < m_inW + 6; j++)
			tmpInImageR[i][j] = tmpInImageG[i][j] = tmpInImageB[i][j] = 127.0;

	// 입력 이미지 -> 임시 입력 이미지
	for (int i = 0; i < m_inH; i++)
		for (int j = 0; j < m_inW; j++) {
			tmpInImageR[i + 3][j + 3] = m_inImageR[i][j];
			tmpInImageG[i + 3][j + 2] = m_inImageG[i][j];
			tmpInImageB[i + 3][j + 3] = m_inImageB[i][j];
		}

	// ** 회선 연산
	double S;

	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// 마스크(7x7)와 한 점을 중심으로 한 7x7 곱하기
			// R
			S = 0.0; // 마스크 49개와 입력값 49개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageR[i + m][j + n] * mask[m][n];

			tmpOutImageR[i][j] = S;

			// G
			S = 0.0; // 마스크 49개와 입력값 49개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageG[i + m][j + n] * mask[m][n];

			tmpOutImageG[i][j] = S;

			// B
			S = 0.0; // 마스크 49개와 입력값 49개를 각각 곱해서 합한 값

			for (int m = 0; m < MSIZE; m++)
				for (int n = 0; n < MSIZE; n++)
					S += tmpInImageB[i + m][j + n] * mask[m][n];

			tmpOutImageB[i][j] = S;
		}
	}

	// 임시 출력 영상 --> 출력 영상
	for (int i = 0; i < m_outH; i++) {
		for (int j = 0; j < m_outW; j++) {
			// R
			if (tmpOutImageR[i][j] < 0.0)
				m_outImageR[i][j] = 0;
			else if (255.0 < tmpOutImageR[i][j])
				m_outImageR[i][j] = 255;
			else
				m_outImageR[i][j] = (unsigned char)tmpOutImageR[i][j];

			// G
			if (tmpOutImageG[i][j] < 0.0)
				m_outImageG[i][j] = 0;
			else if (255.0 < tmpOutImageG[i][j])
				m_outImageG[i][j] = 255;
			else
				m_outImageG[i][j] = (unsigned char)tmpOutImageG[i][j];

			// B
			if (tmpOutImageB[i][j] < 0.0)
				m_outImageB[i][j] = 0;
			else if (255.0 < tmpOutImageB[i][j])
				m_outImageB[i][j] = 255;
			else
				m_outImageB[i][j] = (unsigned char)tmpOutImageB[i][j];
		}
	}

	// 임시 메모리 해제
	OnFree2D(tmpInImageR, m_inH + 6);
	OnFree2D(tmpInImageG, m_inH + 6);
	OnFree2D(tmpInImageB, m_inH + 6);
	OnFree2D(tmpOutImageR, m_outH);
	OnFree2D(tmpOutImageG, m_outH);
	OnFree2D(tmpOutImageB, m_outH);
}


void CImageProcessingDoc::OnChangeSatur()
{
	// TODO: 여기에 구현 코드 추가.
	// 기존 메모리 해제
	OnFreeOutImage();
	// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
	m_outH = m_inH;
	m_outW = m_inW;
	// 메모리 할당
	m_outImageR = OnMalloc2D(m_outH, m_outW);
	m_outImageG = OnMalloc2D(m_outH, m_outW);
	m_outImageB = OnMalloc2D(m_outH, m_outW);
	// ** 진짜 영상처리 알고리즘 **
	for (int i = 0; i < m_inH; i++) {
		for (int j = 0; j < m_inW; j++) {
			// HSI 모델 값
			// H(색상) : 0 ~ 360
			// S(채도) : 0.0 ~ 1.0
			// I(명도) : 0 ~ 255

			// RGB --> HSI
			double H, S, I;
			unsigned char R, G, B;

			R = m_inImageR[i][j];
			G = m_inImageG[i][j];
			B = m_inImageB[i][j];

			double* hsi = RGB2HSI(R, G, B);
			H = hsi[0]; S = hsi[1]; I = hsi[2];

			// 채도(S) 흐리게
			S -= 0.2;
			if (S < 0)
				S = 0.0;

			// HSI --> RGB
			unsigned char* rgb = HSI2RGB(H, S, I);
			R = rgb[0], G = rgb[1], B = rgb[2];

			m_outImageR[i][j] = R;
			m_outImageG[i][j] = G;
			m_outImageB[i][j] = B;
		}
	}
}


double* CImageProcessingDoc::RGB2HSI(int R, int G, int B)
{
	// TODO: 여기에 구현 코드 추가.
	double H, S, I;
	double* HSI = new double[3];
	double min_value, angle;

	I = (R + G + B) / 3.0; // 밝기
	if ((R == G) && (G == B)) { // 그레이
		S = 0.0;
		H = 0.0;
	}
	else {

		min_value = min(min(R, G), B); //최소값 추출
		angle = (R - 0.5 * G - 0.5 * B) / (double)sqrt((R - G) * (R - G) + (R - B) * (G - B));

		H = (double)acos(angle) * 57.29577951;
		S = 1.0f - (3.0 / (R + G + B)) * min_value;
	}

	if (B > G) H = 360. - H;

	HSI[0] = H;
	HSI[1] = S;
	HSI[2] = I;

	return HSI;
}


unsigned char* CImageProcessingDoc::HSI2RGB(double H, double S, double I)
{
	// TODO: 여기에 구현 코드 추가.
	double R, G, B;
	unsigned char* RGB = new unsigned char[3];
	double angle1, angle2, scale;

	if (I == 0.0) { // Black
		RGB[0] = 0;
		RGB[1] = 0;
		RGB[2] = 0;
		return RGB;
	}

	if (H <= 0.0) H += 360.0f;

	scale = 3.0 * I;
	if (H <= 120.0)
	{
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		B = (1.0 - S) / 3.0f;
		R = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		G = 1.0 - R - B;
		B *= scale;
		R *= scale;
		G *= scale;
	}


	else if ((H > 120.0) && (H <= 240.0)) {
		H -= 120.0;
		angle1 = H * 0.017453293;

		angle2 = (60.0 - H) * 0.017453293;
		R = (1.0 - S) / 3.0;
		G = (double)(1.0f + (S * cos(angle1) / cos(angle2))) / 3.0;
		B = 1.0 - R - G;
		R *= scale;
		G *= scale;
		B *= scale;
	}
	else {
		H -= 240.0;
		angle1 = H * 0.017453293;
		angle2 = (60.0 - H) * 0.017453293;
		G = (1.0f - S) / 3.0;
		B = (double)(1.0 + (S * cos(angle1) / cos(angle2))) / 3.0;
		R = 1.0 - G - B;

		R *= scale;
		G *= scale;
		B *= scale;
	}

	RGB[0] = (unsigned char)R;
	RGB[1] = (unsigned char)G;
	RGB[2] = (unsigned char)B;

	return RGB;
}


void CImageProcessingDoc::OnPick()
{
	// TODO: 여기에 구현 코드 추가.
	CColorDlg dlg;
	if (dlg.DoModal() != IDCANCEL) {
		// 기존 메모리 해제
		OnFreeOutImage();
		// 중요! 출력 이미지 크기 결정 --> 알고리즘에 따름...
		m_outH = m_inH;
		m_outW = m_inW;
		// 메모리 할당
		m_outImageR = OnMalloc2D(m_outH, m_outW);
		m_outImageG = OnMalloc2D(m_outH, m_outW);
		m_outImageB = OnMalloc2D(m_outH, m_outW);
		// ** 진짜 영상처리 알고리즘 **
		int colorStart = dlg.m_colorStart;
		int colorEnd = dlg.m_colorEnd;
		bool checkRed = dlg.m_checkRed;

		for (int i = 0; i < m_inH; i++) {
			for (int j = 0; j < m_inW; j++) {
				// HSI 모델 값
				// H(색상) : 0 ~ 360
				// S(채도) : 0.0 ~ 1.0
				// I(명도) : 0 ~ 255

				// RGB --> HSI
				double H, S, I;
				unsigned char R, G, B;

				R = m_inImageR[i][j];
				G = m_inImageG[i][j];
				B = m_inImageB[i][j];

				double* hsi = RGB2HSI(R, G, B);
				H = hsi[0]; S = hsi[1]; I = hsi[2];

				if (checkRed) {
					if ((0 <= H && H <= colorStart) || colorEnd <= H && H <= 360) {
						m_outImageR[i][j] = m_inImageR[i][j];
						m_outImageG[i][j] = m_inImageG[i][j];
						m_outImageB[i][j] = m_inImageB[i][j];
					}
					else {
						double avg = (m_inImageR[i][j] + m_inImageG[i][j] + m_inImageB[i][j]) / 3.0;
						m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)avg;
					}
				}
				else {
					// 오렌지 추출 (H : 8 ~ 20)
					if (colorStart <= H && H <= colorEnd) {
						m_outImageR[i][j] = m_inImageR[i][j];
						m_outImageG[i][j] = m_inImageG[i][j];
						m_outImageB[i][j] = m_inImageB[i][j];
					}
					else {
						double avg = (m_inImageR[i][j] + m_inImageG[i][j] + m_inImageB[i][j]) / 3.0;
						m_outImageR[i][j] = m_outImageG[i][j] = m_outImageB[i][j] = (unsigned char)avg;
					}
				}
			}
		}
	}
}
