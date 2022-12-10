//Okan Karadağ 2017

#if !defined calculator_h
#define calculator_h


#include "symboltable.h"
#include "functiontable.h"
#include "store.h"
#include "serial.h"


class Calculator:public Serializable
{
	friend class Parser;
public:
	Calculator()
		:_funTab(_symTab),_store(_symTab)
	{}
	void Serialize(Serializer &out) const
	{
		_symTab.Serialize(out);
		_store.Serialize(out);
	}
	void DeSerialize(DeSerializer &in)
	{
		_symTab.DeSerialize(in);
		_store.DeSerialize(in);

	}
private:
	Store &GetStore() { return _store; }
	PtrFun GetFun(int id ) const  { return _funTab.GetFun(id); }
	bool IsFunction(int id) const { return id < _funTab.Size(); }

	int AddSymbol(std::string const &str)
	{
		return _symTab.ForceAdd(str);
	}
	int FindSymbol(std::string const &str) const
	{
		return _symTab.Find(str);
	}

	SymbolTable _symTab;
	Function::Table _funTab;
	Store _store;
};

#endif