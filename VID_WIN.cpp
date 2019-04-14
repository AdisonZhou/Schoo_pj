// VID_WIN.cpp: 实现文件
//

#include "stdafx.h"
#include "login3.h"
#include "VID_WIN.h"
#include "afxdialogex.h"


// VID_WIN 对话框

IMPLEMENT_DYNAMIC(VID_WIN, CDialogEx)

VID_WIN::VID_WIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VID_WIN, pParent)
{

}

VID_WIN::~VID_WIN()
{
}

void VID_WIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VID_WIN, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// VID_WIN 消息处理程序


BOOL VID_WIN::OnInitDialog()
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
	//设置大小

	CRect   temprect(0, 0, 640, 480);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);

	//初始化获取window句柄
	friend_win = GetDlgItem(IDC_STATIC3);
	friend_win->SetWindowPos(NULL, 0, 0, 640, 480, SWP_NOZORDER);
	local_win= GetDlgItem(IDC_STATIC4);
	local_win->SetWindowPos(NULL, 480, 0, 160, 120, SWP_NOZORDER);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void VID_WIN::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP4);    //这个IDB_BITMAP1要自己添加
	CBrush   brush2;
	brush2.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush2 = dc.SelectObject(&brush2);
	dc.Rectangle(0, 0, 640, 480);                  //前两个为图片起始位置，后两个为图片终点位置，实际为图片的像素大小
	dc.SelectObject(pOldBrush2);
}
