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
	static const int DEFAULT_ITEM_WIDTH = 10;
	enum {
		CONTINUE,
		BREAK,
	};
	RMenuT();
	~RMenuT();
	void SetItemWidth(unsigned width);
	void SetSelect(unsigned select);
	void Add(const T& name, MenuItemFuncPtr func, void* arg, int key, bool show = true);
	void Run();
private:
	void Show();
	int Enter();	// return continue or break
	class RMenuItem
	{
	public:
		RMenuItem(const T& name, MenuItemFuncPtr func, void* arg, bool show);
		T name;
		MenuItemFuncPtr func;
		void* arg;
		bool show;
		int Select();
	};
	std::map<int, std::shared_ptr<RMenuItem> > m_items_with_key;
	std::map<int, std::shared_ptr<RMenuItem> > m_items_with_specialkey;
	std::vector<std::shared_ptr<RMenuItem> > m_items;	// in order
	int m_item_width;
	int m_select;
};

typedef RMenuT<std::string> RMenuA;
typedef RMenuT<std::wstring> RMenuW;
#ifdef _UNICODE
#define RMenu RMenuW
#else
#define RMenu RMenuA
#endif

};	// namespace rl