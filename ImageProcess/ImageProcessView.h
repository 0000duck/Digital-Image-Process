
// ImageProcessView.h : CImageProcessView ��Ľӿ�
//

#pragma once


class CImageProcessView : public CScrollView
{
protected: // �������л�����
	CImageProcessView();
	DECLARE_DYNCREATE(CImageProcessView)

// ����
public:
	CImageProcessDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:

	//��ӳ�Ա����
	CString BmpName;	// ͼ���ļ���
	CString EntName;	// ͼ����չ��
	CBitmap m_bitmap;	//����λͼ����

	CBitmap m_bitmaplin;   //������ʱλͼ������д���  
	CString BmpNameLin;    //����ͼ�񸱱��ļ�  

	CStringArray m_pDrawText; //ͼ��Ļ��Ʊ���


	int m_nWidth;       //ͼ��ʵ�ʿ��  
	int m_nHeight;      //ͼ��ʵ�ʸ߶�  
	int m_nDrawWidth;   //ͼ����ʾ���  
	int m_nDrawHeight;  //ͼ����ʾ�߶�  
	DWORD m_nImage;     //ͼ�����ݵ��ֽ��� ֻ��λͼ  
	DWORD m_nSize;      //ͼ���ļ���С  
	int m_nLineByte;    //ͼ��һ����ռ�ֽ���  
	int m_nBitCount;    //ͼ��ÿ��������ռλ��  
	int m_nPalette;     //λͼʵ��ʹ�õ���ɫ���е���ɫ��  
	//int m_nWindowWidth; //�ͻ������
	//int m_nWindowHeight;  //�ͻ����߶�

	BYTE *m_pImage;         //����ͼƬ���ݺ��ָ��  
	BITMAPFILEHEADER bfh;   //ȫ�ֱ����ļ�ͷ  
	BITMAPINFOHEADER bih;   //ȫ�ֱ�����Ϣͷ  
	RGBQUAD m_pPal[256];         //��ɫ��ָ��  


	int m_nHistogramColor[256];  //ͳ��ֵ
	double m_dHistogramColor[256]; //�����ܶ� PDF
 
	



	//��ӳ�Ա����
	void ShowBitmap(CDC *pDc, CString BmpName); //��ʾλͼ����
	bool ReadBmp(CString FileName);              //������ȡbmp��ʽͼƬ  
	bool SaveBmp(LPCSTR lpFileName); //��������bmp��ʽͼƬ 
	void WriteCharOnImage(CDC *pDc, CString FileName, LPCTSTR Characters, int m_xPosition, int m_yPosition); //��ͼƬ��д���ַ�
	void BilinearInterpolation(int Width, int Height);//˫���Բ�ֵ
	void RotateImage(int Angle);//��ת
	//void BicubicInterpolation(int Width, int Height);//˫���β�ֵ
	void ShowHistogram(BYTE* Image);//��ʾֱ��ͼ
	void HistogramEqualization();//ֱ��ͼ���⻯
	void MeanFilter(int m, int n);//��ֵ�˲�
	void MedianFilter(int m, int n);//��ֵ�˲�
	void GaussFilter(int m);//��˹�˲�
	void TemplateFilter(BYTE* Image, BYTE* DstImage, int *mask, int m , int n ); //ģ���˲�
	void HighboostFilter(float karr[], int n);//�������˲�
	void FFT();//FFT
	void IFFT();//IFFT
	void ILPF(int nFreq);//�����ͨ�˲�
	void BLPF(int nFreq, int nOrder);//������˹��ͨ�˲�
	void GLPF(int nFreq, int a);//��˹��ͨ�˲�

 


	virtual ~CImageProcessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnWriteCharcter();
	afx_msg void OnBilinearInterpolation();
	afx_msg void OnRotate();
	virtual void OnInitialUpdate();
	afx_msg void OnHelp();
	afx_msg void OnShowHistogram();
	afx_msg void OnHistogramEqualization();
	afx_msg void OnMeanFilter();
	afx_msg void OnMedianFilter();
	afx_msg void OnGaussFilter();
	afx_msg void OnPepperSalt();
	afx_msg void OnHighboostFilter();
	afx_msg void OnUnsharpMasking();
	afx_msg void OnIlpf();
	afx_msg void OnFft();
	afx_msg void OnTest();
	afx_msg void OnIfft();
	afx_msg void OnBlpf();
	afx_msg void OnGlpf();
};

#ifndef _DEBUG  // ImageProcessView.cpp �еĵ��԰汾
inline CImageProcessDoc* CImageProcessView::GetDocument() const
   { return reinterpret_cast<CImageProcessDoc*>(m_pDocument); }
#endif

