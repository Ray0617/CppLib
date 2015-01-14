#pragma once
#include <string>

namespace rl
{

std::wstring StrToWcs(const std::string& str);
std::string WcsToStr(const std::wstring& wcs);

std::string ToStr(const std::string& str);
std::string ToStr(const std::wstring& wcs);
std::wstring ToWcs(const std::string& str);
std::wstring ToWcs(const std::wstring& wcs);

template<typename T>
T ToTempStr(const std::string& str);

//template std::string ToTempStr<std::string>(const std::string& str);
//template std::wstring ToTempStr<std::wstring>(const std::string& str);

#ifdef _UNICODE
#define ToTStr ToWcs
#else
#define ToTStr ToStr
#endif

};	// namespace rl