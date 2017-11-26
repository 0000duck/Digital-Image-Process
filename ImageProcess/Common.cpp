#include "stdafx.h"
#include "Common.h"
#include <afxinet.h> //Http

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
		if (a[i] < a[i - 1]) {     //����i��Ԫ�ش���i-1Ԫ�أ�ֱ�Ӳ��롣С�ڵĻ����ƶ����������  
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



/*************************************************************************
* Function:   GetConfig()
*
* Description:    ��ȡ���������Ϣ
*
* Input:
*
* Returns:   
************************************************************************/
void Common::GetConfig() {

}



/*************************************************************************
* Function:   SetConfig()
*
* Description:    ��ȡ���������Ϣ
*
* Input:
*
* Returns:
************************************************************************/
//void Common::SetConfig(LPCTSTR lpAppName, LPCTSTR lpKeyName, LPCTSTR lpString) {
//	CFileFind finder;   //�����Ƿ����ini�ļ�
//	BOOL ifFind = finder.FindFile(_T("config.ini"));
//	CString configIni = _T("config.ini");
//	//
//	if (!ifFind)	{//�����ڣ�������һ���µ�Ĭ�����õ�ini�ļ� 
//		WritePrivateProfileStringW(_T("xwreg"), _T("IP"), _T("10.210.0.9"), configIni);
// 
//	}
//	else {
//		CString strObject;
//		 
//		WritePrivateProfileString(_T("xwreg"), _T("IP"), strObject, _T("d:\\qzze.ini"));
//	}
//
//
//
//}



/*************************************************************************
* Function:   GetHttpBody()
*
* Description:    ��ȡHTTP����
*
* Input:
*
* Returns:
************************************************************************/
void Common::GetHttpBody(CString requestHost, CString requestUrl, BYTE *Buffer) {
	//ͨ�� http GET Э��
	CInternetSession session;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
	session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

	CHttpConnection* pConnection = session.GetHttpConnection(requestHost, (INTERNET_PORT)80);
	CHttpFile* pFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, requestUrl);
	CString szHeaders = _T("Accept: text/plain, text/html, text/htm\r\n");
	pFile->AddRequestHeaders(szHeaders);//����ͷ
	pFile->SendRequest();//��������
	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);

	if (dwRet = HTTP_STATUS_OK) {
		pFile->Read((void *)Buffer, sizeof(Buffer));
	}
	else {
		CString errText;
		errText.Format(L"POST���������룺%d", dwRet);
		AfxMessageBox(errText);
	}
		
	session.Close();
	pFile->Close();
	delete pFile;
}

 