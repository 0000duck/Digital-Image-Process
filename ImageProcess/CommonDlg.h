#pragma once


// CCommonDlg �Ի���

class CCommonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommonDlg)

public:
	CCommonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommonDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COMMON_PARA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	//��Ա����
	double m_P1;
	double m_P2;
	double m_P3;

	CString m_P1Text;
	CString m_P2Text;
//	CString m_P3Text;

	CString m_sWindowTitle;
	CString m_sHelpTitle;

	bool m_bShowP1;
	bool m_bShowP2;
	bool m_bShowP3;



	//��Ա����
 

	
	virtual BOOL OnInitDialog();
	
	CString m_P3Text;
};
