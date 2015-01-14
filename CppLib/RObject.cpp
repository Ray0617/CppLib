#include "RObject.h"
#include "Rtchar.h"

namespace rl
{

// constructor
template<typename T>
RObjectT<T>::RObjectT()
{
}

template<typename T>
RObjectT<T>::RObjectT(const T& name, const T& value)
	: m_name(name)
	, m_value(value)
	, m_iter(m_attributes.end())
{
}

template<typename T>
RObjectT<T>::RObjectT(const RObjectT& copy)
{
	*this = *copy.Clone();
}

// destructor
template<typename T>
RObjectT<T>::~RObjectT()
{
}

template<typename T>
void RObjectT<T>::SetName(const T& name)
{
	m_name = name;
}

template<typename T>
void RObjectT<T>::SetValue(const T& value)
{
	m_value = value;
}

template<typename T>
void RObjectT<T>::SetAttribute(const T& name, const T& value)
{
	SetAttribute(std::make_shared<RObjectT<T> >(name, value));
}

template<typename T>
void RObjectT<T>::SetAttribute(std::shared_ptr<RObjectT> object)
{
	bool existed = (m_attributes.find(object->GetName()) != m_attributes.end());
	m_attributes[object->GetName()] = object;
	if (!existed)
		m_iter = m_attributes.end();
}

template<typename T>
void RObjectT<T>::CopyAttribute(const RObjectT& object)
{
	SetAttribute(object.Clone());
}

template<typename T>
T RObjectT<T>::GetName() const
{
	return m_name;
}

template<typename T>
T RObjectT<T>::GetValue() const
{
	return m_value;
}

template<typename T>
RObjectT<T>& RObjectT<T>::operator[](const T& name) const
{
	return *GetAttribute(name).get();
}

template<typename T>
std::shared_ptr<RObjectT<T>> RObjectT<T>::GetAttribute(const T& name) const
{
	auto it = m_attributes.find(name);
	if (it == m_attributes.end())
		return std::shared_ptr<RObjectT>();
	return it->second;
}

template<typename T>
std::shared_ptr<RObjectT<T> > RObjectT<T>::Clone() const
{
	std::shared_ptr<RObjectT<T> > clone = std::make_shared<RObjectT<T> >();
	clone->m_name = m_name;
	clone->m_value = m_value;
	for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
	{
		clone->m_attributes[it->first] = it->second->Clone();
	}
	return clone;
}

template<typename T>
bool RObjectT<T>::IsEqual(const RObjectT& object) const
{
	if (m_name != object.m_name || m_value != object.m_value)
		return false;
	if (m_attributes.size() != object.m_attributes.size())
		return false;
	for (auto it = m_attributes.begin(); it != m_attributes.end(); it++)
	{
		if (!it->second->IsEqual(object[it->first]))
			return false;
	}
	return true;
}

template<typename T>
bool RObjectT<T>::operator==(const RObjectT& object) const
{
	return IsEqual(object);
}

template<typename T>
bool RObjectT<T>::IsEmpty() const
{
	return m_name.empty() && m_value.empty() && m_attributes.empty();
}

template<typename T>
std::shared_ptr<RObjectT<T> > RObjectT<T>::FirstAttribute()
{
	if (m_attributes.empty())
		return std::make_shared<RObjectT<T> >();
	m_iter = m_attributes.begin();
	return m_iter->second;
}

template<typename T>
std::shared_ptr<RObjectT<T> > RObjectT<T>::NextAttribute()
{
	if (m_iter == m_attributes.end())
		return std::make_shared<RObjectT<T> >();
	m_iter++;
	if (m_iter == m_attributes.end())
		return std::make_shared<RObjectT<T> >();
	return m_iter->second;
}

template class RObjectT<std::string>;
template class RObjectT<std::wstring>;

};
