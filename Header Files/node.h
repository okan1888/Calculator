#if !defined node_h
#define node_h

#include "functiontable.h"
#include <vector>
#include "auto_vector.h"
#include<cassert>
#include<memory>

class Store; //forward declaration


class Node //abstract class no constructor and virtual functions needed..for polymorphing
{
public:
	virtual ~Node() {} //destructor must be virtual because leave childs to be independent
	virtual double Calc() const = 0;
	virtual bool IsLvalue() const;
	virtual void Assign(double value)  {};

};

class MultiNode :public Node
{
public:
	MultiNode(auto_ptr<Node> &pNode)
	{
		AddChild(pNode, true);
	}
	void AddChild(auto_ptr<Node> &pNode, bool isPositive)
	{
		_aChild.push_back(pNode);//gets from up and release upper,takes the resource go on
		_aIsPositive.push_back(isPositive);
	}
protected:
	auto_vector<Node> _aChild;
	std::vector<bool> _aIsPositive;

};


class SumNode :public MultiNode
{
public:
	SumNode(auto_ptr<Node> &pNode)
		: MultiNode(pNode)
	{}
	double Calc() const;
};

class ProductNode :public MultiNode
{
public:
	ProductNode(auto_ptr<Node> pNode)
		: MultiNode(pNode)
	{}
	double Calc() const;
};



class NumNode :public Node
{
public:
	NumNode(double num) 
		:_num(num) {}
	double Calc() const;
private:
	double const _num;
};

class BinNode : public Node
{
public:
	BinNode(auto_ptr<Node> &pLeft, auto_ptr<Node> &pRight)
		: _pLeft(pLeft), _pRight(pRight) {}
protected:
	auto_ptr<Node> _pLeft;
	auto_ptr<Node> _pRight;
};


class AddNode :public BinNode
{
public:
	AddNode(auto_ptr<Node> pLeft, auto_ptr<Node> pRight)
		: BinNode(pLeft,pRight) {}
	double Calc() const;
};

class SubNode :public BinNode
{
public:
	SubNode(auto_ptr<Node> & pLeft, auto_ptr<Node> &pRight)
		: BinNode(pLeft, pRight) {}
	double Calc() const;
};

class DivideNode :public BinNode
{
public:
	DivideNode(auto_ptr<Node> &pLeft, auto_ptr<Node> &pRight)
		: BinNode(pLeft, pRight) {}
	double Calc() const;
};

class UMinusNode :public Node
{
public:
	UMinusNode(auto_ptr<Node> &pNode)
		: _pNode(pNode) {}
//after introducing auto_ptr,deleting again wrong,so no ~ destructor
	double Calc() const;
private:
	 auto_ptr<Node> _pNode;//Node* instead of this, for better way,used auto_ptr
};

class MultNode :public BinNode
{
public:
	MultNode(auto_ptr<Node> pLeft, auto_ptr<Node> pRight)
		: BinNode(pLeft,pRight) {}
	double Calc() const;
};


class FunNode : public Node
{
public:
	FunNode(PtrFun pFun, auto_ptr<Node> & pNode)
		: _pNode(pNode), _pFun(pFun)
	{}
	double Calc() const;
private:
	PtrFun _pFun;
	auto_ptr<Node> _pNode;

};

class AssignNode :public BinNode
{
public:
	AssignNode(auto_ptr<Node> & pLeft,auto_ptr<Node> & pRight)
		: BinNode(pLeft,pRight)
	{}
	double Calc() const;

};

class VarNode :public Node
{
public:
	VarNode(int id, Store & store)
		: _id(id), _store(store)
	{}
	double Calc() const;
	bool IsLvalue() const;
	void Assign(double val);
private:
	const int _id;
	Store & _store;

};

#endif