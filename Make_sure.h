#pragma once


// Make_sure 对话框

class Make_sure : public CDialogEx
{
	DECLARE_DYNAMIC(Make_sure)
public:
	int accept;
	int refuse;
	int flag_sure;
	CString call_id;
public:
	Make_sure(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Make_sure();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void init()
	{
		CWnd *pa=GetDlgItem(IDC_STATIC1);
		pa->SetWindowTextW(call_id);
	}
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
