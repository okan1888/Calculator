#if !defined parser_h
#define parser_h

#include "auto_vector.h"
#include <vector>
#include "scanner.h"
#include "calculator.h"
#include <memory>

using std::auto_ptr;


class Node;
class Scanner;
class Store;
class SymbolTable;



namespace Function
{
	class Table;
}


enum Status
{
	stOk,
	stQuit,
	stError
};

class Parser
{
public:
	Parser(Scanner &scanner,Calculator &calc);
	Status Eval();
	Status Parse();
	double Calculate() const;
private:
	auto_ptr<Node> Expr();
	auto_ptr<Node> Term();
	auto_ptr<Node> Factor();
	Scanner& _scanner;
	auto_ptr<Node> _pTree;
	Status _status;
	Calculator &_calc;
}; 

#endif