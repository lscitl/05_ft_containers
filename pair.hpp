/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 23:26:30 by seseo             #+#    #+#             */
/*   Updated: 2022/09/30 00:44:17 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __PAIR_H__
#define __PAIR_H__

namespace ft {

template <class T1, class T2>
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;

	first_type  first;
	second_type second;

	// Constructor
	pair();
	template <class U, class V>
	pair( const pair<U, V>& pr );
	pair( const first_type& a, const second_type& b );

	// Assignment operator
	pair& operator=( const pair& pr );
};

// Constructor
template <class T1, class T2>
pair<T1, T2>::pair() : first(), second() {
}

template <class T1, class T2>
template <class U, class V>
pair<T1, T2>::pair( const pair<U, V>& pr )
	: first( pr.first ), second( pr.second ) {
}

template <class T1, class T2>
pair<T1, T2>::pair( const first_type& a, const second_type& b )
	: first( a ), second( b ) {
}

// Assignment operator
template <class T1, class T2>
pair<T1, T2>& pair<T1, T2>::operator=( const pair<T1, T2>& pr ) {
	first = pr.first;
	second = pr.second;
	return *this;
}

// Comparison operator
template <class T1, class T2>
bool operator==( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return ( lhs.first == rhs.first ) && ( lhs.second == rhs.second );
}

template <class T1, class T2>
bool operator!=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return !( lhs == rhs );
}

template <class T1, class T2>
bool operator<( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return lhs.first < rhs.first ||
		   ( !( rhs.first < lhs.first ) && lhs.second < rhs.second );
}

template <class T1, class T2>
bool operator<=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return !( rhs < lhs );
}

template <class T1, class T2>
bool operator>( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return rhs < lhs;
}

template <class T1, class T2>
bool operator>=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return !( lhs < rhs );
}

template <class T1, class T2>
pair<T1, T2> make_pair( T1 t, T2 u ) {
	return pair<T1, T2>( t, u );
}

template <typename T>
class is_pair {
	typedef char yes[1];
	typedef struct {
		char x[2];
	} no;
	template <typename C>
	static yes& test( typename C::first_type = 0, typename C::second_type = 0 );

	template <typename C>
	static no& test( ... );

   public:
	static bool const value = sizeof( test<T>( 0, 0 ) ) == sizeof( yes );
};

}  // namespace ft

#endif
