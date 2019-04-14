#pragma once
#include"stdio.h"
#include"string"
// server_set 对话框
using namespace std;
class server_set : public CDialogEx
{
	DECLARE_DYNAMIC(server_set)

public:
	server_set(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~server_set();
public:
	int port;
	string ip_address;
	CString test;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	void close();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
};
