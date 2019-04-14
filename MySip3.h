#pragma once
#include <pjsua-lib/pjsua.h>
#include"queue"
#include"pjsua2.hpp"
#include"Friend_inf.h"
#include"CMyListCtrl.h"
#include"list"
#include"windows.h"
#include"stdafx.h"
#include"Make_sure.h"
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"dsound.lib")
#define THIS_FILE	"APP"

#define SIP_DOMAIN	"192.168.43.125"
#define SIP_USER	"1001"
#define SIP_PASSWD	"1001"
using namespace std;
using namespace pj;
#include <afxdialogex.h>

class MySip3 :
	public CDialogEx
{
public:
	MySip3();
	~MySip3();

public:
	
	int i = 0;
	string SIP_DOMAIN2;
	string SIP_USER2;
	string SIP_PASSWD2;
	int SIP_PORT;
	bool login_flag;
	Endpoint *ep = new Endpoint;//
	EpConfig ep_cfg;
	TransportConfig tcfg;
	pjsua_acc_id acc_id;
	pjsua_config cfg;
	pjsua_logging_config log_cfg;
	pjsua_transport_config trans_cfg;
	pjsua_acc_config acc_cfg;

	CWnd local_win;
	CWnd friend_win;
	CWnd *main_cwd;
	HWND main_hand;

	static MySip3 *pThis1;
	//
	string tt;
	//
	int accept;
	int wait_flag;
	int rec_flag;
	string call_id="x";
	pjsua_call_id CALL_ID;
	pjsua_vid_win_id local_receive=0;
	int local_receive_flag = 0;
	int message_flag = 0;
	string rec_msg;
	CString connect_state=_T("x");
	BOOL login_state = FALSE;
	int end_call_flag = 0;
	list<Friend_inf> *lis;


public:
	void init();//³õÊ¼»¯
	void destroy();//×¢Ïú
	void login();//µÇÂ¼
	void add_friends(list<Friend_inf> *lis);//Ìí¼ÓºÃÓÑ
	void delete_friends(CString *id);//É¾³ýºÃÓÑ
	bool state_friends(CString fr_id);//ºÃÓÑ×´Ì¬

	static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id,
		pjsip_rx_data *rdata);
	static void on_call_state(pjsua_call_id call_id, pjsip_event *e);
	static void on_call_media_state(pjsua_call_id call_id);
	static void error_exit(const char *title, pj_status_t status);
	static void on_buddy_state(pjsua_buddy_id buddy_id);
	static void on_incoming_subscribe(pjsua_acc_id acc_id, pjsua_srv_pres *srv_pres, pjsua_buddy_id buddy_id, const pj_str_t *from, pjsip_rx_data *rdata, pjsip_status_code *code, pj_str_t *reason, pjsua_msg_data *msg_data_);
	static void on_pager(pjsua_call_id call_id, const pj_str_t *from,
		const pj_str_t *to, const pj_str_t *contact,
		const pj_str_t *mime_type, const pj_str_t *text);

	static void on_reg_state2(pjsua_acc_id acc_id, pjsua_reg_info *info);
		
	void make_call(pj_str_t uri);
	void end_call();
	void ans_call();
	void refuse_call();
};

