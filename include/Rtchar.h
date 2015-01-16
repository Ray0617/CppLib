#pragma once
#include <tchar.h>
#ifdef _UNICODE
#define tcout wcout
#define tcin wcin
#define tstring wstring
#define tsscanf swscanf
#else
#define tcout cout
#define tcin wcin
#define tstring string
#define tsscanf sscanf
#endif