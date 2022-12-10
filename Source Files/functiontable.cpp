#include "stdafx.h"

#include "symboltable.h"
#include "functiontable.h"
#include "parser.h"
#include<cassert>
#include<iostream>
#include<cstdlib>

using namespace std;

namespace Function
{

	double CoTan(double x)
	{
		double y = tan(x);
		if (y == 0)
		{
			return HUGE_VAL;

		}
		return 1.0 / y;
	}

	double sqr(double x)
	{
		return x*x;
	}

	double cube(double x)
	{
		return x*x*x;

	}
	class Entry
	{
	public:
		PtrFun pFun;
		char* strFun;
	};

	static Entry Array[] =
	{
		log,"log",
		log10,"log10",
		exp,"exp",
		sqrt,"sqrt",
		sin,"sin",
		cos,"cos",
		tan,"tan",
		CoTan,"cotan",
		sinh,"sinh",
		cosh,"cosh",
		tanh,"tanh",
		asin,"asin",
		acos,"acos",
		atan,"atan",
		sqr,"sqr",
		cube,"cube"
	};




	Table::Table(SymbolTable &symTab)
		: _size(sizeof Array / sizeof Array[0])
	{
		_pFun = new PtrFun[_size];

		for (int i = 0; i < _size; ++i)
		{

			int len = strlen(Array[i].strFun);
			_pFun[i] = Array[i].pFun;
			int j = symTab.ForceAdd(Array[i].strFun);
			assert(i == j);
		}
	}

}
