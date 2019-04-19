#include "stdafx.h"
#include "MySip.h"
#include <cstring>

MySip *MySip::pThis1 = NULL;



MySip::MySip()
{
	SIP_DOMAIN2 = "192.168.43.125";
	SIP_USER2 = "1001";
	SIP_PASSWD2 = "1001";
	SIP_PORT = 5060;
	login_flag = TRUE;
	pThis1 = this;
	accept = 0;
	wait_flag = 1;
	rec_flag = 0;
}
void MySip::init()
{
		////login_flag = TRUE;//登录标志，初始化为TRUE
		//ep->libCreate();
		////创建库
		//ep_cfg.logConfig.level = 5;
		//ep_cfg.uaConfig.maxCalls = 4;
		//ep_cfg.medConfig.sndClockRate = 16000;
		//ep->libInit(ep_cfg);
		////初始化即配置
		////add your code here
		//

		////媒体设置
		//tcfg.port = SIP_PORT;
		//TransportId tid = ep->transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
		////创建传输
		//ep->libStart();
		////启动库
	

}
void MySip::destroy()
{
	pjsua_destroy();
}
void MySip::login()
{
	
	pj_status_t status = pjsua_create();
	if (status != PJ_SUCCESS) error_exit("Error in pjsua_create()", status);
	//
	/* Init pjsua */
	pjsua_config_default(&cfg);
	cfg.cb.on_incoming_call = &on_incoming_call;
	cfg.cb.on_call_media_state = &on_call_media_state;
	cfg.cb.on_call_state = &on_call_state;
	pjsua_logging_config_default(&log_cfg);
	log_cfg.console_level = 4;
    status = pjsua_init(&cfg, &log_cfg, NULL);
	if (status != PJ_SUCCESS) error_exit("Error in pjsua_init()", status);
	//
	/* Add UDP transport. */
	pjsua_transport_config_default(&trans_cfg);
	trans_cfg.port = 5060;
	status = pjsua_transport_create(PJSIP_TRANSPORT_UDP, &trans_cfg, NULL);
	if (status != PJ_SUCCESS) error_exit("Error creating transport", status);
	//
	//start pjsua;
	status = pjsua_start();
	if (status != PJ_SUCCESS) error_exit("Error starting pjsua", status);
	//
	//register
	pjsua_acc_config_default(&acc_cfg);
	acc_cfg.vid_in_auto_show = PJ_TRUE;
	acc_cfg.vid_out_auto_transmit = PJ_TRUE;
	acc_cfg.vid_cap_dev = PJMEDIA_VID_DEFAULT_CAPTURE_DEV;
	string usr_id ="sip:";
	usr_id += SIP_USER2;
	usr_id += "@";
	usr_id += SIP_DOMAIN2;
	acc_cfg.id = pj_str(const_cast<char*>(usr_id.data()));
	string reg_uri = "sip:";
	reg_uri += SIP_DOMAIN2;
	acc_cfg.reg_uri = pj_str(const_cast<char*>(reg_uri.data()));
	acc_cfg.cred_count = 1;
	acc_cfg.cred_info[0].realm = pj_str(const_cast<char*>(SIP_DOMAIN2.data()));
	acc_cfg.cred_info[0].scheme = pj_str("digest");
	acc_cfg.cred_info[0].username = pj_str(const_cast<char*>(SIP_USER2.data()));
	acc_cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
	acc_cfg.cred_info[0].data = pj_str(const_cast<char*>(SIP_PASSWD2.data()));
	status = pjsua_acc_add(&acc_cfg, PJ_TRUE, &acc_id);
	if (status != PJ_SUCCESS) error_exit("Error adding account", status);



	
	//通话设置
	const pj_str_t codec_id{ "H264",4 };
	pjmedia_vid_codec_param param;
	pjsua_vid_codec_get_param(&codec_id, &param);
	param.enc_fmt.det.vid.size.w = 640;
	param.enc_fmt.det.vid.size.h = 480;
	param.dec_fmt.det.vid.size.w = 640;
	param.dec_fmt.det.vid.size.h = 480;



	param.enc_fmt.det.vid.fps.num = 30;
	param.enc_fmt.det.vid.fps.denum = 1;

	param.dec_fmt.det.vid.fps.num = 30;
	param.dec_fmt.det.vid.fps.denum = 1;


	param.enc_fmt.det.vid.avg_bps = 512000;
	param.enc_fmt.det.vid.max_bps = 1024000;

	pjsua_vid_codec_set_param(&codec_id, &param);
	

}

void MySip::add_friends(list<Friend_inf> *lis)
{
	pjsua_buddy_config bfg;
	//
	Friend_inf temp;
	//遍历好友
	list<Friend_inf>::iterator it; //声明一个迭代器
	for (it =lis->begin(); it != lis->end(); it++) 
	{
		pjsua_buddy_id id_a;
		id_a = temp.buddy_id;
		pjsua_buddy_del(id_a);
		string t1;
		string url;
		char *user;
		t1 = "sip:";
		url = t1;
		temp = *it;
		USES_CONVERSION;
		user= T2A(temp.id.GetBuffer(0));
		temp.id.ReleaseBuffer();
		t1 = user;//好友账号
		url = url + t1;
		t1 = "@";
		url = url + t1;
		t1 = SIP_DOMAIN2;
		url = url + t1;
		const char *ul = url.data();
		char * strc = new char[strlen(url.c_str()) + 1];
		
		strcpy_s(strc, strlen(url.c_str()) + 1, url.c_str());
		bfg.uri = pj_str(strc);
		bfg.subscribe = PJ_TRUE;
		pjsua_buddy_add(&bfg, &id_a);
	}
	
	//add your code
	//
	
}
void MySip::delete_friends(CString *id)
{
	
	//
	//user
	//
	pjsua_buddy_id id_d;
	id_d = _ttoi(*id);
	pjsua_buddy_del(id_d);
}
bool MySip::state_friends(CString fr_id)
{
	///*pjsua_buddy_info  *inf=NULL;

	//pjsua_buddy_get_info(_ttoi(fr_id), inf);
	//if (inf->status == PJSUA_BUDDY_STATUS_ONLINE)
	//{
	//	return TRUE;

	//}
	//else
	//	return FALSE;*/
	//string uri;
	//string user(CW2A(fr_id.GetString()));
	//uri = "sip:";
	//uri = uri + user;
	//uri = uri + "@";
	//uri = uri + SIP_DOMAIN2;
	//BuddyConfig cfg;
	//cfg.uri =uri;
	////acc->removeBuddy(buddy);//移除旧的对象
	//try {
	//	buddy->create(*acc, cfg);
	//	buddy->subscribePresence(true);//添加好友对象
	//}
	//catch (Error& err) {
	//	return FALSE;//出错
	//}
	//buddy->onBuddyState();
	//if (buddy->state_budy == PJSUA_BUDDY_STATUS_ONLINE)
	//	return TRUE;//在线
	//else
		return FALSE;

}


MySip::~MySip()
{
}


void MySip::on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id,
	pjsip_rx_data *rdata)
{
	pThis1->rec_flag = 1;
	pjsua_call_info ci;

	PJ_UNUSED_ARG(acc_id);
	PJ_UNUSED_ARG(rdata);

	pjsua_call_get_info(call_id, &ci);

	PJ_LOG(3, (THIS_FILE, "Incoming call from %.*s!!",
		(int)ci.remote_info.slen,
		ci.remote_info.ptr));

	pjsua_call_setting call_setting;
	pjsua_call_setting_default(&call_setting);
	call_setting.vid_cnt = 1;
	call_setting.aud_cnt = 1;

	CWnd* pWnd = CWnd::FindWindow(NULL, _T("Main"));
	if (pWnd == NULL)
		//AfxMessageBox("Error!");
	pWnd->SendMessage(WM_MyMessage, 0, 0);

	//pThis1->main_cwd->SendMessage(WM_MyMessage, 0, 0);
	
	
	//while (w_recpt->flag_sure == 1)
	//{
	//	;
	//	//等待确认
	//}
	//w_recpt->flag_sure = 1;
	//pThis1->accept = w_recpt->accept;
	//if (pThis1->accept == 1)//接听电话
	//{
		
		/* Automatically answer incoming calls with 200/OK */
		pjsua_call_answer2(call_id, &call_setting, 200, NULL, NULL);
		//获取传入视频。绑定到指定窗口
		int vid_idx;
		pjsua_vid_win_id wid = -1;
		vid_idx = pjsua_call_get_vid_stream_idx(call_id);
		if (vid_idx >= 0)
		{
			pjsua_call_info ci;
			pjsua_call_get_info(call_id, &ci);
			wid = ci.media[vid_idx].stream.vid.win_in;
		}
		pjsua_vid_win_info inf;
		if (wid != -1)//显示对方视频
		{
			pjsua_vid_win_get_info(wid, &inf);
			pjmedia_vid_dev_hwnd pre_hwnd = inf.hwnd;
			HWND w = (HWND)pre_hwnd.info.win.hwnd;
			pThis1->friend_win.Attach(w);//获得对方视频窗口句柄
		}
		pThis1->wait_flag = 2;//falg 显示对方视频
	//}
	//else
	//{
	//	pjsua_call_answer2(call_id, &call_setting, 603, NULL, NULL);
	//	pThis1->wait_flag =3;//拒绝标志
	//}

	//w_recpt->accept = 0;
	//w_recpt->refuse = 0;
}

/* Callback called by the library when call's state has changed */
void MySip::on_call_state(pjsua_call_id call_id, pjsip_event *e)
{
	pjsua_call_info ci;

	PJ_UNUSED_ARG(e);

	pjsua_call_get_info(call_id, &ci);
	PJ_LOG(3, (THIS_FILE, "Call %d state=%.*s", call_id,
		(int)ci.state_text.slen,
		ci.state_text.ptr));
}

/* Callback called by the library when call's media state has changed */
void MySip::on_call_media_state(pjsua_call_id call_id)
{
	pjsua_call_info ci;

	pjsua_call_get_info(call_id, &ci);

	if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE) {
		// When media is active, connect call to sound device.
		pjsua_conf_connect(ci.conf_slot, 0);
		pjsua_conf_connect(0, ci.conf_slot);
	}
}

/* Display error and exit application */
void MySip::error_exit(const char *title, pj_status_t status)
{
	string s = title;
	CString cstr(s.c_str());
	AfxMessageBox(cstr);
	pjsua_perror(THIS_FILE, title, status);
	pjsua_destroy();
	exit(1);
}
void MySip::make_call(pj_str_t uri)
{
	pjsua_call_setting call_setting;
	pjsua_call_setting_default(&call_setting);
	call_setting.vid_cnt = 1;
	call_setting.aud_cnt = 1;
	pj_status_t status = pjsua_call_make_call(acc_id, &uri, &call_setting, NULL, NULL, NULL);
}


