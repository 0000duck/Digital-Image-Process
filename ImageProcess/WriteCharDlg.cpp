// WriteCharDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "WriteCharDlg.h"
#include "afxdialogex.h"


// CWriteCharDlg �Ի���

IMPLEMENT_DYNAMIC(CWriteCharDlg, CDialog)

CWriteCharDlg::CWriteCharDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_WRITECHAR, pParent)
	, m_wCharacter(_T("U"))
	, m_xPosition(1)
	, m_yPosition(1)
{

}

CWriteCharDlg::~CWriteCharDlg()
{
}

void CWriteCharDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHARACTER, m_wCharacter);
	DDX_Text(pDX, IDC_EDIT_CHARACTERX, m_xPosition);
	DDX_Text(pDX, IDC_EDIT_CHARACTERY, m_yPosition);
}


BEGIN_MESSAGE_MAP(CWriteCharDlg, CDialog)
END_MESSAGE_MAP()


// CWriteCharDlg ��Ϣ�������


