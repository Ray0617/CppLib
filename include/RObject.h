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
	RObjectT(const T& name, const T& value);
	RObjectT(const RObjectT& object);
	~RObjectT();
	void SetName(const T& name);
	void SetValue(const T& value);
	void SetAttribute(const T& name, const T& value);
	void SetAttribute(std::shared_ptr<RObjectT> object);
	void CopyAttribute(const RObjectT& object);
	T GetName() const;
	T GetValue() const;
	RObjectT& operator[](const T& name) const;
	std::shared_ptr<RObjectT> GetAttribute(const T& name) const;
	std::shared_ptr<RObjectT> Clone() const;
	bool IsEqual(const RObjectT& object) const;
	bool operator==(const RObjectT& object) const;
	bool IsEmpty() const;
	size_t AttributeSize() const;
	
	std::shared_ptr<RObjectT<T> > FirstAttribute();
	std::shared_ptr<RObjectT<T> > NextAttribute();
private:
	T m_name;
	T m_value;
	std::map<T, std::shared_ptr<RObjectT> > m_attributes;
	typename std::map<T, std::shared_ptr<RObjectT> >::iterator m_iter;
};

typedef RObjectT<std::string> RObjectA;
typedef RObjectT<std::wstring> RObjectW;
#ifdef _UNICODE
#define RObject RObjectW
#else
#define RObject RObjectA
#endif

};	// namespace rl

