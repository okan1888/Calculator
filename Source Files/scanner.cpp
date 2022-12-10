
#include "stdafx.h"
#include "scanner.h"
#include "symboltable.h"

#include <cctype>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <string>

#define _CRT_SECURE_NO_DEPRECATE

using namespace std;


Scanner::Scanner(std::istream &in)
	: _in(in)
{
	Accept();
	_isEmpty = (Token() == tEnd);
}

void Scanner::ReadChar()
{
	_look = _in.get();
	while (_look == ' ' || _look == '\t')
		_look = _in.get();
}

void Scanner::Accept() //accept tokenize input char by char 
{
	
	ReadChar();

	switch (_look)
	{
	case '+':
		_token = tPlus;
		break;
	case '*':
		_token = tMult;
		break;
	case '-':
		_token = tMinus;
		break;
	case '/':
		_token = tDivide;
		break;
	case '(':
		_token = tLParen;
		break;
	case ')':
		_token = tRParen;
		break;
	case '=':
		_token = tAssign;
		break;
	case '!':
		_token = tExclam;
		break;
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
		_token = tNumber;
		_in.putback(_look);
		_in >> _number;
		break;
	case '\n':
	case '\r':
	case EOF:
		_token = tEnd;
		break;
	default:
		if (isalpha(_look) || _look == '_')
		{
			_token = tIdent;
			_symbol.erase();
			do
			{
				_symbol += _look;
				_look = _in.get();

			} while (isalnum(_look));
			_in.putback(_look);
		}
		else
			_token = tError;
		break;
	}
}


std::string Scanner::GetSymbolName()
{

	return _symbol;

}

void Scanner::AcceptCommand()
{
	ReadChar();
	_symbol.erase();
	while (!isspace(_look))
	{
		_symbol += _look;
		_look = _in.get();
	}
}