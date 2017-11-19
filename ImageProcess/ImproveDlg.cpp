// ImproveDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "ImproveDlg.h"
#include "afxdialogex.h"


// CImproveDlg �Ի���

IMPLEMENT_DYNAMIC(CImproveDlg, CDialogEx)

CImproveDlg::CImproveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMPROVE, pParent)
	, m_bImproveYes(FALSE)
 
{

}

CImproveDlg::~CImproveDlg()
{
}

void CImproveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_IMPROVE_YES, m_bImproveYes);
}


BEGIN_MESSAGE_MAP(CImproveDlg, CDialogEx)
	ON_COMMAND(ID_USER_LOGIN, &CImproveDlg::OnUserLogin)
END_MESSAGE_MAP()


// CImproveDlg ��Ϣ�������


BOOL CImproveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString config;
	GetPrivateProfileString(_T("Setting"), _T("Improve"), CString("NULL"), config.GetBuffer(MAX_PATH), MAX_PATH, _T("./config.ini") );

	if (config == _T("yes") ) {
		((CButton *)GetDlgItem(IDC_RADIO_IMPROVE_YES))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO_IMPROVE_NO))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_RADIO_IMPROVE_NO))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO_IMPROVE_YES))->SetCheck(FALSE);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CImproveDlg::OnUserLogin()
{
	// TODO: �ڴ���������������
}
