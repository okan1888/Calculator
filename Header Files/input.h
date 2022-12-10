#pragma once
#if !defined input_h
#define input_h//preprocessor directives


class Input
{
public:
	Input();
	int Token() const { return _token; }
	int Number() const;
	enum { tokNumber = 1 };
	enum { tokError = 2 };
	enum { tokHex = 3 };
private:
	int _token;
	char _buf[maxBuff];
};
#endif