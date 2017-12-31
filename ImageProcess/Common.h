#pragma once
class Common
{
public:
	Common();
	~Common();

	int findIndexofArr(int ar[], int n, int element);

	void InsertSort(int array[], int n);//��������
	int GetMedian(int array[], int n);// ��ȡ���ݵ���λ��
	void CStringToArray(CString string, float *arr);//CStringת��Ϊ����
	float * SplitString(CString str, CString split);
	//void NormalDistribution();//��̬�ֲ�

	void GetGaussianKernel(double ** gaus, const int size, const double sigma);

	void GetConfig();//��ȡ���������Ϣ
	void GetHttpBody(CString Host, CString Url, BYTE *Buffer);

	void LogToFile(double * Input, int Size);

	void UploadFile(CString strFileName, CString strServerUrl, CString strServerUploadFile);

	void UploadByPost(CString strFileName, CString strServerUrl, CString strServerUploadFile);

	CString MakeRequestHeaders(CString & strBoundary);

	CString MakePreFileData(CString & strBoundary, CString & strFileName);

	CString MakePostFileData(CString & strBoundary);



	 


 
};

