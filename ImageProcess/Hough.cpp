#include "stdafx.h"
#include "Hough.h"
#include <algorithm>

Hough::Hough()
{
}



Hough::~Hough()
{
}


void Hough::HoughLines(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int type) {
	memcpy(DstImage, Image, sizeof(double)*ImageSize);//Դ������Ŀ��ͼ��



	//����������ռ��ʼ��
	int maxTheta = 90;  //Theta -90~+90
	int maxRho = sqrt(ImageWidth*ImageWidth + ImageHeight * ImageHeight) + 1;//�Խ��߳���  -D D

	 //�ۼ����� ����Ϊ�Ƕ�theta  ����Ϊ�뾶rho
	int accArrWidth = maxTheta * 2;//180
	int accArrHeight = maxRho * 2;//2D
	int *houghAccAry = new int[accArrWidth * accArrHeight];// -90~90 -D ~D
	memset(houghAccAry, 0, sizeof(int)*accArrWidth * accArrHeight);

	int biasX = 50;//��ֹͼ��߽��Ӱ��
	int biasY = 50;

	//�����ۼ����� Hough accumulator
	for (int j = biasY; j < ImageHeight - biasY; j++) {//y
		for (int i = biasX; i < ImageWidth - biasX; i++) {//x

			int position = j * LineByte + i * BitCount / 8;//��ǰ�����������ĵ�										    
			if (Image[position] == 255) {//��Ե	255Ϊ��ע��
										 //�������нǶ�
				for (int k = 0;k < accArrWidth; k++) {//theta  0~180 => -90~ 90
					double radian = (k - 90) * PI / 180;//ʵ�ʵĻ���
					int rho = i * cos(radian) + j * sin(radian) + 0.5;//ʵ�ʵļ���
					int tempy = rho + accArrHeight / 2; //������洢ʱ��λ��y
					int tempx = k;//�������д洢��λ�� x
					houghAccAry[tempy * accArrWidth + k] += 1;
				}
			}
		}
	}


	/* ֱ�߼�� Ѱ��������ֵ�ķ�ֵ��
	* ˼·�� ����ͼ���Ϊ���� �����ȼ��ϳ��ĺ��� �ټ��϶̵Ĵ���  ʹ��vector�洢������ֵ��theta rho������
	*/

	//���߼�� ���߻�������ˮƽ�� 
	vector<ThetaRho> thetaRhoLong;
	int longLineLength = 280;
	for (int j = 0; j < accArrHeight; j++) {//rho 
		for (int i = 0; i<accArrWidth; i++) {//theta �Ƕ� 0-180

			if (houghAccAry[j * accArrWidth + i] >= longLineLength) {
				double theta = (i - 90);//ʵ�ʵĽǶ�
				int rho = j - accArrHeight / 2;//ʵ�ʵļ���
				if (abs(theta) <= 90 && abs(theta) >= 85) {//������Ϊ��ˮƽ��
					thetaRhoLong.push_back(ThetaRho(theta, rho));//�洢
				}

			}
		}
	}

	//���߼�� ���߻������Ǵ�ֱ�� 
	vector<ThetaRho> thetaRhoShort;
	int shortLineLength = 180;
	for (int j = 0; j < accArrHeight; j++) {//rho 
		for (int i = 0; i<accArrWidth; i++) {//theta �Ƕ� 0-180
			if ((houghAccAry[j * accArrWidth + i] >= 140) && (houghAccAry[j * accArrWidth + i] < 180)) {
				double theta = (i - 90);//ʵ�ʵĽǶ�
				int rho = j - accArrHeight / 2;//ʵ�ʵļ���
				if (abs(theta) <= 5) { //������Ϊ�Ǵ�ֱ��
					thetaRhoShort.push_back(ThetaRho(theta, rho));//�洢
				}
			}
		}
	}

	//ֱ�߼� �����ֱ�߾�ֵ�� ��Ϊһ��ֱ�� ����ֱ�ߵ���Ŀ
	MeanLine(thetaRhoLong, thetaRhoLong.size());
	MeanLine(thetaRhoShort, thetaRhoShort.size());


	/* ����
	* ˼·�� ��Ϊ�������� �� �ϲ����� ����������Ϊ������Ѱ�ҽ���ķ���
	*/
	//double * LineImage = new double[ImageSize];//����ֱ�� ˮƽ+��ֱ (��ɫ) ������ԭ��Ϣ
	double * longLineImage = new double[ImageSize];//����ˮƽ�� (��ɫ) ������ԭ��Ϣ
	double * shortLineImage = new double[ImageSize];//���д�ֱ�� (��ɫ) ������ԭ��Ϣ
													//memset(LineImage, 0, sizeof(double)*ImageSize);
	memset(longLineImage, 0, sizeof(double)*ImageSize);
	memset(shortLineImage, 0, sizeof(double)*ImageSize);

	for (int i = 0;i < thetaRhoLong.size();i++) {
		DrawLine(longLineImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoLong[i].theta, thetaRhoLong[i].rho);
		DrawLine(DstImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoLong[i].theta, thetaRhoLong[i].rho);//
	}

	for (int i = 0;i < thetaRhoShort.size();i++) {
		DrawLine(shortLineImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoShort[i].theta, thetaRhoShort[i].rho);
		DrawLine(DstImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoShort[i].theta, thetaRhoShort[i].rho);//
	}

}

/*************************************************************************
*
* Function:   HoughLines()
*
* Description: ����任���ֱ��
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Hough::HoughLines(double* Image, double* DstImage, int ImageSize, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	memcpy(DstImage, Image, sizeof(double)*ImageSize);//Դ������Ŀ��ͼ��
	
	

	//����������ռ��ʼ��
	int maxTheta = 90;  //Theta -90~+90
	int maxRho = sqrt(ImageWidth*ImageWidth + ImageHeight * ImageHeight) + 1;//�Խ��߳���  -D D
	
	//�ۼ����� ����Ϊ�Ƕ�theta  ����Ϊ�뾶rho
	int accArrWidth = maxTheta*2;//180
	int accArrHeight = maxRho*2;//2D
	int *houghAccAry = new int[accArrWidth * accArrHeight];// -90~90 -D ~D
	memset(houghAccAry, 0, sizeof(int)*accArrWidth * accArrHeight);

	

	//�����ۼ����� Hough accumulator
	int biasX = 2;//��ֹͼ��߽��Ӱ��
	int biasY = 20;
	CalHoughAcc(Image, houghAccAry, accArrWidth, accArrHeight, ImageWidth, ImageHeight, BitCount, LineByte, biasX, biasY);



	/* ֱ�߼�� Ѱ��������ֵ�ķ�ֵ�� 
	 * ˼·�� ����ͼ���Ϊ���� �����ȼ��ϳ��ĺ��� �ټ��϶̵Ĵ���  ʹ��vector�洢������ֵ��theta rho������
	 */

	//ȷ��������ֵ ˼·�����ֵ��ĳ������
	int maxLineLength = *std::max_element(houghAccAry, houghAccAry + accArrWidth * accArrHeight);
	
	int maxLineLengthIndex = std::distance(houghAccAry, std::max_element(houghAccAry, houghAccAry + accArrWidth * accArrHeight));
	
	int maxLineRho = maxLineLengthIndex / 180;
	int maxLineTheta = maxLineLengthIndex % 180;
	if (abs(maxLineTheta) < 5) {//��ֱ��
		if (maxLineRho < ImageWidth*0.3) {//��ֱ�߿����
			biasX = maxLineRho -5;//����ߵĲ��������� ���¼����ۼ�����
			biasX = max(biasX, 0);
			CalHoughAcc(Image, houghAccAry, accArrWidth, accArrHeight, ImageWidth, ImageHeight, BitCount, LineByte, biasX, biasY);
		}
	}
	else if (abs(maxLineTheta) > 85) {//ˮƽ��
		if (maxLineRho < ImageHeight*0.3) {//ˮƽ�߿��·�
			biasY = maxLineRho - 5;//����ߵĲ��������� ���¼����ۼ�����
			biasY = max(biasY, 0);
			CalHoughAcc(Image, houghAccAry, accArrWidth, accArrHeight, ImageWidth, ImageHeight, BitCount, LineByte, biasX, biasY);
		}
	}


	//���߼�� ���߻�������ˮƽ�� 
	vector<ThetaRho> thetaRhoLong;
	int longLineLength = maxLineLength*0.50;

 	for (int j = 0; j < accArrHeight; j++) {//rho 
		for (int i = 0; i<accArrWidth; i++) {//theta �Ƕ� 0-180

			if (houghAccAry[j * accArrWidth + i] >= longLineLength) {
				double theta = (i - 90) ;//ʵ�ʵĽǶ�
				int rho = j - accArrHeight / 2;//ʵ�ʵļ���
				if (abs(theta) <= 90 && abs(theta)>=85) {//������Ϊ��ˮƽ��
					thetaRhoLong.push_back( ThetaRho(theta, rho) );//�洢
				}
				
			}
		}
	}

	//���߼�� ���߻������Ǵ�ֱ�� 
	vector<ThetaRho> thetaRhoShort;
	int shortLineLength1 = 130;
	int shortLineLength2 = 160;

	for (int j = 0; j < accArrHeight; j++) {//rho 
		for (int i = 0; i<accArrWidth; i++) {//theta �Ƕ� 0-180
			if ( (houghAccAry[j * accArrWidth + i] >= shortLineLength1) && (houghAccAry[j * accArrWidth + i] < shortLineLength2) ) {
				double theta = (i - 90);//ʵ�ʵĽǶ�
				int rho = j - accArrHeight / 2;//ʵ�ʵļ���
				if (abs(theta)<=5) { //������Ϊ�Ǵ�ֱ��
					if (abs(abs(rho) - ImageWidth / 2) > 180) { //������߲���ͼ�����Ŀ��ĺܽ� ����Ҫ�����
						thetaRhoShort.push_back(ThetaRho(theta, rho));//�洢
					}
					
				}
			}
		}
	}

	//ֱ�߼� �����ֱ�߾�ֵ�� ��Ϊһ��ֱ�� ����ֱ�ߵ���Ŀ
	MeanLine(thetaRhoLong, thetaRhoLong.size());
	MeanLine(thetaRhoShort, thetaRhoShort.size());

	 
	/* ���� 
	* ˼·�� ��Ϊ�������� �� �ϲ����� ����������Ϊ������Ѱ�ҽ���ķ��� 
	*/
	//double * LineImage = new double[ImageSize];//����ֱ�� ˮƽ+��ֱ (��ɫ) ������ԭ��Ϣ
	double * longLineImage = new double[ImageSize];//����ˮƽ�� (��ɫ) ������ԭ��Ϣ
	double * shortLineImage = new double[ImageSize];//���д�ֱ�� (��ɫ) ������ԭ��Ϣ
	//memset(LineImage, 0, sizeof(double)*ImageSize);
	memset(longLineImage, 0, sizeof(double)*ImageSize);
	memset(shortLineImage, 0, sizeof(double)*ImageSize);

	for (int i = 0;i < thetaRhoLong.size();i++) {
		DrawLine(longLineImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoLong[i].theta, thetaRhoLong[i].rho);
		DrawLine(DstImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoLong[i].theta, thetaRhoLong[i].rho);//
	}
	
	for (int i = 0;i < thetaRhoShort.size();i++) {
		DrawLine(shortLineImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoShort[i].theta, thetaRhoShort[i].rho);
		DrawLine(DstImage, ImageWidth, ImageHeight, BitCount, LineByte, thetaRhoShort[i].theta, thetaRhoShort[i].rho);//
	}


		
	 

	//Ѱ�Ҿ������������ ���ο���ĸ���
	SelectPoints(longLineImage, shortLineImage, m_vRectPoints, ImageWidth, ImageHeight, BitCount, LineByte);


}
 

/*************************************************************************
*
* Function:   CalHoughAcc()
*
* Description: ��������ۼ�����
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*
* Returns:
*
************************************************************************/
void Hough::CalHoughAcc(double* Image,int *houghAccAry, int accArrWidth, int accArrHeight, int ImageWidth, int ImageHeight, int BitCount, int LineByte, int biasX, int biasY) {
	for (int j = biasY; j < ImageHeight - biasY; j++) {//y
		for (int i = biasX; i < ImageWidth - biasX; i++) {//x

			int position = j * LineByte + i * BitCount / 8;//��ǰ�����������ĵ�										    
			if (Image[position] == 255) {//��Ե	255Ϊ��ע��
				//�������нǶ�
				for (int k = 0;k < accArrWidth; k++) {//theta  0~180 => -90~ 90
					double radian = (k - 90) * PI / 180;//ʵ�ʵĻ���
					int rho = i * cos(radian) + j * sin(radian) + 0.5;//ʵ�ʵļ���
					int tempy = rho + accArrHeight / 2; //������洢ʱ��λ��y
					int tempx = k;//�������д洢��λ�� x
					houghAccAry[tempy * accArrWidth + k] += 1;
				}
			}
		}
	}
}

/*************************************************************************
*
* Function:   GetRectPoints()
*
* Description: ��ȡ���ο���ĸ�����Ϣ
*
* Input:
*
* Returns: vector<CPoint> 
*
************************************************************************/
vector<CPoint> Hough::GetRectPoints() {
	return m_vRectPoints;
}



/*************************************************************************
*
* Function:   MeanLine()
*
* Description: ����theat rho���ƶȽ���ֱ�ߵľ�ֵ�� Ŀ���Ǽ�����ֱͬ�ߵ���Ŀ
*
* Input:
*
* Returns:
*
************************************************************************/
void Hough::MeanLine(vector<ThetaRho> &thetaRho, int size) {

	double delt = 10;
	for (int i = 0;i < size;i++) {
		double theta = thetaRho[i].theta;
		int rho = thetaRho[i].rho;

		if (theta == 0 && rho == 0)//��Ч���� 
			continue;//�����ô�ѭ��

		int sumRho = rho;
		//����ʣ�µĲ����� ��rho�ľ�ֵ
		int k = 1;
		for (int j = 0;(j < size) && (j != i);j++) {
			if (abs(rho - thetaRho[j].rho) <= delt && abs(theta - thetaRho[j].theta) <= delt) {
				sumRho += thetaRho[j].rho;//���
				thetaRho[j].rho = 0;//���������0 ɾ��
				thetaRho[j].theta = 0;
				k++;
			}
		}
		//��ֵ
		int meanRho = double(sumRho) / k + 0.5;
		thetaRho[i].rho = meanRho;
	}

}



/*************************************************************************
*
* Function:   DrawLine()
*
* Description: �ܾ�rho��theta��ֱ��
*
* Input:  Image ͼ������  ImageWidth ImageHeight ͼ���� BitCountͼ��λ�� LineByteͼ��һ����ռ�ֽ���
*	theta ʵ�ʽǶ� rhoʵ�ʼ��� 
*
* Returns:
*
************************************************************************/
void Hough::DrawLine(double *Image, int ImageWidth, int ImageHeight, int BitCount, int LineByte, double theta, int rho) {

	double radian = theta * PI / 180;//ʵ�ʵĻ���
	if (abs(rho) <= 0.5)
		return;
	if (theta == 0 ) {//��ֱ��
		int x = rho;//x
		for (int y = 0; y < ImageHeight; y++) {//y
			int position = y * LineByte + x * BitCount / 8;
			Image[position + 2] = 255;
		}
	}
	else if (abs(theta)<45) {//��yΪ����
		//����y����x
		for (int y = 0; y < ImageHeight; y++) {//y
			int x = (rho - y * sin(radian)) / cos(radian) + 0.5;//x
			int position = y * LineByte + x * BitCount / 8;
			if (x > 0 && x < ImageWidth) {
				Image[position + 2] = 255;
			}
		}
	}
	else if(abs(theta)>=45){//��xΪ����
		//����x����y
		for (int x = 0; x < ImageWidth; x++) {//x
			int y = (rho - x * cos(radian)) / sin(radian) + 0.5;//y
			int position = y * LineByte + x * BitCount / 8;
			if (y > 0 && y < ImageHeight) {
				Image[position + 2] = 255;
			}
		}
		
	}
}







/*************************************************************************
*
* Function:   SelectPoints()
*
* Description: Ѱ�Ҿ�����������ľ��ο���ĸ��� 
*
* Input:
*
* Returns: ������������ľ��ο���ĸ���
*
************************************************************************/
void Hough::SelectPoints(double *longLineImage, double *shortLineImage, vector<CPoint> &rectPoints, int ImageWidth, int ImageHeight, int BitCount, int LineByte) {

	vector<MyStructPoint> mypoint;//���� ˮƽ���봹�ߵĽ���
	//���н���
	for (int j = 0; j < ImageHeight; j++) {//y
		for (int i = 0; i < ImageWidth; i++) {//x
			int position = j * LineByte + i * BitCount / 8;//��ǰ�����������ĵ�
			//Rͨ��
			if (longLineImage[position + 2] == 255 && shortLineImage[position + 2] == 255) {//����
				mypoint.push_back( MyStructPoint(CPoint(i,j), 0));
			}
		}
	}

	/* Ѱ�Ҿ�����������ľ��ο���ĸ���
	 * ˼·�� �����ѡ����ľ�ֵ ȷ��һ�����ĵ� 
	 *		 Ȼ��������ĵ㵽��������ľ��� 
	 *		 �����ĵ�Ϊ���Ľ�ͼ���Ϊ�ĸ����� 
	 *       ���ĸ�������ѡ�������������ĵ�  
	 *       ��4������ΪĿ���
	 */

	//�����ѡ����ľ�ֵ
	int xSum = 0, ySum = 0;
	int xCenter = 0, yCenter = 0;
	int kkk = 0;
	for (size_t i = 0; i < mypoint.size(); i++)	{
		xSum += mypoint[i].point.x;
		ySum += mypoint[i].point.y;
		kkk++;
	}
	xCenter = xSum * 1.0 / kkk + 0.5;//���ĵ�����
	yCenter = ySum * 1.0 / kkk + 0.5;
 
	//�������ĵ㵽��������ľ���  
	for (size_t i = 0; i < mypoint.size(); i++) {
		mypoint[i].distance =  (mypoint[i].point.x - xCenter)*(mypoint[i].point.x - xCenter) + (mypoint[i].point.y - yCenter)*(mypoint[i].point.y - yCenter);
	}

	//�ֿ�
	/*
	
	1  |  3
	-------
	2  |  4
	*/

	vector<MyStructPoint> mypointP1, mypointP2, mypointP3, mypointP4;
	for (size_t i = 0; i < mypoint.size(); i++) {
		if (mypoint[i].point.x < xCenter && mypoint[i].point.y >= yCenter)//1
			mypointP1.push_back(mypoint[i]);
		if (mypoint[i].point.x < xCenter && mypoint[i].point.y < yCenter)//2
			mypointP2.push_back(mypoint[i]);
		if (mypoint[i].point.x >= xCenter && mypoint[i].point.y >= yCenter)//3
			mypointP3.push_back(mypoint[i]);
		if (mypoint[i].point.x >= xCenter && mypoint[i].point.y < yCenter)//4
			mypointP4.push_back(mypoint[i]);
	}

	//��ÿ��������ݾ���������� ��С����
	InsertSort(mypointP1);
	InsertSort(mypointP2);
	InsertSort(mypointP3);
	InsertSort(mypointP4);

	//�õ����յ��ĸ���
	vector<CPoint> rectPointsC{ mypointP1[0].point , mypointP2[0].point, mypointP3[0].point, mypointP4[0].point};
	rectPoints.assign(rectPointsC.begin(), rectPointsC.end());
 
	
}


/*************************************************************************
*
* Function:   InsertSort()
*
* Description: ���ݾ����������
*
* Input: vector<MyStructPoint> a
*
* Returns: ��С����ĵ�
*
************************************************************************/
void Hough::InsertSort(vector<MyStructPoint> &a) {
	int n = a.size();
	for (int i = 1; i<n; i++) {
		if (a[i].distance < a[i - 1].distance) { //����i��Ԫ�ش���i-1Ԫ�أ�ֱ�Ӳ��롣С�ڵĻ����ƶ����������  
			int j = i - 1;   //�������һ������
			MyStructPoint x = a[i];        //����Ϊ�ڱ������洢������Ԫ��  
			a[i] = a[i - 1];           //�Ⱥ���һ��Ԫ�� (��Ϊa[i]����X�����Բ��¶�ʧ) 
			while (j >= 0 && x.distance < a[j].distance) {  //�����������Ĳ���λ��  (������)
				a[j + 1] = a[j];
				j--;         //Ԫ�غ���  
			}
			a[j + 1] = x;      //���뵽��ȷλ��
		}
	}
}



