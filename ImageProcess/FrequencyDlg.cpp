// FrequencyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "FrequencyDlg.h"
#include "afxdialogex.h"


// CFrequencyDlg �Ի���

IMPLEMENT_DYNAMIC(CFrequencyDlg, CDialogEx)

CFrequencyDlg::CFrequencyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FREQUENCY, pParent)
	, m_nCutoffFre(50)
{

}

CFrequencyDlg::~CFrequencyDlg()
{
}

void CFrequencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY_CUT, m_nCutoffFre);
}


BEGIN_MESSAGE_MAP(CFrequencyDlg, CDialogEx)
END_MESSAGE_MAP()


// CFrequencyDlg ��Ϣ�������


BOOL CFrequencyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(m_sWindowTitle); 
	SetDlgItemText(IDC_STATIC_FREDLG_TITLE, m_sHelpTitle);
	return TRUE;  
}
