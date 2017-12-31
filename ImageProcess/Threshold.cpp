#include "stdafx.h"
#include "Threshold.h"
#include <algorithm>

Threshold::Threshold()
{
}


Threshold::~Threshold()
{
}


 
/*************************************************************************
*
* Function:   Segment()
*
* Description: ������ֵ��ͼ��ָ�
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns: double T ������ֵ
*
************************************************************************/
void Threshold::BaseThresholding(double *Image, double *DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Type, double *Args) {
	double threshold;
	//ͨ����ͬ������ȡ��ֵ
	switch (Type) {
	case THRESHOLDING_BASIC_GLOBAL:
		threshold = BasicGlobalThreshold(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, Args[0]);
		break;
	case THRESHOLDING_OTSU:
		threshold = OTSUThreshold(Image, DstImage, ImageSize);
		break;
	case THRESHOLDING_LOCAL:
		LocalThreshold(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, Args);
		break;
	case THRESHOLDING_MULTI:
		break;

	}

	if (Type == THRESHOLDING_LOCAL) {
		return;
	}

	//ͼ��ָ�� ȫ����ֵ
	for (int i = 0; i < ImageSize; i++) {
		if (Image[i] > threshold)
			DstImage[i] = 255;
		else
			DstImage[i] = 0;
	}

}


/*************************************************************************
*
* Function:   BasicGlobalThreshold()
*
* Description: ������ֵ�㷨(�����ϵĻ���ȫ����ֵ����)
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns: double T ������ֵ
*
************************************************************************/
double Threshold::BasicGlobalThreshold(double *Image, double *DstImage,int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double DetaT) {

	//��ʼ��
	int *histogram = new int[256];
	memset(histogram, 0, sizeof(int)*256);

	//ֱ��ͼ�Ҷȼ�ͳ��
	for (int i = 0; i < ImageSize; i++) {
		int pixel = Image[i];
		histogram[pixel]++; //��ǰ�Ҷȼ�+1
	}

	//Ѱ�������С�Ҷȼ�
	int histMin = GetHistMin(histogram);
	int histMax = GetHistMax(histogram);
	
	//����������ֵT
	double thresholdOld = (histMin + histMax) / 2.0; //��ʼһ��T
	double thresholdNew = histMax;
	double deta  = thresholdNew - thresholdOld;
	double mean1, mean2;
	while( abs(deta) >= DetaT ) {
		thresholdOld = thresholdNew;
		mean1 = GetHistMean(histMin, (int)thresholdOld, histogram); //С��T�ûҶ�
		mean2 = GetHistMean((int)thresholdOld, histMax + 1, histogram);//���ڵ���T�ĻҶ�
		thresholdNew = (mean1 + mean2) / 2.0;
		deta = thresholdNew - thresholdOld;
	}
	//�ڴ��ͷ�
	delete[] histogram;
	return thresholdNew;

}



/*************************************************************************
*
* Function:   IterativeThreshold()
*
* Description: ������ֵ�㷨(���ϵĻ���ȫ����ֵ����)
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns: double T ������ֵ
*
************************************************************************/
double Threshold::OTSUThreshold(double *Image, double *DstImage, int ImageSize) {


	//��ʼ��
	double *histogram = new double[256];
	memset(histogram, 0, sizeof(double) * 256);
 

	//ֱ��ͼ�Ҷȼ�ͳ�� ��Ŀ
	for (int i = 0; i < ImageSize; i++) {
		int pixel = Image[i];
		histogram[pixel]++; //��ǰ�Ҷȼ�+1
	}
	//ֱ��ͼ�Ҷȼ�ͳ�� ���� 
	for (int i = 0; i < 256; i++) {
		histogram[i] = (double(histogram[i]) / ImageSize);
	}

	//��Ҷ˹ ������ֵ
	double maxDeta = -1.0;
	double maxDetaLocation = 0.0;
	double mG = 0.0;

	for (int i = 0; i<256; i++) {
		mG += i * histogram[i];
	}

	for (int i = 0; i<256; i++) {
		double p1 = 0.0;
		double m1 = 0.0;
		double deta = 0.0;
		for (int j = 0; j <= i; j++) {
			p1 += histogram[j];
			m1 += j * histogram[j];
		}
		deta = p1 * (m1 - mG)*(m1 - mG) / (1 - p1);
		if (deta>maxDeta) {
			maxDetaLocation = i;
			maxDeta = deta;
		}
	}


	//�ڴ��ͷ�
	delete[] histogram;


	return maxDetaLocation;
 
 
	

 

}

/*************************************************************************
*
* Function:   LocalThreshold()
*
* Description: �ֲ���ֵ
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns: double T ������ֵ
*
************************************************************************/
void Threshold::LocalThreshold(double *Image, double *DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double *Args) {
	//��ʼ��
	//�������
	int m = Args[0];//���ڴ�С
	double meanPara = Args[1];//��ֵ
	double stdPara = Args[2];//��׼��


	int a = (m - 1) / 2; 


	//����
	for (int j = a; j < ImageHeight - a; j++) {
		for (int i = a; i < ImageWidth -a ; i++) {
			int position = j * LineByte + i * BitCount / 8;//��ǰ�����������ĵ�
			int surroundPosition;//8�������ص�λ��
			double tempMean = 0; //�ֲ���ֵ
			double tempDeviation = 0;//�ֲ���׼��

			for (int m = -a; m < a + 1; ++m) {
				for (int n = -a; n < a + 1; ++n) {
					surroundPosition = (j + n) * LineByte + (i + m)* BitCount / 8; //��Χ��λ�� 
					int pixel = *(Image + surroundPosition);
					tempMean += pixel;
				}
			}//��ȡ��Χ�������������
			tempMean = (double)tempMean / (m * m);//�ֲ���ֵ

			//for (int m = -a; m < a + 1; ++m) {
			//	for (int n = -a; n < a + 1; ++n) {
			//		surroundPosition = (j + n) * LineByte + (i + m)* BitCount / 8; //��Χ��λ�� 
			//		int pixel = *(Image + surroundPosition);
			//		tempDeviation += (pixel - tempMean)*(pixel - tempMean);
			//	}
			//}//��ȡ��Χ�������������
			//tempDeviation = sqrt( (double)tempDeviation / (m * m) );//�ֲ���׼��

			//��ֵ
			if (Image[position]>tempMean*meanPara) {
				DstImage[position] = 255.0;
				DstImage[position+1] = 255.0;
				DstImage[position+2] = 255.0;
			}
			else {
				DstImage[position] = 0.0;
				DstImage[position + 1] = 0;
				DstImage[position + 2] = 0;
			}

		}
	}

}



/*************************************************************************
*
* Function:   GetHistMean()
*
* Description: ���㲿��ֱ��ͼ�ľ�ֵ �Ҷȷ�Χ [start, end) ����ҿ�
*
* Input:  
*
* Returns:
*
************************************************************************/
double Threshold::GetHistMean(int Start, int End, int *Hist) {
	int count = 0;
	double value = 0;
	for (int i = Start; i < End; i++) {
		count += Hist[i];	//�ûҶȷ�Χ�ڵ���������
		value += (double)Hist[i] * i;//�ûҶȷ�Χ�ڵ�����ֵ��
	}
	return value / (double)count;
}

int Threshold::GetHistMin(int *Hist) {
	for (int i = 0; i <= 255; i++) {
		if (Hist[i] != 0)
			return i;
	}
	return -1;
}
int Threshold::GetHistMax(int *Hist) {
	for (int i = 255; i >= 0; i--) {
		if (Hist[i] != 0)
			return i;
	}
	return -1;
}
