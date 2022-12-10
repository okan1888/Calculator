#include "stdafx.h"

#include"store.h"
#include "node.h"
#include "auto_vector.h"
#include<cassert>
#include<iostream>
#include<cstdlib>

using namespace std;



double NumNode::Calc() const
{
	return _num;
}

double UMinusNode::Calc() const
{
	return -_pNode->Calc();
}

double FunNode::Calc() const
{
	assert(_pFun != 0);
	return (*_pFun)(_pNode->Calc());
}

bool Node::IsLvalue() const
{
	return 0;
}

double AssignNode::Calc() const
{
	double x = _pRight->Calc();
	_pLeft->Assign(x);
	return x;
}

double VarNode::Calc() const
{
	double x = 0.0;
	if (_store.IsInit(_id))
		x = _store.Value(_id);
	else
		cerr << "Error:uninitilazed value" << endl;
	return x;
}

void VarNode::Assign(double val)
{
	_store.SetValue(_id, val);

}

bool VarNode::IsLvalue() const
{
	return true;
}



double SumNode::Calc() const
{
	
	double sum = 0.0;
	auto_vector<Node>::const_iterator childIt = _aChild.begin();
	std::vector<bool>::const_iterator isPosIt = _aIsPositive.begin();

	for (; childIt != _aChild.end();++childIt,++isPosIt)
	{
		assert(isPosIt != _aIsPositive.end());
		double val = childIt->Calc();
		if (*isPosIt)
			sum += val;
		else
			sum -= val;
	}
	assert(isPosIt == _aIsPositive.end());

	return sum;
}


double ProductNode::Calc() const
{
	double prod = 1.0;
	for (int i = 0; i < _aChild.size(); ++i)
	{
		double val = _aChild[i]->Calc();
		if (_aIsPositive[i])
			prod *= val;
		else if (val != 0.0)
		{
			prod /= val;

		}
		else
		{
			cerr << "Error:division by zero" << endl;
			return HUGE_VAL;
		}
	}
	return prod;
}