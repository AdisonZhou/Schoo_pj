// MainDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "login3.h"
#include "MainDialog.h"
#include "afxdialogex.h"
#include<opencv2/opencv.hpp>
#include <SDL_thread.h>
#include"add_friends.h"
#include"thread"
#include"Winuser.h"
#include"string"
#include <stdio.h>  
#define __STDC_CONSTANT_MACROS  
#define timer_id 0
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavdevice/avdevice.h>
#include <libavutil/time.h>
}
#include"windows.h"
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace cv;
using namespace std;

int play_enable = 1;
int close_flag = 0;
int i = 1;
int j = 1;
int k = 1;
int chatflag[3] = { 1,0,0 };
pjsua_recorder_id recorder_id = NULL;
SYSTEMTIME s_time;
CString strDate, strTime;
char *zcj="";

IMPLEMENT_DYNAMIC(MainDialog, CDialogEx)

add_friends *friends_add= new add_friends;
Make_sure *w_recpt = new Make_sure;
VID_WIN *video_win;
MEDIA_SETTING *media_set=new MEDIA_SETTING;



MainDialog::MainDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

MainDialog::~MainDialog()
{
}

void MainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, st);
	DDX_Control(pDX, IDC_BUTTON2, lf);
	DDX_Control(pDX, IDC_BUTTON3, ri);
	DDX_Control(pDX, IDC_BUTTON4, nv);


	DDX_Control(pDX, IDC_BUTTON5, me);
	DDX_Control(pDX, IDC_BUTTON6, fr);
	DDX_Control(pDX, IDC_BUTTON7, gr);
	DDX_Control(pDX, IDC_LIST1, list1);

	DDX_Control(pDX, IDC_STATIC1, m_pictureControl);
	DDX_Control(pDX, IDC_BUTTON9, add);
	DDX_Control(pDX, IDC_BUTTON10, dl);
	DDX_Control(pDX, IDC_BUTTON11, in);
	DDX_Control(pDX, IDC_BUTTON16, ex);
	DDX_Control(pDX, IDC_BUTTON15, rel);
	DDX_Control(pDX, IDC_BUTTON12, rs);
	DDX_Control(pDX, IDC_BUTTON17, time);
	DDX_Control(pDX, IDC_BUTTON13, nt);
	DDX_Control(pDX, IDC_BUTTON14, set);
	DDX_Control(pDX, IDC_BUTTON18, va);
	DDX_Control(pDX, IDC_BUTTON19, vd);
	DDX_Control(pDX, IDC_BUTTON20, voice);
	DDX_Control(pDX, IDC_BUTTON21, up);
	DDX_Control(pDX, IDC_BUTTON22, down);
	DDX_Control(pDX, IDC_BUTTON8, refresh);
	DDX_Control(pDX, IDC_BUTTON26, end_call);
	DDX_Control(pDX, IDC_EDIT2, Mesag);
	DDX_Control(pDX, IDC_BUTTON27, send);
	DDX_Control(pDX, IDC_BUTTON28, Pic);
	//  DDX_Control(pDX, IDC_LIST4, list4);
	DDX_Control(pDX, IDC_LIST4, list4);
	DDX_Control(pDX, IDC_STATIC2, bak_ground);
}


BEGIN_MESSAGE_MAP(MainDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MainDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &MainDialog::OnBnClickedButton4)
	//ON_LBN_SELCHANGE(IDC_LIST2, &MainDialog::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_BUTTON6, &MainDialog::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &MainDialog::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &MainDialog::OnBnClickedButton7)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON9, &MainDialog::OnBnClickedButton9)
	ON_COMMAND(ID_1_1, &MainDialog::On11)
	ON_COMMAND(ID_1_2, &MainDialog::On12)
	ON_BN_CLICKED(IDC_BUTTON10, &MainDialog::OnBnClickedButton10)
	//	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &MainDialog::OnLvnItemchangedList1)
	//ON_WM_RBUTTONDBLCLK()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &MainDialog::OnNMRClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &MainDialog::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON16, &MainDialog::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON3, &MainDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON8, &MainDialog::OnBnClickedButton8)
	ON_COMMAND(ID__32775, &MainDialog::On21)
	ON_COMMAND(ID__32776, &MainDialog::On22)
	//自定义消息

	ON_REGISTERED_MESSAGE(WM_MyMessage, OnMyMessage)
	ON_MESSAGE(REFUSE_CALL, My_Call_Refuse)
	ON_MESSAGE(END_CALL, close_call)
	ON_MESSAGE(BUDDY_INIT, budy_init)
	ON_MESSAGE(BUDDY_ADD, budy_ad)
	ON_MESSAGE(BUDDY_DEL, budy_de)
	ON_MESSAGE(FRIEND_MSG, friend_msg)

	ON_MESSAGE(VIDEO_W, w_video)
	ON_MESSAGE(PREVIEW_W, w_preview)
	ON_MESSAGE(ENCODE_VIDEO, video_encode)
	ON_MESSAGE(ENCODE_VOICE, voice_encode)

	ON_MESSAGE(OPENCV_WIN, win_attach)

    //自定义消息
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON26, &MainDialog::close_call)
	ON_BN_CLICKED(IDC_BUTTON27, &MainDialog::IM_MESAG_SEND)
	ON_BN_CLICKED(IDC_BUTTON15, &MainDialog::re_login)
	ON_BN_CLICKED(IDC_BUTTON14, &MainDialog::System_Set)
	ON_BN_CLICKED(IDC_BUTTON13, &MainDialog::Net_Check)
	ON_BN_CLICKED(IDC_BUTTON12, &MainDialog::Local_Reso)
END_MESSAGE_MAP()



// MainDialog 消息处理程序


BOOL MainDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	friends_add->Create((LPCTSTR)IDD_DIALOG3, NULL);
	w_recpt->Create((LPCTSTR)IDD_DIALOG4, NULL);
	media_set->Create((LPCTSTR)SETTING, NULL);
	Sip_p.lis = &friends_add->lis;
	//
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
	//
	CWnd *pWnd;

	//av_register_all();
	//avdevice_register_all();

	//st.SetIcon(IDI_ICON10, white);//播放状态
	//start or stop
	pWnd = GetDlgItem(IDC_BUTTON1);    
	pWnd->SetWindowPos(NULL, 288, 208, 64, 64, SWP_NOZORDER);  
	st.SetIcon(IDI_ICON10,white);
	st.DrawTransparent(TRUE);
	st.DrawBorder(FALSE);

	//voice
	pWnd = GetDlgItem(IDC_BUTTON4);    
	pWnd->SetWindowPos(NULL, 608, 480, 32, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_BUTTON18);
	pWnd->SetWindowPos(NULL, 560, 480, 32, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_BUTTON20);
	pWnd->SetWindowPos(NULL, 515, 480, 45, 32, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_BUTTON19);
	pWnd->SetWindowPos(NULL, 475, 480, 32, 32, SWP_NOZORDER);
	voice.DrawTransparent(TRUE);
	voice.DrawBorder(FALSE);
	va.SetIcon(IDI_ICON27);
	va.DrawTransparent(TRUE);
	va.DrawBorder(FALSE);
	vd.SetIcon(IDI_ICON28);
	vd.DrawTransparent(TRUE);
	vd.DrawBorder(FALSE);
	nv.SetIcon(IDI_ICON7);
	nv.DrawTransparent(TRUE);
	nv.DrawBorder(FALSE);
	//picture
	pWnd = GetDlgItem(IDC_STATIC1);
	pWnd->SetWindowPos(NULL, 0, 0, 640, 480, SWP_NOZORDER);

	pWnd = GetDlgItem(IDC_STATIC2);
	pWnd->SetWindowPos(NULL, 0, 0, 640, 480, SWP_NOZORDER);
	bak_ground.ShowWindow(FALSE);

	CBitmap bitmap; // CBitmap对象，用于加载位图
	HBITMAP hBmp;   // 保存CBitmap加载的位图的句柄

	bitmap.LoadBitmapW(IDB_BITMAP4);    // 将位图IDB_BITMAP1加载到bitmap
	hBmp = (HBITMAP)bitmap.GetSafeHandle(); // 获取bitmap加载位图的句柄
	bak_ground.SetBitmap(hBmp);   // 设置图片空间m_pictureControl的位图为IDB_BITMAP1


	//download
	pWnd = GetDlgItem(IDC_BUTTON10);
	pWnd->SetWindowPos(NULL, 0,480, 32, 32, SWP_NOZORDER);
	dl.SetIcon(IDI_ICON20);
	dl.DrawTransparent(TRUE);
	dl.DrawBorder(FALSE);
	pWnd = GetDlgItem(IDC_BUTTON11);
	pWnd->SetWindowPos(NULL, 32, 480, 100, 32, SWP_NOZORDER);
	in.DrawTransparent(TRUE);
	in.DrawBorder(FALSE);
	pWnd = GetDlgItem(IDC_BUTTON17);
	pWnd->SetWindowPos(NULL, 150, 480, 60, 32, SWP_NOZORDER);
	time.DrawTransparent(TRUE);
	time.DrawBorder(FALSE);
	SetDlgItemText(IDC_BUTTON17, _T("00:00"));
	//functon
	pWnd = GetDlgItem(IDC_BUTTON12);//rs resource
	pWnd->SetWindowPos(NULL, 60, 560, 120, 32, SWP_NOZORDER);
	rs.SetIcon(IDI_ICON24);
	rs.DrawTransparent(TRUE);
	rs.DrawBorder(FALSE);
	SetDlgItemText(IDC_BUTTON12, _T("本地资源"));
	pWnd = GetDlgItem(IDC_BUTTON13);//nt etwork
	pWnd->SetWindowPos(NULL, 240, 560,120, 32, SWP_NOZORDER);
	nt.SetIcon(IDI_ICON25);
	nt.DrawTransparent(TRUE);
	nt.DrawBorder(FALSE);
	SetDlgItemText(IDC_BUTTON13, _T("网络检测"));
	pWnd = GetDlgItem(IDC_BUTTON14);//setting
	pWnd->SetWindowPos(NULL, 420, 560, 120, 32, SWP_NOZORDER);
	set.SetIcon(IDI_ICON26);
	set.DrawTransparent(TRUE);
	set.DrawBorder(FALSE);
	SetDlgItemText(IDC_BUTTON14, _T("系统设置"));
	pWnd = GetDlgItem(IDC_BUTTON15);//rel relogin
	pWnd->SetWindowPos(NULL, 600, 560, 120, 32, SWP_NOZORDER);
	rel.SetIcon(IDI_ICON22);
	rel.DrawTransparent(TRUE);
	rel.DrawBorder(FALSE);
	SetDlgItemText(IDC_BUTTON15, _T("切换账号"));
	pWnd = GetDlgItem(IDC_BUTTON16);//ex exit
	pWnd->SetWindowPos(NULL, 780, 560, 120, 32, SWP_NOZORDER);
	ex.SetIcon(IDI_ICON23);
	ex.DrawTransparent(TRUE);
	ex.DrawBorder(FALSE);
	SetDlgItemText(IDC_BUTTON16, _T("退出登录"));

	//list
	me.DrawTransparent(TRUE);
	fr.DrawTransparent(TRUE);
	gr.DrawTransparent(TRUE);
	me.DrawBorder(FALSE);
	me.SetIcon(IDI_ICON14);//17
	fr.SetIcon(IDI_ICON15);//12
	fr.DrawBorder(FALSE);
	gr.SetIcon(IDI_ICON16);//13
	gr.DrawBorder(FALSE);
	AfxOleInit();
	
	pWnd = GetDlgItem(IDC_LIST1);
	pWnd->SetWindowPos(NULL, 640, 32, 320, 384, SWP_NOZORDER);//384
	list1.SetBkImage(IDB_BITMAP3);

	DWORD dwStyle = list1.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	list1.SetExtendedStyle(dwStyle); //设置扩展风格

	
	pWnd = GetDlgItem(IDC_BUTTON5);
	pWnd->SetWindowPos(NULL, 640, 416, 64, 64, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_BUTTON6);
	pWnd->SetWindowPos(NULL, 768, 416, 64, 64, SWP_NOZORDER);
	pWnd = GetDlgItem(IDC_BUTTON7);
	pWnd->SetWindowPos(NULL, 896, 416, 64, 64, SWP_NOZORDER);
	
	//add friends
	pWnd = GetDlgItem(IDC_BUTTON9);
	pWnd->SetWindowPos(NULL, 922, 0, 38, 32, SWP_NOZORDER);
	add.DrawTransparent(TRUE);
	add.DrawBorder(FALSE);
	add.SetIcon(IDI_ICON18);
	//refresh
	pWnd = GetDlgItem(IDC_BUTTON8);
	pWnd->SetWindowPos(NULL, 640, 0, 38, 32, SWP_NOZORDER);
	refresh.DrawTransparent(TRUE);
	refresh.DrawBorder(FALSE);
	refresh.SetIcon(IDI_ICON29);

	//up and down
	pWnd = GetDlgItem(IDC_BUTTON21);
    pWnd->SetWindowPos(NULL, 900, 300, 64, 128, SWP_NOZORDER);
	//pWnd = GetDlgItem(IDC_BUTTON22);
	//pWnd->SetWindowPos(NULL, 896, 246, 64, 128, SWP_NOZORDER);
	up.DrawTransparent(TRUE);
	up.DrawBorder(FALSE);
	//初始化list 数据 account imformation
	accountset();
	
	// 状态图标
	m_IconList.Create(32, 32, 1, 10, 4);
	m_IconList.Add(AfxGetApp()->LoadIcon(online));
	m_IconList.Add(AfxGetApp()->LoadIcon(offline));
	m_IconList.Add(AfxGetApp()->LoadIcon(boy));
	m_IconList.Add(AfxGetApp()->LoadIcon(girl));
	//list1.SetImageList(&m_IconList, LVSIL_SMALL);
	//list1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
	//	LVS_EDITLABELS | LVS_EX_SUBITEMIMAGES);
	
	
	SetTimer(timer_id, 100, NULL);

	//chat界面
	end_call.DrawTransparent(TRUE);
	end_call.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 255));
	end_call.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	//end_call.SetIcon(IDI_ICON4);
	pWnd = GetDlgItem(IDC_BUTTON26);
	pWnd->SetWindowPos(NULL, 840, 0, 120, 32, SWP_NOZORDER);
	end_call.ShowWindow(FALSE);

	//
	Mesag.SetBackColor(TRANS_BACK);
	pWnd = GetDlgItem(IDC_EDIT2);
	pWnd->SetWindowPos(NULL, 640, 448, 240, 32, SWP_NOZORDER);
	Mesag.ShowWindow(FALSE);

	pWnd = GetDlgItem(IDC_BUTTON27);
	pWnd->SetWindowPos(NULL, 880, 448, 80, 32, SWP_NOZORDER);
	send.DrawTransparent(TRUE);
	send.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 255));
	send.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	send.ShowWindow(FALSE);

	pWnd = GetDlgItem(IDC_BUTTON28);
	pWnd->SetWindowPos(NULL, 640, 416, 38, 32, SWP_NOZORDER);
	Pic.DrawTransparent(TRUE);
	Pic.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 255));
	Pic.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	Pic.ShowWindow(FALSE);

	pWnd = GetDlgItem(IDC_LIST4);
	pWnd->SetWindowPos(NULL, 640, 32, 320, 384, SWP_NOZORDER);
	list4.ShowWindow(FALSE);
	list4.SetBkImage(IDB_BITMAP6);
	list4.ShowScrollBar(SB_VERT, TRUE);
	

	
	//read friends
	
	
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//播放，暂停
void MainDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	i = -i;
	//st.DrawTransparent(TRUE);
	if (i == 1)//播放状态
	{
		play_enable = 1;
		
		st.SetIcon(IDI_ICON10, white);
	}
	else//暂停状态
	{
		play_enable = 0;
		
		st.SetIcon(IDI_ICON3, white);
	}
	

}


void MainDialog::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	j = -j;
	//nv.DrawTransparent(TRUE);
	if (j == 1)
	{
		nv.SetIcon(IDI_ICON7);
	}
	else
	{
		nv.SetIcon(IDI_ICON11);
	}


	
	

	}





void MainDialog::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	me.SetIcon(IDI_ICON17);//14
	fr.SetIcon(IDI_ICON12);//15
	gr.SetIcon(IDI_ICON16);//13
	chatflag[0] = 0;
	chatflag[1] = 1;
	chatflag[2] = 0;
	friendsset();

	
}


void MainDialog::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	me.SetIcon(IDI_ICON14);//17
	fr.SetIcon(IDI_ICON15);//12
	gr.SetIcon(IDI_ICON16);//13
	chatflag[0] = 1;
	chatflag[1] = 0;
	chatflag[2] = 0;
	accountset();

}


void MainDialog::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	me.SetIcon(IDI_ICON17);//14
	fr.SetIcon(IDI_ICON15);//12
	gr.SetIcon(IDI_ICON13);//16
	chatflag[0] = 0;
	chatflag[1] = 0;
	chatflag[2] = 1;
	groupset();
}



void MainDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect temprect(0, 0, 960, 640);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);

	CBitmap   bitmap5;
	bitmap5.LoadBitmap(IDB_BITMAP5);    //这个IDB_BITMAP1要自己添加
	CBrush   brush5;
	brush5.CreatePatternBrush(&bitmap5);
	CBrush*   pOldBrush5 = dc.SelectObject(&brush5);
	dc.Rectangle(0, 0, 960, 640);                  //前两个为图片起始位置，后两个为图片终点位置，实际为图片的像素大小
	dc.SelectObject(pOldBrush5);

	
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP4);    //这个IDB_BITMAP1要自己添加
	CBrush   brush2;
	brush2.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush2 = dc.SelectObject(&brush2);
	dc.Rectangle(0, 0, 640, 480);                  //前两个为图片起始位置，后两个为图片终点位置，实际为图片的像素大小
	dc.SelectObject(pOldBrush2);
	
	//list1.ShowScrollBar(SB_VERT, TRUE);

	

}


void MainDialog::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu, *pMenu;
	menu.LoadMenu(IDR_MENU1);
	CRect pt;
	GetDlgItem(IDC_BUTTON9)->GetWindowRect(&pt);
	pMenu = menu.GetSubMenu(0);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN, pt.left - 93, pt.bottom, this);
		
	

}


void MainDialog::On11()//add friends
{
	// TODO: 在此添加命令处理程序代码 添加好友
	friends_add->ShowWindow(SW_SHOW);
	


}




void MainDialog::On12()//add group
{
	// TODO: 在此添加命令处理程序代码  添加群组
	CString str;
//	friends_queue->pop();
	str.Format(_T("%d"), Sip_p.lis->size());
	Sip_p.end_call();

	AfxMessageBox(str);
}


void MainDialog::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	//缓存
	k = -k;
	CString s1;
	if (k == 1)
	{
		dl.SetIcon(IDI_ICON20);
		in.SetIcon(white);
		s1 = "";
		SetDlgItemText(IDC_BUTTON11, s1);
		if (recorder_id != NULL)
		{
			//完成录音
			AfxMessageBox(_T("recorder success"));
			pjsua_recorder_destroy(recorder_id);
		}
	}
	else
	{
		dl.SetIcon(IDI_ICON19);
		in.SetIcon(IDI_ICON21);
		s1 = "缓存中";
		SetDlgItemText(IDC_BUTTON11, s1);
		//开始录音	
		GetLocalTime(&s_time);
		strDate.Format(_T("%4d-%2d-%2d"), s_time.wYear, s_time.wMonth, s_time.wDay);
		strTime.Format(_T("%2d:%2d:%2d"), s_time.wHour, s_time.wMinute, s_time.wSecond);
		CString filename = strDate + strTime;
		string s_tp(CW2A(filename.GetString()));
		s_tp += ".wav";
		const char *tp;
		tp = s_tp.c_str();
		char *tp_2;
		tp_2= const_cast<char*>(tp);
		pj_str_t FILENAME = pj_str(tp_2);
		pj_status_t  w_r=pjsua_recorder_create(&FILENAME, 0, NULL, 0,NULL,&recorder_id);
		if (w_r != PJ_SUCCESS)
		{
			AfxMessageBox(_T("recorder error"));
		}
		
	}
}



void MainDialog::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}




//右键选中要操作好友
void MainDialog::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (chatflag[1] == 1)//friends
	{
		if (pNMListView->iItem != -1)
		{
			DWORD dwPos = GetMessagePos();
			CPoint point(LOWORD(dwPos), HIWORD(dwPos));

			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU2));
			CMenu* popup = menu.GetSubMenu(0);
			ASSERT(popup != NULL);
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x + 10, point.y + 5, this);
			//获得选中行的信息
			int row = list1.GetSelectionMark();//获得选 中行的行标
			CString s = list1.GetItemText(row, 2);
			current_friend.id = s;
		}
		if (chatflag[2] == 1)//group
		{
			if (pNMListView->iItem != -1)
			{
				DWORD dwPos = GetMessagePos();
				CPoint point(LOWORD(dwPos), HIWORD(dwPos));

				CMenu menu;
				VERIFY(menu.LoadMenu(IDR_MENU2));
				CMenu* popup = menu.GetSubMenu(0);
				ASSERT(popup != NULL);
				popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x + 10, point.y + 5, this);
			}
		}
		*pResult = 0;
	}
}


void MainDialog::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		CString strtemp;
		strtemp.Format(_T("单击的是第%d行第%d列"),pNMListView->iItem, pNMListView->iSubItem);
		AfxMessageBox(strtemp);
	}

	*pResult = 0;
}

BOOL GetLocalIP(char *ip)
{
	return FALSE;
}


void MainDialog::accountset(void)
{
	list1.SetImageList(NULL, LVSIL_SMALL);
	list1.DeleteAllItems();
	list1.InsertColumn(0, _T(" "), LVCFMT_LEFT, 100);
	list1.InsertColumn(1, _T(" "), LVCFMT_LEFT, 200);
	list1.InsertItem(0, _T(""));
	list1.SetItemText(0, 1, _T(""));
	list1.InsertItem(1, _T("账号"));
	CString s;
	s = Sip_p.SIP_USER2.c_str();
	list1.SetItemText(1, 1, s);
	list1.InsertItem(2, _T(""));
	list1.SetItemText(2, 1, _T(""));
	list1.InsertItem(3, _T("密码"));
	s = Sip_p.SIP_PASSWD2.c_str();
	list1.SetItemText(3, 1, s);
	list1.InsertItem(4, _T(""));
	list1.SetItemText(4, 1, _T(""));
	list1.InsertItem(5, _T("地址"));
	char *ip="xxxxxxxxx";
	string iip = ip;
	CString ip_a;
	ip_a = iip.c_str();
	list1.SetItemText(5, 1, ip_a);

}
void MainDialog::friendsset(void)
{
	//Sip_p.add_friends(Sip_p.lis);

	pj_thread_sleep(100);

	list1.DeleteAllItems();
	list1.InsertColumn(0, _T(" "), LVCFMT_LEFT, 40);
	list1.InsertColumn(1, _T(" "), LVCFMT_LEFT, 140);
	list1.InsertColumn(2, _T(" "), LVCFMT_LEFT, 140);
	list1.SetImageList(&m_IconList, LVSIL_SMALL);
	
   // list1.SetExtendedStyle(list1.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES);
	list<Friend_inf>::iterator it; //声明一个迭代器
	Friend_inf temp;
	int i = 0;
	if (!Sip_p.lis->empty())
	{
		for (it = Sip_p.lis->begin(); it != Sip_p.lis->end(); it++)
		{
			
			temp = *it;
			
			bool tag = FALSE;
			pjsua_buddy_info  *inf=NULL;
			

	        pj_status_t st=pjsua_buddy_get_info(_ttoi(temp.id), inf);
			if (st==PJ_SUCCESS)
			{
				
				if (inf->status == PJSUA_BUDDY_STATUS_ONLINE)
				{
				  tag= TRUE;
				 
				}
				
			}
			
			if (tag == TRUE)//onlinbe
			{
				LV_ITEM lvitem;
				memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
				lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
				lvitem.iItem = i;//行索引
				lvitem.iSubItem = 0;
				lvitem.stateMask = 0;
				lvitem.iImage =0;//图标索引
				lvitem.pszText = _T("");
				list1.InsertItem(&lvitem);
			}
			else//ofline
			{
				LV_ITEM lvitem;
				memset((char *)&lvitem, '\0', sizeof(LV_ITEM));
				lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
				lvitem.iItem = i;//行索引
				lvitem.iSubItem = 0;
				lvitem.stateMask = 0;
				lvitem.iImage =1;//图标索引
				lvitem.pszText = _T("");
				list1.InsertItem(&lvitem);
			}
			//list1.InsertItem(i, _T(""));
			list1.SetItemText(i, 1, temp.re_name);//re_name
			list1.SetItemText(i, 2, temp.id);

			i++;
		}
	}
	
}
void MainDialog::groupset(void)
{
	list1.SetImageList(NULL, LVSIL_SMALL);
	list1.DeleteAllItems();
	list1.InsertColumn(0, _T(" "), LVCFMT_LEFT, 100);
	list1.InsertColumn(1, _T(" "), LVCFMT_LEFT, 200);
	for (int ii = 0; ii < 5; ii++)
	{
		list1.InsertItem(ii, _T("地址"));
		list1.SetItemText(ii, 1, _T("102.168.2.202"));
	}
	
	
	/*pjsua_buddy_id id_a;
	id_a = 1003;*/
	
	

}

//退出登录
void MainDialog::OnBnClickedButton16()//退出登录
{
	// TODO: 在此添加控件通知处理程序代码
	close_flag = 1;
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
	
}


void MainDialog::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void MainDialog::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	if (chatflag[1] == 1)//处在好友列表状态
	{
		friendsset();
	}

}

//发起会话
void MainDialog::On21()
{
	string dsturl="";
	dsturl = "sip:";
	string temp= CT2A(current_friend.id.GetBuffer());
	dsturl += temp;
	current_friend.id.ReleaseBuffer();
	dsturl += "@";
	dsturl += Sip_p.SIP_DOMAIN2;
	
	
	const char  *p = dsturl.c_str();
	zcj= const_cast<char*>(p);
	pj_str_t dst = pj_str(zcj);
	

	if (Sip_p.SIP_USER2 != temp)
	{
		Sip_p.make_call(dst);
		make_call_flag = 1;
		friend_location_flag = 1;
	}

	
	// TODO: 在此添加命令处理程序代码

}

//删除好友
void MainDialog::On22()
{
	// TODO: 在此添加命令处理程序代码
	Sip_p.delete_friends(&current_friend.id);
	//从好友队列中删除
	list<Friend_inf>::iterator it; //声明一个迭代器
	Friend_inf temp;
	if (!Sip_p.lis->empty())
	{
		for (it = Sip_p.lis->begin(); it != Sip_p.lis->end(); it++)
		{
			temp = *it;
			if (temp.id == current_friend.id)
			{
				Sip_p.lis->erase(it);
			}
			
		}
	}
	//从list中删除
	//Sip_p.delete_friends(&current_friend.id);
	SendMessage(BUDDY_DEL, 0, (LPARAM)(&current_friend.buddy_id));


	friendsset();
	//刷新列表

	
}
vector<string> split(const string& str, const string& pattern)
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}


//自定义消息，显示来自好友的信息
LRESULT MainDialog::friend_msg(WPARAM wParam, LPARAM lParam)
{
	int iRow = list4.GetItemCount(); //获取行数
	if (friend_location_flag == 1)//我方为通话发起方
	{
		string s1(CW2A(current_friend.id.GetString()));
		s1 += ":";
		CString s2;
		s2 = s1.c_str();
		list4.InsertItem(iRow,s2);
		CString s3;
		s3 = Sip_p.rec_msg.c_str();
		list4.SetItemText(iRow, 1, s3);
		
	}
	else//我方为通话接收方
	{

		string s1 = Sip_p.call_id;
		vector<string> st = split(s1, ":");
		string id2 = st[1];
		st = split(id2, "@");
		s1= st[0];
		s1 += ":";
		CString s2;
		s2 = s1.c_str();
		list4.InsertItem(iRow, s2);
		CString s3;
		s3 = Sip_p.rec_msg.c_str();
		list4.SetItemText(iRow, 1, s3);
		
	}
	

}

//自定义消息，添加好友
LRESULT MainDialog::budy_ad(WPARAM wParam, LPARAM lParam)
{
	pjsua_buddy_id bdy_id;
	bdy_id = *((pjsua_buddy_id*)lParam);
	pjsua_buddy_del(bdy_id);
	pjsua_buddy_config bfg;
	string budy_id;
	budy_id = std::to_string(bdy_id);
	string budy_uri = "sip:" + budy_id + "@" + Sip_p.SIP_DOMAIN2;
	const char *b_u = budy_uri.data();
	char* temp2 = const_cast<char*>(b_u);
	bfg.uri = pj_str(temp2);
	bfg.subscribe = PJ_TRUE;
	pjsua_buddy_add(&bfg, &bdy_id);
	friendsset();

	/*pjsua_buddy_id id[10];
	unsigned int co = 10;
	pjsua_enum_buddies(id, &co);
	CString str;
	str.Format(_T("%d"), co);
	AfxMessageBox(str);*/
	return 0;
}
//自定义消息，删除好友
LRESULT MainDialog::budy_de(WPARAM wParam, LPARAM lParam)
{
	pjsua_buddy_id bdy_id = *((pjsua_buddy_id*)lParam);
	pjsua_buddy_del(bdy_id);

	/*pjsua_buddy_id id[10];
	unsigned int co = 10;
	pjsua_enum_buddies(id, &co);
	CString str;
	str.Format(_T("%d"), co);
	AfxMessageBox(str);*/

	friendsset();
	return 0;
}
//自定义消息，好友初始化
LRESULT MainDialog::budy_init(WPARAM wParam, LPARAM lParam)
{
	Friend_inf temp;
	string bu_id;
	pjsua_buddy_config bfg;
	pjsua_buddy_id b_id;
	list<Friend_inf>::iterator it; //声明一个迭代器
	for (it = Sip_p.lis->begin(); it != Sip_p.lis->end(); it++)
	{
		temp = *it;
		b_id = temp.buddy_id;
		bu_id=CW2A(temp.id.GetString());
		string budy_uri = "sip:" + bu_id + "@" + Sip_p.SIP_DOMAIN2;
		const char *b_u = budy_uri.data();
		char* temp2 = const_cast<char*>(b_u);
		bfg.uri = pj_str(temp2);
		bfg.subscribe = PJ_TRUE;
		pjsua_buddy_add(&bfg, &b_id);
	}
	pjsua_buddy_id id[10];
	unsigned int countt = 10;
	pjsua_enum_buddies(id, &countt);
	CString str;
	str.Format(_T("%d"), countt);
	AfxMessageBox(str);
}
//自定义消息
LRESULT MainDialog::My_Call_Refuse(WPARAM wParam, LPARAM lParam)
{
	//pjsua_call_setting call_setting;
	//pjsua_call_setting_default(&call_setting);
	//call_setting.vid_cnt = 1;
	//call_setting.aud_cnt = 1;

	///* Automatically answer incoming calls with 200/OK */
	//pjsua_call_answer2(CALL_ID, &call_setting, 603, NULL, NULL);
	Sip_p.refuse_call();
	return 0;
}
//自定义消息
LRESULT MainDialog::close_call(WPARAM wParam, LPARAM lParam)
{
	Sip_p.end_call();
	return 0;
}
//自定义消息确认接通
LRESULT MainDialog::OnMyMessage(WPARAM wParam, LPARAM lParam)

{

	window_reset();
	video_win = new VID_WIN;
    video_win->Create((LPCTSTR)IDD_VID_WIN, NULL);
	
	bak_ground.ShowWindow(FALSE);
	//将video_win绑定到当前界面
	{
		video_win->ShowWindow(FALSE);
		video_win->EnableActiveAccessibility();
		//
		HWND p_hwnd1 = GetDlgItem(IDC_STATIC1)->GetSafeHwnd();
		video_win->ModifyStyle(WS_POPUP, WS_CHILDWINDOW);
		::SetParent(video_win->GetSafeHwnd(), p_hwnd1);   //  关联ck
		DWORD dw = ::GetWindowLong(video_win->m_hWnd, GWL_STYLE);
		dw = dw & ~WS_POPUP;//取消弹出式窗体属性
		dw = dw & ~WS_CAPTION;//取消标题栏
		dw = dw & ~WS_THICKFRAME;//取消拖动改变大小
		dw = dw | WS_CHILD;//属性必须设为WS_CHILD
		::SetWindowLong(video_win->m_hWnd, GWL_STYLE, dw);
		dw = ::GetWindowLong(video_win->m_hWnd, GWL_EXSTYLE);
		dw = dw & ~WS_EX_DLGMODALFRAME;//去掉双边框的扩展属性
		::SetWindowLong(video_win->m_hWnd, GWL_EXSTYLE, dw);
		CRect re;
		GetDlgItem(IDC_STATIC1)->GetWindowRect(re);
		ScreenToClient(re);
		::SetWindowPos(video_win->m_hWnd, HWND_TOPMOST, 0, 0, re.Width(), re.Height(), SWP_NOMOVE | SWP_NOSIZE);
		video_win->MoveWindow(0, 0, re.Width(), re.Height());//用movewindow和setwindowpos都可以
	}





	//通话账号设置
	{
		string s1 = Sip_p.call_id;
		vector<string> st = split(s1, ":");
		string id2 = st[1];
		st = split(id2, "@");
		s1 = st[0];
		CString end_friend = _T("");//好友账户
		string fr_p = "您当前正在和";
		fr_p += s1;
		fr_p += "通话";
		end_friend = fr_p.c_str();
		list4.SetImageList(NULL, LVSIL_SMALL);
		list4.DeleteAllItems();
		list4.InsertColumn(0, _T(" "), LVCFMT_LEFT, 60);
		list4.InsertColumn(1, _T(" "), LVCFMT_LEFT, 265);
		list4.InsertItem(0, _T(""));
		list4.SetItemText(0, 1, end_friend);
	}

	



	//开启预览
	pjsua_vid_preview_param parm;
	pjsua_vid_preview_param_default(&parm);
	parm.rend_id = PJMEDIA_VID_DEFAULT_RENDER_DEV;
	parm.show = PJ_TRUE;
	pj_status_t r = pjsua_vid_preview_start(PJMEDIA_VID_DEFAULT_CAPTURE_DEV, &parm);
	pjsua_vid_win_id wid = pjsua_vid_preview_get_win(PJMEDIA_VID_DEFAULT_CAPTURE_DEV);
	pjsua_vid_win_info pre_inf;
	pjsua_vid_win_get_info(wid, &pre_inf);
	pjmedia_vid_dev_hwnd pre_hwnd = pre_inf.hwnd;
	HWND w2 = (HWND)pre_hwnd.info.win.hwnd;
	CWnd cwd;
	cwd.Attach(w2);
	cwd.ShowWindow(FALSE);
	pjmedia_rect_size r1;
	r1.h = 120;
	r1.w = 160;
	pjsua_vid_win_set_size(wid, &r1);
	cwd.EnableActiveAccessibility();
	/*cwd.SetOwner(GetDlgItem(IDC_STATIC2));
	HWND p_hwnd1 = GetDlgItem(IDC_STATIC2)->GetSafeHwnd();*/
	cwd.SetOwner(video_win->local_win);
	HWND p_hwnd1 =video_win->local_win->GetSafeHwnd();
	cwd.ModifyStyle(WS_POPUP, WS_CHILDWINDOW);
	::SetParent(w2, p_hwnd1);   //  关联ck
	DWORD dw = ::GetWindowLong(cwd.m_hWnd, GWL_STYLE);
	dw = dw & ~WS_POPUP;//取消弹出式窗体属性
	dw = dw & ~WS_CAPTION;//取消标题栏
	dw = dw & ~WS_THICKFRAME;//取消拖动改变大小
	dw = dw | WS_CHILD;//属性必须设为WS_CHILD
	::SetWindowLong(cwd.m_hWnd, GWL_STYLE, dw);
	dw = ::GetWindowLong(cwd.m_hWnd, GWL_EXSTYLE);
	dw = dw & ~WS_EX_DLGMODALFRAME;//去掉双边框的扩展属性
	::SetWindowLong(cwd.m_hWnd, GWL_EXSTYLE, dw);
	CRect re;
    //GetDlgItem(IDC_STATIC2)->GetWindowRect(re);
	video_win->local_win->GetWindowRect(re);
	ScreenToClient(re);
	::SetWindowPos(cwd.m_hWnd, HWND_TOPMOST, 0, 0, re.Width(), re.Height(), SWP_NOMOVE | SWP_NOSIZE);
	cwd.MoveWindow(0, 0, re.Width(), re.Height());//用movewindow和setwindowpos都可以
	cwd.ShowWindow(SW_SHOW);
	
	
	Sip_p.ans_call();
	//获取传入视频。绑定到指定窗口
	int vid_idx;
	pjsua_vid_win_id wid2 = -1;
	vid_idx = pjsua_call_get_vid_stream_idx(CALL_ID);
	if (vid_idx >= 0)
	{
		pjsua_call_info ci;
		pjsua_call_get_info(CALL_ID, &ci);
		wid2 = ci.media[vid_idx].stream.vid.win_in;
	}
	pjsua_vid_win_info inf;
	if (wid2 != -1)//显示对方视频
	{
		pjsua_vid_win_set_show(wid2, PJ_TRUE);

		pjsua_vid_win_get_info(wid2, &inf);
		pjmedia_vid_dev_hwnd pre_hwnd = inf.hwnd;
		HWND w = (HWND)pre_hwnd.info.win.hwnd;
		CWnd cwd;
		cwd.Attach(w);
		cwd.ShowWindow(FALSE);
		pjmedia_rect_size r1;
		r1.h =480;
		r1.w = 640;
		pjsua_vid_win_set_size(wid2, &r1);
		cwd.EnableActiveAccessibility();
		/*cwd.SetOwner(GetDlgItem(IDC_STATIC1));
		HWND p_hwnd = GetDlgItem(IDC_STATIC1)->GetSafeHwnd();*/
		cwd.SetOwner(video_win->friend_win);
		HWND p_hwnd = video_win->friend_win->GetSafeHwnd();
		cwd.ModifyStyle(WS_POPUP, WS_CHILDWINDOW);
		::SetParent(w, p_hwnd);   //  关联ck
		DWORD dw = ::GetWindowLong(cwd.m_hWnd, GWL_STYLE);
		dw = dw & ~WS_POPUP;//取消弹出式窗体属性
		dw = dw & ~WS_CAPTION;//取消标题栏
		dw = dw & ~WS_THICKFRAME;//取消拖动改变大小
		dw = dw | WS_CHILD;//属性必须设为WS_CHILD
		::SetWindowLong(cwd.m_hWnd, GWL_STYLE, dw);
		dw = ::GetWindowLong(cwd.m_hWnd, GWL_EXSTYLE);
		dw = dw & ~WS_EX_DLGMODALFRAME;//去掉双边框的扩展属性
		::SetWindowLong(cwd.m_hWnd, GWL_EXSTYLE, dw);
		CRect re;
		//GetDlgItem(IDC_STATIC1)->GetWindowRect(re);
		video_win->friend_win->GetWindowRect(re);
		ScreenToClient(re);
		cwd.MoveWindow(0, 0, re.Width(), re.Height());//用movewindow和setwindowpos都可以
		//pj_thread_sleep(100);
		cwd.ShowWindow(SW_SHOW);
		

		::SetParent(p_hwnd1,p_hwnd);//将xx1设为xx2的子窗口
		LONG_PTR Style = ::GetWindowLongPtr(p_hwnd, GWL_STYLE);//获取xx2属性
		Style = Style | WS_CLIPCHILDREN;//xx2属性+WS_CLIPCHILDREN      即父窗口不再重绘子窗口覆盖部分
		::SetWindowLongPtr(p_hwnd, GWL_STYLE, Style);
		
		

	}
	
	video_win->ShowWindow(TRUE);
	

	return 0;

}
//自定义消息
LRESULT MainDialog::w_video(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
//自定义消息
LRESULT MainDialog::w_preview(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
//自定义消息
LRESULT MainDialog::video_encode(WPARAM wParam, LPARAM lParam)
{
	int val = *((int*)lParam);
	if (val == H264)//
	{
		const pj_str_t codec_id{ "h264",4 };
		pjmedia_vid_codec_param param;
		pjsua_vid_codec_get_param(&codec_id, &param);
		pjsua_vid_codec_set_priority(&codec_id, 255);
        pjsua_vid_codec_set_param(&codec_id, &param);
	}
	else if (val == H263)
	{
		const pj_str_t codec_id{ "h263",4 };
		pjmedia_vid_codec_param param;
		pjsua_vid_codec_get_param(&codec_id, &param);
		pjsua_vid_codec_set_priority(&codec_id, 255);
		pjsua_vid_codec_set_param(&codec_id, &param);
	}
	return 0;
}
//自定义消息
LRESULT MainDialog::voice_encode(WPARAM wParam, LPARAM lParam)
{
	int val = *((int*)lParam);
	if (val == SPEEX_16000)
	{
		const pj_str_t co_id1{ "speex/16000",11 };
		pjmedia_codec_param *prm = NULL;
		pjsua_codec_get_param(&co_id1, prm);
	    pjsua_codec_set_priority(&co_id1, 255);
		pjsua_codec_set_param(&co_id1, prm);
	}
	else if (val == GSM_8000)
	{
		const pj_str_t co_id1{ "GSM/8000",8 };
		pjmedia_codec_param *prm=NULL;
		pjsua_codec_get_param(&co_id1, prm);
		pjsua_codec_set_priority(&co_id1, 255);
		pjsua_codec_set_param(&co_id1, prm);
	}
	else if (val = G722_16000)
	{
		const pj_str_t co_id1{ "G722/16000",10 };
		pjmedia_codec_param *prm = NULL;
		pjsua_codec_get_param(&co_id1, prm);
		pjsua_codec_set_priority(&co_id1, 255);
		pjsua_codec_set_param(&co_id1, prm);

	}
	return 0;
}

void MainDialog::income_call()
{
	if (Sip_p.wait_flag == 1)
	{
		Sip_p.wait_flag = 0;
		CALL_ID = Sip_p.CALL_ID;
		string id = Sip_p.call_id;
		vector<string> st = split(id, ":");
		string id2 = st[1];
		st = split(id2, "@");
		string id3 = st[0];
		string call_from = "你收到来自" + id3 + "的通话请求";
		w_recpt->call_id = call_from.c_str();
		w_recpt->init();
		w_recpt->ShowWindow(SW_SHOW);
	}
	
}

void MainDialog::make_call_state()
{
	if (Sip_p.connect_state == _T("CONNECTING")&&make_call_flag==1&& Sip_p.local_receive_flag == 1)
	{
		    make_call_flag = 0;
			Sip_p.local_receive_flag = 0;
			call_side = 1;
			window_reset();
			bak_ground.ShowWindow(FALSE);
			CString end_friend = _T("");//好友账户
			string fr_p = "您当前正在和";
			fr_p += CW2A(current_friend.id.GetString());
			fr_p += "通话";
			end_friend = fr_p.c_str();
			list4.SetImageList(NULL, LVSIL_SMALL);
			list4.DeleteAllItems();
			list4.InsertColumn(0, _T(" "), LVCFMT_LEFT, 60);
			list4.InsertColumn(1, _T(" "), LVCFMT_LEFT, 265);
			list4.InsertItem(0, _T(""));
			list4.SetItemText(0, 1, end_friend);

			video_win = new VID_WIN;
			video_win->Create((LPCTSTR)IDD_VID_WIN, NULL);

			//将video_win绑定到当前界面
			{
				video_win->ShowWindow(FALSE);
				video_win->EnableActiveAccessibility();
				//
				HWND p_hwnd1 = GetDlgItem(IDC_STATIC1)->GetSafeHwnd();
				video_win->ModifyStyle(WS_POPUP, WS_CHILDWINDOW);
				::SetParent(video_win->GetSafeHwnd(), p_hwnd1);   //  关联ck
				DWORD dw = ::GetWindowLong(video_win->m_hWnd, GWL_STYLE);
				dw = dw & ~WS_POPUP;//取消弹出式窗体属性
				dw = dw & ~WS_CAPTION;//取消标题栏
				dw = dw & ~WS_THICKFRAME;//取消拖动改变大小
				dw = dw | WS_CHILD;//属性必须设为WS_CHILD
				::SetWindowLong(video_win->m_hWnd, GWL_STYLE, dw);
				dw = ::GetWindowLong(video_win->m_hWnd, GWL_EXSTYLE);
				dw = dw & ~WS_EX_DLGMODALFRAME;//去掉双边框的扩展属性
				::SetWindowLong(video_win->m_hWnd, GWL_EXSTYLE, dw);
				CRect re;
				GetDlgItem(IDC_STATIC1)->GetWindowRect(re);
				ScreenToClient(re);
				::SetWindowPos(video_win->m_hWnd, HWND_TOPMOST, 0, 0, re.Width(), re.Height(), SWP_NOMOVE | SWP_NOSIZE);
				video_win->MoveWindow(0, 0, re.Width(), re.Height());//用movewindow和setwindowpos都可以
			}





			//预览窗口
			{
				pjsua_vid_preview_param parm;
				pjsua_vid_preview_param_default(&parm);
				parm.rend_id = PJMEDIA_VID_DEFAULT_RENDER_DEV;
				parm.show = PJ_TRUE;
				pj_status_t r = pjsua_vid_preview_start(PJMEDIA_VID_DEFAULT_CAPTURE_DEV, &parm);
				pjsua_vid_win_id wid = pjsua_vid_preview_get_win(PJMEDIA_VID_DEFAULT_CAPTURE_DEV);
				pjsua_vid_win_info pre_inf;
				pjsua_vid_win_get_info(wid, &pre_inf);
				pjmedia_vid_dev_hwnd pre_hwnd = pre_inf.hwnd;
				HWND w2 = (HWND)pre_hwnd.info.win.hwnd;
				CWnd cwd2;
				cwd2.Attach(w2);
				cwd2.ShowWindow(FALSE);
				pjmedia_rect_size r2;
				r2.h = 120;
				r2.w = 160;
				pjsua_vid_win_set_size(wid, &r2);
				cwd2.EnableActiveAccessibility();
				//cwd2.SetOwner(GetDlgItem(IDC_STATIC2));
				//HWND p_hwnd1 = GetDlgItem(IDC_STATIC2)->GetSafeHwnd();
				cwd2.SetOwner(video_win->local_win);
				HWND p_hwnd1 =video_win->local_win->GetSafeHwnd();
				cwd2.ModifyStyle(WS_POPUP, WS_CHILDWINDOW);
				::SetParent(w2, p_hwnd1);   //  关联ck
				DWORD dw2 = ::GetWindowLong(cwd2.m_hWnd, GWL_STYLE);
				dw2 = dw2 & ~WS_POPUP;//取消弹出式窗体属性
				dw2 = dw2 & ~WS_CAPTION;//取消标题栏
				dw2 = dw2 & ~WS_THICKFRAME;//取消拖动改变大小
				dw2 = dw2 | WS_CHILD;//属性必须设为WS_CHILD
				::SetWindowLong(cwd2.m_hWnd, GWL_STYLE, dw2);
				dw2 = ::GetWindowLong(cwd2.m_hWnd, GWL_EXSTYLE);
				dw2 = dw2 & ~WS_EX_DLGMODALFRAME;//去掉双边框的扩展属性
				::SetWindowLong(cwd2.m_hWnd, GWL_EXSTYLE, dw2);
				CRect re2;
				//GetDlgItem(IDC_STATIC2)->GetWindowRect(re2);
				video_win->local_win->GetWindowRect(re2);
				ScreenToClient(re2);
				::SetWindowPos(cwd2.m_hWnd, HWND_TOPMOST, 0, 0, re2.Width(), re2.Height(), SWP_NOMOVE | SWP_NOSIZE);
				cwd2.MoveWindow(0, 0, re2.Width(), re2.Height());//用movewindow和setwindowpos都可以
				
				

				//对方窗口
				pjsua_vid_win_info inf;
				pjsua_vid_win_get_info(Sip_p.local_receive, &inf);
				pjmedia_vid_dev_hwnd fri_hwnd = inf.hwnd;
				HWND w = (HWND)fri_hwnd.info.win.hwnd;
				CWnd cwd;
				cwd.Attach(w);
				cwd.ShowWindow(FALSE);
				pjmedia_rect_size r1;
				r1.h = 480;
				r1.w = 640;
				pjsua_vid_win_set_size(Sip_p.local_receive, &r1);
				cwd.EnableActiveAccessibility();
				//cwd.SetOwner(GetDlgItem(IDC_STATIC1));
				//HWND p_hwnd = GetDlgItem(IDC_STATIC1)->GetSafeHwnd();
				cwd.SetOwner(video_win->friend_win);
				HWND p_hwnd = video_win->friend_win->GetSafeHwnd();
				cwd.ModifyStyle(WS_POPUP, WS_CHILDWINDOW);
				::SetParent(w, p_hwnd);   //  关联ck
				DWORD dw = ::GetWindowLong(cwd.m_hWnd, GWL_STYLE);
				dw = dw & ~WS_POPUP;//取消弹出式窗体属性
				dw = dw & ~WS_CAPTION;//取消标题栏
				dw = dw & ~WS_THICKFRAME;//取消拖动改变大小
				dw = dw | WS_CHILD;//属性必须设为WS_CHILD
				::SetWindowLong(cwd.m_hWnd, GWL_STYLE, dw);
				dw = ::GetWindowLong(cwd.m_hWnd, GWL_EXSTYLE);
				dw = dw & ~WS_EX_DLGMODALFRAME;//去掉双边框的扩展属性
				::SetWindowLong(cwd.m_hWnd, GWL_EXSTYLE, dw);
				CRect re;
				//GetDlgItem(IDC_STATIC1)->GetWindowRect(re);
				video_win->friend_win->GetWindowRect(re);
				ScreenToClient(re);
				cwd.MoveWindow(0, 0, re.Width(), re.Height());//用movewindow和setwindowpos都可以
				//pj_thread_sleep(100);
				cwd.ShowWindow(SW_SHOW);
				cwd2.ShowWindow(SW_SHOW);

				//窗口叠加处理
				::SetParent(p_hwnd1, p_hwnd);//将xx1设为xx2的子窗口
				LONG_PTR Style = ::GetWindowLongPtr(p_hwnd, GWL_STYLE);//获取xx2属性
				Style = Style | WS_CLIPCHILDREN;//xx2属性+WS_CLIPCHILDREN      即父窗口不再重绘子窗口覆盖部分
				::SetWindowLongPtr(p_hwnd, GWL_STYLE, Style);
			}
			video_win->ShowWindow(TRUE);
	}

}

void MainDialog::show_msg(void)
{
	if (Sip_p.message_flag == 1)//文本消息
	{
		Sip_p.message_flag = 0;
		SendMessage(FRIEND_MSG, 0, 0);
	}
}

void MainDialog::close_vid_win(void)
{
	if (Sip_p.end_call_flag == 1)
	{
		Sip_p.end_call_flag = 0;
		pjsua_vid_preview_stop(PJMEDIA_VID_DEFAULT_CAPTURE_DEV);
		video_win->DestroyWindow();
		//delete  video_win;
		
		bak_ground.ShowWindow(TRUE);
		//Sip_p.end_call();
		pjsua_call_hangup(CALL_ID, 603, NULL, NULL);
	    

		call_side = 0;
		//显示
		{
			end_call.ShowWindow(FALSE);
			Mesag.ShowWindow(FALSE);
			send.ShowWindow(FALSE);
			Pic.ShowWindow(FALSE);
			list4.ShowWindow(FALSE);
		}
		{
			list1.ShowWindow(TRUE); //隐藏好友列表
			add.ShowWindow(TRUE);//隐藏添加好友按钮
			refresh.ShowWindow(TRUE);//隐藏刷新按钮
			me.ShowWindow(TRUE);
			fr.ShowWindow(TRUE);
			gr.ShowWindow(TRUE);
		}
		friend_location_flag = 0;
	}
}
//定时器
void MainDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 0)
	{
		make_call_state();
		income_call();
		show_msg();
		close_vid_win();
	}

	CDialogEx::OnTimer(nIDEvent);
}
//通话状态重设window
void MainDialog::window_reset()
{
	
	list1.ShowWindow(FALSE);//隐藏好友列表
	add.ShowWindow(FALSE);//隐藏天骄好友按钮
	refresh.ShowWindow(FALSE);//隐藏刷新按钮
	me.ShowWindow(FALSE);
	fr.ShowWindow(FALSE);
	gr.ShowWindow(FALSE);

	//显示
	end_call.ShowWindow(TRUE);
	Mesag.ShowWindow(TRUE);
	send.ShowWindow(TRUE);
	Pic.ShowWindow(TRUE);
	list4.ShowWindow(TRUE);
	//

	
}


void MainDialog::close_call()
{
	// TODO: 在此添加控件通知处理程序代码

	video_win->DestroyWindow();
	
	//delete  video_win;
	friend_location_flag = 0;
	//显示
	{
		end_call.ShowWindow(FALSE);
		Mesag.ShowWindow(FALSE);
		send.ShowWindow(FALSE);
		Pic.ShowWindow(FALSE);
		list4.ShowWindow(FALSE);
	}
	{
		list1.ShowWindow(TRUE); //隐藏好友列表
		add.ShowWindow(TRUE);//隐藏天骄好友按钮
		refresh.ShowWindow(TRUE);//隐藏刷新按钮
		me.ShowWindow(TRUE);
		fr.ShowWindow(TRUE);
		gr.ShowWindow(TRUE);
	}

	pjsua_vid_preview_stop(PJMEDIA_VID_DEFAULT_CAPTURE_DEV);
	bak_ground.ShowWindow(TRUE);
	


	//发送挂断消息
	{
		pjsua_acc_id send_from = Sip_p.acc_id;
		std::string to_id(CW2A(current_friend.id.GetString()));
		string add_to = "sip:" + to_id + "@" + Sip_p.SIP_DOMAIN2;
		const char*add_uri = add_to.data();
		char *uri_dest = (char*)add_uri;
		pj_str_t to = pj_str(uri_dest);


		string  s = "0X603BYEBYE";
		const char *tt;
		tt = s.c_str();
		char *mg;
		mg = const_cast<char*>(tt);
		pj_str_t im_s = pj_str(mg);


		


		pjsua_msg_data msgd;
		pjsua_msg_data_init(&msgd);
		if (call_side == 1)
		{
			pjsua_im_send(send_from, &to, NULL, &im_s, &msgd, NULL);
			
		}
		else
		{
			pjsua_call_send_im(Sip_p.CALL_ID, NULL, &im_s, &msgd, NULL);
			
		}
	}
	call_side = 0;
	pj_thread_sleep(10000);
	Sip_p.end_call();
	
}


void MainDialog::IM_MESAG_SEND()
{
	// TODO: 在此添加控件通知处理程序代码
	pjsua_acc_id send_from = Sip_p.acc_id;
	std::string to_id(CW2A(current_friend.id.GetString()));
	string add_to = "sip:" + to_id + "@" + Sip_p.SIP_DOMAIN2;
	const char*add_uri = add_to.data();
	char *uri_dest = (char*)add_uri;
	pj_str_t to = pj_str(uri_dest);


	CString msg;
	Mesag.GetWindowTextW(msg);
	/*AfxMessageBox(msg);
	char *im=(char*)msg.GetBuffer(msg.GetLength());*/
	string s(CW2A(msg.GetString()));
	const char *tt;
	tt = s.c_str();
	char *mg;
	mg = const_cast<char*>(tt);
	pj_str_t im_s = pj_str(mg);


	pjsua_msg_data msgd;
	pjsua_msg_data_init(&msgd);
	if (call_side == 1)
	{
		pjsua_im_send(send_from, &to, NULL, &im_s, &msgd, NULL);
	}
	else
	{
		pjsua_call_send_im(Sip_p.CALL_ID, NULL, &im_s, &msgd, NULL);
	}

	int iRow = list4.GetItemCount(); //获取行数

	string s1 = Sip_p.SIP_USER2 + ":";
	CString s2;
	s2 = s1.c_str();
	list4.InsertItem(iRow, s2);
	list4.SetItemText(iRow, 1, msg);
	//list4.EnsureVisible(list4.GetItemCount() - 1, FALSE);
	list4.SetScrollPos(list4.GetItemCount(), 1, TRUE);
	Mesag.SetWindowTextW(_T(""));
}



void MainDialog::AutoAdjustColumnWidth(CListCtrl *pListCtrl)
{
	pListCtrl->SetRedraw(FALSE);
	CHeaderCtrl *pHeader = pListCtrl->GetHeaderCtrl();
	int nColumnCount = pHeader->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		pListCtrl->SetColumnWidth(i, LVSCW_AUTOSIZE);
		int nColumnWidth = pListCtrl->GetColumnWidth(i);
		pListCtrl->SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		int nHeaderWidth = pListCtrl->GetColumnWidth(i);
		pListCtrl->SetColumnWidth(i, max(nColumnWidth, nHeaderWidth) + 5);
	}
	pListCtrl->SetRedraw(TRUE);
}

void MainDialog::re_login()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//ShowWindow(FALSE);
	Sip_p.destroy();
	CWnd* pWnd = CWnd::FindWindow(NULL, _T("login"));
	pWnd->ShowWindow(SW_SHOW);
	ShowWindow(SW_HIDE);

}


void MainDialog::System_Set()
{
	// TODO: 在此添加控件通知处理程序代码
	media_set->ShowWindow(TRUE);
}


bool AnalysisFile()
{
	bool rState;//返回状态
	FILE *file;
	char ln[80];
	fopen_s(&file, "returnpingdata.txt", "r");

	fgets(ln, 80, file);//读入空行，舍弃
	fgets(ln, 80, file);//读入ping信息，舍弃
	fgets(ln, 80, file);//读入ping对象返回值，用来分析

	string data = ln;
	int iPos = data.find("=");
	data = data.substr(iPos + 1, 3);//截取字符串返回字节数
	int  n = atoi(data.c_str());
	rState = n > 0;
	fclose(file);
	return rState;
}


void MainDialog::Net_Check()
{
	// TODO: 在此添加控件通知处理程序代码
	string s_pr= "cmd /c ping ";
	string s_domain = Sip_p.SIP_DOMAIN2;
	string s_la = " -n 1 -w 1000 >returnpingdata.txt";
	string s_a = s_pr + s_domain + s_la;
	char *cmdstr = (char*)s_a.data();
	WinExec(cmdstr, SW_HIDE);
	Sleep(1000);//等待1000ms
	bool returndata = AnalysisFile();//分析命令行返回文件，得到网络连接情况
	if (returndata == true)
	{
		AfxMessageBox(_T("网络正常"));
	}
	else
	{
		AfxMessageBox(_T("网络故障"));
	}
}

BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	// Get the required size of the buffer that receives the Unicode 
	// string. 
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);
	assert(dwSize >= dwMinSize);

	// Convert headers from ASCII to Unicode.
	MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
	return TRUE;
}

void MainDialog::Local_Reso()
{

	// TODO: 在此添加控件通知处理程序代码

	CString filePath1;
	//true, _T(".jpg"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Image file (*.jpg)|*.jpg|All   Files   (*.*)|*.*||"), this);
	CFileDialog dlg(true, _T(".avi"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("video Files(*.avi)|*.avi|audio Files(*.wav)|*.wav||"), AfxGetMainWnd());
	if (IDOK == dlg.DoModal())
	{
		filePath1 = dlg.GetPathName();//获得选择文档的路劲并保存在filePath变量中
		//m_selFile = filePath;//m_selFile为与要显示路径的编辑框绑定的变量
		UpdateData(FALSE);//将与编辑框绑定的变量的值传到编辑框，并且显示到编辑框
	}

	
	
	USES_CONVERSION;
	char * pFileName = T2A(filePath1);
	CString w = filePath1.Right(3); //同理，q.Left（3）为获得左边字符
	UpdateData(false);
	if(w=="avi")
	{//avi 
		cvNamedWindow("video", 0);
		cvResizeWindow("video", 640, 480);
		SendMessage(OPENCV_WIN, 0, 0);
		bak_ground.ShowWindow(FALSE);
		CvCapture* capture = cvCreateFileCapture(pFileName);
		IplImage* frame;
		while (1) {
			if (play_enable == 1)
			{
				frame = cvQueryFrame(capture);
				if (!frame) break;
				cvShowImage("video", frame);
				cvWaitKey(33);
				if (close_flag == 1) break;
			}
			else
			{
				cvWaitKey(33);
				if (close_flag == 1)
					break;
			}
		}
		cvReleaseCapture(&capture);
		cvDestroyWindow("video");
		bak_ground.ShowWindow(TRUE);
	}
	else if (w = "wav")
	{
		

		USES_CONVERSION;
		CString str = CString(pFileName);
		LPCWSTR wszClassName = new WCHAR[str.GetLength() + 1];
		wcscpy((LPTSTR)wszClassName, T2W((LPTSTR)str.GetBuffer(NULL)));
		str.ReleaseBuffer();
		bool fg=PlaySound(wszClassName, NULL, SND_FILENAME | SND_ASYNC|SND_NODEFAULT);
		if (fg == FALSE)
		{
			AfxMessageBox(_T("error"));
		}
	}
}
//自定义消息
LRESULT MainDialog::win_attach(WPARAM wParam, LPARAM lParam)
{
	{
		CWnd* pWnd = CWnd::FindWindow(NULL, _T("video"));
		ASSERT(pWnd);

		HWND w = pWnd->GetSafeHwnd();

		pWnd->ShowWindow(FALSE);

		pWnd->EnableActiveAccessibility();


		pWnd->SetOwner(GetDlgItem(IDC_STATIC1));
		HWND p_hwnd = GetDlgItem(IDC_STATIC1)->GetSafeHwnd();
		pWnd->ModifyStyle(WS_POPUP, WS_CHILDWINDOW);
		::SetParent(w, p_hwnd);   //  关联ck
		DWORD dw = ::GetWindowLong(pWnd->m_hWnd, GWL_STYLE);
		dw = dw & ~WS_POPUP;//取消弹出式窗体属性
		dw = dw & ~WS_CAPTION;//取消标题栏
		dw = dw & ~WS_THICKFRAME;//取消拖动改变大小
		dw = dw | WS_CHILD;//属性必须设为WS_CHILD
		::SetWindowLong(pWnd->m_hWnd, GWL_STYLE, dw);
		dw = ::GetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE);
		dw = dw & ~WS_EX_DLGMODALFRAME;//去掉双边框的扩展属性
		::SetWindowLong(pWnd->m_hWnd, GWL_EXSTYLE, dw);
		CRect re;
		GetDlgItem(IDC_STATIC1)->GetWindowRect(re);
		ScreenToClient(re);
		pWnd->MoveWindow(0, 0, re.Width(), re.Height());//用movewindow和setwindowpos都可以
		pWnd->ShowWindow(TRUE);
	}
	return 0;
}