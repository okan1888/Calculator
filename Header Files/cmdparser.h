#if !defined cmdparser_h
#define cmdparser_h
class Scanner;
class Calculator;

class CommandParser
{
	enum ECommand
	{
		comSave,
		comLoad,
		comQuit,
		comError
	};
public:
	CommandParser(Scanner &scanner, Calculator &calc);
	Status Execute();
private:
	Status Load(std::string const &nameFile);
	Status Save(std::string const &nameFile);

	Scanner &_scanner;
	Calculator &_calc;
	ECommand _command;

};

#endif

