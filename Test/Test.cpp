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
bool TestRMenu();

int main()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG)|_CRTDBG_LEAK_CHECK_DF);
	assert( TestRMenu() );
	assert( TestRString() );
	assert( TestRObject() );
	assert( TestRDatabase() );
	return 0;
}