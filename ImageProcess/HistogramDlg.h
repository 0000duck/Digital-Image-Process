#pragma once


// CHistogramDlg �Ի���

class CHistogramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramDlg)

public:
	CHistogramDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHistogramDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HISTOGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:


	int * HistogramColor;
	CString m_sWindowTitle;

	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
