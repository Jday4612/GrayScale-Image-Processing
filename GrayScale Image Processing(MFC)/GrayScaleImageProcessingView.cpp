
// GrayScaleImageProcessingView.cpp: CGrayScaleImageProcessingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GrayScaleImageProcessing.h"
#endif

#include "GrayScaleImageProcessingDoc.h"
#include "GrayScaleImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrayScaleImageProcessingView

IMPLEMENT_DYNCREATE(CGrayScaleImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CGrayScaleImageProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CGrayScaleImageProcessingView::OnEqualImage)
	ON_COMMAND(IDM_ADD_IMAGE, &CGrayScaleImageProcessingView::OnAddImage)
	ON_COMMAND(IDM_MUL_IMAGE, &CGrayScaleImageProcessingView::OnMulImage)
	ON_COMMAND(IDM_AND_IMAGE, &CGrayScaleImageProcessingView::OnAndImage)
	ON_COMMAND(IDM_OR_IMAGE, &CGrayScaleImageProcessingView::OnOrImage)
	ON_COMMAND(IDM_XOR_IMAGE, &CGrayScaleImageProcessingView::OnXorImage)
	ON_COMMAND(IDM_NOT_IMAGE, &CGrayScaleImageProcessingView::OnNotImage)
	ON_COMMAND(IDM_GAMMA_IMAGE, &CGrayScaleImageProcessingView::OnGammaImage)
	ON_COMMAND(IDM_CAP_IMAGE, &CGrayScaleImageProcessingView::OnCapImage)
	ON_COMMAND(IDM_CUP_IMAGE, &CGrayScaleImageProcessingView::OnCupImage)
	ON_COMMAND(IDM_POSTERIZING_IMAGE, &CGrayScaleImageProcessingView::OnPosterizingImage)
	ON_COMMAND(IDM_STRESS_IMAGE, &CGrayScaleImageProcessingView::OnStressImage)
	ON_COMMAND(IDM_BW_IMAGE, &CGrayScaleImageProcessingView::OnBwImage)
	ON_COMMAND(IDM_BW_AVG_IMAGE, &CGrayScaleImageProcessingView::OnBwAvgImage)
	ON_COMMAND(IDM_BW_MED_IMAGE, &CGrayScaleImageProcessingView::OnBwMedImage)
	ON_COMMAND(IDM_ZOOM_OUT_IMAGE, &CGrayScaleImageProcessingView::OnZoomOutImage)
	ON_COMMAND(IDM_ZOOM_OUT_AVG_IMAGE, &CGrayScaleImageProcessingView::OnZoomOutAvgImage)
	ON_COMMAND(IDM_ZOOM_OUT_MED_IMAGE, &CGrayScaleImageProcessingView::OnZoomOutMedImage)
	ON_COMMAND(IDM_ZOOM_IN1_IMAGE, &CGrayScaleImageProcessingView::OnZoomIn1Image)
	ON_COMMAND(IDM_ZOOM_IN2_IMAGE, &CGrayScaleImageProcessingView::OnZoomIn2Image)
	ON_COMMAND(IDM_ZOOM_IN_BILINEAR_IMAGE, &CGrayScaleImageProcessingView::OnZoomInBilinearImage)
	ON_COMMAND(IDM_ROTATE1_IMAGE, &CGrayScaleImageProcessingView::OnRotate1Image)
	ON_COMMAND(IDM_ROTATE2_IMAGE, &CGrayScaleImageProcessingView::OnRotate2Image)
	ON_COMMAND(IDM_ROTATE_ZOOM_IN_IMAGE, &CGrayScaleImageProcessingView::OnRotateZoomInImage)
	ON_COMMAND(IDM_ROTATE_ZOOM_IN_BILINEAR_IMAGE, &CGrayScaleImageProcessingView::OnRotateZoomInBilinearImage)
	ON_COMMAND(IDM_MIRROR_VER_IMAGE, &CGrayScaleImageProcessingView::OnMirrorVerImage)
	ON_COMMAND(IDM_MIRROR_HOR_IMAGE, &CGrayScaleImageProcessingView::OnMirrorHorImage)
	ON_COMMAND(IDM_MOVE_IMAGE, &CGrayScaleImageProcessingView::OnMoveImage)
	ON_COMMAND(IDM_MORPHING_IMAGE, &CGrayScaleImageProcessingView::OnMorphingImage)
	ON_COMMAND(IDM_HISTO_STRETCH_IMAGE, &CGrayScaleImageProcessingView::OnHistoStretchImage)
	ON_COMMAND(IDM_END_IN_IMAGE, &CGrayScaleImageProcessingView::OnEndInImage)
	ON_COMMAND(IDM_HISTO_EQUAL_IMAGE, &CGrayScaleImageProcessingView::OnHistoEqualImage)
	ON_COMMAND(IDM_EMBOSS_IMAGE, &CGrayScaleImageProcessingView::OnEmbossImage)
	ON_COMMAND(IDM_BLUR1_IMAGE, &CGrayScaleImageProcessingView::OnBlur1Image)
	ON_COMMAND(IDM_BLUR2_IMAGE, &CGrayScaleImageProcessingView::OnBlur2Image)
	ON_COMMAND(IDM_SHARP_IMAGE, &CGrayScaleImageProcessingView::OnSharpImage)
	ON_COMMAND(IDM_SHARP_HF_IMAGE, &CGrayScaleImageProcessingView::OnSharpHfImage)
	ON_COMMAND(IDM_SHARP_LF_IMAGE, &CGrayScaleImageProcessingView::OnSharpLfImage)
	ON_COMMAND(IDM_GAUSSIAN_IMAGE, &CGrayScaleImageProcessingView::OnGaussianImage)
	ON_COMMAND(IDM_EDGE_VER_IMAGE, &CGrayScaleImageProcessingView::OnEdgeVerImage)
	ON_COMMAND(IDM_EDGE_HOR_IMAGE, &CGrayScaleImageProcessingView::OnEdgeHorImage)
	ON_COMMAND(IDM_EDGE_HOMOGEN_IMAGE, &CGrayScaleImageProcessingView::OnEdgeHomogenImage)
	ON_COMMAND(IDM_EDGE_DIFF_IMAGE, &CGrayScaleImageProcessingView::OnEdgeDiffImage)
	ON_COMMAND(IDM_EDGE_ROBERTS_IMAGE, &CGrayScaleImageProcessingView::OnEdgeRobertsImage)
	ON_COMMAND(IDM_EDGE_PREWITT_IMAGE, &CGrayScaleImageProcessingView::OnEdgePrewittImage)
	ON_COMMAND(IDM_EDGE_SOBEL_IMAGE, &CGrayScaleImageProcessingView::OnEdgeSobelImage)
	ON_COMMAND(IDM_EDGE_LAPLACIAN_IMAGE, &CGrayScaleImageProcessingView::OnEdgeLaplacianImage)
	ON_COMMAND(IDM_EDGE_LOG_IMAGE, &CGrayScaleImageProcessingView::OnEdgeLogImage)
	ON_COMMAND(IDM_EDGE_DOG_IMAGE, &CGrayScaleImageProcessingView::OnEdgeDogImage)
END_MESSAGE_MAP()

// CGrayScaleImageProcessingView 생성/소멸

CGrayScaleImageProcessingView::CGrayScaleImageProcessingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGrayScaleImageProcessingView::~CGrayScaleImageProcessingView()
{
}

BOOL CGrayScaleImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGrayScaleImageProcessingView 그리기

void CGrayScaleImageProcessingView::OnDraw(CDC* pDC)
{
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	/*unsigned char R, G, B;

	for (int i = 0; i < pDoc->m_inH; i++) {
		for (int j = 0; j < pDoc->m_inW; j++) {
			R = G = B = pDoc->m_inImage[i][j];
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	for (int i = 0; i < pDoc->m_outH; i++) {
		for (int j = 0; j < pDoc->m_outW; j++) {
			R = G = B = pDoc->m_outImage[i][j];
			pDC->SetPixel(pDoc->m_inW + j + 10, i + 5, RGB(R, G, B));
		}
	}*/

	/////////////////////
	/// 성능 개선을 위한 더블 버퍼링 
	////////////////////
	int i, k;
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

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_inH; i++) {
		for (k = 0; k < pDoc->m_inW; k++) {
			R = G = B = pDoc->m_inImage[i][k];
			memDC.SetPixel(k, i, RGB(R, G, B));
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

	// 메모리 DC에 그리기
	for (i = 0; i < pDoc->m_outH; i++) {
		for (k = 0; k < pDoc->m_outW; k++) {
			R = G = B = pDoc->m_outImage[i][k];
			memDC.SetPixel(k, i, RGB(R, G, B));
		}
	}
	// 메모리 DC를 화면 DC에 고속 복사
	pDC->BitBlt(pDoc->m_inW + 10, 5, pDoc->m_outW, pDoc->m_outH, &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


// CGrayScaleImageProcessingView 인쇄

BOOL CGrayScaleImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGrayScaleImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGrayScaleImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGrayScaleImageProcessingView 진단

#ifdef _DEBUG
void CGrayScaleImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CGrayScaleImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGrayScaleImageProcessingDoc* CGrayScaleImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGrayScaleImageProcessingDoc)));
	return (CGrayScaleImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CGrayScaleImageProcessingView 메시지 처리기


void CGrayScaleImageProcessingView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEqualImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnAddImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnAddImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnMulImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMulImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnAndImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnAndImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnOrImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnOrImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnXorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnXorImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnNotImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnNotImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnGammaImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnGammaImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnCapImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnCapImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnCupImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnCupImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnPosterizingImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnPosterizingImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnStressImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnStressImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnBwImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBwImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnBwAvgImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBwAvgImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnBwMedImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBwMedImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnZoomOutImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoomOutImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnZoomOutAvgImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoomOutAvgImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnZoomOutMedImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoomOutMedImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnZoomIn1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoomIn1Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnZoomIn2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoomIn2Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnZoomInBilinearImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoomInBilinearImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnRotate1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnRotate1Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnRotate2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnRotate2Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnRotateZoomInImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnRotateZoomInImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnRotateZoomInBilinearImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnRotateZoomInBilinearImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnMirrorVerImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMirrorVerImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnMirrorHorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMirrorHorImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnMoveImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMoveImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnMorphingImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMorphingImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnHistoStretchImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHistoStretchImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEndInImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEndInImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnHistoEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHistoEqualImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEmbossImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEmbossImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnBlur1Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBlur1Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnBlur2Image()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBlur2Image();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnSharpImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSharpImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnSharpHfImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSharpHfImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnSharpLfImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSharpLfImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnGaussianImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnGaussianImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgeVerImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgeVerImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgeHorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgeHorImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgeHomogenImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgeHomogenImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgeDiffImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgeDiffImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgeRobertsImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgeRobertsImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgePrewittImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgePrewittImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgeSobelImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgeSobelImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgeLaplacianImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgeLaplacianImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgeLogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgeLogImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}


void CGrayScaleImageProcessingView::OnEdgeDogImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGrayScaleImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEdgeDogImage();
	Invalidate(TRUE); // OnDraw() 호출 효과
}
