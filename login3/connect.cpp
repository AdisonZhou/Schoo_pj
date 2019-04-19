// connect.cpp: 实现文件
//

#include "stdafx.h"
#include "login3.h"
#include "connect.h"
#include "afxdialogex.h"


// connect 对话框

IMPLEMENT_DYNAMIC(connect, CDialogEx)

connect::connect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

connect::~connect()
{
}

void connect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(connect, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &connect::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &connect::OnBnClickedButton2)
END_MESSAGE_MAP()


// connect 消息处理程序


BOOL connect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);


	// TODO:  在此添加额外的初始化
	accept = 0;
	refuse = 0;


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



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void connect::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	accept = 1;
	ShowWindow(SW_HIDE);
}


void connect::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	refuse =1;
	ShowWindow(SW_HIDE);
}
