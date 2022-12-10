
#if !defined functiontable_h
#define functiontable_h

#include<cstdlib>

typedef double(*PtrFun)(double);
using namespace std;

class SymbolTable;
namespace Function
{

	class Table
	{
	public:
		Table(SymbolTable &symTab);//avoiding copy array FunctionEnrty funArr[]
		~Table() { delete[] _pFun; }
		int Size() const { return _size; }
		PtrFun GetFun(int id) const { return _pFun[id]; }
	private:
		PtrFun *_pFun;
		int _size;
	};
}
#endif