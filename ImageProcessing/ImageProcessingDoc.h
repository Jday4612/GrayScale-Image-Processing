
// ImageProcessingDoc.h: CImageProcessingDoc 클래스의 인터페이스
//


#pragma once
#include <iostream>

class CImageProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProcessingDoc() noexcept;
	DECLARE_DYNCREATE(CImageProcessingDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** m_inImageR = NULL;
	unsigned char** m_inImageG = NULL;
	unsigned char** m_inImageB = NULL;
	unsigned char** m_outImageR = NULL;
	unsigned char** m_outImageG = NULL;
	unsigned char** m_outImageB = NULL;
	unsigned char** m_dataImage = NULL;
	int m_inH = 0 ;
	int m_inW = 0;
	int m_outH = 0;
	int m_outW = 0;
	int m_dataH = 0;
	int m_dataW = 0;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	unsigned char** OnMalloc2D(int h, int w);
	template <typename T>
	void OnFree2D(T** memory, int h);
	virtual void OnCloseDocument();
	void OnEqualImage();
	void OnFreeOutImage();
	void OnGrayScale();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnAddImage();
	void OnMulImage();
	void OnAndImage();
	void OnMakeDataImage();
	void OnOrImage();
	void OnXorImage();
	void OnNotImage();
	void OnGammaImage();
	void OnCapImage();
	void OnCupImage();
	void OnPosterizingImage();
	void OnStressImage();
	void OnBwImage();
	void OnBwAvgImage();
	void OnBwMedImage();
	void OnZoomOutImage();
	void OnZoomOutAvgImage();
	void OnZoomOutMedImage();
	void OnZoomIn1Image();
	void OnZoomIn2Image();
	void OnZoomInBilinearImage();
	void OnRotate1Image();
	void OnRotate2Image();
	void OnRotateZoomInImage();
	void OnRotateZoomInBilinearImage();
	void OnMirrorVerImage();
	void OnMirrorHorImage();
	void OnMoveImage();
	void OnMorphingImage();
	void OnHistoStretchImage();
	void OnHistoEndInImage();
	void OnHistoEqualImage();
	void OnEmbossImage();
	void OnEmbossHsiImage();
	double** OnMalloc2D_double(int h, int w);
	void OnBlur1Image();
	void OnBlur2Image();
	void OnSharpImage();
	void OnSharpHfImage();
	void OnSharpLfImage();
	void OnGaussianImage();
	void OnEdgeVerImage();
	void OnEdgeHorImage();
	void OnEdgeHomogenImage();
	void OnEdgeDiffImage();
	void OnEdgeRobertsImage();
	void OnEdgePrewittImage();
	void OnEdgeSobelImage();
	void OnEdgeLaplacianImage();
	void OnEdgeLogImage();
	void OnEdgeDogImage();
	void OnChangeSatur();
	double* RGB2HSI(int R, int G, int B);
	unsigned char* HSI2RGB(double H, double S, double I);
	void OnPick();
};
