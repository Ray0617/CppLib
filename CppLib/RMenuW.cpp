#ifndef _UNICODE
#define _UNICODE_SHOULD_BE_UNDEF
#endif

#define _UNICODE

#include "RMenuImp.h"
namespace rl
{

template class RMenuT<std::wstring>;

};	// namespace rl

#ifdef _UNICODE_SHOULD_BE_UNDEF
#undef _UNICODE
#endif