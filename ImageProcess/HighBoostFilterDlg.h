#pragma once


// CHighBoostFilterDlg �Ի���

class CHighBoostFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHighBoostFilterDlg)

public:
	CHighBoostFilterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHighBoostFilterDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HIGHBOOST_FILTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// Kֵ
	CString m_nHighBoostK;
};
