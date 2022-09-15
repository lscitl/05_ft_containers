/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:22:31 by seseo             #+#    #+#             */
/*   Updated: 2022/09/16 00:22:29 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <utility>
#include <memory>
#include <climits>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

template <class T>
class vector_iterator {
   public:
	typedef typename iterator_traits<T*>::value_type        value_type;
	typedef typename iterator_traits<T*>::pointer           pointer;
	typedef typename iterator_traits<T*>::reference         reference;
	typedef typename iterator_traits<T*>::difference_type   difference_type;
	typedef typename iterator_traits<T*>::iterator_category iterator_category;

   protected:
	pointer _current;

   public:
	vector_iterator() : _current( NULL ) {
	}

	explicit vector_iterator( pointer x ) : _current( x ) {
	}

	template <class U>
	vector_iterator( const vector_iterator<U>& u ) : _current( u.base() ) {
	}

	template <class U>
	vector_iterator& operator=( const vector_iterator<U>& u ) {
		_current = u.base();
		return *this;
	}

	pointer base() const {
		return _current;
	};

	reference operator*() const {
		return *_current;
	}

	pointer operator->() const {
		return &( operator*() );
	}

	vector_iterator& operator++() {
		++_current;
		return *this;
	}

	vector_iterator operator++( int ) {
		vector_iterator ret( *this );
		++_current;
		return ret;
	}

	vector_iterator& operator--() {
		--_current;
		return *this;
	}

	vector_iterator operator--( int ) {
		vector_iterator ret( *this );
		--_current;
		return ret;
	}

	vector_iterator operator+( difference_type n ) const {
		return vector_iterator( _current + n );
	}

	vector_iterator& operator+=( difference_type n ) {
		_current += n;
		return *this;
	}

	vector_iterator operator-( difference_type n ) const {
		return vector_iterator( _current - n );
	}

	vector_iterator& operator-=( difference_type n ) {
		_current -= n;
		return *this;
	}

	reference operator[]( difference_type n ) const {
		return this->base()[n];
	}
};

template <class Iterator>
vector_iterator<Iterator> operator+(
	typename vector_iterator<Iterator>::difference_type n,
	const vector_iterator<Iterator>&                    iter ) {
	return iter + n;
}

template <class Iterator1, class Iterator2>
typename vector_iterator<Iterator1>::difference_type operator-(
	const vector_iterator<Iterator1>& lhs,
	const vector_iterator<Iterator2>& rhs ) {
	return lhs.base() - rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator==( const ft::vector_iterator<Iterator1>& lhs,
				 const ft::vector_iterator<Iterator2>& rhs ) {
	return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=( const ft::vector_iterator<Iterator1>& lhs,
				 const ft::vector_iterator<Iterator2>& rhs ) {
	return lhs.base() != rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<( const ft::vector_iterator<Iterator1>& lhs,
				const ft::vector_iterator<Iterator2>& rhs ) {
	return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=( const ft::vector_iterator<Iterator1>& lhs,
				 const ft::vector_iterator<Iterator2>& rhs ) {
	return lhs.base() <= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>( const ft::vector_iterator<Iterator1>& lhs,
				const ft::vector_iterator<Iterator2>& rhs ) {
	return lhs.base() > rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=( const ft::vector_iterator<Iterator1>& lhs,
				 const ft::vector_iterator<Iterator2>& rhs ) {
	return lhs.base() >= rhs.base();
}

template <class T, class Allocator = std::allocator<T> >
class vector {
   public:
	typedef Allocator                               allocator_type;
	typedef typename allocator_type::size_type      size_type;
	typedef T                                       value_type;
	typedef value_type&                             reference;
	typedef const value_type&                       const_reference;
	typedef typename allocator_type::pointer        pointer;
	typedef typename allocator_type::const_pointer  const_pointer;
	typedef typename ft::vector_iterator<T>         iterator;
	typedef typename ft::vector_iterator<const T>   const_iterator;
	typedef typename ft::reverse_iterator<iterator> reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>
													 const_reverse_iterator;
	typedef typename allocator_type::difference_type difference_type;

   protected:
	pointer        _begin;
	pointer        _end;
	pointer        _end_cap;
	allocator_type _alloc;

	void      vec_allocate( size_type n );
	void      vec_reallocate( size_type n );
	size_type recommand_size( size_type n ) const;
	pointer range_construct( pointer start, pointer end, const_reference val );

   public:
	// Constructor, Copy Assignment Operator, Destructor
	explicit vector( const allocator_type& alloc = allocator_type() );
	explicit vector( size_type n, const_reference val = value_type(),
					 const allocator_type& alloc = allocator_type() );
	template <class InputIterator>
	vector( InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
			typename enable_if<!is_integral<InputIterator>::value,
							   InputIterator>::type* = 0 );
	vector( const vector& x );
	~vector();
	vector& operator=( const vector& x );

	// Capacity
	void      resize( size_type n, value_type val = value_type() );
	void      reserve( size_type n );
	size_type max_size( void ) const {
		return std::min<size_type>(
			_alloc.max_size(), std::numeric_limits<difference_type>::max() );
	}
	size_type size( void ) const {
		return static_cast<size_type>( _end - _begin );
	}
	size_type capacity( void ) const {
		return static_cast<size_type>( _end_cap - _begin );
	}
	bool empty() const {
		return this->size() == size_type( 0 );
	}

	// Element access
	reference       operator[]( size_type n );
	const_reference operator[]( size_type n ) const;
	reference       at( size_type n );
	const_reference at( size_type n ) const;
	reference       front();
	const_reference front() const;
	reference       back();
	const_reference back() const;

	// Modifier
	template <class InputIterator>
	void     assign( InputIterator first, InputIterator last,
					 typename enable_if<!is_integral<InputIterator>::value,
                                    InputIterator>::type* = 0 );
	void     assign( size_type n, const_reference val );
	void     push_back( const_reference val );
	void     pop_back();
	iterator insert( iterator position, const_reference val );
	void     insert( iterator position, size_type n, const_reference val );
	template <class InputIterator>
	void     insert( iterator position, InputIterator first, InputIterator last,
					 typename enable_if<!is_integral<InputIterator>::value,
                                    InputIterator>::type* = 0 );
	iterator erase( iterator position );
	iterator erase( iterator first, iterator last );
	void     swap( vector& x );
	void     clear();

	// Allocator
	allocator_type get_allocator() const {
		return _alloc;
	}

	// Iterators
	iterator begin() {
		iterator ret( _begin );
		return ret;
	}
	const_iterator begin() const {
		const_iterator ret( _begin );
		return ret;
	}
	iterator end() {
		return iterator( _end );
	}
	const_iterator end() const {
		return const_iterator( _end );
	}
	reverse_iterator rbegin() {
		return reverse_iterator( this->end() );
	}
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator( this->end() );
	}
	reverse_iterator rend() {
		return reverse_iterator( this->begin() );
	}
	const_reverse_iterator rend() const {
		return const_reverse_iterator( this->begin() );
	}
};

template <class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::recommand_size(
	size_type n ) const {
	const size_type ms = this->max_size();
	if ( ms < n )
		throw std::length_error( "vector: length error" );
	const size_type cp = this->capacity();
	if ( cp > ms / 2 )
		return ms;
	return std::max<size_type>( cp * 2, n );
}

template <class T, class Allocator>
void vector<T, Allocator>::vec_allocate( size_type n ) {
	if ( n > max_size() )
		throw std::length_error( "vector: length error" );
	_begin = _end = _alloc.allocate( n );
	_end_cap = _begin + n;
}

template <class T, class Allocator>
void vector<T, Allocator>::vec_reallocate( size_type n ) {
	if ( n > max_size() )
		throw std::length_error( "vector: length error" );

	pointer   tmp_begin, tmp_end, tmp_end_cap;
	size_type origin_size = this->size();

	tmp_begin = tmp_end = _alloc.allocate( n );
	tmp_end_cap = tmp_begin + n;
	for ( size_type i = 0; i < origin_size; ++i ) {
		_alloc.construct( tmp_end++, _begin[i] );
		_alloc.destroy( &_begin[i] );
	}
	if ( _begin )
		_alloc.deallocate( _begin, _end_cap - _begin );
	_begin = tmp_begin;
	_end = tmp_end;
	_end_cap = tmp_end_cap;
}

template <class T, class Allocator>
typename vector<T, Allocator>::pointer vector<T, Allocator>::range_construct(
	pointer start, pointer end, const_reference val ) {
	for ( ; start != end; ++start ) {
		_alloc.construct( start, val );
	}
	return end;
}

template <class T, class Allocator>
void vector<T, Allocator>::resize( size_type n, value_type val ) {
	if ( this->size() >= n ) {
		for ( ; _end != _begin + n; --_end ) {
			_alloc.destroy( _end );
		}
	} else {
		if ( this->capacity() < n ) {
			this->vec_reallocate( this->recommand_size( n ) );
		}
		for ( ; this->size() != n; ++_end ) {
			_alloc.construct( _end, val );
		}
	}
}

template <class T, class Allocator>
void vector<T, Allocator>::reserve( size_type n ) {
	if ( this->capacity() < n ) {
		vec_reallocate( n );
	}
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](
	size_type n ) {
	return _begin[n];
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](
	size_type n ) const {
	return _begin[n];
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(
	size_type n ) {
	if ( n >= this->size() )
		throw std::out_of_range( "vector: out of range" );
	return _begin[n];
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(
	size_type n ) const {
	if ( n >= this->size() )
		throw std::out_of_range( "vector: out of range" );
	return _begin[n];
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::front() {
	return *_begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front()
	const {
	return *_begin;
}

template <class T, class Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::back() {
	return *( _end - 1 );
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back()
	const {
	return *( _end - 1 );
}

template <class T, class Allocator>
template <class InputIterator>
void vector<T, Allocator>::assign(
	InputIterator first, InputIterator last,
	typename enable_if<!is_integral<InputIterator>::value,
					   InputIterator>::type* ) {
	this->clear();
	size_type input_len = ft::distance( first, last );
	if ( this->capacity() < input_len ) {
		this->vec_reallocate( recommand_size( input_len ) );
	}
	for ( ; first != last; ++first ) {
		_alloc.construct( _end, *first );
		++_end;
	}
}

template <class T, class Allocator>
void vector<T, Allocator>::assign( size_type n, const_reference val ) {
	this->clear();
	if ( this->capacity() < n ) {
		this->vec_reallocate( recommand_size( n ) );
	}
	_end = this->range_construct( _end, _end + n, val );
}

template <class T, class Allocator>
void vector<T, Allocator>::push_back( const_reference val ) {
	if ( !this->capacity() ) {
		this->reserve( 1 );
	} else if ( this->capacity() == this->size() ) {
		this->vec_reallocate( recommand_size( this->size() + 1 ) );
	}
	_alloc.construct( _end, val );
	++_end;
}

template <class T, class Allocator>
void vector<T, Allocator>::pop_back() {
	_alloc.destroy( _end-- );
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
	iterator position, const_reference val ) {
	size_type pos_index = position.base() - _begin;
	if ( this->capacity() == this->size() ) {
		size_type n = recommand_size( this->capacity() + 1 );
		if ( n > max_size() )
			throw std::length_error( "vector: length error" );

		pointer tmp_begin, tmp_end, tmp_end_cap;

		tmp_begin = tmp_end = _alloc.allocate( n );
		tmp_end_cap = tmp_begin + n;
		pointer p( _begin );
		for ( ; tmp_end != tmp_begin + pos_index; ++tmp_end, ++p ) {
			_alloc.construct( tmp_end, *( p ) );
			_alloc.destroy( p );
		}
		_alloc.construct( tmp_end++, val );
		for ( ; p != _end; ++tmp_end, ++p ) {
			_alloc.construct( tmp_end, *( p ) );
			_alloc.destroy( p );
		}
		if ( _begin )
			_alloc.deallocate( _begin, _end_cap - _begin );
		_begin = tmp_begin;
		_end = tmp_end;
		_end_cap = tmp_end_cap;
	} else {
		pointer p = position.base();
		for ( pointer tmp( _end ); p != tmp; --tmp ) {
			_alloc.construct( tmp, tmp[-1] );
			_alloc.destroy( &tmp[-1] );
		}
		_alloc.construct( p, val );
		++_end;
	}
	return position;
}

template <class T, class Allocator>
void vector<T, Allocator>::insert( iterator position, size_type n,
								   const_reference val ) {
	size_type pos_index = position.base() - _begin;
	if ( this->capacity() < this->size() + n ) {
		size_type rec_size = recommand_size( this->size() + n );
		if ( rec_size > max_size() )
			throw std::length_error( "vector: length error" );

		pointer tmp_begin, tmp_end, tmp_end_cap;

		tmp_begin = tmp_end = _alloc.allocate( rec_size );
		tmp_end_cap = tmp_begin + rec_size;
		pointer p( _begin );
		for ( ; tmp_end != tmp_begin + pos_index; ++tmp_end, ++p ) {
			_alloc.construct( tmp_end, *( p ) );
			_alloc.destroy( p );
		}
		tmp_end = this->range_construct( tmp_end, tmp_end + n, val );
		for ( ; p != _end; ++tmp_end, ++p ) {
			_alloc.construct( tmp_end, *( p ) );
			_alloc.destroy( p );
		}
		if ( _begin )
			_alloc.deallocate( _begin, _end_cap - _begin );
		_begin = tmp_begin;
		_end = tmp_end;
		_end_cap = tmp_end_cap;
	} else {
		pointer tmp_end = _end;
		pointer tmp_cpy_end = tmp_end + n - 1;
		for ( ; tmp_end != position.base(); --tmp_cpy_end, --tmp_end ) {
			_alloc.construct( tmp_cpy_end, tmp_end[-1] );
			_alloc.destroy( &tmp_end[-1] );
		}
		this->range_construct( position.base(), position.base() + n, val );
		_end += n;
	}
}

template <class T, class Allocator>
template <class InputIterator>
void vector<T, Allocator>::insert(
	iterator position, InputIterator first, InputIterator last,
	typename enable_if<!is_integral<InputIterator>::value,
					   InputIterator>::type* ) {
	difference_type input_len = ft::distance( first, last );
	size_type       pos_index = position.base() - _begin;
	if ( this->capacity() < this->size() + input_len ) {
		size_type rec_size = recommand_size( this->size() + input_len );
		if ( rec_size > max_size() )
			throw std::length_error( "vector: length error" );

		pointer tmp_begin, tmp_end, tmp_end_cap;

		tmp_begin = tmp_end = _alloc.allocate( rec_size );
		tmp_end_cap = tmp_begin + rec_size;
		pointer p( _begin );
		for ( ; tmp_end != tmp_begin + pos_index; ++tmp_end, ++p ) {
			_alloc.construct( tmp_end, *( p ) );
			_alloc.destroy( p );
		}
		tmp_end = std::copy( first, last, tmp_end );
		for ( ; p != _end; ++tmp_end, ++p ) {
			_alloc.construct( tmp_end, *( p ) );
			_alloc.destroy( p );
		}
		if ( _begin )
			_alloc.deallocate( _begin, _end_cap - _begin );
		_begin = tmp_begin;
		_end = tmp_end;
		_end_cap = tmp_end_cap;
	} else {
		pointer tmp_end = _end;
		pointer tmp_cpy_end = tmp_end + input_len - 1;
		for ( ; tmp_end != position.base(); --tmp_cpy_end, --tmp_end ) {
			_alloc.construct( tmp_cpy_end, tmp_end[-1] );
			_alloc.destroy( &tmp_end[-1] );
		}
		std::copy( first, last, position );
		_end += input_len;
	}
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(
	iterator position ) {
	_alloc.destroy( position.base() );
	for ( pointer tmp = position.base(); tmp < _end - 1; ++tmp ) {
		_alloc.construct( tmp, *( tmp + 1 ) );
		_alloc.destroy( tmp + 1 );
	}
	--_end;
	return position;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(
	iterator first, iterator last ) {
	size_type del_len = static_cast<size_type>( last.base() - first.base() );
	size_type move_len = static_cast<size_type>( _end - last.base() );
	for ( pointer tmp = first.base(); tmp < last.base(); ++tmp ) {
		_alloc.destroy( tmp );
		if ( move_len ) {
			_alloc.construct( tmp, tmp[del_len] );
			_alloc.destroy( tmp - del_len );
			--move_len;
		}
	}
	pointer tmp = last.base();
	while ( move_len ) {
		_alloc.construct( tmp, tmp[del_len] );
		_alloc.destroy( tmp - del_len );
		++tmp;
		--move_len;
	}
	_end -= del_len;
	return first;
}

template <class T, class Allocator>
void vector<T, Allocator>::swap( vector& x ) {
	pointer tmp_begin = x._begin;
	pointer tmp_end = x._end;
	pointer tmp_end_cap = x._end_cap;

	x._begin = _begin;
	x._end = _end;
	x._end_cap = _end_cap;
	_begin = tmp_begin;
	_end = tmp_end;
	_end_cap = tmp_end_cap;
}

template <class T, class Allocator>
void vector<T, Allocator>::clear() {
	while ( _begin != _end ) {
		_alloc.destroy( _end-- );
	}
}

// Constructor
template <class T, class Allocator>
vector<T, Allocator>::vector( const allocator_type& alloc )
	: _begin( NULL ), _end( NULL ), _end_cap( NULL ), _alloc( alloc ) {
}

template <class T, class Allocator>
vector<T, Allocator>::vector( size_type n, const_reference val,
							  const allocator_type& alloc )
	: _begin( NULL ), _end( NULL ), _end_cap( NULL ), _alloc( alloc ) {
	if ( n > 0 ) {
		vec_allocate( n );
		for ( size_type i = 0; i < n; ++i ) {
			_alloc.construct( _end, val );
			++_end;
		}
	}
}

template <class T, class Allocator>
template <class InputIterator>
vector<T, Allocator>::vector(
	InputIterator first, InputIterator last, const allocator_type& alloc,
	typename enable_if<!is_integral<InputIterator>::value,
					   InputIterator>::type* )
	: _begin( NULL ), _end( NULL ), _end_cap( NULL ), _alloc( alloc ) {
	size_type input_len = static_cast<size_type>( ft::distance( first, last ) );

	vec_allocate( input_len );
	for ( ; first != last; ++first ) {
		_alloc.construct( _end, *first );
		++_end;
	}
}

template <class T, class Allocator>
vector<T, Allocator>::vector( const vector& x )
	: _begin( NULL ), _end( NULL ), _alloc( x._alloc ) {
	size_type n = x.size();
	if ( n > 0 ) {
		vec_allocate( n );
		_end = std::copy( x.begin(), x.end(), this->begin() ).base();
	}
}

template <class T, class Allocator>
vector<T, Allocator>::~vector() {
	if ( _begin ) {
		for ( ; _end != _begin; --_end ) {
			_alloc.destroy( _end - 1 );
		}
		_alloc.deallocate( _begin, _end_cap - _begin );
		_begin = _end = _end_cap = NULL;
	}
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=( const vector& x ) {
	if ( this != &x ) {
		this->clear();
		if ( this->capacity() < x.capacity() ) {
			_alloc.deallocate( _begin, _end_cap - _begin );
			_begin = _end = _end_cap = NULL;
			size_type n = x.size();
			vec_allocate( n );
		}
		_end = std::copy( x.begin(), x.end(), this->begin() ).base();
	}
	return *this;
}

template <class T, class Alloc>
bool operator==( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) {
	if ( lhs.size() != rhs.size() )
		return false;
	vector<T, Alloc>::pointer lbegin, lend, rbegin, rend;
	lbegin = lhs.begin().base();
	lend = lhs.end().base();
	rbegin = rhs.begin().base();
	rend = rhs.end().base();
	for ( ; lbegin != lend; ++lbegin, ++rbegin ) {
		if ( *lbegin != *rbegin )
			return false;
	}
	return true;
}

template <class T, class Alloc>
bool operator!=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs );

template <class T, class Alloc>
bool operator<( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs );
template <class T, class Alloc>
bool operator<=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs );
template <class T, class Alloc>
bool operator>( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs );
template <class T, class Alloc>
bool operator>=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs );

template <class T, class Allocator>
void swap( vector<T, Allocator>& x, vector<T, Allocator>& y ) {
	x.swap( y );
}

};  // namespace ft

#endif
