/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:22:31 by seseo             #+#    #+#             */
/*   Updated: 2022/09/07 23:40:41 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iterator>
#include <utility>
#include <memory>
#include <climits>
#include <limits>
#include <stdexcept>
#include <algorithm>

// public:
// typedef _Allocator allocator_type;
// typedef allocator_traits<allocator_type> __alloc_traits;
// typedef typename __alloc_traits::size_type size_type;

// protected:
// typedef _Tp value_type;
// typedef value_type& reference;
// typedef const value_type& const_reference;
// typedef typename __alloc_traits::difference_type difference_type;
// typedef typename __alloc_traits::pointer pointer;
// typedef typename __alloc_traits::const_pointer const_pointer;
// typedef pointer iterator;
// typedef const_pointer const_iterator;

// namespace ft {

// template <class T, class Allocator = std::allocator<T> >
// // template <class _Tp, class _Allocator>
// class vector {
//    public:
// 	typedef T value_type;
// 	typedef Allocator allocator_type;

// 	typedef typename allocator_type::reference reference;
// 	typedef typename allocator_type::const_reference const_reference;
// 	typedef typename allocator_type::size_type size_type;
// 	typedef typename allocator_type::difference_type difference_type;
// 	typedef typename allocator_type::pointer pointer;
// 	typedef typename allocator_type::const_pointer const_pointer;
// 	typedef pointer iterator;
// 	typedef const_pointer const_iterator;

// 	// typedef std::reverse_iterator<iterator> reverse_iterator;
// 	// typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

// 	vector()( is_nothrow_default_constructible<allocator_type>::value );
// 	explicit vector( const allocator_type& );
// 	explicit vector( size_type n );
// 	vector( size_type n, const value_type& value,
// 			const allocator_type& = allocator_type() );
// 	template <class InputIterator>
// 	vector( InputIterator first, InputIterator last,
// 			const allocator_type& = allocator_type() );
// 	vector( const vector& x );
// 	vector( vector&& x )(
// 		is_nothrow_move_constructible<allocator_type>::value );
// 	vector( initializer_list<value_type> il );
// 	vector( initializer_list<value_type> il, const allocator_type& a );
// 	~vector();

// 	vector& operator=( const vector& x );
// 	vector& operator=( initializer_list<value_type> il );

// 	template <class InputIterator>
// 	void assign( InputIterator first, InputIterator last );
// 	void assign( size_type n, const value_type& u );

// 	allocator_type get_allocator() const;

// 	iterator begin();
// 	const_iterator begin() const;

// 	iterator end();
// 	const_iterator end() const;

// 	reverse_iterator rbegin();
// 	const_reverse_iterator rbegin() const;

// 	reverse_iterator rend();
// 	const_reverse_iterator rend() const;

// 	size_type size() const;
// 	size_type max_size() const;

// 	size_type capacity() const;

// 	bool empty() const;
// 	void reserve( size_type n );
// 	void shrink_to_fit();

// 	reference operator[]( size_type n );
// 	const_reference operator[]( size_type n ) const;

// 	reference at( size_type n );
// 	const_reference at( size_type n ) const;

// 	reference front();
// 	const_reference front() const;

// 	reference back();
// 	const_reference back() const;

// 	value_type* data();
// 	const value_type* data() const;

// 	void push_back( const value_type& x );
// 	void push_back( value_type&& x );
// 	template <class... Args>
// 	void pop_back();

// 	template <class... Args>
// 	iterator emplace( const_iterator position, Args&&... args );
// 	iterator insert( const_iterator position, const value_type& x );
// 	iterator insert( const_iterator position, value_type&& x );
// 	iterator insert( const_iterator position, size_type n,
// 					 const value_type& x );

// 	template <class InputIterator>
// 	iterator insert( const_iterator position, InputIterator first,
// 					 InputIterator last );
// 	iterator insert( const_iterator position, initializer_list<value_type> il );

// 	iterator erase( const_iterator position );
// 	iterator erase( const_iterator first, const_iterator last );

// 	void clear();

// 	void resize( size_type sz );
// 	void resize( size_type sz, const value_type& c );

// 	void swap( vector& x );

// 	bool __invariants() const;
// };
// };  // namespace ft

namespace ft {

template <class Iter>
struct iterator_traits {
	typedef Iter::difference_type   difference_type;
	typedef Iter::value_type        value_type;
	typedef Iter::pointer           pointer;
	typedef Iter::reference         reference;
	typedef Iter::iterator_category iterator_category;
};

template <class _Tp>
struct iterator_traits<_Tp*> {
	typedef std::ptrdiff_t                  difference_type;
	typedef _Tp                             value_type;
	typedef const _Tp*                      pointer;
	typedef const _Tp&                      reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template <class Iter>
class __vector_iterator {
   public:
	typedef Iter                                         iterator_type;
	typedef ft::iterator_traits<Iter>::iterator_category iterator_category;
	typedef ft::iterator_traits<Iter>::value_type        value_type;
	typedef ft::iterator_traits<Iter>::difference_type   difference_type;
	typedef ft::iterator_traits<Iter>::pointer           pointer;
	typedef ft::iterator_traits<Iter>::reference         reference;

	__vector_iterator();
	explicit __vector_iterator( iterator_type it );

	template <class Iter>
	__vector_iterator( const reverse_iterator<Iter>& rev_it );
};
namespace ft {
template <class _T, _Allocator = std::allocator<T> >
class vector {};
};  // namespace ft

#endif
