#include "stdafx.h"
#include "Test.h"
#include "Common.h"

Test::Test()
{
}


Test::~Test()
{
}


//���ֵ�ʶ��
void Test::DigitPredict() {
	//����Images/digitsĿ¼������ͼ��
	CString szFileNameDir = _T("images\\digits\\");
	CString szFileName = szFileNameDir + "*.bmp"; //����Ŀ��ΪĿ¼�µ�����bmp�ļ�
	WIN32_FIND_DATA findData;
	HANDLE hFindFile = ::FindFirstFile(szFileName, &findData);
	if (hFindFile != INVALID_HANDLE_VALUE){
		do	{
			// ����Ϊ��.����Ŀ¼����Ŀ¼������Ϊ��..����Ŀ¼������һ��Ŀ¼
			if (findData.cFileName[0] == '.')
				continue;

			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){// �ҵ��Ĳ���Ŀ¼�����ļ�
				CString strFileName = szFileNameDir;//·��
				strFileName += findData.cFileName;//�ļ���

				//TRACE(L"%s\r\n", strFileName);
				//�ϴ�ͼ��
				Common common;
				//CString filename = _T("picture.bmp");
				CString serverHost = _T("doc.zhfsky.com");
				CString requestUrl = _T("/api/python/digit/index.php");
				common.UploadByPost(strFileName, serverHost, requestUrl);//�õ�Ԥ�������
				Sleep(500);
				
				
			}

		} while (::FindNextFile(hFindFile, &findData));
		::FindClose(hFindFile);
	}


	

	//�õ�Ԥ�������

	

}
 
