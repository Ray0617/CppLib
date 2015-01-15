#pragma once
#include <string>
#include <stdarg.h>

namespace rl
{

std::wstring StrToWcs(const std::string& str);
std::string WcsToStr(const std::wstring& wcs);

std::string ToStr(const std::string& str);
std::string ToStr(const std::wstring& wcs);
std::wstring ToWcs(const std::string& str);
std::wstring ToWcs(const std::wstring& wcs);

std::string Sprintf(const char* str, ...);
std::wstring Sprintf(const wchar_t* wcs, ...);

template<typename T>
T ToTempStr(const std::string& str);

#ifdef _UNICODE
#define ToTStr ToWcs
#else
#define ToTStr ToStr
#endif

};	// namespace rl