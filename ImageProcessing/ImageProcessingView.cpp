
// ImageProcessingView.cpp: CImageProcessingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CImageProcessingView::OnEqualImage)
	ON_COMMAND(IDM_GRAY_SCALE, &CImageProcessingView::OnGrayScale)
	ON_COMMAND(IDM_ADD_IMAGE, &CImageProcessingView::OnAddImage)
	ON_COMMAND(IDM_MUL_IMAGE, &CImageProcessingView::OnMulImage)
	ON_COMMAND(IDM_AND_IMAGE, &CImageProcessingView::OnAndImage)
	ON_COMMAND(IDM_OR_IMAGE, &CImageProcessingView::OnOrImage)
	ON_COMMAND(IDM_XOR_IMAGE, &CImageProcessingView::OnXorImage)
	ON_COMMAND(IDM_NOT_IMAGE, &CImageProcessingView::OnNotImage)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CImageProcessingView::OnGammaImage)
	ON_COMMAND(IDM_CAP_IMAGE, &CImageProcessingView::OnCapImage)
	ON_COMMAND(IDM_CUP_IMAGE, &CImageProcessingView::OnCupImage)
	ON_COMMAND(IDM_POSTERIZING_IMAGE, &CImageProcessingView::OnPosterizingImage)
	ON_COMMAND(IDM_CHANGE_SATUR, &CImageProcessingView::OnChangeSatur)
	ON_COMMAND(IDM_PICK, &CImageProcessingView::OnPick)
	ON_COMMAND(IDM_STRESS_IMAGE, &CImageProcessingView::OnStressImage)
	ON_COMMAND(IDM_BW_IMAGE, &CImageProcessingView::OnBwImage)
	ON_COMMAND(IDM_BW_AVG_IMAGE, &CImageProcessingView::OnBwAvgImage)
	ON_COMMAND(IDM_BW_MED_IMAGE, &CImageProcessingView::OnBwMedImage)
	ON_COMMAND(IDM_ZOOM_OUT_IMAGE, &CImageProcessingView::OnZoomOutImage)
	ON_COMMAND(IDM_ZOOM_OUT_AVG_IMAGE, &CImageProcessingView::OnZoomOutAvgImage)
	ON_COMMAND(IDM_ZOOM_OUT_MED_IMAGE, &CImageProcessingView::OnZoomOutMedImage)
	ON_COMMAND(IDM_ZOOM_IN1_IMAGE, &CImageProcessingView::OnZoomIn1Image)
	ON_COMMAND(IDM_ZOOM_IN2_IMAGE, &CImageProcessingView::OnZoomIn2Image)
	ON_COMMAND(IDM_ZOOM_IN_BILINEAR_IMAGE, &CImageProcessingView::OnZoomInBilinearImage)
	ON_COMMAND(IDM_ROTATE1_IMAGE, &CImageProcessingView::OnRotate1Image)
	ON_COMMAND(IDM_ROTATE2_IMAGE, &CImageProcessingView::OnRotate2Image)
	ON_COMMAND(IDM_ROTATE_ZOOM_IN_IMAGE, &CImageProcessingView::OnRotateZoomInImage)
	ON_COMMAND(IDM_ROTATE_ZOOM_IN_BILINEAR_IMAGE, &CImageProcessingView::OnRotateZoomInBilinearImage)
	ON_COMMAND(IDM_MIRROR_VER_IMAGE, &CImageProcessingView::OnMirrorVerImage)
	ON_COMMAND(IDM_MIRROR_HOR_IMAGE, &CImageProcessingView::OnMirrorHorImage)
	ON_COMMAND(IDM_MOVE_IMAGE, &CImageProcessingView::OnMoveImage)
	ON_COMMAND(IDM_MORPHING_IMAGE, &CImageProcessingView::OnMorphingImage)
	ON_COMMAND(IDM_HISTO_STRETCH_IMAGE, &CImageProcessingView::OnHistoStretchImage)
	ON_COMMAND(IDM_HISTO_END_IN_IMAGE, &CImageProcessingView::OnHistoEndInImage)
	ON_COMMAND(IDM_HISTO_EQUAL_IMAGE, &CImageProcessingView::OnHistoEqualImage)
	ON_COMMAND(IDM_EMBOSS_IMAGE, &CImageProcessingView::OnEmbossImage)
	ON_COMMAND(IDM_EMBOSS_HSI_IMAGE, &CImageProcessingView::OnEmbossHsiImage)
	ON_COMMAND(IDM_BLUR1_IMAGE, &CImageProcessingView::OnBlur1Image)
	ON_COMMAND(IDM_BLUR2_IMAGE, &CImageProcessingView::OnBlur2Image)
	ON_COMMAND(IDM_SHARP_IMAGE, &CImageProcessingView::OnSharpImage)
	ON_COMMAND(IDM_SHARP_HF_IMAGE, &CImageProcessingView::OnSharpHfImage)
	ON_COMMAND(IDM_SHARP_LF_IMAGE, &CImageProcessingView::OnSharpLfImage)
	ON_COMMAND(IDM_GAUSSIAN_IMAGE, &CImageProcessingView::OnGaussianImage)
	ON_COMMAND(IDM_EDGE_VER_IMAGE, &CImageProcessingView::OnEdgeVerImage)
	ON_COMMAND(IDM_EDGE_HOR_IMAGE, &CImageProcessingView::OnEdgeHorImage)
	ON_COMMAND(IDM_EDGE_HOMOGEN_IMAGE, &CImageProcessingView::OnEdgeHomogenImage)
	ON_COMMAND(IDM_EDGE_DIFF_IMAGE, &CImageProcessingView::OnEdgeDiffImage)
	ON_COMMAND(IDM_EDGE_ROBERTS_IMAGE, &CImageProcessingView::OnEdgeRobertsImage)
	ON_COMMAND(IDM_EDGE_PREWITT_IMAGE, &CImageProcessingView::OnEdgePrewittImage)
	ON_COMMAND(IDM_EDGE_SOBEL_IMAGE, &CImageProcessingView::OnEdgeSobelImage)
	ON_COMMAND(IDM_EDGE_LAPLACIAN_IMAGE, &CImageProcessingView::OnEdgeLaplacianImage)
	ON_COMMAND(IDM_EDGE_LOG_IMAGE, &CImageProcessingView::OnEdgeLogImage)
	ON_COMMAND(IDM_EDGE_DOG_IMAGE, &CImageProcessingView::OnEdgeDogImage)
END_MESSAGE_MAP()

// CImageProcessingView 생성/소멸

CImageProcessingView::CImageProcessingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingView 그리기

void CImageProcessingView::OnDraw(CDC* pDC)
{
	//CImageProcessingDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//int R, G, B;
	//for (int i=0; i<pDoc->m_inH; i++)
	//	for (int j = 0; j < pDoc->m_inW; j++) {
	//		R = pDoc->m_inImageR[i][j];
	//		G = pDoc->m_inImageG[i][j];
	//		B = pDoc->m_inImageB[i][j];
	//		pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
	//	}

	//for (int i = 0; i < pDoc->m_outH; i++)
	//	for (int j = 0; j < pDoc->m_outW; j++) {
	//		R = pDoc->m_outImageR[i][j];
	//		G = pDoc->m_outImageG[i][j];
	//		B = pDoc->m_outImageB[i][j];
	//		pDC->SetPixel(pDoc->m_inW + j + 10, i + 5, RGB(R, G, B));
	//	}

		///////////////////
	/// ** 더블 버퍼링 **
	///////////////////
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 
	////////////////////
	int i, j;
	unsigned char R, G, B;
	// 메모리 DC 선언
	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_inW, pDoc->m_inH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_inW, pDoc->m_inH, WHITENESS); // 흰색으로 초기화

	// 출력 영상의 크기를 자동 조절
	double MAXSIZE = 800;  // 필요시 실 모니터 또는 화면의 해상도에 따라서 변경 가능!
	int inH = pDoc->m_inH;
	int inW = pDoc->m_inW;
	double hop = 1.0; // 기본

	if (inH > MAXSIZE || inW > MAXSIZE) {
		// hop을 새로 계산.
		if (inW > inH)
			hop = (inW / MAXSIZE);
		else
			hop = (inH / MAXSIZE);

		inW = (int)(inW / hop);
		inH = (int)(inH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_inH; i++) {
		for (j = 0; j < pDoc->m_inW; j++) {
			R = pDoc->m_inImageR[(int)(i * hop)][(int)(j * hop)];
			G = pDoc->m_inImageG[(int)(i * hop)][(int)(j * hop)];
			B = pDoc->m_inImageB[(int)(i * hop)][(int)(j * hop)];
			memDC.SetPixel(j, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(5, 5, pDoc->m_inW, pDoc->m_inH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();

	///////////////////

	// 화면 DC와 호환되는 메모리 DC 객체를 생성
	memDC.CreateCompatibleDC(pDC);

	// 마찬가지로 화면 DC와 호환되는 Bitmap 생성
	bitmap.CreateCompatibleBitmap(pDC, pDoc->m_outW, pDoc->m_outH);

	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, pDoc->m_outW, pDoc->m_outH, WHITENESS); // 흰색으로 초기화

	int outH = pDoc->m_outH;
	int outW = pDoc->m_outW;
	hop = 1.0; // 기본

	if (outH > MAXSIZE || outW > MAXSIZE) {
		// hop을 새로 계산.
		if (outW > outH)
			hop = (outW / MAXSIZE);
		else
			hop = (outH / MAXSIZE);

		outW = (int)(outW / hop);
		outH = (int)(outH / hop);
	}

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_outH; i++) {
		for (j = 0; j < pDoc->m_outW; j++) {
			R = pDoc->m_outImageR[(int)(i * hop)][(int)(j * hop)];
			G = pDoc->m_outImageG[(int)(i * hop)][(int)(j * hop)];
			B = pDoc->m_outImageB[(int)(i * hop)][(int)(j * hop)];
			memDC.SetPixel(j, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(pDoc->m_inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


// CImageProcessingView 인쇄

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProcessingView 진단

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView 메시지 처리기



void CImageProcessingView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnGrayScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGrayScale();
	Invalidate(TRUE);
}


void CImageProcessingView::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAddImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMulImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMulImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnAndImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnOrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnXorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnXorImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnNotImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNotImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnCapImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnCapImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnCupImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnCupImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnPosterizingImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPosterizingImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnChangeSatur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnChangeSatur();
	Invalidate(TRUE);
}


void CImageProcessingView::OnPick()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPick();
	Invalidate(TRUE);
}


void CImageProcessingView::OnStressImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStressImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnBwImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBwImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnBwAvgImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBwAvgImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnBwMedImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBwMedImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnZoomOutImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomOutImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnZoomOutAvgImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomOutAvgImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnZoomOutMedImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomOutMedImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnZoomIn1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn1Image();
	Invalidate(TRUE);
}


void CImageProcessingView::OnZoomIn2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn2Image();
	Invalidate(TRUE);
}


void CImageProcessingView::OnZoomInBilinearImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomInBilinearImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnRotate1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate1Image();
	Invalidate(TRUE);
}


void CImageProcessingView::OnRotate2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotate2Image();
	Invalidate(TRUE);
}


void CImageProcessingView::OnRotateZoomInImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotateZoomInImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnRotateZoomInBilinearImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotateZoomInBilinearImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMirrorVerImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorVerImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMirrorHorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorHorImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMoveImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMoveImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnMorphingImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMorphingImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHistoStretchImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretchImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHistoEndInImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEndInImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHistoEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqualImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEmbossImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEmbossHsiImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossHsiImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnBlur1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlur1Image();
	Invalidate(TRUE);
}


void CImageProcessingView::OnBlur2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlur2Image();
	Invalidate(TRUE);
}


void CImageProcessingView::OnSharpImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnSharpHfImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpHfImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnSharpLfImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpLfImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnGaussianImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGaussianImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgeVerImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeVerImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgeHorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeHorImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgeHomogenImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeHomogenImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgeDiffImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeDiffImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgeRobertsImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeRobertsImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgePrewittImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgePrewittImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgeSobelImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeSobelImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgeLaplacianImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeLaplacianImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgeLogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeLogImage();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEdgeDogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEdgeDogImage();
	Invalidate(TRUE);
}
