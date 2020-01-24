// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F4394DF4_C8A7_4A08_A1B9_381CD342D816__INCLUDED_)
#define AFX_STDAFX_H__F4394DF4_C8A7_4A08_A1B9_381CD342D816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <cerrno>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#include <string>
#include <vector>
#include <map>
#include <hash_map>
#include <hash_set>
#include <set>
#include <deque>
#include <list>
#ifdef _DEBUG
#define DEBUG
#endif

//#define  PARAM_DEBUG

#endif // !defined(AFX_STDAFX_H__F4394DF4_C8A7_4A08_A1B9_381CD342D816__INCLUDED_)

//#pragma once


#include <iostream>
#include <tchar.h>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <set>
#include <list>
//#include <user.h>
//#include <web_server.h>
#include <windows.h>
#include <winsock.h>
// TODO: reference additional headers your program requires here
#pragma warning( disable:4800)
#pragma warning( disable:4018)