#pragma once
class Common
{
public:
	Common();
	~Common();

	void InsertSort(int array[], int n);//��������
	int GetMedian(int array[], int n);// ��ȡ���ݵ���λ��
	void CStringToArray(CString string, float *arr);//CStringת��Ϊ����
	float * SplitString(CString str, CString split);


	void GetConfig();//��ȡ���������Ϣ
};

