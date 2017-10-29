/*************************************************
Copyright:Naihai
Author: Naihai
Date:2017-10-8
Description:BMP�ļ�����Ҫ����
**************************************************/


#pragma once
class BmpCommonOp :
	public CDocument
{
public:
	BmpCommonOp();
	~BmpCommonOp();


	//��Ա����


	//��Ա����

	void WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize);
	BYTE* AddPepperSaltNoise(BYTE * Image, double SNR, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte);
	void RGB2Gray(BYTE*Image);
	void Normalized(int * Image, BYTE * DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte); //ͼ�����ݹ�һ��
	void ShowBmpImage(CDC *cdc,BYTE* Image, int Position_x, int Position_y, int ImageWidth, int ImageHeight, int BitCount, int LineByte);//��ʾBMPͼ��
	void WriteTextOnScreen(CDC *pDC, int Position_x, int Position_y);
};

