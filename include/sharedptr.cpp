// sharedptr.cpp : Defines the entry point for the console application.
//


#include "stdlib.h"
#include <iostream>

template <class T>
class Shared_ptr
{
public:
	Shared_ptr();
	Shared_ptr(T* pointer);
	Shared_ptr(const Shared_ptr<T>& src);
	Shared_ptr<T> operator= (Shared_ptr<T>& other);
	~Shared_ptr();
	
	bool unique() const;
	size_t use_count() const;
	T* get() const;
	operator bool();
	void reset();

private:
	T* ptr;
	size_t* count;
};

template <typename T, class ...Args>
auto make_shared(Args && ...args) -> Shared_ptr<T>
{
	return Shared_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
Shared_ptr<T>::Shared_ptr() : ptr(nullptr), count(nullptr)
{}

template <class T>
Shared_ptr<T>::Shared_ptr(T* pointer) : ptr(pointer), count(new size_t(1))
{}

template <class T>
Shared_ptr<T>::Shared_ptr(const Shared_ptr<T>& src) : ptr(src.ptr), count(src.count)
{
	(*count)++;
}

template <class T>
Shared_ptr<T> Shared_ptr<T>::operator= (Shared_ptr<T>& other)
{
	if (this != &other)
	{
		if (count) {
			if (*count == 1)
			{
				delete ptr;
				delete count;
			}
			else
			{
				*count--;
			}
		}
		ptr = other.ptr;
		count = other.count;
		(*count)++;
	}
	return *this;
}

template <class T>
Shared_ptr<T>::~Shared_ptr(){
	if (count) {
		if (*count == 1) {
			delete count;
			delete ptr;
		}
		else (*count)--;
	}
}

template <class T>
bool Shared_ptr<T>::unique() const
{
	if (count == nullptr)
		throw "nullptr";
	return (*count == 1);
}

template <class T>
size_t Shared_ptr<T>::use_count() const
{
	if (count == nullptr)
		return 0;
	else
		return *count;
}

template <class T>
T* Shared_ptr<T>::get() const
{
	return ptr;
}

template <class T>
Shared_ptr<T>::operator bool()
{
	return (this->get() != nullptr);
}

template <class T>
void Shared_ptr<T>::reset()
{
	if ((ptr != nullptr) && ( *count == 1))
	{
		delete ptr;
		delete count;
	}
    ptr = nullptr;
	(*count)--;
}



int _tmain(int argc, _TCHAR* argv[])
{
	Shared_ptr<int> p1(new int(9));
	std::cout << "p1.use_count " << p1.use_count() << "\n";
	std::cout << "p1.unique " << ((p1.unique()) ? "true" : "false") << "\n\n";
	Shared_ptr<int> p2;
	p2 = p1;
	std::cout << "p1.unique " << ((p2.unique()) ? "true" : "false") << "\n\n";
	std::cout << "p2.get " << *p2.get() << "\n\n";
	if (p2)	std::cout << "p2.operator bool " << true << "\n\n";
	std::cout << "p2.reset " << "\n\n";
	p2.reset();
	std::cout << "p1.get " << *p1.get() << "\n\n";
	std::cout << "p1.unique " << ((p1.unique()) ? "true" : "false") << "\n\n";
	system("pause");
	return 0;
}

