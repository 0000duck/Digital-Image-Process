#pragma once


// CImproveDlg �Ի���

class CImproveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImproveDlg)

public:
	CImproveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CImproveDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMPROVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
 
	BOOL m_bImproveYes;
	virtual BOOL OnInitDialog();
	afx_msg void OnUserLogin();
};
