/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_TYPES_CLONE_PTR_INCLUDED
#define DCG_TYPES_CLONE_PTR_INCLUDED

#include <memory>
#include <cassert>
#include "dcg/functions/Util.hpp"


namespace dcg{

namespace detail{

class Copier{
public:
	Copier() {}
	virtual void* makeCopy(void* p){ assert(false); }//NOP
};

template<class T>
class Copier_t : public Copier{
public:
	Copier_t() : Copier() {}
	virtual void* makeCopy(void* p){ 
		//std::cout << "pop!\n";
		return((void*) (new T(*((T*)p)))); 
	}
};

}


//a pointer that copies the object it points to every time
//it gets copied.  single ownership.
//"so what's the point?", you may ask yourself.
//polymorphism and RAII(Recource Allocation Is Initialization) is
//the point.  you need a pointer for those things.
template<class T>
class c_ptr{
private:
	using Copier = detail::Copier;
	template<class U>
	using Copier_t = detail::Copier_t<U>;

private:
	T* p = nullptr;
	std::shared_ptr<Copier> c;

public:
	explicit c_ptr() : 
		p(nullptr),
		c(std::make_shared<Copier_t<T>>())
	{}

	explicit c_ptr(T* p) : 
		p(p), 
		c(std::make_shared<Copier_t<T>>())
	{}

	template<class U>
	explicit c_ptr(U* p) : 
		p(p), 
		c(std::make_shared<Copier_t<U>>())
	{
		b_assert(Util::instanceof<T, U>());
	}

	//implicit copy constructor for same type.
	c_ptr(const c_ptr<T>& other) : 
		c(std::make_shared<Copier_t<T>>())
	{
		p = (T*) other.makeCopy();
	}

	//implicit copy constructor for a derived type
	template<class U>
	c_ptr(const c_ptr<U>& other) : 
		c(std::make_shared<Copier_t<U>>())
	{
		b_assert(Util::instanceof<T, U>());
		p = (T*) other.makeCopy();
	}

	//copies val
	explicit c_ptr(T val) : 
		c(std::make_shared<Copier_t<T>>())
	{
		p = (T*) c->makeCopy(&val);
	}

	//copies val
	template<class U>
	explicit c_ptr(U val) : 
		c(std::make_shared<Copier_t<U>>())
	{
		b_assert(Util::instanceof<T, U>());
		p = (T*) c->makeCopy(&val);
	}

	//reset to null
	void reset(){
		if(!isNull()){
			delete p;
			//cout << "bang!\n";
		}
		p = nullptr;
	}
	//reset and assign new value
	//takes ownership of pointer.
	void reset(T* p){
		this->c = std::make_shared<Copier_t<T>>();
		this->p = p;
	}
	//reset and assign new value.
	//takes ownership of pointer.
	template<class U>
	void reset(U* p){
		b_assert(Util::instanceof<T, U>());
		this->c = std::make_shared<Copier_t<U>>();
		this->p = (T*) p;
	}
	//reset and assign new value
	void reset(const c_ptr<T>& other){ 
		this->c = std::make_shared<Copier_t<T>>();
		this->p = (T*) other.makeCopy();
	}
	//reset and assign new value
	template<class U>
	void reset(const c_ptr<U>& other){ 
		b_assert(Util::instanceof<T, U>());
		this->c = std::make_shared<Copier_t<U>>();
		this->p = (T*) other.makeCopy();
	}
	//reset and assign new value
	//copies val
	void reset(T val){ 
		this->c = std::make_shared<Copier_t<T>>();
		this->p = (T*) c->makeCopy(&val);
	}
	//reset and assign new value
	//copies val
	template<class U>
	void reset(U val){ 
		this->c = std::make_shared<Copier_t<U>>();
		this->p = (U*) c->makeCopy(&val);
	}

	~c_ptr(){ 
		reset();
	}

	T* operator->(){ 
		assert(!isNull());
		return(p); 
	}
	T& operator*(){ 
		assert(!isNull());
		return(*p); 
	}

	void operator=(const c_ptr<T>& other){
		reset(other);
	}

	bool isNull(){ return(p == nullptr); }

public:
	void* makeCopy() const {
		assert(p != nullptr);
		return(c->makeCopy(p));
	}
};

template<class T, class ... Ts>
c_ptr<T> make_c(Ts ... ts){
	return(c_ptr<T>(new T(ts ...)));
}


/*//example
void test(c_ptr<Base> v){
	v->n++;
	v->v();
}
int main(){
	c_ptr<Base> b0;
	c_ptr<Base> b3(new Derived(3));
	b3->v();
	test(b3);
	b3->v();
	//
	c_ptr<Base> b4 = b3;
	b4->n+=2;
	b4->v();
	//
	c_ptr<Base> b5 = make_c<Base>(9);
	c_ptr<Base> b6 = make_c<Derived>(99);
	b5->v();
	b6->v();
	test(b5);
	//b5.reset(new Base(66));
	//b5.reset(new Derived(66));
	b5.reset(b5);
	b5->v();
	test(b6);
	//
	//shared_ptr<Base>(new Derived(6));
	//
	c_ptr<Base> d_copy(Derived(42));
	c_ptr<Base> b_copy(Base(42));
	b_copy->v();
}*/

}

#endif









































































/*

#include <memory>

template<class T>
class clone_ptr : public shared_ptr<T>{
public:
	//copy constructor
	clone_ptr() : 
		shared_ptr<T>() {}
	clone_ptr(const clone_ptr<T>& original) : 
		shared_ptr<T>(new T(original.get())) {}
	clone_ptr(T* ptr) : 
		shared_ptr<T>(ptr) {}
};

template<class T>
using c_ptr = clone_ptr<T>;

*/