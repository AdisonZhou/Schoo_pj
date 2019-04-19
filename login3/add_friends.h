#pragma once
#include"Friend_inf.h"
#include"queue"
#include"list"

// add_friends 对话框
using namespace std;
class add_friends : public CDialogEx
{
	DECLARE_DYNAMIC(add_friends)

public:
	add_friends(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~add_friends();
public:
	CString friends_id;
	CString friends_rename;
	void close_c();
	int flag_close = 0;
	//queue<Friend_inf> friend_queue;
	list<Friend_inf> lis;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
