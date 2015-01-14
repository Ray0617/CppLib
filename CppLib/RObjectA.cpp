#ifdef _UNICODE
#define _UNICODE_SHOULD_BE_DEFINE
#endif
#undef _UNICODE

#include "RObjectImp.h"

namespace rl
{

template class RObjectT<std::string>;

};	// namespace rl

#ifdef _UNICODE_SHOULD_BE_DEFINE
#define _UNICODE
#endif