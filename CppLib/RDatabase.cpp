#include "RDatabase.h"
#include <fstream>
#include "../../pugixml/src/pugiconfig.hpp"
#include "../../pugixml/src/pugixml.hpp"
#include "RString.h"

using namespace std;

namespace rl
{

static const std::string g_root = "root";

template<typename T>
RDatabaseT<T>::RDatabaseT()
	: m_data(make_shared<RObjectT<T> >())
{
}

template<typename T>
RDatabaseT<T>::~RDatabaseT()
{
}

template<typename T>
void LoadNode(pugi::xml_node& node, shared_ptr<RObjectT<T> > obj)
{
	obj->SetName(ToTempStr<T>(node.name()));
	pugi::xml_node child_node = node.first_child();
	while (child_node)
	{
		if (child_node.type() == pugi::node_pcdata)
		{
			obj->SetValue(ToTempStr<T>(child_node.value()));
		}
		else
		{
			shared_ptr<RObjectT<T> > child_obj = make_shared<RObjectT<T> >();
			LoadNode(child_node, child_obj);
			obj->SetAttribute(child_obj);
		}
		child_node = child_node.next_sibling();
	}
}

template<typename T>
bool RDatabaseT<T>::Load(const T& filename)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(ToTStr(filename).c_str());
	if (!result)
		return false;
	m_data = make_shared<RObjectT<T> >();
	LoadNode(doc, m_data);
	return true;
}

template<typename T>
void SaveNode(pugi::xml_node& node, shared_ptr<RObjectT<T> > obj)
{
	node.set_name(ToTStr(obj->GetName()).c_str());
	if (!obj->GetValue().empty())
		node.append_child(pugi::node_pcdata).set_value(ToTStr(obj->GetValue()).c_str());
	auto attr = obj->FirstAttribute();
	while (!attr->IsEmpty())
	{
		pugi::xml_node child = node.append_child(pugi::node_element);
		SaveNode(child, attr);
		attr = obj->NextAttribute();
	}
}

template<typename T>
bool RDatabaseT<T>::Save(const T& filename)
{
	pugi::xml_document doc;
	SaveNode(doc, m_data);
	return doc.save_file(filename.c_str());
}

template<typename T>
void RDatabaseT<T>::Set(std::shared_ptr<RObjectT<T> > object)
{
	m_data->SetAttribute(object);
}

template<typename T>
std::shared_ptr<RObjectT<T> > RDatabaseT<T>::Get(const T& name)
{
	if (m_data.get())
		return m_data->GetAttribute(name);
	else
		return std::shared_ptr<RObjectT<T> >();
}

template class RDatabaseT<std::string>;
template class RDatabaseT<std::wstring>;

};	// namespace rl