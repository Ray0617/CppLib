#pragma once
#include <string>
#include <vector>
#include <memory>
#include "RObject.h"

// NOTE: do 

namespace rl
{

template<typename T>
class RDatabaseT
{
public:
	typedef bool (*FilterFuncPtr)(std::shared_ptr<RObjectT<T> > test);
	RDatabaseT();
	~RDatabaseT();
	bool Load(const T& filename);
	bool Save(const T& filename);
	void Set(std::shared_ptr<RObjectT<T> > object);
	std::shared_ptr<RObjectT<T> > Get(const T& name);
	std::shared_ptr<RObjectT<T> > First();
	std::shared_ptr<RObjectT<T> > Next();
	std::shared_ptr<RDatabaseT<T> > Filter(FilterFuncPtr filter);
	size_t Size();
private:
	std::shared_ptr<RObjectT<T> > m_data;
};

typedef RDatabaseT<std::string> RDatabaseA;
typedef RDatabaseT<std::wstring> RDatabaseW;
#ifdef _UNICODE
#define RDatabase RDatabaseW
#else
#define RDatabase RDatabaseA
#endif

};	// namespace rl