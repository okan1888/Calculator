#if !defined SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "symboltable.h"
#include "serialstream.h"
#include <iostream>
#include "serial.h"
#include<map>
#include<string>


//we are now using STL containers in our program
//Okan Karadağ 2017

class HTable; //forward declaration

class SymbolTable :public Serializable
{
public:
	enum {idNotFound=-1};
	SymbolTable() : _id(0) {}
	~SymbolTable() {};
	int ForceAdd(std::string const &str);
	int Find(std::string const &str) const;
	void Serialize(Serializer &out) const;
	void DeSerialize(DeSerializer &in);
private:
	std::map<std::string,int> _dictionary;
	int					_id;
	
};

#endif