#include "stdafx.h"
#include "Morphology.h"


Morphology::Morphology()
{
}


Morphology::~Morphology()
{
}



/*************************************************************************
*
* Function:   Erosion()
*
* Description: ��ʴ
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Morphology::Erosion(double * Image, double * DstImage, double *SE, int SeWidth, int SeHeight, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	
	int a = (SeWidth - 1) / 2;
	int b = (SeHeight - 1) / 2;
	memcpy(DstImage, Image, sizeof(double)*ImageSize);

	for (int j = b; j < ImageHeight - b; j++) {
		for (int i = a; i < ImageWidth - a; i++) {
			int position = j * LineByte + i * BitCount / 8;//��ǰ�������� ����Ķ���
			if (Image[position] == 255) { //���ĵ�
				//��ǰ����ǰ�� ��Ҫ����
				for (int m = -b; m < b + 1; m++) {
					for (int n = -a; n < a + 1; n++) {
						int surroundPosition = (j + m) * LineByte + (i + n) * BitCount / 8; //��Χ��λ��
						if (SE[(m + b) * SeWidth + (n + a)] == 255) {
							if (Image[surroundPosition] == 0) {
								DstImage[position] = 0;
								DstImage[position + 1] = 0;
								DstImage[position + 2] = 0;
							}
							
						}

					}
				}
			}
		}
	}
}




/*************************************************************************
*
* Function:   Dilation()
*
* Description: ����
*
* Input:  SE �ṹԪ  SeWidth SeWidth 
*
* Returns:
*
************************************************************************/
void Morphology::Dilation(double * Image, double * DstImage, double *SE, int SeWidth, int SeHeight, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
 
	int a = (SeWidth - 1) / 2;
	int b = (SeHeight - 1) / 2;
	//memset(DstImage, 0, sizeof(double)*ImageSize);

	for (int j = b; j < ImageHeight - b; j++) {
		for (int i = a; i < ImageWidth -a ; i++) {
			int position = j * LineByte + i * BitCount / 8;//��ǰ�������� ����Ķ���
			if (Image[position] == 255) {
				//��ǰ����ǰ�� ��Ҫ����
				for (int m = -b; m < b + 1; m++) {
					for (int n = -a; n < a + 1; n++) {
						 
						int surroundPosition = (j + m) * LineByte + (i + n) * BitCount / 8; //��Χ��λ��
						if (SE[(m+b) * SeWidth + (n+a)] == 255) {
							DstImage[surroundPosition] = 255;
							DstImage[surroundPosition + 1] = 255;
							DstImage[surroundPosition + 2] = 255;
						}

					}
				}
			}
		}
	}
 


}
