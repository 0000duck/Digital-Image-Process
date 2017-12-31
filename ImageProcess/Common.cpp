#include "stdafx.h"
#include "Common.h"
#include <afxinet.h> //Http

Common::Common()
{
}


Common::~Common()
{
}

int Common::findIndexofArr(int ar[], int n, int element)//����Ԫ�ز�����λ���±�,find(���飬���ȣ�Ԫ��)  
{
	int i = 0;
	int index = -1;//ԭʼ�±꣬û�ҵ�Ԫ�ط���-1  
	for (i = 0; i <n; i++)
	{
		if (element == ar[i])
		{
			index = i;//��¼Ԫ���±�  
		}
	}
	return index;//�����±�  
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
* Function:   GetGaussianKernel()
*
* Description:    ��ȡ���������Ϣ
*
* Input:
*
* Returns:
************************************************************************/
void Common::GetGaussianKernel(double **gaus, const int size, const double sigma){
	const double PI = 4.0*atan(1.0); //Բ���ʦи�ֵ  
	 
	return;
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

void Common::LogToFile(double * Input, int Size) {
  
   
	//CFile file(_T("log.txt"), CFile::modeCreate | CFile::modeWrite);
	//for (int i = 0; i < polarWidth * polarHeight; i++) {
	//	CString aa;
	//	aa.Format(_T("%f \t"), houghAccAry[i]);
	//	file.Write(aa, sizeof(CString));
	//}
	//// �ر��ļ�   
	//file.Close();

 }



 
/*************************************************************************
* Function:   UploadFile()
*
* Description:    HTTP�ϴ��ļ�
*
* Input:
*
* Returns:
************************************************************************/

void Common::UploadByPost(CString strFileName, CString  strServerUrl, CString strServerUploadFile)
{

	DWORD dwTotalRequestLength;
	DWORD dwChunkLength;
	DWORD dwReadLength;
	DWORD dwResponseLength;
	CHttpFile* pHTTP = NULL;

	dwChunkLength = 64 * 1024;
	void* pBuffer = malloc(dwChunkLength);
	CFile file;

	if (!file.Open(strFileName.GetBuffer(),
		CFile::modeRead | CFile::shareDenyWrite))
	{
		return;
	}

	CInternetSession session(_T("sendFile"));
	CHttpConnection *connection = NULL;

	try
	{
		//Create the multi-part form data that goes before and after the actual file upload.

		CString strHTTPBoundary = _T("----WebKitFormBoundarytcFcFiMKaoCRdCof");
		CString strPreFileData = MakePreFileData(strHTTPBoundary, file.GetFileName());
		CString strPostFileData = MakePostFileData(strHTTPBoundary);
		CString strRequestHeaders = MakeRequestHeaders(strHTTPBoundary);
		dwTotalRequestLength = strPreFileData.GetLength() + strPostFileData.GetLength() + file.GetLength();

		connection = session.GetHttpConnection(/*L"www.YOURSITE.com"*/strServerUrl.GetBuffer(), NULL, INTERNET_DEFAULT_HTTP_PORT);

		pHTTP = connection->OpenRequest(CHttpConnection::HTTP_VERB_POST, strServerUploadFile.GetBuffer());//_T("/YOUURL/submit_file.pl"));
		pHTTP->AddRequestHeaders(strRequestHeaders);
		pHTTP->SendRequestEx(dwTotalRequestLength, HSR_SYNC | HSR_INITIATE);

		//Write out the headers and the form variables
		//pHTTP->Write((LPSTR)(LPCSTR)strPreFileData.GetBuffer(), strPreFileData.GetLength());
		pHTTP->Write((LPSTR)(LPCSTR)CW2A(strPreFileData.GetBuffer()), strPreFileData.GetLength());

		//upload the file.

		dwReadLength = -1;
		int length = file.GetLength(); //used to calculate percentage complete.
		while (0 != dwReadLength)
		{
			dwReadLength = file.Read(pBuffer, dwChunkLength);
			if (0 != dwReadLength)
			{
				pHTTP->Write(pBuffer, dwReadLength);
			}
		}

		file.Close();

		//Finish the upload.
		//pHTTP->Write((LPSTR)(LPCSTR)strPostFileData.GetBuffer(), strPostFileData.GetLength());
		pHTTP->Write((LPSTR)(LPCSTR)CW2A(strPostFileData.GetBuffer()), strPostFileData.GetLength());
		pHTTP->EndRequest(HSR_SYNC);


		//get the response from the server.
		LPSTR szResponse;
		CString strResponse;
		dwResponseLength = pHTTP->GetLength();
		while (0 != dwResponseLength)
		{
			szResponse = (LPSTR)malloc(dwResponseLength + 1);
			szResponse[dwResponseLength] = '\0';
			pHTTP->Read(szResponse, dwResponseLength);
			strResponse += szResponse;
			free(szResponse);
			dwResponseLength = pHTTP->GetLength();
		}

		TRACE(L"%s", strResponse.GetBuffer());

		//��Responseд���ļ���
		CFile resultFile(_T("images/result.txt"), CFile::modeCreate | CFile::modeWrite);//
		CString aa;
		aa.Format(_T("%s \t"), strResponse.GetBuffer());
		resultFile.Write(aa, sizeof(aa));
		resultFile.Close();// �ر��ļ� 


		//close everything up.
		pHTTP->Close();
		connection->Close();
		session.Close();
	}
	catch (CInternetException* e)
	{
		TRACE(L"error: %d \n", e->m_dwError);
	}
	catch (CFileException* e)
	{
		TRACE(L"error: %d \n", e->m_cause);
	}
	catch (...)
	{
		TRACE(L" unexpected error");
	}

}


CString Common::MakeRequestHeaders(CString& strBoundary)
{
	CString strFormat;
	CString strData;
	strFormat = _T("Content-Type: multipart/form-data; boundary=%s\r\n");
	strFormat += _T("User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36\r\n");
	strFormat += _T("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n");
	strFormat += _T("Accept-Language: zh-CN,zh;q=0.9,en;q=0.8\r\n");
	strData.Format(strFormat, strBoundary);
	return strData;
}

CString Common::MakePreFileData(CString& strBoundary, CString& strFileName)
{
	CString strFormat;
	CString strData;

	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"file\"; filename=\"%s\"");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Type: text/plain");

	strFormat += _T("\r\n");
	strFormat += _T(" XXXXX ");
	strFormat += _T("\r\n\r\n");

	strData.Format(strFormat, strBoundary,/* m_Name, strBoundary,*/ strFileName);

	return strData;
}

CString Common::MakePostFileData(CString& strBoundary)
{

	CString strFormat;
	CString strData;

	strFormat = _T("\r\n");
	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"submit\"");
	strFormat += _T("\r\n\r\n");
	strFormat += _T("Submit");
	strFormat += _T("\r\n");
	strFormat += _T("--%s--");
	strFormat += _T("\r\n");

	strData.Format(strFormat, strBoundary, strBoundary);

	return strData;

}

 