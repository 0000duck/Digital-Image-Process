
// ImageProcessView.cpp : CImageProcessView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ImageProcess.h"
#endif

#include "ImageProcessDoc.h"
#include "ImageProcessView.h"
#include "WriteCharDlg.h"
#include "InterpolationDlg.h"
#include "RotateDlg.h"
#include "HelpDlg.h"
#include "BmpCommonOp.h"
#include "HistogramDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessView

IMPLEMENT_DYNCREATE(CImageProcessView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProcessView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CImageProcessView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CImageProcessView::OnFileSave)
	ON_COMMAND(ID_WRITE_CHARCTER, &CImageProcessView::OnWriteCharcter)
	ON_COMMAND(ID_BILINEAR_INTERPOLATION, &CImageProcessView::OnBilinearInterpolation)
	ON_COMMAND(ID_ROTATE, &CImageProcessView::OnRotate)
	ON_COMMAND(ID_HELP, &CImageProcessView::OnHelp)
	ON_COMMAND(ID_SHOW_HISTOGRAM, &CImageProcessView::OnShowHistogram)
	ON_COMMAND(ID_HISTOGRAM_EQUALIZATION, &CImageProcessView::OnHistogramEqualization)
END_MESSAGE_MAP()

// CImageProcessView ����/����

CImageProcessView::CImageProcessView()
{
	// TODO: �ڴ˴���ӹ������

}

CImageProcessView::~CImageProcessView()
{
}

BOOL CImageProcessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}


void CImageProcessView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	SetScrollSizes(MM_TEXT, CSize(1200, 900));
	 
}
// CImageProcessView ����

//void CImageProcessView::OnDraw(CDC* /*pDC*/)
//{
//	CImageProcessDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
//}


// CImageProcessView ��ӡ

BOOL CImageProcessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImageProcessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImageProcessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CImageProcessView ���

#ifdef _DEBUG
void CImageProcessView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcessView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcessDoc* CImageProcessView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessDoc)));
	return (CImageProcessDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessView ��Ϣ�������


/*************************************************************/
/* numPicture������ʾͼƬ����
/* 0-��ʾ�����δ��ͼƬ 1-��ʾһ��ͼƬ 2-��ʾ����ͼƬ�ʹ���
/*************************************************************/
int numPicture = 0;
CString flag  = _T("normal"); //��־λ


//****************��ʾBMP��ʽͼƬ****************//
void CImageProcessView::ShowBitmap(CDC *pDC, CString BmpName)
{



	//����bitmapָ�� ���ú���LoadImageװ��λͼ
	HBITMAP m_hBitmap = NULL ;
	m_hBitmap = (HBITMAP)LoadImage(NULL, BmpName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);

	if (m_bitmap.m_hObject)
	{
		m_bitmap.Detach();           //�ж�CWnd�ʹ�����ϵ
	}
	m_bitmap.Attach(m_hBitmap);      //�����HBITMAP m_hBitmap��CBitmap m_bitmap����

									 //�߽�
	CRect rect;
	GetClientRect(&rect);

	//ͼƬ��ʾ(x,y)��ʼ����
	int m_showX = 0;
	int m_showY = 0;
	int m_nWindowWidth = rect.right - rect.left;   //����ͻ������
	int m_nWindowHeight = rect.bottom - rect.top;  //����ͻ����߶�

												   //���岢����һ���ڴ��豸����DC
	CDC dcBmp;
	if (!dcBmp.CreateCompatibleDC(pDC))   //���������Ե�DC
		return;

	BITMAP m_bmp;                          //��ʱbmpͼƬ����
	m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��

	CBitmap *pbmpOld = NULL;
	dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����

	//ͼƬ��ʾ���ú���stretchBlt
	pDC->StretchBlt(0, 0, m_bmp.bmWidth, m_bmp.bmHeight, &dcBmp, 0, 0, m_bmp.bmWidth, m_bmp.bmHeight, SRCCOPY);


	dcBmp.SelectObject(pbmpOld);           //�ָ���ʱDC��λͼ
	DeleteObject(&m_bitmap);               //ɾ���ڴ��е�λͼ
	dcBmp.DeleteDC();                      //ɾ��CreateCompatibleDC�õ���ͼƬDC


	/**
	* �Ƿ���ʾЧ��ͼƬ
	*/
	if (numPicture == 2) {
		//��ʾͼƬ����LoadImage  
		HBITMAP m_hBitmapChange = NULL;

		//LW_LOADMAP3DCOLORS ����ӵ�����Ч���ļ������˰�ɫ����/��·  �����������˺ü��졣��
		m_hBitmapChange = (HBITMAP)LoadImage(NULL, BmpNameLin, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_CREATEDIBSECTION);
				 

		if (m_bitmap.m_hObject) {
			m_bitmap.Detach();            //m_bitmapΪ������λͼ����  
		}
		m_bitmap.Attach(m_hBitmapChange);
		//���岢����һ���ڴ��豸����  
		CDC dcBmp;
		if (!dcBmp.CreateCompatibleDC(pDC))   //���������Ե�DC  
			return;
		BITMAP m_bmp ;                          //��ʱbmpͼƬ����  
		m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��  
		CBitmap *pbmpOld = NULL;
		dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����  


		//���ԭͼ+Ч��ͼ�� ��Ⱥ� ���ڴ��ڿ�� ���������Ĵ���
		if (m_nDrawWidth + m_bmp.bmWidth < m_nWindowWidth) {
			SetScrollSizes(MM_TEXT, CSize(m_nWindowWidth , m_bmp.bmHeight + 10)); //���ڹ��ָ߶�����Ӧ
 
		}
		else {
			SetScrollSizes(MM_TEXT, CSize(m_nDrawWidth + m_bmp.bmWidth + 12 , m_bmp.bmHeight + 10));
			
		}
		pDC->BitBlt(m_nDrawWidth + 12, 0, m_bmp.bmWidth, m_bmp.bmHeight, &dcBmp, 0, 0, SRCCOPY);
		 
		
		
		dcBmp.SelectObject(pbmpOld);	//�ָ���ʱDC��λͼ  
		DeleteObject(&m_bitmap);        //ɾ���ڴ��е�λͼ
		dcBmp.DeleteDC();               //ɾ��CreateCompatibleDC�õ���ͼƬDC
	}



}





//***************��ȡͼƬ����*************//
bool CImageProcessView::ReadBmp(CString FileName) //FileName
{


	USES_CONVERSION;
	LPCSTR FileNameChar = (LPCSTR)T2A(FileName); //��CStringת��const char*

	FILE *fp;
	errno_t err = fopen_s(&fp, FileNameChar, "rb");

	if (err != 0)
	{
		AfxMessageBox(_T("�޷����ļ�!"), MB_OK, 0);
		return 0;
	}
	//��ȡ�ļ�ͷ ���BMP��ʽ���õķ���
	fread(&bfh.bfType, sizeof(WORD), 1, fp);
	fread(&bfh.bfSize, sizeof(DWORD), 1, fp);
	fread(&bfh.bfReserved1, sizeof(WORD), 1, fp);
	fread(&bfh.bfReserved2, sizeof(WORD), 1, fp);
	fread(&bfh.bfOffBits, sizeof(DWORD), 1, fp);
	//ͼ���ļ������ֽ���
	m_nSize = bfh.bfSize;
	//�ж��Ƿ���bmp��ʽͼƬ
	if (bfh.bfType != 0x4d42)   //'BM'
	{
		AfxMessageBox(_T("����BMP��ʽͼƬ!"), MB_OK, 0);
		return 0;
	}
	//��ȡ��Ϣͷ
	fread(&bih.biSize, sizeof(DWORD), 1, fp);
	fread(&bih.biWidth, sizeof(LONG), 1, fp);
	fread(&bih.biHeight, sizeof(LONG), 1, fp);
	fread(&bih.biPlanes, sizeof(WORD), 1, fp);
	fread(&bih.biBitCount, sizeof(WORD), 1, fp);
	fread(&bih.biCompression, sizeof(DWORD), 1, fp);
	fread(&bih.biSizeImage, sizeof(DWORD), 1, fp);
	fread(&bih.biXPelsPerMeter, sizeof(LONG), 1, fp);
	fread(&bih.biYPelsPerMeter, sizeof(LONG), 1, fp);
	fread(&bih.biClrUsed, sizeof(DWORD), 1, fp);
	fread(&bih.biClrImportant, sizeof(DWORD), 1, fp);
	if (bih.biSize != sizeof(bih))
	{
		AfxMessageBox(_T("���ṹ��ռ���ֽ������ִ���"));
		return 0;
	}
	//λͼѹ�����ͣ������� 0����ѹ���� 1��BI_RLE8ѹ�����ͣ���2��BI_RLEѹ�����ͣ�֮һ
	if (bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)
	{
		AfxMessageBox(_T("λͼ��ѹ��!"));
		return 0;
	}
	
	//��ȡ��ɫ��  2 4 8λ��Ҫ  24λ����Ҫ  Ŀǰ��֧��24λ��8λ��BMPͼ����
	if (bih.biBitCount == 8)  // 8bit bmp
	{  
		if (bih.biClrUsed == 0) //�����ֵΪ��,����2��biBitCount���ݸ�Ԫ��
		{
			memset(m_pPal, 0, sizeof(RGBQUAD) * 256);
			fseek(fp, bfh.bfOffBits - sizeof(RGBQUAD) * 256, SEEK_SET);
			fread(&m_pPal, sizeof(RGBQUAD), 256, fp); //8bit BMP
		}
		else {
			memset(m_pPal, 0, sizeof(RGBQUAD)*bih.biClrUsed);
			fseek(fp, bfh.bfOffBits - sizeof(RGBQUAD)*bih.biClrUsed, SEEK_SET);
			fread(&m_pPal, sizeof(RGBQUAD), bih.biClrUsed, fp);
		}
		
	}

	//��ȡͼ��߿��ÿ��������ռλ��
	m_nHeight = bih.biHeight;
	m_nWidth = bih.biWidth;
	m_nDrawHeight = bih.biHeight;
	m_nDrawWidth = bih.biWidth;
	m_nBitCount = bih.biBitCount;   //ÿ��������ռλ��
	//����ͼ��ÿ��������ռ���ֽ�����������32�ı�����
	m_nLineByte = (m_nWidth*m_nBitCount + 31) / 32 * 4;

	//ͼƬ��С ����ϵͳ�Դ����ļ�ͷ BITMAPFILEHEADER bfh; BITMAPINFOHEADER bih; 
	//������ BITMAPFILEHEADER_ bfh; BITMAPINFOHEADER_ bih;Ҫ m_nImage = m_nLineByte * m_nHeight - 2;
	m_nImage = m_nLineByte * m_nHeight;
	//λͼʵ��ʹ�õ���ɫ���е���ɫ�� biClrUsed
	m_nPalette = 0;                       //��ʼ��

	if (bih.biClrUsed)
		m_nPalette = bih.biClrUsed;
	//����λͼ�ռ� ��СΪλͼ��С m_nImage
	m_pImage = (BYTE*)malloc(m_nImage);
	fread(m_pImage, m_nImage, 1, fp);
	fclose(fp);
	return true;
}



//****************�����ļ�****************//
bool CImageProcessView::SaveBmp(LPCSTR lpFileName) //lpFileNameΪҪ����Ϊ��λͼ�ļ���
{
	
	USES_CONVERSION;

	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin); //��CStringת��const char*

	FILE *fpo;
	errno_t err = fopen_s(&fpo, BmpFileNameLin, "rb"); //����ʱЧ���ļ��ж�ȡ����

	if (err != 0)
	{
		AfxMessageBox(_T("������Ч���ļ�!"), MB_OK, 0);
		return 0;
	}


	//����Ӱ��ȫ�ֱ���
	BITMAPFILEHEADER tempBfh ; //��ʱ�ļ�ͷ
	BITMAPINFOHEADER tempBih ; //��ʱ��Ϣͷ
	RGBQUAD tempPal[256]; //��ʱ��ɫ��

	fread(&tempBfh, sizeof(BITMAPFILEHEADER), 1, fpo); //�ļ�ͷ
	fread(&tempBih, sizeof(BITMAPINFOHEADER), 1, fpo); //��Ϣͷ
	
	//��ȡ��ɫ�� 
	if (bih.biBitCount == 8)  // 8bit bmp
	{
		if (bih.biClrUsed == 0) //�����ֵΪ��,����2��biBitCount���ݸ�Ԫ��
		{
			memset(tempPal, 0, sizeof(RGBQUAD) * 256);
			fseek(fpo, bfh.bfOffBits - sizeof(RGBQUAD) * 256, SEEK_SET);
			fread(&tempPal, sizeof(RGBQUAD), 256, fpo); //8bit BMP
		}
		else {
			memset(tempPal, 0, sizeof(RGBQUAD)*bih.biClrUsed);
			fseek(fpo, bfh.bfOffBits - sizeof(RGBQUAD)*bih.biClrUsed, SEEK_SET);
			fread(&tempPal, sizeof(RGBQUAD), bih.biClrUsed, fpo);
		}

	}

	int tempSrcImageSize = tempBfh.bfSize - tempBfh.bfOffBits; //ʵ�ʴ�С-ͷ��С=ʵ��λͼ���ݴ�С

	BYTE * tempSrcImage = (BYTE*)malloc(tempSrcImageSize);  //�����ڴ�ռ�  
	//BYTE * tempSrcImage = new BYTE[tempSrcImageSize];
	fread(tempSrcImage, tempSrcImageSize, 1, fpo);  //λͼ����

	//��BMPͼ������д���ļ�
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(lpFileName, tempBfh, tempBih, tempPal, tempSrcImage, tempSrcImageSize);

	fclose(fpo);
	free(tempSrcImage);
	//free(&tempPal);
	//delete[] tempPal;
	return true;
}


//****************��ͼƬ��д���ַ�****************//
void CImageProcessView::WriteCharOnImage(CDC *pDC,CString FileName, LPCTSTR Characters, int m_xPosition, int m_yPosition)
{

	//����bitmapָ�� ���ú���LoadImageװ��λͼ
	HBITMAP m_hBitmap;
	m_hBitmap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);


	if (m_bitmap.m_hObject)
	{
		m_bitmap.Detach();           //�ж�CWnd�ʹ�����ϵ
	}
	m_bitmap.Attach(m_hBitmap);      //�����HBITMAP m_hBitmap��CBitmap m_bitmap����

									 //�߽�
	CRect rect;
	GetClientRect(&rect);

	//ͼƬ��ʾ(x,y)��ʼ����
	int m_showX = 0;
	int m_showY = 0;
	int m_nWindowWidth = rect.right - rect.left;   //����ͻ������
	int m_nWindowHeight = rect.bottom - rect.top;  //����ͻ����߶�

	//���岢����һ���ڴ��豸����DC
	CDC dcBmp;
	if (!dcBmp.CreateCompatibleDC(pDC))   //���������Ե�DC
		return;

	BITMAP m_bmp;                          //��ʱbmpͼƬ����
	m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��

	CBitmap *pbmpOld = NULL;
	dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����

	//����������Ϣ
	CFont font;
	font.CreateFont(20, 20, 0, 0, 200, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("Times New Roman"));
	dcBmp.SetTextColor(RGB(255, 0, 0));

	dcBmp.SelectObject(&font); //����������ѡ��DC
	

	dcBmp.SetBkMode(TRANSPARENT); //����͸��

	//���ַ�����������
	//dcBmp.DrawText(Characters, sizeof(Characters), &CRect(0, 0, 100, 40), DT_CENTER); 

	dcBmp.TextOut(m_xPosition, m_yPosition, Characters, _tcslen(Characters));

	//���������ֵ�ͼƬ������ʱ�ļ���

	unsigned char *pTemp = new unsigned char[m_nLineByte*m_nHeight];
	GetDIBits(dcBmp, (HBITMAP)m_bitmap.m_hObject, 0, m_nHeight, (LPVOID)pTemp, (BITMAPINFO*)&bih, DIB_RGB_COLORS);

	USES_CONVERSION;
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin); //��CStringת��const char*

	//��BMPͼ������д���ļ�
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, bfh, bih, m_pPal, pTemp, m_nImage);

	dcBmp.SelectObject(pbmpOld);           //�ָ���ʱDC��λͼ

	numPicture = 2;
	Invalidate();
	
}






//****************˫�����ڲ�****************//
/*Ŀǰ���ڵ����⣺
1.8bit bmp����� ��ʾʱ���ְ�ɫ��·2017.10.8   ===�ѽ��2017.10.11 
*/

void CImageProcessView::BilinearInterpolation(int Width, int Height)
{
	
	//��͸ߵı���
	float f_wScale = (float) m_nWidth  / Width;
	float f_hScale = (float) m_nHeight / Height;

	 
	int DstLineByte = (Width*m_nBitCount + 31) / 32 * 4; //Ŀ��λͼÿ�д�С �ֽ�
	int DstImageSize = DstLineByte * Height;			 //Ŀ��λͼ���ݴ�С
 
	//�ֽڶ������� ���б��
	if (Width %4 != 0) {
		Width = Width + (4 - Width % 4);
	}

	BYTE *DstImage = NULL;
	DstImage = new BYTE[DstImageSize];
 

	USES_CONVERSION;
	//LPCSTR BmpFileName = (LPCSTR)T2A(BmpName);
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);

 

	//FILE *fpo;

	////��ȡͼ��  ԭͼ����Ч��ͼ? �����������������Ч��ͼ 
	//if (fopen_s(&fpo, BmpFileNameLin, "rb") == 0) { //�������Ч��ͼ ��ʹ��Ч��ͼ
	//	ReadBmp(BmpNameLin);
	//	 
	//}
	//else { //���������Ч��ͼ ��ֱ��ʹ��ԭͼ����
	//	ReadBmp(BmpName);
	//	 
	//}
	
	
	

	//����ʼ
	for (int j = 0; j < Height;j++)  //Y
	{

		float y = (float)((j + 0.5)*f_hScale - 0.5); //��ӦԴͼ���Y���� ����ͼ��ļ��������غ�
		int z_y = (int)floor(y); //����ȡ��  ��������
		float x_y = y - z_y; //С������

		if (z_y < 0) {
			x_y = 0; z_y = 0;
		}
		if (z_y > m_nHeight - 1) {
			x_y = 0; z_y = m_nHeight - 2;
		}

		for (int i = 0; i < Width;i++) //X
		{
			float x = (float)((i + 0.5)*f_wScale - 0.5); //��ӦԴͼ���X���� ����ͼ��ļ��������غ� 
			int z_x = (int)floor(x); //����ȡ��  ��������
			float x_x = x - z_x; //С������

			if (z_x < 0) {
				x_x = 0; z_x = 0;
			}
			if (z_x > m_nWidth - 1) {
				x_x = 0; z_x = m_nWidth - 2;
			}

			//8bit BMP
			if (bih.biBitCount == 8) {
				int q11 = *(m_pImage + z_x + z_y*m_nLineByte);
				int q21 = *(m_pImage + (z_x + 1) + z_y*m_nLineByte);
				int q12 = *(m_pImage + z_x + (z_y + 1)*m_nLineByte);
				int q22 = *(m_pImage + (z_x + 1) + (z_y + 1)*m_nLineByte);

				*(DstImage + j*Width + i) =  q11*(1.0 - x_x)*(1.0 - x_y) + q21*x_x*(1.0 - x_y) + q12*(1.0 - x_x)*x_y + q22*x_x*x_y;
			}

			//24bit BMP
			if (bih.biBitCount == 24) {

				//�ֱ����ԭͼ�� �ĸ��������
				unsigned int a1 = z_x * 3 + z_y*m_nLineByte;
				if (a1 > m_nImage) 	a1 = m_nImage - 2;//��ֹԽ��
				int q11_r = *(m_pImage + a1);
				int q11_g = *(m_pImage + a1 + 1);
				int q11_b = *(m_pImage + a1 + 2);

				unsigned int a2 = (z_x + 1) * 3 + z_y*m_nLineByte;
				if (a2 > m_nImage) 	a2 = m_nImage - 2;//��ֹԽ��
				int q21_r = *(m_pImage + a2);
				int q21_g = *(m_pImage + a2 + 1);
				int q21_b = *(m_pImage + a2 + 2);

				unsigned int a3 = z_x * 3 + (z_y + 1)*m_nLineByte;
				if (a3 > m_nImage) a3 = m_nImage - 2;//��ֹԽ��
				int q12_r = *(m_pImage + a3);
				int q12_g = *(m_pImage + a3 + 1);
				int q12_b = *(m_pImage + a3 + 2);


				unsigned int a4 = (z_x + 1) * 3 + (z_y + 1)*m_nLineByte;
				if (a4 > m_nImage) 	a4 = m_nImage - 2;//��ֹԽ��
				int q22_r = *(m_pImage + a4);
				int q22_g = *(m_pImage + a4 + 1);
				int q22_b = *(m_pImage + a4 + 2);

				//RGB ����
				*(DstImage + j*Width * 3 + i * 3) = q11_r*(1.0 - x_x)*(1.0 - x_y) + q21_r*x_x*(1.0 - x_y) + q12_r*(1.0 - x_x)*x_y + q22_r*x_x*x_y;
				*(DstImage + j*Width * 3 + i * 3 + 1) = q11_g*(1.0 - x_x)*(1.0 - x_y) + q21_g*x_x*(1.0 - x_y) + q12_g*(1.0 - x_x)*x_y + q22_g*x_x*x_y;
				*(DstImage + j*Width * 3 + i * 3 + 2) = q11_b*(1.0 - x_x)*(1.0 - x_y) + q21_b*x_x*(1.0 - x_y) + q12_b*(1.0 - x_x)*x_y + q22_b*x_x*x_y;




			}

		}
	}

 
	//�������



	//�ļ�ͷ����Ϣͷ���޸� 
	BITMAPFILEHEADER tempBfh = bfh; //��ʱ�ļ�ͷ
	BITMAPINFOHEADER tempBih = bih; //��ʱ��Ϣͷ

	tempBfh.bfSize = DstImageSize + tempBfh.bfOffBits;
	tempBih.biWidth = Width;
	tempBih.biHeight = Height;

	//��BMPͼ������д���ļ�
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, tempBfh, tempBih, m_pPal, DstImage, DstImageSize);

	///fclose(fpo);
	//delete[] DstImage;
	//delete[] SrcImage;
	numPicture = 2;
	Invalidate();

}






//**************ͼ����ת****************//

/*Ŀǰ���ڵ����⣺
1.ͼ��������Ч������ 2017.10.7      ===���Ż� ����˫���Բ�ֵ 2017.10.8
2.��Ե��ݻ���ĳЩ�Ƕ��±Ƚ����� 2017.10.7  


*/

void CImageProcessView::RotateImage(int Angle)
{
	//8bit BMP
	//��д�ļ�

	USES_CONVERSION;
	 
	LPCSTR BmpFileNameLin = (LPCSTR)T2A(BmpNameLin);

	//FILE *fpo;
	////��ȡͼ��  ԭͼ����Ч��ͼ? �����������������Ч��ͼ 
	//if (fopen_s(&fpo, BmpFileNameLin, "rb") == 0) { //�������Ч��ͼ ��ʹ��Ч��ͼ
	//	ReadBmp(BmpNameLin);
	//	fclose(fpo);
	//}
	//else { //���������Ч��ͼ ��ֱ��ʹ��ԭͼ����
	//	ReadBmp(BmpName);
	//	fclose(fpo);
	//}

 

	


	/*����PA=3.14ʱʹ�õķ�����arcsin(1.0/2)*6��Ϊ��*/
	double PA; //3.1415926
	PA = asin(0.5) * 6;

	double degree;
	degree = (double) PA*Angle / 180; //����

	int XCenter = (int)bih.biWidth / 2;  //ԭͼ���ĵ�X����
	int YCenter = (int)bih.biHeight / 2; //ԭͼ���ĵ�Y����


	

	//����ʼ


	//Դͼ������

	/*int x_pre;
	int y_pre;*/
	float x_pre; //˫���Բ�ֵ 
	float y_pre;


	//ֱ������Ŀ��ͼ���С Ҳ����ͨ����ѧ���� �ԶԽ��߳��ȵ���Ϊ���յĿ��
	//int DstImageWidth = 2 * m_nWidth; //ע�������ص�λ �����ֽڵ�λ
	//int DstImageHeight = 2 * m_nHeight;

	int DstImageWidth = (int) sqrt(m_nWidth*m_nWidth + m_nHeight*m_nHeight) + 1;
	if (DstImageWidth % 4 != 0) {
		DstImageWidth = DstImageWidth + (4 - DstImageWidth % 4);
	}
	int DstImageHeight = DstImageWidth;


	int DstImageLine = (DstImageWidth * bih.biBitCount + 31) / 32 * 4;
	int DstImageSize = DstImageLine*DstImageHeight;
	BYTE * DstImage = new BYTE[DstImageSize];
	memset(DstImage, 255, DstImageSize); //��ʼ��Ϊ255 ��ɫ

	//��Ŀ��ͼ������ �ҵ���Ӧ��Դͼ������
	
	
	for (int x = 0; x < DstImageWidth; x++) {
		for (int y = 0; y < DstImageHeight; y++) {

			//������ԭͼ��Ӧ������� �漰��ֵ 

			//ֱ��int ��������ڲ�ֵ 
			//������ʱʹ������ڲ�ֵ �������ʹ��˫�����ڲ� 2017.10.7
			//x_pre = (int)((x - DstImageWidth / 2)*cos(degree) - (y - DstImageWidth / 2)*sin(degree) + XCenter);
			//y_pre = (int)((x - DstImageHeight / 2)*sin(degree) + (y - DstImageHeight / 2)*cos(degree) + YCenter);


			//2017.10.8���� ����˫�����ڲ�
			x_pre = (float)((x - DstImageWidth / 2)*cos(degree) - (y - DstImageWidth / 2)*sin(degree) + XCenter);
			y_pre = (float)((x - DstImageHeight / 2)*sin(degree) + (y - DstImageHeight / 2)*cos(degree) + YCenter);

			int z_x = (int)floor(x_pre); //�������� ����ȡ��
			float x_x = x_pre - z_x;  //С������
			int z_y = (int)floor(y_pre); //�������� ����ȡ��
			float x_y = y_pre - z_y; //С������


			//if (x_pre >= 0 && y_pre >= 0 && x_pre < m_nWidth && y_pre < m_nHeight) {
			if (z_x >= 0 && z_y >= 0 && z_x + 1 < m_nWidth && z_y + 1  < m_nHeight) {


				//8bit ��24bit�ֿ�����

				//8bit BMP����
				if (bih.biBitCount == 8) {
					//����ڲ�ֵ2017.10.7
					//*(DstImage + x + y * DstImageWidth) = *(m_pImage + x_pre + y_pre *m_nWidth);

					//˫���Բ�ֵ 2017.10.8
					int q11 = *(m_pImage + z_x + z_y*m_nLineByte);
					int q21 = *(m_pImage + (z_x + 1) + z_y*m_nLineByte);
					int q12 = *(m_pImage + z_x + (z_y + 1)*m_nLineByte);
					int q22 = *(m_pImage + (z_x + 1) + (z_y + 1)*m_nLineByte);

					*(DstImage + y*DstImageWidth + x) = q11*(1.0 - x_x)*(1.0 - x_y) + q21*x_x*(1.0 - x_y) + q12*(1.0 - x_x)*x_y + q22*x_x*x_y;


				}


				//24bit BMP����
				if (bih.biBitCount == 24) {

					//����ڲ�ֵ2017.10.7
					//int position = x_pre * 3 + y_pre *m_nWidth * 3; //ԭͼ�е�λ��
					//if (position + 2 < m_nImage) {
					//	*(DstImage + x * 3 + y * DstImageWidth * 3) = *(m_pImage + position);
					//	*(DstImage + x * 3 + y * DstImageWidth * 3 + 1) = *(m_pImage + position + 1);
					//	*(DstImage + x * 3 + y * DstImageWidth * 3 + 2) = *(m_pImage + position + 2);
					//}

					//˫���Բ�ֵ 2017.10.8

					//�ֱ����ԭͼ�� �ĸ��������
					unsigned int a1 = z_x * 3 + z_y*m_nLineByte;
					if (a1 > m_nImage) 	a1 = m_nImage - 2; //��ֹԽ��
					int q11_r = *(m_pImage + a1);
					int q11_g = *(m_pImage + a1 + 1);
					int q11_b = *(m_pImage + a1 + 2);

					unsigned int a2 = (z_x + 1) * 3 + z_y*m_nLineByte;
					if (a2 > m_nImage) 	a2 = m_nImage - 2;//��ֹԽ��
					int q21_r = *(m_pImage + a2);
					int q21_g = *(m_pImage + a2 + 1);
					int q21_b = *(m_pImage + a2 + 2);

					unsigned int a3 = z_x * 3 + (z_y + 1)*m_nLineByte;
					if (a3 > m_nImage) a3 = m_nImage - 2;//��ֹԽ��
					int q12_r = *(m_pImage + a3);
					int q12_g = *(m_pImage + a3 + 1);
					int q12_b = *(m_pImage + a3 + 2);


					unsigned int a4 = (z_x + 1) * 3 + (z_y + 1)*m_nLineByte;
					if (a4 > m_nImage) 	a4 = m_nImage - 2;//��ֹԽ��
					int q22_r = *(m_pImage + a4);
					int q22_g = *(m_pImage + a4 + 1);
					int q22_b = *(m_pImage + a4 + 2);


					*(DstImage + y*DstImageWidth * 3 + x * 3)	  = q11_r*(1.0 - x_x)*(1.0 - x_y) + q21_r*x_x*(1.0 - x_y) + q12_r*(1.0 - x_x)*x_y + q22_r*x_x*x_y;
					*(DstImage + y*DstImageWidth * 3 + x * 3 + 1) = q11_g*(1.0 - x_x)*(1.0 - x_y) + q21_g*x_x*(1.0 - x_y) + q12_g*(1.0 - x_x)*x_y + q22_g*x_x*x_y;
					*(DstImage + y*DstImageWidth * 3 + x * 3 + 2) = q11_b*(1.0 - x_x)*(1.0 - x_y) + q21_b*x_x*(1.0 - x_y) + q12_b*(1.0 - x_x)*x_y + q22_b*x_x*x_y;



				}

				
			}

		}
	}


	//�������


	//�ļ�ͷ����Ϣͷ���޸� 
	BITMAPFILEHEADER tempBfh = bfh; //��ʱ�ļ�ͷ
	BITMAPINFOHEADER tempBih = bih; //��ʱ��Ϣͷ

	tempBfh.bfSize = DstImageSize + tempBfh.bfOffBits;
	tempBih.biWidth = DstImageWidth;
	tempBih.biHeight = DstImageHeight;

	//��BMPͼ������д���ļ�
	BmpCommonOp bmpcommomop;
	bmpcommomop.WriteBmpDataToFile(BmpFileNameLin, tempBfh, tempBih, m_pPal, DstImage, DstImageSize);

 

	 
	delete[] DstImage;
	numPicture = 2;
	flag = _T("rotate");  //���α任           
	Invalidate();

	 
}



//****************˫���β�ֵ****************//
//void CImageProcessView::BicubicInterpolation(int Width, int Height) {
//
//
//
//
//
//}


//****************��ʾֱ��ͼ****************//
void  CImageProcessView::ShowHistogram() {

	memset(m_nHistogramColor, 0, sizeof(int) *256);
	for (int i = 0; i < m_nImage; i++) {
			int currentColor = m_pImage[i];
			m_nHistogramColor[currentColor]++; //��ǰ�Ҷȼ�+1
	}
}

//****************ֱ��ͼ���⻯****************//
void CImageProcessView::HistogramEqualization() {

}










 
//**************����ͼ��****************//
void CImageProcessView::OnDraw(CDC* pDC)
{
	CImageProcessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (EntName.Compare(_T("bmp")) == 0)
	{

		if (ReadBmp(BmpName)) {
			ShowBitmap(pDC, BmpName);
		}
		
	}

}


//**************�ļ���****************//
void CImageProcessView::OnFileOpen()
{
	// TODO: �ڴ���������������
 

	//Ŀǰ��֧��BMP�ļ��ı���
	CString bmpfilter = _T("BMP(*.bmp)|*.bmp||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, bmpfilter, this);

	//����ȷ����ť dlg.DoModal() ������ʾ�Ի���
	if (dlg.DoModal() == IDOK)
	{

		BmpName = dlg.GetPathName();     //��ȡ�ļ�·����   ��D:\pic\abc.bmp

		BmpNameLin = _T("picture.bmp");   //��ʱ������  
		numPicture = 1;                  //��ʾһ��ͼƬ 
		EntName = dlg.GetFileExt();      //��ȡ�ļ���չ��
		EntName.MakeLower();             //���ļ���չ��ת��Ϊһ��Сд�ַ�

		Invalidate();                    //���øú����ͻ����OnDraw�ػ滭ͼ
	}
}





//******************�ļ�����*****************//
void CImageProcessView::OnFileSave()
{
	// TODO: �ڴ���������������

	//Ŀǰ��֧��BMP�ļ��ı���
	CString bmpfilter = _T("BMP(*.bmp)|*.bmp||");
	//1-�ļ��� 0-�ļ�����
	CFileDialog dlg(0, NULL, _T("effect"), OFN_HIDEREADONLY, bmpfilter, NULL);
	//����ȷ����ť
	if (dlg.DoModal() == IDOK) {

		CString str;
		CString strName;
		CString filename;
		str = dlg.GetPathName();           //��ȡ�ļ���·��
		filename = dlg.GetFileTitle();     //��ȡ�ļ���
		int nFilterIndex = dlg.m_ofn.nFilterIndex;
		if (nFilterIndex == 1)            //���û�ѡ���ļ�������Ϊ".BMP"ʱ
		{
			str = str + _T(".bmp");	           //�Զ�����չ��.bmp

			USES_CONVERSION;
			LPCSTR lpstr = (LPCSTR)T2A(str);

			if ( SaveBmp(lpstr) )  AfxMessageBox(_T("ͼƬ����ɹ�"), MB_OK, 0);  //����bmpͼƬ  
		              

			
		}
	}
}


//******************ʹ�ð���*****************//
void CImageProcessView::OnHelp()
{
	// TODO: �ڴ���������������
	CHelpDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		
	}
}



//******************д���ַ�*****************//
void CImageProcessView::OnWriteCharcter()
{
	// TODO: �ڴ���������������
	
	//���û�е���ͼƬֱ��д���ַ� ��ʾ����
	if (numPicture == 0)
	{
		AfxMessageBox(_T("����ͼƬ�����д���ַ�!"));
		return;
	}
	//����д���ַ�����Ի���
	CWriteCharDlg dlg;
	//��ʾ�Ի���
	if (dlg.DoModal() == IDOK ) 
	{
	 

		if (dlg.m_xPosition <= 0 || dlg.m_yPosition <= 0) {
			AfxMessageBox(_T("�����������Ϊ������!"), MB_OK, 0);
			return;
		}
		if (dlg.m_xPosition > m_nWidth || dlg.m_yPosition > m_nHeight) {
			AfxMessageBox(_T("�������겻��Ϊ����ԭͼ����!"), MB_OK, 0);
			return;
		}

		if (dlg.m_wCharacter.GetLength()==0) {
			AfxMessageBox(_T("д���ַ�����Ϊ��!"), MB_OK, 0);
			return;
		}

		CDC *pDc = GetDC();	 //��ȡ��ǰDC
		WriteCharOnImage(pDc, BmpName, dlg.m_wCharacter, dlg.m_xPosition, dlg.m_yPosition);

	}

	
}


//******************˫�����ڲ�*****************//
void CImageProcessView::OnBilinearInterpolation()
{
	// TODO: �ڴ���������������

	//���û�е���ͼƬ ��ʾ����
	if (numPicture == 0)
	{
		AfxMessageBox(_T("����ͼƬ�����ִ��˫�����ڲ�!"));
		return;
	}

	//��ʾ�Ի���
	CInterpolationDlg dlg;
	
	if (dlg.DoModal() == IDOK) 
	{
		if (dlg.m_nWidth <= 0 || dlg.m_nHeight <= 0) {
			AfxMessageBox(_T("�����͸߱���Ϊ������!"), MB_OK, 0);
			return;
		}

		BilinearInterpolation(dlg.m_nWidth, dlg.m_nHeight);
		 
	}

}



//******************ͼƬ��ת*****************//
void CImageProcessView::OnRotate()
{
	// TODO: �ڴ���������������

	//���û�е���ͼƬ ��ʾ����
	if (numPicture == 0)
	{
		AfxMessageBox(_T("����ͼƬ�����ִ��ͼƬ��ת!"));
		return;
	}

	//��ʾ�Ի���
	CRotateDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		RotateImage(dlg.m_nRotateAngle); //��ת
	}



}

//******************��ʾֱ��ͼ*****************//
void CImageProcessView::OnShowHistogram()
{
	// TODO: �ڴ���������������

	//���û�е���ͼƬ ��ʾ����
	if (numPicture == 0)
	{
		AfxMessageBox(_T("����ͼƬ�������ʾֱ��ͼ!"));
		return;
	}

	//��ʾ�Ի���
	CHistogramDlg dlg;
	ShowHistogram(); //ͳ�ƻҶ�
	dlg.HistogramColor = m_nHistogramColor;  //��ͳ�ƽ�����ݸ��Ի���

	if (dlg.DoModal() == IDOK)
	{
		 
	}
}











//******************ֱ��ͼ���⻯*****************//
void CImageProcessView::OnHistogramEqualization()
{
	// TODO: �ڴ���������������
	//���û�е���ͼƬ ��ʾ����
	if (numPicture == 0)
	{
		AfxMessageBox(_T("����ͼƬ����ܽ���ֱ��ͼ���⻯����!"));
		return;
	}

	HistogramEqualization(); 

}
