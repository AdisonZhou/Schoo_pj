#pragma once


// VID_WIN 对话框

class VID_WIN : public CDialogEx
{
	DECLARE_DYNAMIC(VID_WIN)

public:
	VID_WIN(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~VID_WIN();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VID_WIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWnd *local_win;
	CWnd *friend_win;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
