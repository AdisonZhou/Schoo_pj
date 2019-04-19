
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#include"resource.h"
#include"SkinH.h"
#pragma comment(lib,"SkinH.lib")
#define _CRT_SECURE_NO_WARNINGS
//#include<opencv2/opencv.hpp>
//#include"iostream"
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>
#include <afxcontrolbars.h>

//#include"comdef.h"
//#include"gdiplus.h"
//using namespace Gdiplus;
//#pragma comment(lib,"gdiplus.lib")


static UINT WM_MyMessage = RegisterWindowMessage(_T("myMessage"));
#define REFUSE_CALL WM_USER+8
#define END_CALL WM_USER+16
#define BUDDY_INIT WM_USER+3
#define BUDDY_ADD WM_USER+2
#define BUDDY_DEL WM_USER+1
#define FRIEND_MSG WM_USER+4
#define VIDEO_W WM_USER + 100
#define PREVIEW_W WM_USER +101
#define ENCODE_VIDEO WM_USER + 102
#define ENCODE_VOICE WM_USER + 103
#define OPENCV_WIN WM_USER+51

#define W_CHAT_WIN WM_USER+91
#define W_VIDEO_WIN WM_USER+92

#define H264 1001
#define H263 1002
#define SPEEX_16000 2001
#define GSM_8000 2002
#define G722_16000 2003

extern "C"
{
#include "libavcodec/avcodec.h"  
#include "libavformat/avformat.h"  
#include "libswscale/swscale.h"  
#include "libavutil/imgutils.h"  
#include "SDL.h"  
};


/*#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif*/


