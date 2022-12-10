#if !defined scanner_h
#define scanner_h

#pragma warning (disable:4786)
#include <istream>
#include <string>
#include <cassert>


enum EToken
{
	tEnd,
	tError,
	tNumber,
	tPlus,
	tMult,
	tMinus,
	tDivide,
	tLParen,
	tRParen,
	tAssign,
	tIdent,
	tExclam
};




class Scanner
{
public:
	explicit Scanner(std::istream &in);
	EToken Token() const { return _token; }
	bool IsDone() const { return _token == tEnd; }
	bool IsEmpty() const { return _isEmpty; }
	void Accept();
	void AcceptCommand();
	bool IsCommand() const { return _token == tExclam; }
	std::string  GetSymbolName(); 
	double Number()
	{
		assert(_token == tNumber);
		return _number;
	}

private:
	void ReadChar();
	std::istream &_in;
	int _look;
	bool _isEmpty;
	EToken _token;
	double _number;
	std::string _symbol;
};

#endif 