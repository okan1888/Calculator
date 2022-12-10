#if !defined serialstream_h
#define serialstream_h

#include<fstream>

using std::ios_base;
const long TruePattern = 0xfab1fab2;
const long FalsePattern = 0xbad1bad2;

class DeSerializer
{
public:
	DeSerializer(std::string const &nameFile)
		: _stream(nameFile.c_str(), ios_base::in | ios_base::binary)
	{
		if (!_stream.is_open())
			throw "cant open file";
	}
	long GetLong()
	{
		if (_stream.eof())
			throw "unexpected end of file";
		long l;
		_stream.read(reinterpret_cast<char *>(&l), sizeof(long)); 
		if (_stream.bad())
			throw "file read failed";
		return l;
	}
	double GetDouble()
	{
		double d;
		if (_stream.eof())
			throw "unexpected end of file";
		_stream.read(reinterpret_cast<char *> (&d), sizeof(double)); 
		if (_stream.bad())
			throw "file read failed";
		return d;
	}

	std::string GetString()
	{
		long len = GetLong();
		std::string str;
		str.resize(len);
		_stream.read(&str[0], len);
		if (_stream.bad())
			throw "file read bad";
		return str;
	}
	bool GetBool()
	{
		long b = GetLong();
		if (_stream.bad())
			throw "file read failed";
		if (b == TruePattern)
			return true;
		else if (b == FalsePattern)
			return false;
		else
			throw "data corruption";
	}
private:
	std::fstream _stream;
};

class Serializer
{
public:
	Serializer(std::string const & nameFile)
		: _stream(nameFile.c_str(), ios_base::out | ios_base::binary)
	{
		if (!_stream.is_open())
			throw "couldn't open file";
	}
	void PutLong(long l)
	{
		_stream.write(reinterpret_cast<char *> (&l), sizeof(long));
		if (_stream.bad())
			throw "file write failed";
	}
	void PutDouble(double d)
	{
		_stream.write(reinterpret_cast<char *> (&d), sizeof(double));
		if (_stream.bad())
			throw "file write failed";
	}
	void PutString(std::string const & str)
	{
		int len = str.length();
		PutLong(len);
		_stream.write(str.data(), len);
		if (_stream.bad())
			throw "file write failed";
	}
	void PutBool(bool b)
	{
		long l = b ? TruePattern : FalsePattern;
		PutLong(l);
		if (_stream.bad())
			throw "file write failed";
	}
private:
	std::ofstream _stream;
};


#endif

