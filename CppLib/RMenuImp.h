#include "RMenu.h"
#include "RString.h"
#include <iostream>
#include <iomanip>
#include "Rtchar.h"
#include <conio.h>
using namespace std;

namespace rl
{

static const int MAX_CHARPERLINE = 80;
static const int MAX_COLUMNS_PER_SCREEN = 50;

template<typename T>
RMenuT<T>::RMenuItem::RMenuItem(const T& _name, MenuItemFuncPtr _func, void* _arg, bool _show)
	: name(_name)
	, func(_func)
	, arg(_arg)
	, show(_show)
{}

template<typename T>
int RMenuT<T>::RMenuItem::Select()
{
	return func(arg);
}

// constructor
template<typename T>
RMenuT<T>::RMenuT()
	: m_item_width(DEFAULT_ITEM_WIDTH)
	, m_select(0)
{
}

// destructor
template<typename T>
RMenuT<T>::~RMenuT()
{
}

template<typename T>
void RMenuT<T>::SetItemWidth(unsigned width)
{
	m_item_width = width;
}

template<typename T>
void RMenuT<T>::SetSelect(unsigned select)
{
	m_select = select;
}

template<typename T>
void RMenuT<T>::Add(const T& name, MenuItemFuncPtr func, void* arg, int key, bool show)
{
	shared_ptr<RMenuItem> item = make_shared<RMenuItem>(name, func, arg, show);
	if (show)
		m_items.push_back(item);
	m_items_with_key[key] = item;
}

template<typename T>
void RMenuT<T>::Run()
{
	do
	{
		Show();
		int cmd = getchar();
		if (cmd == 224)
		{
			cmd = getchar();	// Up, Down, Left, Right, Home, End, PgDn, PgUp, ...etc
			switch (cmd)
			{
			case 71:	// Home
				m_select = 0;
				break;
			case 72:	// Up
				m_select -= MAX_CHARPERLINE / m_item_width;
				if (m_select < 0)
					m_select += (m_items.size() / (MAX_CHARPERLINE / m_item_width) + 1) * (MAX_CHARPERLINE / m_item_width);
				break;
			case 73:	// PgUp
				break;
			case 75:	// Left
				m_select--;
				if (m_select < 0)
					m_select = m_items.size() - 1;
				break;
			case 77:	// Right
				m_select++;
				if ((unsigned)m_select >= m_items.size())
					m_select = 0;
				break;
			case 79:	// End
				m_select = m_items.size() - 1;
				break;
			case 80:	// Down
				m_select += MAX_CHARPERLINE / m_item_width;
				if ((unsigned)m_select >= m_items.size())
					m_select %= MAX_CHARPERLINE / m_item_width;
				break;
			case 81:	// PgDn
				break;
			}
		}
		else if (cmd == 13)	// Enter
		{
			if (m_select >= 0 && (unsigned)m_select < m_items.size())
			{
				int ret = m_items[m_select]->Select();
				if (ret == BREAK)
					break;
			}
		}
		else
		{
			auto it = m_items_with_key.find(cmd);
			if (it != m_items_with_key.end())
			{
				int ret = it->second->Select();
				if (ret == BREAK)
					break;
			}
		}
	}
	while (true);
}

template<typename T>
void RMenuT<T>::Show()
{
	tcout << T(MAX_COLUMNS_PER_SCREEN, _T('\n'));
	int columns = MAX_CHARPERLINE / m_item_width;
	int id = 0;
	for (auto it : m_items)
	{
		tcout << setw(1) << ((m_select == id)?_T("*"):_T(" ")) << setw(m_item_width) << left << it->name;
		id++;
		if (id % columns == 0)
			tcout << endl;
	}
}

template<typename T>
int RMenuT<T>::Enter()
{
	return 0;
}

};	// namespace rl
