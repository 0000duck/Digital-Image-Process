#pragma once


// CInterpolationDlg �Ի���

class CInterpolationDlg : public CDialog
{
	DECLARE_DYNAMIC(CInterpolationDlg)

public:
	CInterpolationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInterpolationDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INTERPOLATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ���
	int m_nWidth;
	// �߶�
	int m_nHeight;

	
};
