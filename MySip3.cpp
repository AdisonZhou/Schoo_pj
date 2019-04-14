#include "stdafx.h"
#include "MySip3.h"
#include <cstring>
#include"thread"
#include"mutex"
MySip3 *MySip3::pThis1 = NULL;
 using namespace std;
 mutex mut;
MySip3::MySip3()
{
	SIP_DOMAIN2 = "192.168.43.125";
	SIP_USER2 = "1001";
	SIP_PASSWD2 = "1001";
	SIP_PORT = 5060;
	login_flag = TRUE;
	pThis1 = this;
	accept = 0;
	wait_flag =0;
	rec_flag = 0;
}

void MySip3::init()
{
	
}
void MySip3::destroy()
{
	pjsua_destroy();
}
void MySip3::login()
{

	pj_status_t status = pjsua_create();
	if (status != PJ_SUCCESS) error_exit("Error in pjsua_create()", status);
	//
	/* Init pjsua */
	pjsua_config_default(&cfg);
	cfg.cb.on_incoming_call = &on_incoming_call;
	cfg.cb.on_call_media_state = &on_call_media_state;
	cfg.cb.on_call_state = &on_call_state;
	cfg.cb.on_buddy_state = &on_buddy_state;
	cfg.cb.on_incoming_subscribe = &on_incoming_subscribe;
	cfg.cb.on_pager = &on_pager;
	cfg.cb.on_reg_state2 = &on_reg_state2;
	
	
	//
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
	acc_cfg.vid_in_auto_show = PJ_FALSE;
	acc_cfg.vid_out_auto_transmit = PJ_TRUE;
	acc_cfg.vid_cap_dev = PJMEDIA_VID_DEFAULT_CAPTURE_DEV;
	string usr_id = "sip:";
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

	pjsua_vid_codec_set_priority(&codec_id, 255);
	pjsua_vid_codec_set_param(&codec_id, &param);

	const pj_str_t co_id3{ "G722/16000",10 };

	pjmedia_codec_param *prm = NULL;
	pjsua_codec_get_param(&co_id3, prm);
	pjsua_codec_set_priority(&co_id3, 255);
	pjsua_codec_set_param(&co_id3, prm);

}
// unsed 
void MySip3::add_friends(list<Friend_inf> *lis)
{
	//pjsua_buddy_config bfg;
	////
	//Friend_inf temp;
	////遍历好友
	//pjsua_buddy_id id[10];
	//unsigned int countt = 10;
	//
	//CString str;
	//
	//list<Friend_inf>::iterator it; //声明一个迭代器
	//for (it = lis->begin(); it != lis->end(); it++)
	//{
	//	
	//    temp = *it;
	//	pjsua_buddy_id id_a, id_a2;
	//	id_a = temp.buddy_id;
	//	id_a2 = id_a;

	//	pjsua_enum_buddies(id, &countt);
	//	str.Format(_T("%d"), countt);
	//	AfxMessageBox(str);

	//	//pjsua_buddy_del(id_a);

	//	pjsua_enum_buddies(id, &countt);
	//	str.Format(_T("%d"), countt);
	//	AfxMessageBox(str);

	//	std::string budy_id(CW2A(temp.id.GetString()));
	//	string budy_uri = "sip:" + budy_id + "@" + SIP_DOMAIN2;
	//	const char *b_u = budy_uri.data();
	//	char* temp2 = const_cast<char*>(b_u);
	//	bfg.uri = pj_str(temp2);
	//	bfg.subscribe = PJ_TRUE;
	//	pjsua_buddy_add(&bfg, &id_a2);

	//	pjsua_enum_buddies(id, &countt);
	//	str.Format(_T("%d"), countt);
	//	AfxMessageBox(str);
	//}
	//
}
void MySip3::delete_friends(CString *id)
{

	//
	//user
	//
	pjsua_buddy_id id_d;
	id_d = _ttoi(*id);
	pjsua_buddy_del(id_d);
}
// unsed 
bool MySip3::state_friends(CString fr_id)
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


MySip3::~MySip3()
{
}


void MySip3::on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id,
	pjsip_rx_data *rdata)
{
	pThis1->wait_flag = 1;
	
	pjsua_call_info ci;

	PJ_UNUSED_ARG(acc_id);
	PJ_UNUSED_ARG(rdata);

	pjsua_call_get_info(call_id, &ci);
	pThis1->call_id = ci.remote_info.ptr;
	PJ_LOG(3, (THIS_FILE, "Incoming call from %.*s!!",
		(int)ci.remote_info.slen,
		ci.remote_info.ptr));
	pThis1->CALL_ID = call_id;
	//AfxMessageBox(_T("sssss"));

}

/* Callback called by the library when call's state has changed */
void MySip3::on_call_state(pjsua_call_id call_id, pjsip_event *e)
{
	pjsua_call_info ci;

	PJ_UNUSED_ARG(e);

	pjsua_call_get_info(call_id, &ci);
	PJ_LOG(3, (THIS_FILE, "Call %d state=%.*s", call_id,
		(int)ci.state_text.slen,
		ci.state_text.ptr));
	string s = ci.state_text.ptr;
	pThis1->connect_state = s.c_str();
	
}

/* Callback called by the library when call's media state has changed */
void MySip3::on_call_media_state(pjsua_call_id call_id)
{
	pjsua_call_info ci;

	pjsua_call_get_info(call_id, &ci);
	
	if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE) {
		// When media is active, connect call to sound device.
		pjsua_conf_connect(ci.conf_slot, 0);
		pjsua_conf_connect(0, ci.conf_slot);
	}
	int vid_idx = pjsua_call_get_vid_stream_idx(call_id);
	if (vid_idx >= 0)
	{
		pjsua_call_info ci;
		pjsua_call_get_info(call_id, &ci);
		pThis1->local_receive= ci.media[vid_idx].stream.vid.win_in;
		pThis1->local_receive_flag = 1;	
		pj_thread_sleep(100);
		pThis1->CALL_ID = call_id;
	}
	


}

/*call back by the library when buddy state changed*/
void MySip3::on_buddy_state(pjsua_buddy_id buddy_id)
{
	pjsua_buddy_info info;
	pjsua_buddy_get_info(buddy_id, &info);
	string statu = info.status_text.ptr;//当前状态
	string s = info.uri.ptr;
	
	/*CString str;
	str = statu.c_str();
	AfxMessageBox(str);
	str.Format(_T("%d"), buddy_id);

	str = s.c_str();
	AfxMessageBox(str);*/
	Friend_inf temp;
	list<Friend_inf>::iterator it; //声明一个迭代器
	for (it = pThis1->lis->begin(); it != pThis1->lis->end(); it++)
	{
		
		temp = *it;
		if (temp.buddy_id == buddy_id)
		{
			/*CString s;
			s = statu.c_str();
			AfxMessageBox(s);*/
			temp.status = statu.c_str();
			pThis1->lis->erase(it);
			pThis1->lis->insert(it, temp);
		}

	}
	
	
}
/* Display error and exit application */
void MySip3::error_exit(const char *title, pj_status_t status)
{
	string s = title;
	CString cstr(s.c_str());
	AfxMessageBox(cstr);
	pjsua_perror(THIS_FILE, title, status);
	pjsua_destroy();
	exit(1);
}
//incoming subscribe 
void MySip3::on_incoming_subscribe(pjsua_acc_id acc_id,
	pjsua_srv_pres *srv_pres,
	pjsua_buddy_id buddy_id,
	const pj_str_t *from,
	pjsip_rx_data *rdata,
	pjsip_status_code *code,
	pj_str_t *reason,
	pjsua_msg_data *msg_data_)
{
	/* Just accept the request (the default behavior) */
	PJ_UNUSED_ARG(acc_id);
	PJ_UNUSED_ARG(srv_pres);
	PJ_UNUSED_ARG(buddy_id);
	PJ_UNUSED_ARG(from);
	PJ_UNUSED_ARG(rdata);
	PJ_UNUSED_ARG(code);
	PJ_UNUSED_ARG(reason);
	PJ_UNUSED_ARG(msg_data_);
}

/*
Incoming IM message(i.e.MESSAGE request)!
*/
void MySip3::on_pager(pjsua_call_id call_id, const pj_str_t *from,
	const pj_str_t *to, const pj_str_t *contact,
	const pj_str_t *mime_type, const pj_str_t *text)
{
	/* Note: call index may be -1 */
	PJ_UNUSED_ARG(call_id);
	PJ_UNUSED_ARG(to);
	PJ_UNUSED_ARG(contact);
	PJ_UNUSED_ARG(mime_type);

	//判断消息类型
	char *m_tp = mime_type->ptr;
	string s1 = m_tp;
	CString s2;
	s2=s1.c_str();
	string mg= text->ptr;
	CString s_mg;
	s_mg = mg.c_str();
	if (s2 =="text/plain")
	{
		if (s_mg == "0X603BYEBYE")
		{
			pThis1->end_call_flag = 1;
		}
		//AfxMessageBox(s2);
		/*else if (s_mg == "CONNECT_CALL")
		{
			pThis1->wait_flag = 1;
			pjsua_call_info ci;
			pjsua_call_get_info(call_id, &ci);
			pThis1->call_id = ci.remote_info.ptr;
			PJ_LOG(3, (THIS_FILE, "Incoming call from %.*s!!",
				(int)ci.remote_info.slen,
				ci.remote_info.ptr));
			pThis1->CALL_ID = call_id;
		}*/
		else 
		{
			pThis1->message_flag = 1;//收到文本消息
			pThis1->rec_msg = mg;
		}
	}
	else if (m_tp=="sss")
	{
		//收到图片
		pThis1->message_flag = 2;
	}

	PJ_LOG(3, (THIS_FILE, "MESSAGE from %.*s: %.*s (%.*s)",
		(int)from->slen, from->ptr,
		(int)text->slen, text->ptr,
		(int)mime_type->slen, mime_type->ptr));
	/*CString sss;
	string s = text->ptr;
	sss = s.c_str();
	AfxMessageBox(sss);*/
}
void MySip3::on_reg_state2(pjsua_acc_id acc_id, pjsua_reg_info *info) {
	if (info->renew != 0) {
		if (info->cbparam->code == 200) {
			//"登录成功");
			pThis1->login_state = TRUE;
		}
		else {
			//登录失败code:%d ",info->cbparam->code);
		}
	}
	else {
		if (info->cbparam->code == 200)
		{
			//"SIP退出登录成功");
		}
	}
}

void MySip3::make_call(pj_str_t uri)
{
	pjsua_call_setting call_setting;
	pjsua_call_setting_default(&call_setting);
	call_setting.vid_cnt = 1;
	call_setting.aud_cnt = 1;
	pj_status_t status = pjsua_call_make_call(acc_id, &uri, &call_setting, NULL, NULL, &pThis1->CALL_ID);
	
	if (status != PJ_SUCCESS)
	{
		AfxMessageBox(_T("make_call_error"));
		//pjsua_acc_id send_from =pThis1->acc_id;
		//pj_str_t to = uri;
		//CString msg = _T("CONNECT_CALL");
		//string s(CW2A(msg.GetString()));
		//const char *tt;
		//tt = s.c_str();
		//char *mg;
		//mg = const_cast<char*>(tt);
		//pj_str_t im_s = pj_str(mg);
		//pjsua_msg_data msgd;
		//pjsua_msg_data_init(&msgd);
		//pjsua_im_send(send_from, &to, NULL, &im_s, &msgd, NULL);
	}
}

void MySip3::end_call(void)
{
	pjsua_call_id id[10];
	unsigned count = 10;
	pjsua_enum_calls(id, &count);
	if (count != 0)
	{

	   pjsua_call_hangup_all();
	}
	
}

void MySip3::ans_call()
{
	//call 设置
	pjsua_call_setting call_setting;
	pjsua_call_setting_default(&call_setting);
	call_setting.vid_cnt = 1;
	call_setting.aud_cnt = 1;
	pjsua_call_answer2(CALL_ID, &call_setting, 200, NULL, NULL);
}
void MySip3::refuse_call()
{
	pjsua_call_setting call_setting;
	pjsua_call_setting_default(&call_setting);
	call_setting.vid_cnt = 1;
	call_setting.aud_cnt = 1;
	//refuse call
	pjsua_call_answer2(CALL_ID, &call_setting, 603, NULL, NULL);
}
