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

//template <typename T>
//T SprintfT(const );
//template<typename T>
//std::basic_string<T> SprintfT(const T* fmt);
//typedef 

std::string Sprintf(const char* str, ...);
std::wstring Sprintf(const wchar_t* wcs, ...);

// ref http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
std::string trim(const std::string& str);
std::wstring trim(const std::wstring& wcs);

template<typename T>
T ToTempStr(const std::string& str);

#ifdef _UNICODE
#define ToTStr ToWcs
#else
#define ToTStr ToStr
#endif

};	// namespace rl