#if !defined store_h
#define store_h

#include "serial.h"
#include <cassert>
#include <vector>


class SymbolTable; //forward declaration so no need to include"....h"

class Store :public Serializable
{
	enum {stNotInit,stInit};
public:
	explicit Store(SymbolTable &symTab);
	bool IsInit(int id) const
	{
		assert(id >= 0);
		return (id < _IsInit.size()) && _IsInit[id];

	}
	double Value(int id) const
	{
		assert(id >= 0);
		assert(IsInit(id));
		return _Cell[id];
	}

	void SetValue(int id, double val)
	{
		assert(id >= 0 );
		if (id < _Cell.size())
		{
			_Cell[id] = val;
			_IsInit[id] = stInit;
		}
		else
		{
			AddValue(id, val);
		}
	}
	void AddValue(int id, double val)
	{
		assert(id >= 0);
		_Cell.resize(id + 1);
		_IsInit.resize(id + 1);
		_Cell[id] = val;
		_IsInit[id] = true;
	}
	void Serialize(Serializer &out) const;
	void DeSerialize(DeSerializer &in);

private:
	std::vector<double> _Cell;
	std::vector<bool> _IsInit;
};

#endif