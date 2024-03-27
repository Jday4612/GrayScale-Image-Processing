
// GrayScaleImageProcessingView.h: CGrayScaleImageProcessingView 클래스의 인터페이스
//

#pragma once


class CGrayScaleImageProcessingView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGrayScaleImageProcessingView() noexcept;
	DECLARE_DYNCREATE(CGrayScaleImageProcessingView)

// 특성입니다.
public:
	CGrayScaleImageProcessingDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGrayScaleImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEqualImage();
	afx_msg void OnAddImage();
	afx_msg void OnMulImage();
	afx_msg void OnAndImage();
	afx_msg void OnOrImage();
	afx_msg void OnXorImage();
	afx_msg void OnNotImage();
	afx_msg void OnGammaImage();
	afx_msg void OnCapImage();
	afx_msg void OnCupImage();
	afx_msg void OnPosterizingImage();
	afx_msg void OnStressImage();
	afx_msg void OnBwImage();
	afx_msg void OnBwAvgImage();
	afx_msg void OnBwMedImage();
	afx_msg void OnZoomOutImage();
	afx_msg void OnZoomOutAvgImage();
	afx_msg void OnZoomOutMedImage();
	afx_msg void OnZoomIn1Image();
	afx_msg void OnZoomIn2Image();
	afx_msg void OnZoomInBilinearImage();
	afx_msg void OnRotate1Image();
	afx_msg void OnRotate2Image();
	afx_msg void OnRotateZoomInImage();
	afx_msg void OnRotateZoomInBilinearImage();
	afx_msg void OnMirrorVerImage();
	afx_msg void OnMirrorHorImage();
	afx_msg void OnMoveImage();
	afx_msg void OnMorphingImage();
	afx_msg void OnHistoStretchImage();
	afx_msg void OnEndInImage();
	afx_msg void OnHistoEqualImage();
	afx_msg void OnEmbossImage();
	afx_msg void OnBlur1Image();
	afx_msg void OnBlur2Image();
	afx_msg void OnSharpImage();
	afx_msg void OnSharpHfImage();
	afx_msg void OnSharpLfImage();
	afx_msg void OnGaussianImage();
	afx_msg void OnEdgeVerImage();
	afx_msg void OnEdgeHorImage();
	afx_msg void OnEdgeHomogenImage();
	afx_msg void OnEdgeDiffImage();
	afx_msg void OnEdgeRobertsImage();
	afx_msg void OnEdgePrewittImage();
	afx_msg void OnEdgeSobelImage();
	afx_msg void OnEdgeLaplacianImage();
	afx_msg void OnEdgeLogImage();
	afx_msg void OnEdgeDogImage();
};

#ifndef _DEBUG  // GrayScaleImageProcessingView.cpp의 디버그 버전
inline CGrayScaleImageProcessingDoc* CGrayScaleImageProcessingView::GetDocument() const
   { return reinterpret_cast<CGrayScaleImageProcessingDoc*>(m_pDocument); }
#endif

