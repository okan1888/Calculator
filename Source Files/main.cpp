// main.cpp : Defines the entry point for the console calculator application
// you can use the project for educational purposes.
// Okan Karadağ 2017

#include "stdafx.h"

#include<iostream>
#include<cassert>
#include<stdlib.h>
#include<string.h>
#include"node.h"
#include "scanner.h"
#include "symboltable.h"
#include "functiontable.h"
#include "store.h"
#include "parser.h"
#include "cmdparser.h"

using namespace std;


int main()
{


	Status status;

	//Calculator ICalculator;//initialize function table,variable table and value stores..
	//but pass by value restriced since Calculator cannot be used like that

	Calculator calc;

		
	do
	{
		cout << ">";
		Scanner scanner(cin);

		if (!scanner.IsEmpty())
		{
			
			if (scanner.IsCommand())
			{
				CommandParser parser(scanner, calc);
				status = parser.Execute();
			}
			else
			{
				Parser parser(scanner, calc);
				status = parser.Parse();
				if (status == stOk)
				{
					double result = parser.Calculate();
					cout << "Result is= " << result << endl;
				}
				else
				{
					cerr << "Error:syntax error" << endl;
				}
			}
		}
		else
		{
			break;
		}
	} while (status != stQuit);


	cout << "exiting main..................."<< endl ;

	return 0;
}

