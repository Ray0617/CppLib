#include "RMenu.h"
#include <assert.h>
#include <tchar.h>
#include <memory>
using namespace std;
using namespace rl;

static int step = 0;
// input: aAxxAAxxOxxxxKxxxxaAOK
//        11  11  2    3.break...
static int Item1(void* arg)
{
	if (step == 0)
	{
		assert((int)arg == 0);
		step = 1;
	}
	else if (step == 1 || step == 2 || step == 3)
	{
		assert((int)arg == 1);
		step++;
	}
	else
	{
		assert(0);
	}
	return RMenu::CONTINUE;
}

static int Item2(void* arg)
{
	assert(step == 4);
	step++;
	return RMenu::CONTINUE;
}

static int Item3(void* arg)
{
	assert(step == 5);
	return RMenu::BREAK;
}

bool TestRMenu()
{
	FILE* f = freopen("Test\\TestRMenu1.txt", "r", stdin);
	RMenu menu;
	menu.Add(_T("Item1"), Item1, (void*)0, 'a');
	menu.Add(_T("Item1"), Item1, (void*)1, 'A', false);	
		// note: show = false so it could not be selected from direction arrow and enter in the main menu
	menu.Add(_T("Item2"), Item2, (void*)2, 'O');
	menu.Add(_T("Item3"), Item3, (void*)3, 'K');
	menu.Run();
	return true;
}