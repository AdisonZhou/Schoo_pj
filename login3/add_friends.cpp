// add_friends.cpp: 实现文件
//

#include "stdafx.h"
#include "login3.h"
#include "add_friends.h"
#include "afxdialogex.h"
#include"GLOBAL.h"

// add_friends 对话框

IMPLEMENT_DYNAMIC(add_friends, CDialogEx)

add_friends::add_friends(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

add_friends::~add_friends()
{
}

void add_friends::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(add_friends, CDialogEx)
	ON_BN_CLICKED(IDOK, &add_friends::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &add_friends::OnBnClickedButton1)
END_MESSAGE_MAP()


// add_friends 消息处理程序


BOOL add_friends::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
	//
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

	//
	CString strText;
	CString s1;
	TCHAR exepath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, exepath, MAX_PATH);
	strText = exepath;
	strText = strText.Left(strText.ReverseFind('\\'));
	strText += _T("\\");
	strText += _T("account_information");
	CreateDirectory(strText, NULL);
	s1 = strText + _T("\\") + _T("friends.txt");

	CStdioFile ioFile(s1, CFile::modeRead);
	std::vector<CString> vecResult;
	CString strValue = _T("");
	int i = 1;
	Friend_inf temp;
	while (ioFile.ReadString(strValue))
	{
		if (i % 3 == 1)
		{
			temp.id = strValue;
		}
		if (i % 3 == 2)
		{
			temp.re_name = strValue;
		}
		if (i % 3 == 0)
		{
			temp.buddy_id = _ttoi(strValue);
			lis.push_back(temp);
		}
		i++;
	}
	ioFile.Close();
	
	

	//




	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void add_friends::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT1, friends_id);
	GetDlgItemText(IDC_EDIT2, friends_rename);
	Friend_inf temp;
	temp.id = friends_id;
	temp.re_name = friends_rename;
	temp.buddy_id=_ttoi(friends_id);
	lis.push_back(temp);
	//friend_queue.push(temp);
	//AfxMessageBox(friend_queue.size());
	flag_close = 1;
	
	CWnd* pWnd = CWnd::FindWindow(NULL, _T("Main"));
	ASSERT(pWnd);
	::SendMessageW(pWnd->GetSafeHwnd(), BUDDY_ADD, 0, (LPARAM)(&temp.buddy_id));

	ShowWindow(SW_HIDE);
}


void add_friends::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
}
void add_friends::close_c()
{
	ShowWindow(SW_HIDE);
}
