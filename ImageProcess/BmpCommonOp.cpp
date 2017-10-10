#include "stdafx.h"
#include "BmpCommonOp.h"


BmpCommonOp::BmpCommonOp()
{
}


BmpCommonOp::~BmpCommonOp()
{
}






/*************************************************************************
*
* Function:  WriteBmpDataToFile ()
*
* Description:   ��BMP�ļ�����д���ļ�
*
* Input:  FileName Ҫд���ļ��ľ���·��������; bfh �ļ�ͷ bih ��Ϣͷ colorTable��ɫ��
*
* Returns:   �ɹ�����0 ʧ�ܷ��� -1 ��0
*
************************************************************************/

void BmpCommonOp::WriteBmpDataToFile(LPCSTR FileName, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], BYTE * Image, int ImageSize) {

 
	FILE *fpw = NULL;

	fopen_s(&fpw, FileName, "wb+");

	//д���ļ�ͷ
	fwrite(&BitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fpw);
	//д����Ϣͷ
	fwrite(&BitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fpw);

	//д����ɫ��
	if (BitmapInfoHeader.biBitCount == 8)  // 8bit BMP
	{
		if (BitmapInfoHeader.biClrUsed == 0) //�����ֵΪ��,����2��biBitCount���ݸ�Ԫ��
		{
			fwrite(colorTable, sizeof(RGBQUAD), 256, fpw);
		}
		else {
			fwrite(colorTable, sizeof(RGBQUAD), BitmapInfoHeader.biClrUsed, fpw);
		}
	}


	//д��λͼ��������
	fwrite(Image, ImageSize, 1, fpw);

	fclose(fpw); //�ر��ļ�ָ��

	return ;
}
