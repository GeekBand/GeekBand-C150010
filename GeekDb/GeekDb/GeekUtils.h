//*************************************************
// Module:  GeekUtils.h
// Notices: Copyright (c) 2015 Zhang Wenjie
//*************************************************

#pragma once

#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <Shlwapi.h>	// for PathFileExists invocation
#include <time.h>
#include "GeekDefs.h"

//
// Must link the Shlwapi.lib module for the Windows function:
// PathFileExists.
//
#pragma comment(lib, "Shlwapi.lib")

namespace geek {


	inline std::string ws2s(const std::wstring& ws) {
		std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
		setlocale(LC_ALL, "chs");
		const wchar_t* _Source = ws.c_str();
		size_t _Dsize = 2 * ws.size() + 1;
		char *_Dest = new char[_Dsize];
		memset(_Dest, 0, _Dsize);

		size_t i;
		wcstombs_s(&i, _Dest, _Dsize, _Source, _Dsize);
		std::string result = _Dest;
		delete[]_Dest;
		setlocale(LC_ALL, curLocale.c_str());
		return result;
	}
	inline std::wstring s2ws(const std::string& s) {
		setlocale(LC_ALL, "chs");
		const char* _Source = s.c_str();
		size_t _Dsize = s.size() + 1;
		wchar_t *_Dest = new wchar_t[_Dsize];
		wmemset(_Dest, 0, _Dsize);

		size_t i;
		mbstowcs_s(&i, _Dest, _Dsize, _Source, _Dsize);
		std::wstring result = _Dest;
		delete[]_Dest;
		setlocale(LC_ALL, "C");
		return result;
	}

	//Date Function
	inline std::wstring GetCurrentDate() {
		char szBuf[20] = { 0 };
		time_t timer = time(NULL);
		tm t;
		localtime_s(&t, &timer);

		strftime(szBuf, 20U, "%Y-%m-%d %H:%M:%S", &t);
		return s2ws(std::string(szBuf));
	}

	//
	// Indicates whether a string is empty.
	//
	inline const bool IsNullOrEmpty(const std::wstring& wsz) {
		return (wsz.empty() ? true : false);
	}

	inline const bool IsFileExists(const std::wstring& wszFileName) {
		return (::PathFileExists(wszFileName.c_str()) == TRUE) ? true : false;
	}

	// 
	// Functor to print all the key/value entries in a database.
	// Must overload operator().
	//
	struct PrintKeyValue : std::unary_function<GeekKeyValue, void> {
	public:
		void operator()(const GeekKeyValue& entry) {
			std::wcout << L"[Key]:  -> " << entry.first << std::endl
				<< L"[Value]:-> " << entry.second << std::endl
				<< std::endl;
		}
	};

	//
	// The Macro to exit a function once a "Geek Error" occurs.
	//
#if !defined(ON_GEEKFAILED_RETURN)
#define ON_GEEKFAILED_RETURN(gr) {	\
			if (GEEKFAILED(gr)) {		\
				goto e_Exit;			\
			}							\
		}
#endif

//
// The Macro to exit a function once a "Windows Error" occurs.
//
#if !defined(ON_FAILED_RETURN)
#define ON_FAILED_RETURN(hr, gr, err) {	\
			if (FAILED(hr)) {				\
				gr = err;					\
				goto e_Exit;				\
			}								\
		}
#endif

//
// The Macro to release an Ole object.
//
#if !defined(RELEASE_OLE_OBJECT)
#define RELEASE_OLE_OBJECT(obj) {	\
		if (obj != NULL) {				\
			obj->Release();				\
			obj = NULL;					\
		}								\
	}
#endif

//
// The Macro to release an object created by the [new] operator.
//
#if !defined(DISPOSE_OBJECT)
#define DISPOSE_OBJECT(obj) {	\
			if (obj != NULL) {		\
				delete obj;			\
				obj = NULL;			\
			}						\
		}
#endif

//
// The Macro to release an array.
//
#if !defined(DISPOSE_ARRAY)
#define DISPOSE_ARRAY(obj) {	\
			if (obj != NULL) {		\
				delete[] obj;		\
				obj = NULL;			\
			}						\
		}
#endif


}