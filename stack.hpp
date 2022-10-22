/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:58:10 by seseo             #+#    #+#             */
/*   Updated: 2022/10/23 00:54:25 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __STACK_H__
#define __STACK_H__

#include "vector.hpp"

namespace ft {

template <class T, class Container = vector<T> >
class stack;

template <class T, class Container>
class stack {
   public:
	typedef Container                                container_type;
	typedef typename container_type::value_type      value_type;
	typedef typename container_type::reference       reference;
	typedef typename container_type::const_reference const_reference;
	typedef typename container_type::size_type       size_type;

   protected:
	container_type c;

   public:
	explicit stack( const container_type& ctnr = container_type() );
	stack( const stack& other );
	~stack();
	stack& operator=( const stack& other );

	bool              empty() const;
	void              pop();
	void              push( const value_type& val );
	size_type         size() const;
	value_type&       top();
	const value_type& top() const;

	template <class T1, class C1>
	friend bool operator==( const stack<T1, C1>& lhs,
							const stack<T1, C1>& rhs );

	template <class T1, class C1>
	friend bool operator<( const stack<T1, C1>& lhs, const stack<T1, C1>& rhs );
};

template <class T, class Container>
bool operator==( const stack<T, Container>& lhs,
				 const stack<T, Container>& rhs ) {
	return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=( const stack<T, Container>& lhs,
				 const stack<T, Container>& rhs ) {
	return !( lhs == rhs );
}

template <class T, class Container>
bool operator<( const stack<T, Container>& lhs,
				const stack<T, Container>& rhs ) {
	return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator<=( const stack<T, Container>& lhs,
				 const stack<T, Container>& rhs ) {
	return !( rhs < lhs );
}

template <class T, class Container>
bool operator>( const stack<T, Container>& lhs,
				const stack<T, Container>& rhs ) {
	return rhs < lhs;
}

template <class T, class Container>
bool operator>=( const stack<T, Container>& lhs,
				 const stack<T, Container>& rhs ) {
	return !( lhs < rhs );
}

template <class T, class Container>
bool stack<T, Container>::empty() const {
	return c.size() == 0;
}

template <class T, class Container>
void stack<T, Container>::pop() {
	c.pop_back();
}

template <class T, class Container>
void stack<T, Container>::push( const value_type& val ) {
	c.push_back( val );
}

template <class T, class Container>
typename stack<T, Container>::size_type stack<T, Container>::size() const {
	return c.size();
}

template <class T, class Container>
typename stack<T, Container>::value_type& stack<T, Container>::top() {
	return c.back();
}

template <class T, class Container>
const typename stack<T, Container>::value_type& stack<T, Container>::top()
	const {
	return c.back();
}

// Constructor, Destructor, Copy Assignment
template <class T, class Container>
stack<T, Container>::stack(
	const typename stack<T, Container>::container_type& ctnr )
	: c( ctnr ) {
}

template <class T, class Container>
stack<T, Container>::stack( const stack<T, Container>& other ) : c( other.c ) {
}

template <class T, class Container>
stack<T, Container>::~stack() {
}

template <class T, class Container>
stack<T, Container>& stack<T, Container>::operator=( const stack& other ) {
	if ( this != &other ) {
		this->c = other.c;
	}
	return *this;
}

}  // namespace ft

#endif
