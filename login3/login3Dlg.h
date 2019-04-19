
// login3Dlg.h: 头文件
//

#pragma once
#include"BtnST.h"
#include"CEditTrans.h"
#include"StaticTrans.h"
// Clogin3Dlg 对话框
class Clogin3Dlg : public CDialogEx
{
// 构造
public:
	Clogin3Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButtonST login_bt;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	CEditTrans edit1;
	CEditTrans edit2;
	CButtonST account;
	CButtonST password;
	CButtonST enter;
	CButtonST reme;
	CButtonST noa;
	CButtonST reg;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();
	CButtonST login_2;
	afx_msg void login_no_account();
};
