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
};

