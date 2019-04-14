// MEDIA_SETTING.cpp: 实现文件
//

#include "stdafx.h"
#include "login3.h"
#include "MEDIA_SETTING.h"
#include "afxdialogex.h"


// MEDIA_SETTING 对话框

IMPLEMENT_DYNAMIC(MEDIA_SETTING, CDialogEx)

MEDIA_SETTING::MEDIA_SETTING(CWnd* pParent /*=nullptr*/)
	: CDialogEx(SETTING, pParent)
{

}

MEDIA_SETTING::~MEDIA_SETTING()
{
}

void MEDIA_SETTING::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MEDIA_SETTING, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &MEDIA_SETTING::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MEDIA_SETTING::OnBnClickedButton2)
END_MESSAGE_MAP()


// MEDIA_SETTING 消息处理程序


BOOL MEDIA_SETTING::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//去边框
	DWORD dwStyle = GetStyle();//获取旧样式  
	DWORD dwNewStyle = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	dwNewStyle &= dwStyle;//按位与将旧样式去掉  
	SetWindowLong(m_hWnd, GWL_STYLE, dwNewStyle);//设置成新的样式  
	DWORD dwExStyle = GetExStyle();//获取旧扩展样式  
	DWORD dwNewExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR;
	dwNewExStyle &= dwExStyle;//按位与将旧扩展样式去掉  
	SetWindowLong(m_hWnd, GWL_EXSTYLE, dwNewExStyle);//设置新的扩展样式  
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);//告诉windows：我的样式改变了，窗口位置和大小保持原来不变！
	//

	//居中显示
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
	//
	//移动控件

	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_STATIC1);    
	pWnd->SetWindowPos(NULL, 20, 25, 100, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_RADIO1);
	pWnd->SetWindowPos(NULL, 140, 20, 100, 32, SWP_NOZORDER);

	pWnd = GetDlgItem(IDC_STATIC2);
	pWnd->SetWindowPos(NULL, 20, 57, 100, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_RADIO2);
	pWnd->SetWindowPos(NULL, 140, 52, 100, 32, SWP_NOZORDER);

	pWnd = GetDlgItem(IDC_STATIC3);
	pWnd->SetWindowPos(NULL, 20, 89, 100, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_RADIO3);
	pWnd->SetWindowPos(NULL, 140, 116, 100, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_RADIO4);
	pWnd->SetWindowPos(NULL, 140, 148, 100, 32, SWP_NOZORDER);

	pWnd = GetDlgItem(IDC_STATIC4);
	pWnd->SetWindowPos(NULL, 20, 185, 100, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_RADIO5);
	pWnd->SetWindowPos(NULL, 140, 212, 100, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_RADIO6);
	pWnd->SetWindowPos(NULL, 140, 244, 100, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_RADIO7);
	pWnd->SetWindowPos(NULL, 140, 276, 100, 32, SWP_NOZORDER);

	pWnd = GetDlgItem(IDC_BUTTON1);
	pWnd->SetWindowPos(NULL, 20, 332, 80, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_BUTTON2);
	pWnd->SetWindowPos(NULL, 156, 332, 80, 32, SWP_NOZORDER);
	

	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(TRUE);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void MEDIA_SETTING::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect temprect(0, 0, 256, 384);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);

}

//确定
void MEDIA_SETTING::OnBnClickedButton1()
{
	CWnd* pWnd = CWnd::FindWindow(NULL, _T("Main"));
	ASSERT(pWnd);
	int val=H264;
	int val2 = G722_16000;
	// TODO: 在此添加控件通知处理程序代码
	int w_video = ((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck();//返回1表示选上，0表示没选上
	
	int w_preview = ((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck();//返回1表示选上，0表示没选上

	int ec_263 = ((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck();//返回1表示选上，0表示没选上
	int ec_264 = ((CButton *)GetDlgItem(IDC_RADIO4))->GetCheck();//返回1表示选上，0表示没选上

	if (ec_263 == 1)
	{
		val = H263;
	}
	else if (ec_264 == 1)
	{
		val = H264;
	}
	::SendMessageW(pWnd->GetSafeHwnd(), ENCODE_VIDEO, 0, (LPARAM)(&val));


	int ec_speex = ((CButton *)GetDlgItem(IDC_RADIO4))->GetCheck();//返回1表示选上，0表示没选上
	int ec_gsm = ((CButton *)GetDlgItem(IDC_RADIO5))->GetCheck();//返回1表示选上，0表示没选上
	int ec_g722= ((CButton *)GetDlgItem(IDC_RADIO6))->GetCheck();//返回1表示选上，0表示没选上
	
	if (ec_speex == 1)
	{
		val2 = SPEEX_16000;
	}
	else if (ec_gsm == 1)
	{
		val2 = GSM_8000;
	}
	else if (ec_g722 == 1)
	{
		val2 = G722_16000;
	}
	::SendMessageW(pWnd->GetSafeHwnd(), ENCODE_VOICE, 0, (LPARAM)(&val2));


	ShowWindow(SW_HIDE);
}

//取消
void MEDIA_SETTING::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);

}
