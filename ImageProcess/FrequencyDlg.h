#pragma once


// CFrequencyDlg �Ի���

class CFrequencyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFrequencyDlg)

public:
	CFrequencyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFrequencyDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FREQUENCY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	//��Ա����
	
	int m_nCutoffFre;// ��ֹƵ��
	CString m_sWindowTitle;
	CString m_sHelpTitle;

	//��Ա����
	virtual BOOL OnInitDialog();
};
