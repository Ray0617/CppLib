#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <tchar.h>
#include "RObject.h"
#include <assert.h>
using namespace rl;

bool TestRObject();
bool TestRDatabase();
bool TestRString();

int main()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG)|_CRTDBG_LEAK_CHECK_DF);
	assert( TestRObject() );
	assert( TestRDatabase() );
	assert( TestRString() );
	return 0;
}