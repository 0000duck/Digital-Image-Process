#pragma once


// CUserDlg �Ի���

class CUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserDlg)

public:
	CUserDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//��Ա����
	CDatabase m_dbfile;
	CString m_Email;
	CString m_Password;
	bool m_Userlogin;//�Ƿ��Ѿ���¼
	CString m_Name;
	CString m_Ip;

	//��Ա����
	virtual BOOL OnInitDialog();
	//bool UserLogin(CString email, CString password);//��¼
	void UserCenter();//
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonRegister();
};
