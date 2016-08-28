/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_D_ITER_INCLUDED
#define DCG_D_ITER_INCLUDED

#include "dcg/types/c_ptr.hpp"

namespace dcg{

//an interface to an iterator of any type.
class AnyIter{
public:
	const size_t typeSize;

public:
	AnyIter(size_t typeSize) : typeSize(typeSize) {}

	virtual void* get(){
		assert(false);
		return(NULL);
	}
	void set(void* data){
		memmove(get(), data, typeSize);
	}

	virtual AnyIter* operator+(size_t n){
		assert(false);//NOP
	}
	virtual bool operator ==(const AnyIter& other){
		assert(false);//NOP
		return(false);
	}
	virtual bool operator !=(const AnyIter& other){
		assert(false);//NOP
		return(false);
	}
};


//T should be an iterator type.
template<class IterType>
class AnyIter_t : public AnyIter{
public:
	IterType it;

public:
	AnyIter_t(IterType it) : 
		AnyIter(sizeof(std::iterator_traits<IterType>::value_type)) ,
		it(it)
	{}

	virtual void* get(){
		return(&*it);
	}
	virtual AnyIter* operator+(size_t n){
		return(new AnyIter_t(it + n));
	}
	virtual bool operator ==(const AnyIter& other){
		return(it == ((AnyIter_t<IterType> *) &other)->it);
	}
	virtual bool operator !=(const AnyIter& other){
		return(it == ((AnyIter_t<IterType> *) &other)->it);
	}
};


template<class ValueType>
class AnyIter_Single : public AnyIter{
	ValueType* p;
	size_t n;

public:
	AnyIter_Single(ValueType* p, size_t n = 0) : 
		AnyIter(sizeof(ValueType)),
		p(p),
		n(n)
	{}

	void* get(){ 
		return(p); 
	}

	virtual AnyIter* operator+(size_t n){
		return(new AnyIter_Single<ValueType>(*this, this->n + n));
	}

	virtual bool operator ==(const AnyIter& other){ 
		return(
			(p==((AnyIter_Single<ValueType>*) &other)->p) && 
			(n==((AnyIter_Single<ValueType>*) &other)->n)
		); 
	}
	virtual bool operator !=(const AnyIter& other){ 
		return(! (*this == other));
	}
};




class DIter{
	c_ptr<AnyIter> it;	

public:
	DIter(AnyIter* it) : it(it) {}

	void* get(){ 
		return(it->get()); 
	}

	void set(void* data){ 
		it->set(data); 
	}

	DIter operator+(size_t n){
		return(DIter((*it + n)));
	}

	bool operator ==(DIter& other){
		return(*it == *(other.it));
	}

	bool operator !=(DIter& other){
		return(*it != *(other.it));
	}
};


}

#endif














/*


//an interface to an iterator of any type.
class AnyIter : Copyable{
public:
	const size_t typeSize;

public:
	AnyIter(size_t typeSize) : typeSize(typeSize) {}

	DValue operator*(){ return(DValue(typeSize, getPtr())); }

	virtual void* makeCopy(){
		assert(false);//NOP
		return(NULL);
	}

	virtual AnyIter* operator+(size_t n){
		assert(false);//NOP
	}
	virtual bool operator ==(const AnyIter& other){
		assert(false);//NOP
		return(false);
	}
	virtual bool operator !=(const AnyIter& other){
		assert(false);//NOP
		return(false);
	}

private:
	virtual void* getPtr(){
		assert(false);
		return(NULL);
	}
};


//T should be an iterator type.
template<class IterType>
class AnyIter_t : public AnyIter{
public:
	IterType it;

public:
	AnyIter_t(IterType it) : 
		AnyIter(sizeof(std::iterator_traits<IterType>::value_type)) ,
		it(it)
	{}
	
	virtual AnyIter_t* makeCopy(){
		return(new AnyIter_t(*this));
	}

	virtual AnyIter* operator+(size_t n){
		return(new AnyIter_t(it + n));
	}
	virtual bool operator ==(const AnyIter& other){
		return(it == ((AnyIter_t<IterType> *) &other)->it);
	}
	virtual bool operator !=(const AnyIter& other){
		return(it == ((AnyIter_t<IterType> *) &other)->it);
	}

private:
	virtual void* getPtr(){
		return(it.get());
	}
};


class DIter{
	c_ptr<AnyIter> it;	

public:
	DIter(AnyIter* it) : it(it) {}

	void* get(){ return(
	DIter operator+(size_t n){
		return(DIter(new AnyIter(*it + n)));
	}
	bool operator ==(const DIter& other){
		return(c_ptr<AnyIter>::operator*() == *other.it));
	}
	bool operator !=(const DIter& other){
		return(c_ptr<AnyIter>::operator*() != *(other.it));
	}
};









   
   DValue operator*(){ 
		return(*it);
	}
   
   
   
   
   template<class T>
class BasicIter : public VoidIter{
	typedef iterator<std::forward_iterator_tag, T> IterType;
	IterType it;

public:
	BasicIter(IterType it) : VoidIter() {
		this->it = it;
	}

	virtual void* get(){
		return(&(*it));
	}

	virtual shared_ptr<VoidIter> operator+(size_t n){
		return(make_shared<BasicIter>(it + n));
	}
};*/



/*template<class IterType>
class BasicIter : public VoidIter{
	IterType it;

public:
	BasicIter(IterType it) : 
		VoidIter(sizeof(std::iterator_traits<IterType>::value_type)) ,
		it(it)
	{}

	virtual void* get(){
		return(&(*it));
	}

	virtual shared_ptr<VoidIter> operator+(size_t n){
		return(make_shared<BasicIter>(it + n));
	}
};











*/
