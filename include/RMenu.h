#pragma once
#include <memory>
#include <vector>
#include <map>

namespace rl
{

typedef int (*MenuItemFuncPtr)(void*);

template<typename T>
class RMenuT
{
public:
	typedef T (*MenuInfoFuncPtr)(void*);

	static const int DEFAULT_ITEM_WIDTH = 10;
	enum {
		CONTINUE,
		BREAK,
	};
	RMenuT();
	~RMenuT();
	void SetItemWidth(unsigned width);
	void SetSelect(unsigned select);
	void SetInfo(MenuInfoFuncPtr info, void* arg = 0);
	void Add(const T& name, MenuItemFuncPtr func, void* arg);
	void AddHotkey(int key, MenuItemFuncPtr func, void* arg);
	int Run();
private:
	void Show();
	int Enter();	// return continue or break
	class RMenuItem
	{
	public:
		RMenuItem(const T& name, MenuItemFuncPtr func, void* arg);
		T name;
		MenuItemFuncPtr func;
		void* arg;
		int Select();
	};
	std::map<int, std::shared_ptr<RMenuItem> > m_items_with_key;
	std::map<int, std::shared_ptr<RMenuItem> > m_items_with_specialkey;
	std::vector<std::shared_ptr<RMenuItem> > m_items;	// in order
	int m_item_width;
	int m_select;
	MenuInfoFuncPtr m_info;
	void* m_info_arg;
};

typedef RMenuT<std::string> RMenuA;
typedef RMenuT<std::wstring> RMenuW;
#ifdef _UNICODE
#define RMenu RMenuW
#else
#define RMenu RMenuA
#endif

};	// namespace rl