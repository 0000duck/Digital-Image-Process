// InterpolationDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "InterpolationDlg.h"
#include "afxdialogex.h"


// CInterpolationDlg �Ի���

IMPLEMENT_DYNAMIC(CInterpolationDlg, CDialog)

CInterpolationDlg::CInterpolationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_INTERPOLATION, pParent)
	, m_nWidth(1152)
	, m_nHeight(864)
{

}

CInterpolationDlg::~CInterpolationDlg()
{
}

void CInterpolationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHW, m_nWidth);
	DDX_Text(pDX, IDC_EDIT_CHH, m_nHeight);
}


BEGIN_MESSAGE_MAP(CInterpolationDlg, CDialog)
END_MESSAGE_MAP()


// CInterpolationDlg ��Ϣ�������

