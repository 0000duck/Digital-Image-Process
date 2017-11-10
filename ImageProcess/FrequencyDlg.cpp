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
	, m_dGammaH(2)
	, m_dGammaL(0.25)
	, m_dHomoC(1)
{

}

CFrequencyDlg::~CFrequencyDlg()
{
}

void CFrequencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY_CUT, m_nCutoffFre);
	DDX_Text(pDX, IDC_EDIT_GAMMAH, m_dGammaH);
	DDX_Text(pDX, IDC_EDIT_GAMMAL, m_dGammaL);
	DDX_Text(pDX, IDC_EDIT_HOMOC, m_dHomoC);
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
	GetDlgItem(IDC_STATIC_GAMMAH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_GAMMAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_GAMMAH)->ShowWindow(SW_HIDE); 
	GetDlgItem(IDC_EDIT_GAMMAL)->ShowWindow(SW_HIDE); 
	GetDlgItem(IDC_EDIT_HOMOC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_HOMOC)->ShowWindow(SW_HIDE);
	//��ʾ̬ͬ�˲��������ÿؼ�
	if (showGammaControls) {
		GetDlgItem(IDC_STATIC_GAMMAH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_GAMMAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_GAMMAH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_GAMMAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_HOMOC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_HOMOC)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_EDIT_GAMMAH)->SetWindowText(_T("2.5"));
		GetDlgItem(IDC_EDIT_GAMMAL)->SetWindowText(_T("0.2"));
		GetDlgItem(IDC_EDIT_HOMOC)->SetWindowText(_T("0.2"));
		GetDlgItem(IDC_EDIT_FREQUENCY_CUT)->SetWindowText(_T("600"));

	}
	 
	return TRUE;  
}
