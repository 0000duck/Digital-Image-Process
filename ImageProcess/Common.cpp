#include "stdafx.h"
#include "Common.h"


Common::Common()
{
}


Common::~Common()
{
}

/*************************************************************************
* Function:   InsertSort()
*
* Description:    ��������
*
* Input: 
*
* Returns:  �Ӵ�С����õ�����
************************************************************************/
void Common::InsertSort(int a[], int n) {
	for (int i = 1; i<n; i++) {
		if (a[i] < a[i - 1]) {               //����i��Ԫ�ش���i-1Ԫ�أ�ֱ�Ӳ��롣С�ڵĻ����ƶ����������  
			int j = i - 1;   //�������һ������
			int x = a[i];        //����Ϊ�ڱ������洢������Ԫ��  
			a[i] = a[i - 1];           //�Ⱥ���һ��Ԫ�� (��Ϊa[i]����X�����Բ��¶�ʧ) 
			while (j >= 0 && x < a[j]) {  //�����������Ĳ���λ��  (������)
				a[j + 1] = a[j];
				j--;         //Ԫ�غ���  
			}
			a[j + 1] = x;      //���뵽��ȷλ��  
		}
	}
}




/*************************************************************************
* Function:   GetMedian()
*
* Description:    ��ȡ��λ��
*
* Input:	 
*
* Returns:  
************************************************************************/
int Common::GetMedian(int arr[], int n) 
{
	int median;
	InsertSort(arr, n);//arr�Ѿ��������
	if (n%2==1) {//������
		median = arr[(n+1) / 2];
	}
	else {//ż����
		median = (int) (arr[n / 2] + arr[n/2 -1]) /2;
	}
	return median;
	
}



/*************************************************************************
* Function:   CStringToArray()
*
* Description:    CStringת��Ϊ����
*
* Input:
*
* Returns:
************************************************************************/
void Common::CStringToArray(CString string, float *arr) {
	//USES_CONVERSION;
	 


	/*for (int i = 0; i < string.GetLength(); i++) {
		while (string.GetAt(i) != _T(",") )  {

		}
	}*/
	 
}

/*************************************************************************
* Function:   SplitString()
*
* Description:    �ָ�CStringΪ����
*
* Input:
*
* Returns:
************************************************************************/
float * Common::SplitString(CString str, CString split)
{
	int iSubStrs;
	int iPos = 0; //�ָ��λ��
	int iNums = 0; //�ָ��������
	CString strTemp = str;
	CString strRight;
	USES_CONVERSION;

	//�ȼ������ַ���������
	while (iPos != -1)
	{
		iPos = strTemp.Find(split); //��ƥ��Ļ����� - 1; ������0 ��ʼ
		if (iPos == -1)
		{
			break;
		}
		strRight = strTemp.Mid(iPos + 1);
		strTemp = strRight;
		iNums++; //���ַ���������
	}


	
	//���ַ�������
	iSubStrs = iNums + 1; //�Ӵ������� = �ָ������ + 1
	float* pStrSplit;
	pStrSplit = new float[iSubStrs];
	strTemp = str;
	CString strLeft;


	if (iNums == 0) //û���ҵ��ָ��
	{
		//���ַ����������ַ�������
		iSubStrs = 1;
		LPCSTR tempstrTemp = (LPCSTR)T2A(strTemp);
		pStrSplit[0] = atof(tempstrTemp);
		//return NULL;
	}

	for (int i = 0; i < iNums; i++)
	{
		iPos = strTemp.Find(split);
		//���Ӵ�
		strLeft = strTemp.Left(iPos);
		//���Ӵ�
		strRight = strTemp.Mid(iPos + 1);
		strTemp = strRight;
		LPCSTR tempstrLeft = (LPCSTR)T2A(strLeft);
		pStrSplit[i] = atof(tempstrLeft);
	}
	LPCSTR tempstrTemp = (LPCSTR)T2A(strTemp);
	pStrSplit[iNums] = atof(tempstrTemp);
	return pStrSplit;
}