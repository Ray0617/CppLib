#pragma once
#include <tchar.h>
#ifdef _UNICODE
#define tcout wcout
#define tcin wcin
#define tstring wstring
#else
#define tcout cout
#define tcin wcin
#define tstring string
#endif