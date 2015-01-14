#pragma once
#include <tchar.h>
#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif