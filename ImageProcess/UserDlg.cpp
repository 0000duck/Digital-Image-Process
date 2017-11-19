// UserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "UserDlg.h"
#include "afxdialogex.h"
#include "Common.h"
#include <afxinet.h> //Http
#include "time.h"
 
#include <regex> 
 
// CUserDlg �Ի���

IMPLEMENT_DYNAMIC(CUserDlg, CDialogEx)

CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_USER_LOGIN, pParent)
	, m_Email(_T(""))
	, m_Password(_T(""))
{

}

CUserDlg::~CUserDlg()
{
	///�Ͽ����ݿ⣻����
	if (m_dbfile.IsOpen()) {
		m_dbfile.Close();//

	}

}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER_LOGIIN_EM, m_Email);
	DDX_Text(pDX, IDC_EDIT_USER_LOGIIN_PA, m_Password);
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CUserDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CUserDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// CUserDlg ��Ϣ�������


BOOL CUserDlg::OnInitDialog()
{
	
	
	
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(_T("�û���¼"));

	//�������ݿ�
	CString sConnect = _T("DSN= ;server =  ;PWD= ;UID= ;database =  ; port =  "); //mysql
	try {
		m_dbfile.Open(NULL, false, false, sConnect);
		//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
	}
	catch (CDBException &e) { // ����ʧ��
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
		return false;
	}

	if (m_Userlogin) {
		UserCenter(); //�Ѿ���¼  ת����������ҳ��  
		OnCancel();//�ر�ģ̬�Ի���
	}
	
	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}




//******************�û�����*****************//
void CUserDlg::UserCenter() {
	if (!m_Userlogin) return;

	CDialog*  Dlg = new CDialog;
	Dlg->Create(IDD_DIALOG_USER_CENTER);
	Dlg->SetWindowText(_T("��������"));
	Dlg->ShowWindow(SW_SHOW);
	//��ʾ�û���Ϣ
	//SetDlgItemText(IDC_STATIC_USER_NAME, m_Name);
	//SetDlgItemText(IDC_STATIC_USER_EMAIL, m_Email);
 

}




//******************��¼*****************//
void CUserDlg::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);


	//�������md5 ͨ��http����get����õ����ܺ��ַ���
	CString requestHost = _T("doc.zhfsky.com");
	CString requestUrl;
	requestUrl.Format(_T("/api/md5/?str=%s") , m_Password);
	char responseBody[32];
 
	
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
		pFile->Read((void *)responseBody, sizeof(responseBody));
	}
	else {
		CString errText;
		errText.Format(L"POST���������룺%d", dwRet);
		AfxMessageBox(errText);
	}
	session.Close();
	pFile->Close();
	delete pFile;

	CString Password;
	for (int i = 0; i < 32;i++) {
		Password += responseBody[i];
	}
 
	//������
	if (m_Email.IsEmpty()) {
		AfxMessageBox(_T("����������!"), MB_OK, 0);
		return;
	}

	std::regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
	USES_CONVERSION;
	LPCSTR  Email_Str = (LPCSTR)T2A(m_Email);
	if (!std::regex_match(Email_Str, pattern)) {
		AfxMessageBox(_T("������Ϸ�������!"), MB_OK, 0);
		return;
	}

	if (m_Password.IsEmpty()){
		AfxMessageBox(_T("����������!"), MB_OK, 0);
		return;
	}
	


	// ���ݿ��ѯ����
	if (m_dbfile.IsOpen()) {
		//����CRecordset����
		CRecordset recordSet(&m_dbfile);
		//SQL���
		CString sqlStr;
		sqlStr.Format(_T("SELECT id, email , password FROM user WHERE email = '%s' AND password='%s'"), m_Email, Password);
		//AfxMessageBox(sqlStr);
		 
		//�򿪼�¼��
		bool  isExists = recordSet.Open(CRecordset::forwardOnly, sqlStr, CRecordset::readOnly);
		if (!recordSet.IsEOF() ) {
			//��¼�ɹ�
			//AfxMessageBox(_T("��¼�ɹ�!"));
			//��ȡ�û���Ϣ
			//recordSet.MoveFirst();
			//recordSet.GetFieldValue(_T("name"), m_Name); 
			//recordSet.GetFieldValue(_T("ip"), m_Ip);
			m_Userlogin = 1;
			UserCenter();
			OnCancel();//�ر�ģ̬�Ի���
			//д���¼��Ϣ
			CString timeStr;
			timeStr.Format(_T("%d"), time(0));
			WritePrivateProfileString(_T("Information"), _T("Login"), _T("yes"), _T("./config.ini"));
			WritePrivateProfileString(_T("Information"), _T("LoginTime"), timeStr, _T("./config.ini"));

		}
		else {
			//��¼ʧ��
			AfxMessageBox(_T("�˺Ż����������!"));
		}


	}
	else {
		AfxMessageBox(_T("���ݿ�δ����!"));
	}

}


void CUserDlg::OnBnClickedButtonRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
