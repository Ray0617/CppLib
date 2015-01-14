#define _CRT_SECURE_NO_WARNINGS		// for wctomb

#include "RString.h"
#include <memory>
#ifdef _WIN32
#include <Windows.h>
// just use WideCharToMultiByte and MultiByteToWideChar
#else
#include <stdlib.h>
#endif
namespace rl
{

#ifdef _WIN32
std::wstring StrToWcs(const std::string& str)
{	auto len =  str.length();
	auto wlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), len, NULL, 0);
	wchar_t* wcs = new wchar_t [wlen + 1];
	wcs[wlen] = 0;
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), len, wcs, wlen + 1);
	std::wstring ret = wcs;
	delete [] wcs;
	return ret;
}
std::string WcsToStr(const std::wstring& wcs)
{
	auto wlen =  wcs.length();
	auto len = WideCharToMultiByte(CP_ACP, 0, wcs.c_str(), wlen, NULL, 0, NULL, NULL);
	char* str = new char [len + 1];
	str[len] = 0;
	WideCharToMultiByte(CP_ACP, 0, wcs.c_str(), wlen, str, len + 1, NULL, NULL);
	std::string ret = str;
	delete [] str;
	return ret;
}
#else
std::wstring StrToWcs(const std::string& str)
{
	std::wstring wcs;
	std::unique_ptr<wchar_t[]> buf(new wchar_t[16]);
	for (size_t i = 0; i < str.size(); i++)
	{
		int wlen = mbtowc(buf.get(), &str[i], str.size() - i);
		buf.get()[wlen] = L'\0';
		wcs += buf.get();
	}
	return wcs;
}
std::string WcsToStr(const std::wstring& wcs)
{
	std::string str;
	std::unique_ptr<char[]> buf(new char[16]);
	for (auto wch : wcs)
	{
		int len = wctomb(buf.get(), wch);
		buf.get()[len] = '\0';
		str += buf.get();
	}
	return str;
}
#endif

std::string ToStr(const std::string& str)
{
	return str;
}

std::string ToStr(const std::wstring& wcs)
{
	return WcsToStr(wcs);
}

std::wstring ToWcs(const std::string& str)
{
	return StrToWcs(str);
}

std::wstring ToWcs(const std::wstring& wcs)
{
	return wcs;
}

template <> 
std::string ToTempStr<std::string>(const std::string& str)
{
	return str;
}

template <> 
std::wstring ToTempStr<std::wstring>(const std::string& str)
{
	return ToWcs(str);
}

};	// namespace rl