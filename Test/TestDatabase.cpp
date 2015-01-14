#include "RDatabase.h"
#include <assert.h>
#include <tchar.h>

using namespace std;
using namespace rl;

bool TestRDatabase()
{
	RDatabase db1;
	shared_ptr<RObject> person1 = make_shared<RObject>(_T("Ray"), _T(""));
	person1->SetAttribute(_T("Age"), _T("32"));
	person1->SetAttribute(_T("Height"), _T("5'8\""));
	shared_ptr<RObject> contact1 = make_shared<RObject>(_T("Contact"), _T(""));
	contact1->SetAttribute(_T("cell"), _T("123-456-7890"));
	contact1->SetAttribute(_T("email"), _T("lrm0617@gmail.com"));
	person1->SetAttribute(contact1);
	shared_ptr<RObject> person2 = make_shared<RObject>(_T("Sofya"), _T(""));
	person2->SetAttribute(_T("Age"), _T("30"));
	person2->SetAttribute(_T("Height"), _T("5'4\""));
	person2->SetAttribute(_T("SpecialTest"), _T("and='&'; greater_than='>'; less_than='<'; space:' '"));
	db1.Set(person1);
	db1.Set(person2);
	assert( db1.Save(_T("Test\\TestRDatabase1.txt")) );	// note: directory Test must be existed

	shared_ptr<RDatabase> db2 = make_shared<RDatabase>();
	assert( db2->Load(_T("Test\\TestRDatabase1.txt")) );
	assert(db2->Get(_T("Ray")) != person1);
	assert(*(db2->Get(_T("Ray")).get()) == *person1);
	assert(*db2->Get(_T("Sofya")) == *person2);
	assert((*db2->Get(_T("Ray")))[_T("Contact")][_T("cell")].GetValue() == _T("123-456-7890"));
	assert(db2->Get(_T("Sofya"))->GetAttribute(_T("SpecialTest"))->GetValue() == _T("and='&'; greater_than='>'; less_than='<'; space:' '"));
	return true;
}
