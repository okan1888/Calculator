#include "stdafx.h"

#include "symboltable.h"
#include "functiontable.h"
#include "node.h"
#include "store.h"
#include "scanner.h"
#include "parser.h"
#include "upcast.h"
#include "calculator.h"
#include "cmdparser.h"
#include<memory>
#include<cassert>
#include<iostream>
#include<cstdlib>


const long Version = 1;

CommandParser::CommandParser(Scanner &scanner, Calculator &calc)
	:_scanner(scanner), _calc(calc)
{
	assert(_scanner.IsCommand());
	_scanner.Accept();
	std::string name = _scanner.GetSymbolName();
	switch (name[0])
	{
	case 'q':
	case 'Q':
		_command = comQuit;
		break;
	case 's':
	case 'S':
		_command = comSave;
		break;
	case 'l':
	case 'L':
		_command = comLoad;
		break;
	}
}

Status CommandParser::Execute()
{
	_scanner.AcceptCommand();
	std::string nameFile;
	switch (_command)
	{
	case comSave:
		nameFile = _scanner.GetSymbolName();
		return Save(nameFile);
	case comLoad:
		nameFile = _scanner.GetSymbolName();
		return Load(nameFile);
	case comQuit:
		cerr << "Good Bye!" << endl;
		return stQuit;
	case comError:
		cerr << "Error" << endl;
		return stError;
	}
	return stOk;
}

Status CommandParser::Save(std::string const &nameFile)
{
	cerr<<"Save to:\""<< nameFile<<endl;
	Status status = stOk;
	try
	{
		Serializer out(nameFile);
		out.PutLong(Version);
		_calc.Serialize(out);
	}
	catch(char *msg)
	{
		cerr << "Error:Save failed: " << msg << endl;
		status = stError;
	}
	return status;

}


Status CommandParser::Load(std::string const &nameFile)
{
	cerr << "Load from File: " << nameFile << endl;
	Status status = stOk;
	try
	{
		DeSerializer in(nameFile);
		long ver = in.GetLong();
		if (ver != Version)
			throw "version mismatch";
		_calc.DeSerialize(in);
	} catch(char *msg)
	{
		cerr << "Error:Load failed: " << msg << endl;
		status = stError;

	}
	return status;
}