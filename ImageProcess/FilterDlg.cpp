// FilterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "FilterDlg.h"
#include "afxdialogex.h"


// CFilterDlg �Ի���

IMPLEMENT_DYNAMIC(CFilterDlg, CDialogEx)

CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_FILTER, pParent)
	, m_nLinearM(3)
	, m_nLinearN(3)
{

}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LINEAR_M, m_nLinearM);
	DDX_Text(pDX, IDC_EDIT_LINEAR_N, m_nLinearN);
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialogEx)
END_MESSAGE_MAP()


// CFilterDlg ��Ϣ�������
