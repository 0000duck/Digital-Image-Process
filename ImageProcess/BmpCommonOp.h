/*************************************************
Copyright:Naihai
Author: Naihai
Date:2017-10-8
Description:BMP�ļ�����Ҫ����
**************************************************/
#include "Fourier.h"
#include <complex>
#include <math.h>
#include <random>
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
	void WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize, int ImageWidth, int ImageHeight);
	void WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize, int Bitcount);
	BYTE* AddPepperSaltNoise(BYTE * Image, double Rate, int noiseChose, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//��������
	void RGB2Gray(BYTE*Image, BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void RGB2Gray(double *Image, double* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	//void RGB2Gray8Bit(BYTE * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256]);
	//BYTE * RGB2Gray8Bit(BYTE * Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256]);
	//BYTE * RGB2Gray8Bit(BYTE * Image, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256]);
	//BYTE * RGB2Gray8Bit(BYTE * Image, BITMAPFILEHEADER & BitmapFileHeader, BITMAPINFOHEADER & BitmapInfoHeader, RGBQUAD colorTable[256]);
	//BYTE * RGB2Gray8Bit(BYTE * Image, int ImageWidth, int ImageHeight, int BitCount);
	//BYTE * RGB24BitToGray8Bit(BYTE * Image, int ImageWidth, int ImageHeight);
	void RGB24BitToGray8Bit(BYTE * Image, BYTE * DstImage, int ImageWidth, int ImageHeight);
	void Normalized(int * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte); //ͼ�����ݹ�һ��
	void ShowBmpImage(CDC *cdc,BYTE* Image, int Position_x, int Position_y, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//��ʾBMPͼ��
	void WriteTextOnScreen(CDC *pDC, int Position_x, int Position_y);
	
	void ImgFourierInit(int ImageWidth, int ImageHeight, int BitCount);
	void ImgFFT(BYTE* Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void ImgIFFT( BYTE* DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void GetAmplitudespectrum(complex<double>  * src, BYTE * DstImage, int width, int height, int BitCount, int ShitFlag); //��ȡͼ���Ƶ��ͼ 8bit
	void GetAmplitudespectrum(complex<double>  * srcB, complex<double>  * srcG, complex<double>  * srcR, BYTE * DstImage, int width, int height, int BitCount, int isReverse); //24bit
	void ImgFreTemplateFilter(BYTE* DstImage, double *filter, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//Ƶ��ģ���˲�
	void ImgIdealPassFilter(BYTE* DstImage, int nFreq, int HLFlag, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//�����˲�
	void ImgButterworthPassFilter(BYTE* DstImage, int nOrder,  int nFreq, int HLFlag, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//������˹�˲�
	void ImgGaussianPassFilter(BYTE* DstImage, int Sigma, int HLFlag, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//��˹�˲�
	void ImgHomomorphicFilter(BYTE* Image, BYTE* DstImage, int Sigma, double c, double GammaH, double GammaL, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//̬ͬ�˲�

	BYTE* GaussianNoise(BYTE * Image, double Rate, double mean, double viarance, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//��˹����

	void ContraharmonicMeanFilter(BYTE* Image, BYTE* DstImage, int m, int n, int  q, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//��г����ֵ�˲���

	void FilterEdgeProcess(BYTE* Image,BYTE* DstImage,int a,int b, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//�˲��ı�Ե����
	void TemplateFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int *mask, int m, int n, bool needWc); //ģ���˲�
	void MeanFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int m, int n);//��ֵ�˲�
	void MedianFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int m, int n);//��ֵ�˲�
	void GaussFilter(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int m, int n);//��˹�˲�
	
	
};

