
// login3Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "login3.h"
#include "login3Dlg.h"
#include "afxdialogex.h"
#include"MainDialog.h"
#include"MySip3.h"
#include"server_set.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
int flag_server_set = 0;
//添加一个MySip的全局变量
//MySip mysip1;
//server
server_set *server_inf = new server_set;

MainDialog *dlg_main = new MainDialog;


CString strText;
CString s1, s2;


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Clogin3Dlg 对话框



Clogin3Dlg::Clogin3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clogin3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, login_bt);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, edit2);

	//  DDX_Control(pDX, IDC_EDIT4, account);
	//  DDX_Control(pDX, IDC_EDIT5, password);
	DDX_Control(pDX, IDC_BUTTON2, account);
	DDX_Control(pDX, IDC_BUTTON3, password);
	DDX_Control(pDX, IDC_BUTTON4, enter);
	DDX_Control(pDX, IDC_BUTTON5, reme);
	DDX_Control(pDX, IDC_BUTTON6, noa);
	DDX_Control(pDX, IDC_BUTTON7, reg);
	DDX_Control(pDX, IDC_BUTTON8, login_2);
}

BEGIN_MESSAGE_MAP(Clogin3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &Clogin3Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &Clogin3Dlg::OnEnChangeEdit1)
//	ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON4, &Clogin3Dlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON7, &Clogin3Dlg::OnBnClickedButton7)
ON_BN_CLICKED(IDC_BUTTON8, &Clogin3Dlg::login_no_account)
END_MESSAGE_MAP()


// Clogin3Dlg 消息处理程序

BOOL Clogin3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	//server_set
	server_inf->Create((LPCTSTR)IDD_DIALOG2, NULL);

	
	dlg_main->Create((LPCTSTR)IDD_DIALOG1, NULL);

	


	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CRect temprect(0, 0, 640, 480);

	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);



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

	//移动控件


	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_BUTTON1);    //获取控件指针，IDC_BUTTON1为控件ID号
	pWnd->SetWindowPos(NULL, 603, 0, 37, 37, SWP_NOZORDER);    //把按钮移到窗口的(50,80)处
	//login_bt.SetIcon(IDI_ICON2);//icn set
	login_bt.DrawTransparent(TRUE);
	CString s1;
	s1 = "×";
	SetDlgItemText(IDC_BUTTON1, s1);//close button

	//id and password edit control
	edit1.SetBackColor(TRANS_BACK);
	edit2.SetBackColor(TRANS_BACK);
	account.DrawTransparent(TRUE);
	password.DrawTransparent(TRUE);
	account.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 255));
	account.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	account.SetIcon(IDI_ICON4);
	password.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 255));
	password.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	password.SetIcon(IDI_ICON6);

	pWnd = GetDlgItem(IDC_BUTTON2);    
	pWnd->SetWindowPos(NULL, 190, 150, 120, 35, SWP_NOZORDER);  
	pWnd = GetDlgItem(IDC_BUTTON3);  
	pWnd->SetWindowPos(NULL, 190, 205, 120, 35, SWP_NOZORDER);  
	pWnd = GetDlgItem(IDC_EDIT1);  
	pWnd->SetWindowPos(NULL, 320, 150, 150, 35, SWP_NOZORDER);    
	pWnd = GetDlgItem(IDC_EDIT2);  
	pWnd->SetWindowPos(NULL, 320, 205, 150, 35, SWP_NOZORDER);    


	//登录
	enter.DrawTransparent(TRUE);
	enter.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 255));
	enter.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 255, 0));
	enter.SetIcon(IDI_ICON5);
	pWnd = GetDlgItem(IDC_BUTTON4);
	pWnd->SetWindowPos(NULL, 300, 300, 100, 35, SWP_NOZORDER);

	pWnd = GetDlgItem(IDC_BUTTON8);
	pWnd->SetWindowPos(NULL, 0, 430, 100, 35, SWP_NOZORDER);
	login_2.DrawTransparent(TRUE);
	login_2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 69, 0));
	login_2.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 255, 0));
	//记住我
	
	pWnd = GetDlgItem(IDC_CHECK1);
	pWnd->SetWindowPos(NULL, 190, 250, 20, 20, SWP_NOZORDER);
	reme.DrawTransparent(TRUE);
	pWnd = GetDlgItem(IDC_BUTTON5);
	pWnd->SetWindowPos(NULL, 210, 240, 130, 40, SWP_NOZORDER);


	//z注册
	noa.DrawTransparent(TRUE);
	reg.DrawTransparent(TRUE);
	pWnd = GetDlgItem(IDC_BUTTON6);
	pWnd->SetWindowPos(NULL, 450, 410, 100, 40, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_BUTTON7);
	pWnd->SetWindowPos(NULL, 550, 430, 90, 40, SWP_NOZORDER);
	reg.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(128, 128, 128));
	reg.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 255, 0));

	//默认账号
	TCHAR exepath[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, exepath, MAX_PATH);
	strText = exepath;
	strText = strText.Left(strText.ReverseFind('\\'));
	strText += _T("\\");
	strText += _T("account_information");
	CreateDirectory(strText, NULL);
    s1=strText+ _T("\\")+_T("account.txt");
	s2= strText + _T("\\") + _T("password.txt");
	CStdioFile ioFile(s1,CFile::modeRead);
	CStdioFile ioFile2(s2, CFile::modeRead);
	CString account1;
	ioFile.ReadString(account1);
	CString password1;
	ioFile2.ReadString(password1);
	ioFile.Close();
	ioFile2.Close();
	
	edit1.SetWindowTextW(account1);
	edit2.SetWindowTextW(password1);


	SkinH_Attach();//skin set
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Clogin3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Clogin3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);                                 //获取对话框长宽       
		CDC   dcBmp;                                           //定义并创建一个内存设备环境
		dcBmp.CreateCompatibleDC(&dc);                         //创建兼容性DC
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);                 //载入资源中的IDB_BITMAP1图片
		BITMAP   m_bitmap;                                     //图片变量                
		bmpBackground.GetBitmap(&m_bitmap);                    //将图片载入位图中
		CBitmap   *pbmpOld = dcBmp.SelectObject(&bmpBackground); //将位图选入临时内存设备环境
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Clogin3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Clogin3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));//移动界面
	CDialogEx::OnLButtonDown(nFlags, point);
}


void Clogin3Dlg::OnBnClickedButton1()
{
	 DestroyWindow();
	// TODO: 在此添加控件通知处理程序代码
}








void Clogin3Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




void Clogin3Dlg::OnBnClickedButton4()//登陆button
{
	// TODO: 在此添加控件通知处理程序代码
	
	
	
	

	CString account;
	edit1.GetWindowTextW(account);
	CString password;
	edit2.GetWindowTextW(password);
	USES_CONVERSION;
	char * account_id = W2A(account);//get account and password from the ui
	char *account_password = W2A(password);
	//get account and password from the ui

	dlg_main->Sip_p.SIP_USER2 = account_id;
	dlg_main->Sip_p.SIP_PASSWD2 = account_password;
	//账号与密码赋值给mysip
	dlg_main->Sip_p.SIP_PORT = server_inf->port;
	dlg_main->Sip_p.SIP_DOMAIN2 = server_inf->ip_address;
	//服务器ip和端口
	if (flag_server_set == 1)
	{
		server_inf->close();
		flag_server_set = 0;
	}//关闭服务器设置界面
	
	
	//登录
	dlg_main->Sip_p.login();

	
	
	
	//判断是否记住账号
	{
		TCHAR exepath[MAX_PATH] = { 0 };
		::GetModuleFileName(NULL, exepath, MAX_PATH);
		strText = exepath;
		strText = strText.Left(strText.ReverseFind('\\'));
		strText += _T("\\");
		strText += _T("account_information");
		CreateDirectory(strText, NULL);
		s1 = strText + _T("\\") + _T("account.txt");
		s2 = strText + _T("\\") + _T("password.txt");
		CStdioFile ioFile(s1, CFile::modeCreate | CFile::modeWrite);
		CStdioFile ioFile2(s2, CFile::modeCreate | CFile::modeWrite);
		if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1))
		{
			//记住账号
			//将账号与密码写入本地文件
			ioFile.WriteString(account);
			ioFile2.WriteString(password);
		}
		else
		{
			ioFile.WriteString(_T(""));
			ioFile2.WriteString(_T(""));
		}
		ioFile.Close();
		ioFile2.Close();
	}
	int i = 50;
	while (i--)
	{
		pj_thread_sleep(100);
		if (dlg_main->Sip_p.login_state == TRUE)
		{
			//登录成功
			break;
		}
	}
	if (i>0)
	{
		//登录成功
		ShowWindow(SW_HIDE);
		dlg_main->ShowWindow(SW_SHOW);
		dlg_main->Sip_p.login_state = FALSE;
	}
	else
	{
		AfxMessageBox(_T("登录失败"));
		dlg_main->Sip_p.destroy();
	}
	

}


void Clogin3Dlg::OnBnClickedButton7()//设置
{
	// TODO: 在此添加控件通知处理程序代码
	//功能：设置服务器ip以及端口
	flag_server_set = 1;
	server_inf->ShowWindow(SW_SHOW);
	
}


void Clogin3Dlg::login_no_account()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	dlg_main->ShowWindow(SW_SHOW);
}
