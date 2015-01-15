#ifdef _UNICODE
#define _UNICODE_SHOULD_BE_DEFINE
#endif
#undef _UNICODE

#include "RMenuImp.h"

namespace rl
{

template class RMenuT<std::string>;

};	// namespace rl

#ifdef _UNICODE_SHOULD_BE_DEFINE
#define _UNICODE
#endif