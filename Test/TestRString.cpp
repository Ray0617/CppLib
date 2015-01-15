#include <string>
#include <assert.h>
#include "RString.h"
#include "Rtchar.h"
using namespace rl;
bool TestRString()
{
	std::string str = "test";
	std::wstring wcs = L"test";
	std::tstring tstr = _T("test");
	assert(StrToWcs(str) == wcs);
	assert(WcsToStr(wcs) == str);
	assert(ToStr(str) == str);
	assert(ToStr(wcs) == str);
	assert(ToStr(tstr) == str);
	assert(ToWcs(str) == wcs);
	assert(ToWcs(wcs) == wcs);
	assert(ToWcs(tstr) == wcs);
	assert(ToTStr(str) == _T("test"));
	assert(ToTStr(wcs) == _T("test"));
	assert(ToTStr(tstr) == _T("test"));
	assert(Sprintf("%s%d", str.c_str(), 1) == "test1");
	assert(Sprintf(L"%s%d", wcs.c_str(), 2) == L"test2");
	assert(trim(" \t123 \t456\n \t ") == "123 \t456");
	return true;
}