#pragma once
#include <string>
#include <map>
#include "RObject.h"

namespace rl
{

class RRecord	// row
{
public:
	void Set(const std::string& column, const std::string& value);
	std::string Get(const std::string& column);
private:
	std::map<std::string, std::string> m_columns;
};

class RDatabase
{
public:
	bool Load(const std::string& filename);
	bool Save(const std::string& filename);
private:
	RObject m_root;
};

};	// namespace rl