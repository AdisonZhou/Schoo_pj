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
//#include"MainDialog.h"
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"ole32.lib")
#pragma comment(lib,"dsound.lib")
#define THIS_FILE	"APP"

#define SIP_DOMAIN	"192.168.43.125"
#define SIP_USER	"1001"
#define SIP_PASSWD	"1001"

static UINT WM_MyMessage = RegisterWindowMessage(_T("myMessage"));
using namespace std;
using namespace pj;

//class MyCall :public Call
//{
//public:
//	MyCall(Account &acc, int call_id = PJSUA_INVALID_ID)
//		: Call(acc, call_id)
//	{ }
//
//	~MyCall()
//	{ }
//
//	// Notification when call's state has changed.
//	virtual void onCallState(OnCallStateParam &prm)
//	{
//		CallInfo ci = getInfo();
//		if (ci.state == PJSIP_INV_STATE_DISCONNECTED)
//		{
//			/* Schedule/Dispatch call deletion to another thread here */
//			//del_call_scheduled = true;
//		}
//	}
//
//	// Notification when call's media state has changed.
//	virtual void onCallMediaState(OnCallMediaStateParam &prm)
//	{
//		CallInfo ci = getInfo();
//		// Iterate all the call medias
//		for (unsigned i = 0; i < ci.media.size(); i++) {
//			if (ci.media[i].type == PJMEDIA_TYPE_AUDIO && getMedia(i)) {
//				AudioMedia *aud_med = (AudioMedia *)getMedia(i);
//
//				// Connect the call audio media to sound device
//				AudDevManager& mgr = Endpoint::instance().audDevManager();
//				aud_med->startTransmit(mgr.getPlaybackDevMedia());
//				mgr.getCaptureDevMedia().startTransmit(*aud_med);
//			}
//		}
//	}
//
//};
//class MyAccount :public Account
//{
//public:
//	MyAccount() {}
//	//~MyAccount()
//	//{
//	//	// Invoke shutdown() first..
//	//	//shutdown();
//	//	
//	//	// ..before deleting any member objects.
//	//}
//
//	virtual void onRegState(OnRegStateParam &prm)
//	{
//		AccountInfo ai = getInfo();
//		//cout << (ai.regIsActive ? "*** Register: code=" : "*** Unregister: code=")
//		//	<< prm.code << endl;
//	}
//
//	virtual void onIncomingCall(OnIncomingCallParam &iprm)
//	{
//		//MyCall *call = new MyCall(*this, iprm.callId);
//
//		//
//
//		pjsua_call_setting call_setting;
//		pjsua_call_setting_default(&call_setting);
//		call_setting.vid_cnt = 1;
//		pjsua_call_answer2(iprm.callId, &call_setting, 200, NULL, NULL);
//		
//		//
//		// Just hangup for now
//		//CallOpParam op;
//		//op.statusCode = PJSIP_SC_DECLINE;
//		//call->hangup(op);
//
//		// And delete the call
//		//delete call;
//	}
//};
//
//class MyBuddy : public Buddy
//{
//public:
//	MyBuddy() {}
//	~MyBuddy() {}
//	pjsua_buddy_status state_budy;
//	virtual void onBuddyState()
//	{
//		BuddyInfo bi = getInfo();
//		state_budy= bi.presStatus.status;
//	}
//};


class MySip
{
public:
	int i = 0;
	string SIP_DOMAIN2;
	string SIP_USER2;
	string SIP_PASSWD2;
	int SIP_PORT;
	bool login_flag;
//	MyAccount *acc = new MyAccount;
//	MyBuddy *buddy=new MyBuddy;
	//pjsua2 
	Endpoint *ep=new Endpoint;//
	EpConfig ep_cfg;
	TransportConfig tcfg;
	//AccountConfig acc_cfg;
	/*AccountCallConfig *cal_cfg = new AccountCallConfig;
	AccountMediaConfig *meida_cfg = new AccountMediaConfig;
	AccountVideoConfig *video_cfg = new AccountVideoConfig;*/
	pjsua_acc_id acc_id;
	pjsua_config cfg;
	pjsua_logging_config log_cfg;
	pjsua_transport_config trans_cfg;
	pjsua_acc_config acc_cfg;
	
	CWnd local_win;
	CWnd friend_win;
	CWnd *main_cwd;
	HWND main_hand;
	
	static MySip *pThis1;
	//
	string tt;
	//
	int accept;
	int wait_flag;
	int rec_flag;


public:
	MySip();
	~MySip();
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
	void make_call(pj_str_t uri);
	void end_call();
	
};

