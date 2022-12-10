#include "stdafx.h"

#include "symboltable.h"
#include "functiontable.h"
#include "node.h"
#include "store.h"
#include "scanner.h"
#include "parser.h"
#include "upcast.h"
#include "calculator.h"
#include<memory>
#include<cassert>
#include<iostream>
#include<cstdlib>

using namespace std;


class Syntax {}; // for throwing special errors...


Parser::Parser(Scanner &scanner,Calculator &calc)
	:_scanner(scanner),_calc(calc)
{
}

Status Parser::Eval()
{
	Parse();
	if (_status == stOk)
		return _status;
	else
		_status = stQuit;

	return _status;

}

double Parser::Calculate() const
{
	assert(_status == stOk);
	assert(_pTree.get() != 0);
	return _pTree->Calc();
}

Status  Parser::Parse()
{
	// Everything is an expression
	try {
		_pTree = Expr();
		if (!_scanner.IsDone())
			_status = stError;
		return _status;
	}
	catch (Syntax)
	{
		_status = stError;
	}
	return _status;

	
}

auto_ptr<Node>  Parser::Expr()
{
	auto_ptr<Node> pNode=Term();//we used smart pointer device
	if (pNode.get() == 0)
		return pNode;
	EToken token = _scanner.Token();
	if (token == tPlus || token == tMinus)
	{
		auto_ptr<MultiNode> pMultiNode(new SumNode(pNode));//modifed sumnode constructor as smartpointer device
		do
		{
			_scanner.Accept();
			auto_ptr<Node>  pRight=Term();//we used smart pointer here and transferred down below line.
			pMultiNode->AddChild(pRight, (token == tPlus));
			token = _scanner.Token();
		} while(token == tPlus || token == tMinus);
		pNode = up_cast<Node>(pMultiNode); // here may give an error!!! upcasting function template
	}
	else if (token == tAssign)
	{
		_scanner.Accept();
		auto_ptr<Node> pRight=Expr();
		if (pNode->IsLvalue())
		{
			pNode = auto_ptr<Node> (new AssignNode(pNode, pRight));// this move is nice!!
		}
		else
		{
			_status = stError;
			pNode=Expr();
		}
	}
	return pNode;
}


auto_ptr<Node> Parser::Term()
{
	auto_ptr<Node> pNode = Factor();
	EToken token = _scanner.Token();

	if (token == tMult || token == tDivide)
	{
		auto_ptr<MultiNode> pMultiNode(new ProductNode(pNode));
		do
		{
			_scanner.Accept();
			auto_ptr<Node> pRight = Factor();
			pMultiNode->AddChild(pRight, (token == tMult));
			token = _scanner.Token();
		} while(token == tMult || token == tDivide);
		pNode = up_cast<Node>(pMultiNode);
	}
	return pNode;
}


auto_ptr<Node> Parser::Factor()
{
	
	auto_ptr<Node> pNode;
	EToken token = _scanner.Token();
	if (token == tLParen)
	{
		_scanner.Accept();// accept '('
		pNode = Expr();
		if (_scanner.Token() != tRParen)
			_status = stError;
		_scanner.Accept();//accept ')'
		
	}
	else if (token == tNumber)
	{
		pNode = auto_ptr<Node>(new NumNode(_scanner.Number()));
		_scanner.Accept();

	}
	else if (token == tIdent)
	{
		std::string strSymbol=_scanner.GetSymbolName();
		int id = _calc.FindSymbol(strSymbol);
		_scanner.Accept();
		if (_scanner.Token() == tLParen)
		{
			_scanner.Accept();
			pNode = Expr();
			assert(pNode.get() != 0);
			if (_scanner.Token() == tRParen)
				_scanner.Accept();
			else
				throw Syntax(); // instead of making_status = stError,we throw the error
			if (id != SymbolTable::idNotFound && id < _calc.IsFunction(id))
			{
				pNode = auto_ptr<Node>(new FunNode(_calc.GetFun(id), pNode));
			}
			else
			{
				cerr << "Error:unknown function!" << endl;
				throw Syntax();

			}
		}
		else
		{
			if (id == SymbolTable::idNotFound)
			{
				id = _calc.AddSymbol(strSymbol);
			}
			pNode = auto_ptr<Node>(new VarNode(id, _calc.GetStore()));
		}
	}
	else if (token == tMinus)
	{
		_scanner.Accept();
		pNode = auto_ptr<Node>(new  UMinusNode(Factor()));
	}
	else
	{
		_scanner.Accept();
		throw Syntax();
	}
	return pNode;
}
