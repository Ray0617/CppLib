#pragma once
#include <stdarg.h>
#include <stdio.h>
// copy from http://stackoverflow.com/questions/2915672/snprintf-and-visual-studio-2010

#ifdef _MSC_VER

#define vsnprintf c99_vsnprintf
#define vsnwprintf c99_vsnwprintf
#define snprintf c99_snprintf
#define snwprintf c99_snwprintf

inline int c99_vsnprintf(char* str, size_t size, const char* format, va_list ap)
{
    int count = -1;

    if (size != 0)
        count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
    if (count == -1)
        count = _vscprintf(format, ap);

    return count;
}

inline int c99_snprintf(char* str, size_t size, const char* format, ...)
{
    int count;
    va_list ap;

    va_start(ap, format);
    count = c99_vsnprintf(str, size, format, ap);
    va_end(ap);

    return count;
}

inline int c99_vsnwprintf(wchar_t* str, size_t size, const wchar_t* format, va_list ap)
{
    int count = -1;

    if (size != 0)
        count = _vsnwprintf_s(str, size, _TRUNCATE, format, ap);
    if (count == -1)
        count = _vscwprintf(format, ap);

    return count;
}

inline int c99_snwprintf(wchar_t* str, size_t size, const wchar_t* format, ...)
{
    int count;
    va_list ap;

    va_start(ap, format);
    count = c99_vsnwprintf(str, size, format, ap);
    va_end(ap);

    return count;
}

#endif // _MSC_VER