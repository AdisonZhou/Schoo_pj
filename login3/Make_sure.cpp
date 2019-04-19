// Make_sure.cpp: 实现文件
//

#include "stdafx.h"
#include "login3.h"
#include "Make_sure.h"
#include "afxdialogex.h"


// Make_sure 对话框

IMPLEMENT_DYNAMIC(Make_sure, CDialogEx)

Make_sure::Make_sure(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

Make_sure::~Make_sure()
{
}

void Make_sure::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Make_sure, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Make_sure::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Make_sure::OnBnClickedButton2)
END_MESSAGE_MAP()


// Make_sure 消息处理程序


BOOL Make_sure::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	accept = 0;
	refuse = 0;
	flag_sure = 1;

	// TODO:  在此添加额外的初始化
	//
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
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


void Make_sure::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	accept = 1;
	flag_sure = 0;
	CWnd* pWnd = CWnd::FindWindow(NULL, _T("Main"));
	ASSERT(pWnd);
	::SendMessageW(pWnd->GetSafeHwnd(), WM_MyMessage, 0, 0);
	ShowWindow(SW_HIDE);
}


void Make_sure::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	refuse = 1;
	flag_sure = 0;
	CWnd* pWnd = CWnd::FindWindow(NULL, _T("Main"));
	ASSERT(pWnd);
	::SendMessageW(pWnd->GetSafeHwnd(), REFUSE_CALL, 0, 0);
	ShowWindow(SW_HIDE);
}
