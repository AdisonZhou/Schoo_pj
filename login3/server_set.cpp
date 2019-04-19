// server_set.cpp: 实现文件
//

#include "stdafx.h"
#include "login3.h"
#include "server_set.h"
#include "afxdialogex.h"


// server_set 对话框

IMPLEMENT_DYNAMIC(server_set, CDialogEx)

server_set::server_set(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

server_set::~server_set()
{
}

void server_set::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(server_set, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &server_set::OnBnClickedButton1)
END_MESSAGE_MAP()


// server_set 消息处理程序


void server_set::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sp;
	GetDlgItemText(IDC_EDIT1, sp);
	test = sp;
	port = _ttoi(sp);
	CString ip;
	GetDlgItemText(IDC_EDIT2, ip);

	string ip_address2(CW2A(ip.GetString()));
	ip_address = ip_address2;

	//USES_CONVERSION;
	//ip_address = W2A(ip);//get account and password from the ui

	//EndDialog(0);
	ShowWindow(SW_HIDE);//隐藏当前对话框
}
void server_set::close()
{
	OnClose();
}

BOOL server_set::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	//
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);


	// TODO:  在此添加额外的初始化
	ip_address = "192.168.43.125";
	port = 5060;
	test = "sssss";
	SetDlgItemText(IDC_EDIT1, _T("5060"));
	SetDlgItemText(IDC_EDIT2, _T("192.168.43.125"));


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


BOOL server_set::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}
