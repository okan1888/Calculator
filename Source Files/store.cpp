#include "stdafx.h"

#include "symboltable.h"
#include "store.h"
#include<cassert>
#include<iostream>
#include<cstdlib>

using namespace std;

Store::Store(SymbolTable &symTab)
{

	//adding predefined constants
	cout << "e=" << exp(1) << endl;
	int id = symTab.ForceAdd("e");
	AddValue(id, exp(1));
	cout << "pi=" << 2 * acos(0.0) << endl;
	id = symTab.ForceAdd("pi");
	AddValue(id, 2.0*acos(0.0));

}

void Store::Serialize(Serializer &out) const
{
	int len = _Cell.size();
	out.PutLong(len);
	for (int i = 0; i < len; ++i)
	{
		out.PutLong(_Cell[i]);
		out.PutLong(_IsInit[i]);

	}

}

void Store::DeSerialize(DeSerializer &in)
{
	_Cell.clear();
	_IsInit.clear();
	int len = in.GetLong();
	_Cell.resize(len);
	_IsInit.resize(len);
	for (int i = 0; i < len; ++i)
	{
		_Cell[i] = in.GetDouble();
		_IsInit[i] = in.GetBool();
	}
}