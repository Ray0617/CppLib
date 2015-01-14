#include "RObject.h"
#include <assert.h>
#include <tchar.h>
#include <memory>
using namespace std;
using namespace rl;

bool TestRObject()
{
	// test if memory leak

	RObject obj1;
	obj1.SetValue(_T("test1"));
	RObject obj2(_T("test2"));
	RObject obj3(obj2);
	assert(obj3.GetValue() == obj2.GetValue());
	obj3.SetValue(_T("test3"));
	assert(obj2.GetValue() == _T("test2"));	// value of different object should be independent
	RObjectA obj4("test4");
	RObjectW obj5(L"test5");
	//RObjectA obj6(obj5);	// different class

	// without smart pointer, only CopyAttribute() method is allowed
	obj1.SetAttribute(_T("attr1"), _T("value1"));
	assert(obj1[_T("attr1")].GetValue() == _T("value1"));
	obj1.CopyAttribute(_T("attr2"), obj2);
	obj3.CopyAttribute(_T("attr1"), obj1);
	assert(obj3[_T("attr1")][_T("attr2")].GetValue() == _T("test2"));
	obj3[_T("attr1")].SetValue(_T("obj3.attr1"));
	assert(obj1.GetValue() == _T("test1"));	// copy attribute would clone another instance 
		// so that the cloned one could be independent with the new one

	shared_ptr<RObject> pobj1;	// pobj1 is empty; it's non-sense to use shared_ptr in this way
	assert(pobj1.get() == nullptr);
	pobj1 = shared_ptr<RObject>(new RObject(_T("test1")));
	assert(pobj1->GetValue() == _T("test1"));
	shared_ptr<RObject> pobj2(new RObject(_T("test2")));
	shared_ptr<RObject> pobj3(new RObject(*pobj2));	// clone
	assert(pobj3->GetValue() == pobj2->GetValue());
	pobj3->SetValue(_T("test3"));
	assert(pobj2->GetValue() == _T("test2"));	// value of different object should be independent

	shared_ptr<RObject> pobj4(pobj3);	// pobj4 and pobj3 are exactly the same (reference)
	assert(pobj4->GetValue() == _T("test3"));
	pobj4->SetValue(_T("test4"));
	assert(pobj3->GetValue() == _T("test4"));	// changed 

	pobj3->SetAttribute(_T("attr1"), pobj1);	// pobj3["attr1"] are exactly the same with pobj1
	assert((*pobj3)[_T("attr1")] == *pobj1);
	assert(pobj3->GetAttribute(_T("attr1")) == pobj1);

	// to sum up, shared_ptr and SetAttribute is suggested;
	// handy one (for simple use) is to use RObject directly and CopyAttribute, 
	// which is very inefficient for the deep copy
	return true;
}