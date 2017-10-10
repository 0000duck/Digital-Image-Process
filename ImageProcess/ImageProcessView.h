
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


	int m_nWidth;       //ͼ��ʵ�ʿ��  
	int m_nHeight;      //ͼ��ʵ�ʸ߶�  
	int m_nDrawWidth;   //ͼ����ʾ���  
	int m_nDrawHeight;  //ͼ����ʾ�߶�  
	DWORD m_nImage;     //ͼ�����ݵ��ֽ��� ֻ��λͼ  
	DWORD m_nSize;      //ͼ���ļ���С  
	int m_nLineByte;    //ͼ��һ����ռ�ֽ���  
	int m_nBitCount;    //ͼ��ÿ��������ռλ��  
	int m_nPalette;     //λͼʵ��ʹ�õ���ɫ���е���ɫ��  

	BYTE *m_pImage;         //����ͼƬ���ݺ��ָ��  
	BITMAPFILEHEADER bfh;   //ȫ�ֱ����ļ�ͷ  
	BITMAPINFOHEADER bih;   //ȫ�ֱ�����Ϣͷ  
	RGBQUAD m_pPal[256];         //��ɫ��ָ��  

	



	//��ӳ�Ա����
	void ShowBitmap(CDC *pDc, CString BmpName); //��ʾλͼ����
	bool ReadBmp(CString FileName);              //������ȡbmp��ʽͼƬ  
	bool SaveBmp(LPCSTR lpFileName); //��������bmp��ʽͼƬ 
	void WriteCharOnImage(CDC *pDc, CString FileName, LPCTSTR Characters, int m_xPosition, int m_yPosition); //��ͼƬ��д���ַ�
	void BilinearInterpolation(int Width, int Height);//˫���Բ�ֵ
	void RotateImage(int Angle);//��ת
	



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
};

#ifndef _DEBUG  // ImageProcessView.cpp �еĵ��԰汾
inline CImageProcessDoc* CImageProcessView::GetDocument() const
   { return reinterpret_cast<CImageProcessDoc*>(m_pDocument); }
#endif

