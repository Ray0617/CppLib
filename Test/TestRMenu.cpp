#define _CRT_SECURE_NO_WARNINGS		// freopen
#include "RMenu.h"
#include <assert.h>
#include <tchar.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
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
	// Note: RMenu is for UI with keyboard, so it's non-sense to test here
	//  so here I only test the memory leak.
	// (however, it's possible to test UI if the library uses cin or getchar() instead of getch() and getche())
	ifstream input("Test\\TestRMenu1.txt");
	streambuf* issue_buf = input.rdbuf();
	streambuf* cin_buf = cin.rdbuf(issue_buf);
	RMenu menu;
	menu.AddHotkey('a', Item1, (void*)0);
	menu.AddHotkey('A', Item1, (void*)1);
	menu.AddHotkey('O', Item2, (void*)2);
	menu.AddHotkey('K', Item3, (void*)3);
	// menu.Run();
	return true;
}