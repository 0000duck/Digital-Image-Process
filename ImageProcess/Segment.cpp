#pragma once

#include "stdafx.h"
#include "Segment.h"






Segment::Segment()
{
}


Segment::~Segment()
{
}



/*************************************************************************
*
* Function:   EdgeDetection()
*
* Description: ��Ե���
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Segment::EdgeDetection(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Detector, int Smooth, double Threshold, double Threshold2=0) {
	switch (Detector) {
		case EDGE_DETECTOR_ROBERT:
			break;
		case EDGE_DETECTOR_PREWITT:
			break;
		case EDGE_DETECTOR_SOBEL:
			SobelDetection(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, Smooth, Threshold);
			break;
		case EDGE_DETECTOR_LOG:
			break;
		case EDGE_DETECTOR_DOG:
			break;
		case EDGE_DETECTOR_CANNY:
			CannyDetection(Image, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, Smooth, Threshold, Threshold2);
			break;

	}
}






/*************************************************************************
*
* Function:   RobertDetection()
*
* Description: ��ȡ�ݶȵķ���(�Ƕ�)
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Segment::RobertDetection(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	//����mask
	 
}


/*************************************************************************
*
* Function:   PrewittDetection()
*
* Description: ��ȡ�ݶȵķ���(�Ƕ�)
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/


/*************************************************************************
*
* Function:   SobelDetection()
*
* Description: ��ȡ�ݶȵķ���(�Ƕ�)
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
* Smooth ʹ�ú����˲���������������
* Returns:
*
************************************************************************/
void Segment::SobelDetection(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Smooth, double Threshold) {
	
	//��ʼ��
	BmpCommonOp bmpcommonop;

	double * GrayImage = new double[ImageSize];//�Ҷ�ͼ

	double * EdgeOutImageX = new double[ImageSize];//X�ݶ�
	double * EdgeOutImageY = new double[ImageSize];//Y�ݶ�
	double * EdgeOutImage = new double[ImageSize];//�ݶȷ�ֵ
	double * EdgeAngle= new double[ImageSize];//�ݶȷ���
 
	
	//����mask
	int MaskX[] = { -1,-2,-1,  0,0,0 ,  1,2,1 };//3x3 sobel mask
	int MaskY[] = { -1,0,1,  -2,0,2,  -1,0,1 };


	//�ҶȻ�
	if (BitCount == 24)
		bmpcommonop.RGB2Gray(Image, GrayImage, ImageWidth, ImageHeight, BitCount, LineByte);
	else
		memcpy(GrayImage, Image, sizeof(double)*ImageSize);

	//��������
	switch (Smooth) {
		case SMOOTH_MEAN:
			bmpcommonop.MeanFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//��ֵ�˲�
			break;
		case SMOOTH_GAUSSIAN:
			bmpcommonop.GaussFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//��ֵ�˲�
			break;
		case SMOOTH_MEDIAN:

			break;
		default:
			break;//Ĭ�ϲ�����ƽ������
	}

	//�ݶȼ���
	bmpcommonop.TemplateFilter(GrayImage, EdgeOutImageX, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, MaskX, 3, 3, false);
	bmpcommonop.TemplateFilter(GrayImage, EdgeOutImageY, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, MaskY, 3, 3, false);

	//�ݶȷ�ֵͼ��
	for (int i = 0; i < ImageSize; ++i) {
		EdgeOutImage[i] = abs(EdgeOutImageX[i]) + abs(EdgeOutImageY[i]);
	}

	//�ݶȷ���
	GetEdgeAngle(EdgeOutImageX, EdgeOutImageY, EdgeAngle, ImageSize);

	//��ֵ
	//�ֲ���ֵ ��ȫ����ֵ����
	double maxE = *max_element(EdgeOutImage, EdgeOutImage + ImageSize);//����ݶ�
	if (Threshold<=1.0) {
		//������ֵ �ݶ����ֵ�ı���
		for (int i = 0; i < ImageSize; ++i) {
			if (EdgeOutImage[i] <maxE*Threshold)
				DstImage[i] = 0;
			else
				DstImage[i] = 255;
		}
	}
	else {
		//�̶���ֵ
		for (int i = 0; i < ImageSize; ++i) {
			if (EdgeOutImage[i] <Threshold)
				DstImage[i] = 0;
			else
				DstImage[i] = 255;
		}
	}



	//�ڴ��ͷ�
	delete[] GrayImage;
	delete[] EdgeOutImageX;
	delete[] EdgeOutImageY;
	delete[] EdgeOutImage;

}


/*************************************************************************
*
* Function:   LoGDetection()
*
* Description: ��ȡ�ݶȵķ���(�Ƕ�)
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/



/*************************************************************************
*
* Function:   DoGDetection()
*
* Description: ��ȡ�ݶȵķ���(�Ƕ�)
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/



/*************************************************************************
*
* Function:   CannyDetection()
*
* Description: ��ȡ�ݶȵķ���(�Ƕ�)
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Segment::CannyDetection(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int Smooth, double LowThreshold, double HighThreshold) {

	//��ʼ��
	BmpCommonOp bmpcommonop;

	//�ڴ����
	double * GrayImage = new double[ImageSize];//�Ҷ�ͼ

	double * EdgeOutImageX = new double[ImageSize];//X�ݶ�
	double * EdgeOutImageY = new double[ImageSize];//Y�ݶ�
	double * EdgeOutImage = new double[ImageSize];//�ݶȷ�ֵ
	double * EdgeAngle = new double[ImageSize];//�ݶȽǶ�
	//double * EdgeDirection= new double[ImageSize];//�ݶȻ������� 

	//����mask
	int MaskX[] = { -1,-2,-1,  0,0,0 ,  1,2,1 };//3x3 sobel mask
	int MaskY[] = { -1,0,1,  -2,0,2,  -1,0,1 };


	//�ҶȻ�
	if (BitCount == 24) {
		bmpcommonop.RGB2Gray(Image, GrayImage, ImageWidth, ImageHeight, BitCount, LineByte);
	}
	else {
		memcpy(GrayImage, Image, sizeof(double)*ImageSize);
	}
	


	//��������
	switch (Smooth) {
	case SMOOTH_MEAN:
		bmpcommonop.MeanFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//��ֵ�˲�
		break;
	case SMOOTH_GAUSSIAN:
		bmpcommonop.GaussFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//��˹�˲�
		break;
	case SMOOTH_MEDIAN:

		break;
	default:
		bmpcommonop.GaussFilter(GrayImage, GrayImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, 5, 5);//��˹�˲�
		break;//Ĭ�ϸ�˹�˲�
	}

	//�ݶȼ��� ���
	bmpcommonop.TemplateFilter(GrayImage, EdgeOutImageX, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, MaskX, 3, 3, false);
	bmpcommonop.TemplateFilter(GrayImage, EdgeOutImageY, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, MaskY, 3, 3, false);

	//�ݶȷ�ֵͼ��
	for (int i = 0; i < ImageSize; ++i) {
		EdgeOutImage[i] = abs(EdgeOutImageX[i]) + abs(EdgeOutImageY[i]);
	}

	//�ݶȷ���
	GetEdgeAngle(EdgeOutImageX, EdgeOutImageY, EdgeAngle, ImageSize);
	//���������
	GetNearestDirection(EdgeAngle, EdgeAngle, ImageSize);//��������
	NotMaxSuppression(EdgeOutImage, EdgeOutImage, EdgeAngle, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte);//���ݶȷ�ֵͼ����зǼ�������

	//˫��ֵ���������ӱ�Ե
	DoubleThreshold(EdgeOutImage, DstImage, ImageSize, ImageWidth, ImageHeight, BitCount, LineByte, LowThreshold, HighThreshold);

	//�ڴ��ͷ�
	delete[] GrayImage;
	delete[] EdgeOutImageX;
	delete[] EdgeOutImageY;
	delete[] EdgeOutImage;
	delete[] EdgeAngle;

}



/*************************************************************************
*
* Function:   getEdgeAngle()
*
* Description: ��ȡ�ݶȵķ���(�Ƕ�)
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Segment::GetEdgeAngle(double *ImageX, double *ImageY, double *Angle, int ImageSize) {

	double x, y;
	for (int i = 0; i<ImageSize; ++i) {
		x = ImageX[i];
		y = ImageY[i];
		if (!(x == 0.0&&y == 0.0)) {
			double angle = atan2(y, x)*180.0 / PI;
			if (angle<0.0)
				angle += 360.0;
			Angle[i] = angle;
		}
		else
			Angle[i] = -1.0;
	}

}



/*************************************************************************
*
* Function:   GetNearestDirection()
*
* Description: ��ȡ�ݶȷ�������Ļ�����Ե���� 
*
* Input:  
*	Edge �ݶȷ�������(ע��������0~360 ������-180~180) ˮƽ -45 ��ֱ +45 => 1.0 2.0 3.0 4.0 
*	ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Segment::GetNearestDirection(double* Edge, double* DstEdge, int ImageSize) {
	double angle = 0.0;
	for (int i = 0; i<ImageSize; i++) {
		angle = Edge[i];
		if (angle< 22.5 && angle>= 0)//ˮƽ��Ե
			DstEdge[i] = 1.0;
		else if (angle<67.5 && angle >= 22.5)//-45
			DstEdge[i] = 2.0;
		else if (angle<112.5 && angle >= 67.5) //��ֱ��Ե
			DstEdge[i] = 3.0;
		else if (angle<157.5 && angle >= 112.5)//+45
			DstEdge[i] = 4.0;
		else if (angle<202.5 && angle >= 157.5)//ˮƽ��Ե
			DstEdge[i] = 1.0;
		else if (angle<247.5 && angle >= 202.5)//-45
			DstEdge[i] = 2.0;
		else if (angle<292.5 && angle >= 247.5)//��ֱ��Ե
			DstEdge[i] = 3.0;
		else if (angle<337.5 && angle >= 292.5)//+45
			DstEdge[i] = 4.0;
		else if(angle < 360 && angle >= 337.5)//ˮƽ��Ե
			DstEdge[i] = 1.0;
		else if (angle == -1.0)//��Ч�ĽǶ�
			DstEdge[i] = -1.0;
	}
}



/*************************************************************************
*
* Function:   NotMaxSuppression()
*
* Description: �Ǽ�������
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*	Edge������������
*
* Returns:
*
************************************************************************/
void Segment::NotMaxSuppression(double* Image, double* DstImage, double* Edge, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	
	memcpy(DstImage, Image, sizeof(double)*ImageSize);
	//int wSize = 3;//���ô��ڴ�СΪ3x3 ��8���� 
	for (int j = 1; j < ImageHeight-1; j++) {//�߽��1�����ز�����
		for (int i = 1; i < ImageWidth-1; i++) {
			int position = j * LineByte + i * BitCount/8;//��ǰ�����������ĵ� ��p5 arr[5]
			int surroundPosition;//8�������ص�λ��

			double *arr = new double[9];//��Ŵ�������ֵ
			memset(arr, 0, sizeof(double)*9);//��ʼ��Ϊ0
			int k = 0;
			for (int m = -1; m < 2; ++m) {
				for (int n = -1; n < 2; ++n) {
					surroundPosition = (j + n) * LineByte + (i + m)* BitCount / 8; //��Χ��λ��
					arr[k] = *(Image + surroundPosition);
					k++;
				}
			}//��ȡ��Χ�������������
			 
			switch(int(Edge[position])){
				case 1://ˮƽ
					if (arr[5] >= arr[4] && arr[5] >= arr[6])
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = arr[5];
					else
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = 0;
						 
					break;
				case 2://-45
					if (arr[5] >= arr[3] && arr[5] >= arr[7])
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = arr[5];
					else
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = 0;
					break;
				case 3://��ֱ
					if (arr[5] >= arr[2] && arr[5] >= arr[8])
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = arr[5];
					else
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = 0;
					break;
				case 4://+45
					if (arr[5] >= arr[1] && arr[5] >= arr[9])
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = arr[5];
					else
						for (int kk = 0; kk < BitCount / 8; kk++)
							DstImage[position + kk] = 0;
					break;
				default:
					break;

			}

		}
	}

}



/*************************************************************************
*
* Function:   DoubleThreshold()
*
* Description: ˫��ֵ����
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Segment::DoubleThreshold(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double LowThreshold, double HighThreshold) {
	
	memcpy(DstImage, Image, sizeof(double)*ImageSize);//Դ������Ŀ��ͼ��

	//˫��ֵ�򵥴���
	for (int i = 0; i < ImageSize;i++) {
		if (Image[i] < LowThreshold)
			DstImage[i] = 0;
		if(Image[i] > HighThreshold)
			DstImage[i] = 255;//ǿ���ص�
	}

	//�м� �����ص�
	for (int j = 1; j < ImageHeight - 1; j++) {//�߽��1�����ز�����
		for (int i = 1; i < ImageWidth - 1; i++) {
			int position = j * LineByte + i * BitCount / 8;//��ǰ�����������ĵ� ��p5 arr[5]

			//��ǰ�Ѿ���255��0 ֱ���˳��ò�ѭ��
			if ( (DstImage[position] == 255) || (DstImage[position] == 0) ){
				continue;
			}
				

			int surroundPosition;//8�������ص�λ��

			double *arr = new double[9];//���8��������ֵ
			memset(arr, 0, sizeof(double) * 9);//��ʼ��Ϊ0
			int k = 0;
			for (int m = -1; m < 2; m++) {
				for (int n = -1; n < 2; n++) {
					surroundPosition = (j + n) * LineByte + (i + m)* BitCount / 8 ; //��Χ��λ��
					arr[k] = *(DstImage + surroundPosition);
					k++;
				}
			}//��ȡ��Χ�������������

			double maxE = *max_element(arr, arr + 9);//�������������

			if (maxE == 255) {
				for (int kk = 0; kk < BitCount / 8; kk++) {
					DstImage[position + kk] = 255;
				}
					
			}
			else {
				for (int kk = 0; kk < BitCount / 8; kk++) {
					DstImage[position + kk] = 0;
				}	
			}
				
		}
	}
 
}









/*************************************************************************
*
* Function:   SlopeAdjust()
*
* Description: �Ƕ�У��
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Segment::SlopeAdjust(double *Image, double *DstImage, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	
}



/*************************************************************************
*
* Function:   RectSeg()
*
* Description: ���ο�ķָ� 
*
* Input:  Image ͼ������ RectPoints���������Ϣ
*
* Returns: double* �ָ��õ��ľ��ο�
*
************************************************************************/
double* Segment::RectSeg(double *Image, vector<CPoint> rectPoints, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {
	
	 
	int minX = min(rectPoints[0].x, rectPoints[1].x) + 5;
	int maxX = max(rectPoints[2].x, rectPoints[3].x) - 5;
	int minY = min(rectPoints[0].y, rectPoints[1].y) + 5;
	int maxY = max(rectPoints[2].y, rectPoints[3].y) - 5;

	int digImWidth = (maxX - minX);
	int digImHeight = (maxY - minY);
	int digImLineByte = (digImWidth*BitCount + 31) / 32 * 4;
	int digImSize = digImLineByte * digImHeight;
	//�ڴ����
	double * digOnlyImage = new double[digImSize];
	//��ʼ��
	for (int i = 0;i < digImSize;i++) {
		digOnlyImage[i] = 0;
	}

	for (size_t j = minY, jj = 0; j < maxY, jj<digImHeight; j++, jj++) {
		for (size_t i = minX, ii = 0; i < maxX, ii<digImWidth; i++, ii++) {
			int position = j * LineByte + i * BitCount / 8;//��ǰ�����������ĵ�
			int positionDig = jj * digImLineByte + ii * BitCount / 8;//��ǰ�����������ĵ�
			for (int k = 0;k < BitCount / 8;k++) {
				digOnlyImage[positionDig + k] = Image[position + k];//��ԭʼͼ���н�ȡ
			}
		}
	}

	//���³�Ա������Ϣ
	m_RectSegWidth = digImWidth;
	m_RectSegHeight = digImHeight;
	m_RectSegLineByte = digImLineByte;
	m_RectSegSize = digImSize;
	//�ļ�ͷ����Ϣͷ�ĸ���
	m_RectSegbfh = BitmapFileHeader;
	m_RectSegbih = BitmapInfoHeader;
	m_RectSegbfh.bfSize = BitmapFileHeader.bfOffBits + digImSize;
	m_RectSegbih.biWidth = digImWidth;
	m_RectSegbih.biHeight = digImHeight;
	m_RectSegbih.biSizeImage = digImSize;
 

	return digOnlyImage;
}



/*************************************************************************
*
* Function:   DigitalSegPosition()
*
* Description: �����и�λ�ò��� 
*
* Input:  Image ����õ��ľ��ο��ڵ�����ͼ��(��ֵ�������)����  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns: vector<CPoint>point �������ֵ���ʼλ�� 
*
************************************************************************/
vector<CPoint> Segment::DigitalSegPosition(double *Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	int *Arr = new int[ImageWidth];
	memset(Arr, 0 ,sizeof(int)* ImageWidth);

	//��x��ͶӰ
	int biasy = 10;
	for (int i = 0; i < ImageWidth; i++) {
		for (int j = biasy; j < ImageHeight- biasy; j++) {
			int position = j * LineByte + i * BitCount / 8;//��ǰ�����������ĵ�
			//B��ͨ��
			if (Image[position] == 255) {
				Arr[i] += 1;
			}
		}
	}

	//���ݼ���ҵ��������ֵ���ʼλ��(������)
	int biasx = 100;//ȥ��ǰ��mm��ĸ��Ӱ��
	int start = 0;
	int end = 0;
	bool flag = false;
	vector<CPoint> point;//x=start y=end
	for (int i = biasx; i < ImageWidth; i++) {
		int maxheight = 0;
		if (!flag && Arr[i] > 10) {//��������
			//����
			int *temarr = new int[ImageHeight];
			
			for (int kk = ImageHeight-5;kk>0;kk--) {
				int position = kk * LineByte + i * BitCount / 8;
				if (Image[position] == 255) {
					maxheight = kk;//�����ֵĸ߶�
					break;
				}	
			}
			if (maxheight > 30) {//���Ǽ���߶ȴ���20��ȷʵ������  ����������
				flag = true;
				start = i;
			}
		}
		else if (Arr[i] <= 5 && flag) {//������� 
			flag = false;
			end = i;
			if (end - start < 20 && maxheight < 20)//�߶ȺͿ�Ⱦ��ǳ�С ���ǵ� ��������  ��ȥ
				continue;
			point.push_back(CPoint(start, end));
		}
	}

	return point;

}

/*************************************************************************
*
* Function:   DigitalSeg()
*
* Description: ���ַָ�
*
* Input:  Image ����õ��ľ��ο��ڵ�����ͼ��(��ֵ�������)����
*
* Returns: �� ֱ�����ͼ�񵽱����ļ�
*
************************************************************************/
void Segment::DigitalSeg(double *Image, BITMAPFILEHEADER BitmapFileHeader, BITMAPINFOHEADER BitmapInfoHeader, RGBQUAD colorTable[256], int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

 
	//�������ֵ���ʼλ��
	vector<CPoint> digSegPoints = DigitalSegPosition(Image, ImageWidth, ImageHeight, BitCount, LineByte);
	int testsize = ImageHeight * LineByte;
	//��ͼ������и�
	int biasy = 0;
	int digHeight = 160;//�������־�Ϊ 160 �߶�

	int digbaisx = 5;//��ǰƫ��
	int digbiasy = 5;//���ƫ��

	for (int k = 0;k < digSegPoints.size();k++) {
		//ƫ�ô���
		/*digSegPoints[k].y += digbiasy;
		digSegPoints[k].x -= digbaisx;*/

		//�����ڴ�
		int width = digSegPoints[k].y - digSegPoints[k].x;
		int height = digHeight;
		int lineByte = (width* BitCount + 31) / 32 * 4;
		int imageSize = lineByte * height;
		BYTE *ImageSeg = new BYTE[imageSize];
		memset(ImageSeg, 0, imageSize);

		for (size_t i = digSegPoints[k].x, ii = 0; i < digSegPoints[k].y, ii<width; i++, ii++) {//x
			for (size_t j = 0, jj = 0; j < height, jj<height; j++, jj++) {//y
				
				int position = j * LineByte + i * BitCount / 8;//��ǰ�����������ĵ�
				int positionDig = jj * lineByte + ii * BitCount / 8;//��ǰ����
				if (position < ImageHeight*LineByte) {
					for (int kk = 0;kk < BitCount / 8;kk++) {
						ImageSeg[positionDig + kk] = Image[position];//�Ӿ��ο�ͼ���н�ȡ��������
					}
				}
				
			}
			
		}


		//��BMPͼ������д���ļ�
		BmpCommonOp bmpcommonop;
		CString TempFileName;
		CreateDirectory(_T("images\\digits"), NULL);
		TempFileName.Format(_T("images/digits/picture_%d.bmp"), k);
		USES_CONVERSION;
		LPCSTR BmpFileNameLin = (LPCSTR)T2A(TempFileName);
		bmpcommonop.WriteBmpDataToFile(BmpFileNameLin, BitmapFileHeader, BitmapInfoHeader, colorTable, ImageSeg, imageSize, width, height);

	}

}

