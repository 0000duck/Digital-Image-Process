/*************************************************
Copyright:Naihai
Author: Naihai
Date:2017-10-8
Description:BMP�ļ�����Ҫ����
**************************************************/
#include "Fourier.h"
#include <complex>
#include <math.h>
using namespace std;

 
#pragma once
class BmpCommonOp :
	public CDocument
{
public:
	BmpCommonOp();
	~BmpCommonOp();


	//��Ա����
	complex<double>* m_TimeDomain; //��άԭͼ��ʱ��������
	complex<double>* m_TimeDomainB;
	complex<double>* m_TimeDomainG;
	complex<double>* m_TimeDomainR;
	complex<double>* m_FrequencyDomain; //��άԭͼ��FFT�任�õ���Ƶ������
	complex<double>* m_FrequencyDomainB;
	complex<double>* m_FrequencyDomainG;
	complex<double>* m_FrequencyDomainR;

	int m_nImageWidth;  //��0��������ͼ��� 
	int m_nImageHeight;//��0��������ͼ���
	int m_nLineByte;    //ͼ��һ����ռ�ֽ���  
	int m_nLineBytePer;//ÿ��ͨ�� ͼ��һ����ռ�ֽ���  
	int m_isExpanded; //�Ƿ�ִ���˲�0����
	int m_nImageSize; //��ͼ���С byte
	int m_nImageSizePer; //��ͼ���С byte ÿ��ͨ��
	int m_bFourierinit; //�Ƿ��ʼ���� 1 yes 0no


	//��Ա����

	void WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize);
	BYTE* AddPepperSaltNoise(BYTE * Image, double SNR, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void RGB2Gray(BYTE*Image, BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void Normalized(int * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte); //ͼ�����ݹ�һ��
	void ShowBmpImage(CDC *cdc,BYTE* Image, int Position_x, int Position_y, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//��ʾBMPͼ��
	void WriteTextOnScreen(CDC *pDC, int Position_x, int Position_y);
	
	void ImgFourierInit(int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void ImgFFT(BYTE* Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void ImgIFFT( BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void GetAmplitudespectrum(complex<double>  * src, BYTE * DstImage, int width, int height, int BitCount, int ShitFlag); //��ȡͼ���Ƶ��ͼ 8bit
	void GetAmplitudespectrum(complex<double>  * srcB, complex<double>  * srcG, complex<double>  * srcR, BYTE * DstImage, int width, int height, int BitCount, int isReverse); //24bit
	void ImgFreTemplateFilter(BYTE* DstImage, double *filter, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//Ƶ��ģ���˲�
	void ImgIdealLowPassFilter(BYTE* DstImage, int nFreq, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//�����ͨ�˲�
	void ImgButterworthLowPassFilter(BYTE* DstImage, int nOrder,  int nFreq, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//������˹��ͨ�˲�
	void ImgGaussianLowPassFilter(BYTE* DstImage, int nFreq, int a, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//��˹��ͨ�˲�
};

