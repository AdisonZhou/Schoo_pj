#pragma once
#include"stdafx.h"

// MEDIA_SETTING 对话框

class MEDIA_SETTING : public CDialogEx
{
	DECLARE_DYNAMIC(MEDIA_SETTING)

public:
	MEDIA_SETTING(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MEDIA_SETTING();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
