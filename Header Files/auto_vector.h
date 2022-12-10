#if !defined auto_vector_h
#define auto_vector_h

#include<memory>

//standard vector may create problem with auto_ptr objects so
//we create our auto_vector type
//okan karadağ 2017

template<class T>
class const_auto_iterator : public
	std::iterator<std::forward_iterator_tag, T const *> //we inherited standard iterator
{
public:
	const_auto_iterator() : _pp(0) {}
	const_auto_iterator(auto_ptr<T> const * pp) : _pp(pp) {}
	bool operator != (const_auto_iterator<T> const & it) const
	{
		return it._pp != _pp;
	}
	const_auto_iterator operator++ (int) { return _pp++; }
	const_auto_iterator operator++ () { return ++_pp; }
	T const * operator * () { return _pp->get(); }
	T const * operator-> () { return _pp->get(); }
private:
	auto_ptr<T> const * _pp;
};

template <class T>
class auto_vector
{
public:
	explicit auto_vector(size_t capacity = 0)
		: _arr(0), _end(0), _capacity(0)
	{
		if (capacity != 0)
			_arr = new auto_ptr<T>[capacity];
		_capacity = capacity;
	}
	~auto_vector()
	{
		delete[]_arr;
	}
	size_t size() const { return _end; }
	T const * operator [] (size_t i) const
	{
		assert(i < _end);
		return _arr[i].get();
	}
	T * operator [] (size_t i)
	{
		assert(i < _end);
		return _arr[i].get();
	}
	void assign(size_t i, auto_ptr<T> & p)
	{
		assert(i < _end);
		_arr[i] = p;
	}
	void assign_direct(size_t i, T * p)
	{
		assert(i < _end);
		_arr[i].reset(ptr);
	}
	void push_back(auto_ptr<T> & p)
	{
		if (_end == _capacity)
			grow(_end + 1);
		_arr[_end++] = p;
	}
	auto_ptr<T> pop_back()
	{
		assert(_end != 0);
		return _arr[--_end];
	}
	typedef const_auto_iterator<T> const_iterator; //typedef can be here..
	//vector -also a container- should have an iterator
	const_iterator begin() const { return _arr; }
	const_iterator end() const { return _arr + _end; }
private:
	void grow(size_t reqCapacity);

	auto_ptr<T>  *_arr;
	size_t		  _capacity;
	size_t		  _end;
};

template <class T>
void auto_vector<T>::grow(size_t reqCapacity)
{
	size_t newCapacity = 2 * _capacity;
	if (reqCapacity > newCapacity)
		newCapacity = reqCapacity;
	// allocate new array
	auto_ptr<T> * arrNew = new auto_ptr<T>[newCapacity];
	// transfer all entries
	for (size_t i = 0; i < _capacity; ++i)
		arrNew[i] = _arr[i];
	_capacity = newCapacity;
	// free old memory
	delete[]_arr;
	// substitute new array for old array
	_arr = arrNew;
}


#endif
