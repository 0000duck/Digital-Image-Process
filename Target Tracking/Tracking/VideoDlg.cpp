// VideoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Tracking.h"
#include "VideoDlg.h"
#include "afxdialogex.h"


// CVideoDlg �Ի���

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VIDEO, pParent)
{

	EnableAutomation();

}

CVideoDlg::~CVideoDlg()
{
}

void CVideoDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OCX1, m_player);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVideoDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IVideoDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {67300A47-852E-4F72-AE96-94CB23680D99}
static const IID IID_IVideoDlg =
{ 0x67300A47, 0x852E, 0x4F72, { 0xAE, 0x96, 0x94, 0xCB, 0x23, 0x68, 0xD, 0x99 } };

BEGIN_INTERFACE_MAP(CVideoDlg, CDialogEx)
	INTERFACE_PART(CVideoDlg, IID_IVideoDlg, Dispatch)
END_INTERFACE_MAP()


// CVideoDlg ��Ϣ�������


BOOL CVideoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_player.put_URL(m_vidoeUrl);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
