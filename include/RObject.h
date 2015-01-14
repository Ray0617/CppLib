#pragma once
#include <map>
#include <string>
#include <memory>

namespace rl
{

template<typename T>
class RObjectT
{
public:
	RObjectT();
	RObjectT(const T& value);
	RObjectT(const RObjectT& value);
	~RObjectT();
	void SetValue(const T& value);
	void SetAttribute(const T& name, const T& value);
	void SetAttribute(const T& name, std::shared_ptr<RObjectT> object);
	void CopyAttribute(const T& name, const RObjectT& object);
	T GetValue() const;
	RObjectT& operator[](const T& name) const;
	std::shared_ptr<RObjectT> GetAttribute(const T& name) const;
	std::shared_ptr<RObjectT> Clone() const;
	bool IsEqual(const RObjectT& object) const;
	bool operator==(const RObjectT& object) const;
private:
	T m_value;
	std::map<T, std::shared_ptr<RObjectT> > m_attributes;
};

typedef RObjectT<std::string> RObjectA;
typedef RObjectT<std::wstring> RObjectW;
#ifdef _UNICODE
#define RObject RObjectW
#else
#define RObject RObjectA
#endif

};	// namespace rl
