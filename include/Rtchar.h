#pragma once
#include <tchar.h>
#ifdef _UNICODE
#define tcout wcout
#define tstring wstring
#else
#define tcout cout
#define tstring string
#endif