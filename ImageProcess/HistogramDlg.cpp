// HistogramDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "HistogramDlg.h"
#include "afxdialogex.h"


// CHistogramDlg �Ի���

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialogEx)

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HISTOGRAM, pParent)
{

	HistogramColor = NULL;
}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHistogramDlg ��Ϣ�������


BOOL CHistogramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(m_sWindowTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CHistogramDlg::OnPaint()
{
	 
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	 
 
 
	//��ȡ���ڼ�����ͼ�ε�����
	CWnd *pWnd = GetDlgItem(IDC_STATIC_HISTOGRAM);
	CDC *pDC = pWnd->GetDC();
	 
	CRect rectpic;
	pWnd->GetWindowRect(&rectpic);

	int x, y;
	x = rectpic.Width();//X��
	y = rectpic.Height();//Y��


	int x_offset = 10;//����ƫ�� ƫ�ñ���ֱ��ͼ������ϵ�º����λ��
	int y_offset = 10;

	//��������
	CPen *RedPen = new CPen();
 
	RedPen->CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); //����ʵ�Ļ��ʣ��ֶ�Ϊ1����ɫΪ��ɫ
													
	CGdiObject *RedOlderPen = pDC->SelectObject(RedPen); // ѡ���»��ʣ������ɻ��ʵ�ָ�뱣�浽RedOlderPen   



	double max = 0; //ͳ���е����ֵ
	for (int i = 0; i < 256; i++) {
		if (HistogramColor[i] > max) {
			max = HistogramColor[i];
		}
	}


	//����ͼ��
	/*˵��������windows��ɨ��ʹ洢ͼ��������4���ֽ�Ϊ�ڴ浥Ԫ 
		���ͼ���ֽڶ����� Ĭ����0��255��䣨��Ҫ����memset�ĵڶ���ֵ ����
		��0�ı������������ģ���˶���ͼ���Ȳ���4�ı����Ľ�������Ϊ0��255������ͳ�Ʒ�ֵ
	*/
	for (int i = 0; i<256; i++)
	{
		int y_Position = ((double)HistogramColor[i] / max * (y-y_offset));//���������ŵ�Y��  y_PositionС��Y ��˲��ؽ���Խ�紦��
		int x_Position = (double (i) /256) *(x- x_offset); //���������ŵ�X��								 
		pDC->MoveTo(x_Position, y-1);
		pDC->LineTo(x_Position, y - y_Position);

	}


	//�ָ���ǰ����
	pDC->SelectObject(RedOlderPen);
	delete RedPen;
	ReleaseDC(pDC);

}



