#include "stdafx.h"

#include "symboltable.h"
#include<cassert>
#include<iostream>
#include<cstdlib>
#include<map>
#include<string>

using namespace std;

int SymbolTable::ForceAdd(std::string const &str)
{
	std::string name(str);
	std::pair<std::string, int> p(str, _id);//or _dictionary[name] = _id;
	_dictionary.insert(p);
	return _id++;
}


int SymbolTable::Find(std::string const &str) const
{
	std::map<std::string, int>::const_iterator it;
	it = _dictionary.find(str);
	if (it != _dictionary.end())
		return it->second;
	return idNotFound;
	

}

void SymbolTable::Serialize(Serializer &out) const
{
	out.PutLong(_dictionary.size());
	std::map<std::string, int>::const_iterator it;
	for (it = _dictionary.begin(); it != _dictionary.end(); ++it)
	{
		out.PutString(it->first);
		out.PutLong(it->second);
	}

	out.PutLong(_id);

}

void SymbolTable::DeSerialize(DeSerializer &in)
{
	_dictionary.clear();// before take in data,clear old data
	int len = in.GetLong();
	for (int i = 0; i < len; ++i)
	{
		std::string str = in.GetString();
		int id = in.GetLong();
		_dictionary[str] = id;
	}
	_id = in.GetLong();
}
