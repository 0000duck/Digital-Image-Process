#pragma once


// CWriteCharDlg �Ի���

class CWriteCharDlg : public CDialog
{
	DECLARE_DYNAMIC(CWriteCharDlg)

public:
	CWriteCharDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWriteCharDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WRITECHAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �ַ�
	CString m_wCharacter;
	int m_xPosition;
	int m_yPosition;
};
