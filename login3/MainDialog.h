#pragma once
#include"StaticTrans.h"
#include"BtnST.h"
#include"CMyListCtrl.h"
#include"MySip3.h"
#include"queue"
#include"list"
#include"Friend_inf.h"
#include"Make_sure.h"
#include"CEditTrans.h"
#include"VID_WIN.h"
#include"MEDIA_SETTING.h"

//自定义消息
//自定义消息

using namespace std;
class MainDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MainDialog)

public:
	queue<Friend_inf> *friends_queue;
	Friend_inf current_friend;
public:
	MainDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainDialog();
public:
	MySip3 Sip_p;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void accountset(void);
	void friendsset(void);
	void groupset(void);
	void income_call(void);
	void make_call_state(void);
	void window_reset(void);
	void show_msg(void);
	void close_vid_win(void);

	void win_change();
	int make_call_flag = 0;
	int timer_flag = 1;
	int call_side = 0;
	int friend_location_flag = 0;
	pjsua_call_id CALL_ID;
	//视频窗口
	CWnd local_vid_win;
	CWnd friend_vid_win;
	void AutoAdjustColumnWidth(CListCtrl *pListCtrl);
	afx_msg void OnBnClickedButton1();
	CButtonST st;
	CButtonST lf;
	CButtonST ri;
	CButtonST nv;
	afx_msg void OnBnClickedButton4();
	//预览与否
	bool PREVIEW_AVAILABLE = TRUE;
	//是否支持视频
	bool VIDEO_AVAILABLE = TRUE;

	void confirm_call(void);
	
	CButtonST me;
	CButtonST fr;
	CButtonST gr;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton7();
	CClassListWnd list1;
	CImageList m_IconList;

	
	CListCtrl list2;
	afx_msg void OnPaint();
	CStatic m_pictureControl;
	afx_msg void OnBnClickedButton9();
	afx_msg void On11();
	afx_msg void On12();
	CButtonST add;
	CButtonST dl;
	CButtonST in;
	afx_msg void OnBnClickedButton10();
	CButtonST ex;
	CButtonST rel;
	CButtonST rs;
	CButtonST time;
	CButtonST nt;
	CButtonST set;

	CButtonST va;
	CButtonST vd;
	CButtonST voice;
	CButtonST up;
	CButtonST down;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton3();


	
	CButtonST refresh;
	afx_msg void OnBnClickedButton8();
	afx_msg void On21();
	afx_msg void On22();

	//自定义消息
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam); // add lyw

	afx_msg LRESULT My_Call_Refuse(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT close_call(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT budy_init(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT budy_ad(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT budy_de(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT friend_msg(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT w_video(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT w_preview(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT video_encode(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT voice_encode(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT win_attach(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT chat_win_change(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT video_win_change(WPARAM wParam, LPARAM lParam);
	//自定义消息

	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	CListCtrl list_chat;
//	CButtonST send;
////	CButtonST file;
//	CButtonST close;
//	CEditTrans mesg;
//	CButtonST File_l;
	CButtonST end_call;
	CEditTrans Mesag;
	CButtonST send;
	CButtonST Pic;
//	CListCtrl list4;
	afx_msg void close_call();
	afx_msg void IM_MESAG_SEND();
	afx_msg void re_login();
	CClassListWnd list4;
	CStatic bak_ground;
	afx_msg void System_Set();
	afx_msg void Net_Check();
	afx_msg void Local_Reso();
};
