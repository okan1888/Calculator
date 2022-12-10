#if !defined upcast_h
#define upcast_h
#include <memory>

//upcasting function template !!!
//okan karadağ 2017

template<class To,class From>
auto_ptr<To> up_cast(auto_ptr<From> &from)
{
	return auto_ptr<To>(from.release());
}

#endif