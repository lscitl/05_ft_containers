/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:22:31 by seseo             #+#    #+#             */
/*   Updated: 2022/09/23 23:08:40 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "lexico_cmp.hpp"
#include "vector_iterator.hpp"

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector {
   public:
	typedef Allocator                                   allocator_type;
	typedef typename allocator_type::size_type          size_type;
	typedef T                                           value_type;
	typedef value_type&                                 reference;
	typedef const value_type&                           const_reference;
	typedef typename allocator_type::pointer            pointer;
	typedef typename allocator_type::const_pointer      const_pointer;
	typedef typename ft::vector_iterator<pointer>       iterator;
	typedef typename ft::vector_iterator<const_pointer> const_iterator;
	typedef typename ft::reverse_iterator<iterator>     reverse_iterator;
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
			typename enable_if<!is_integral<InputIterator>::value &&
								   is_input_iterator<InputIterator>::value &&
								   !is_forward_iterator<InputIterator>::value,
							   InputIterator>::type* = 0 );

	template <class ForwardIterator>
	vector( ForwardIterator first, ForwardIterator last,
			const allocator_type& alloc = allocator_type(),
			typename enable_if<!is_integral<ForwardIterator>::value &&
								   is_forward_iterator<ForwardIterator>::value,
							   ForwardIterator>::type* = 0 );

	vector( const vector& x );
	~vector();
	vector& operator=( const vector& x );

	// Capacity
	void      resize( size_type n, value_type val = value_type() );
	void      reserve( size_type n );
	size_type max_size( void ) const;
	size_type size( void ) const;
	size_type capacity( void ) const;
	bool      empty() const;

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
	void assign(
		InputIterator first, InputIterator last,
		typename enable_if<!is_integral<InputIterator>::value &&
							   is_input_iterator<InputIterator>::value &&
							   !is_forward_iterator<InputIterator>::value,
						   InputIterator>::type* = 0 );

	template <class ForwardIterator>
	void assign(
		ForwardIterator first, ForwardIterator last,
		typename enable_if<!is_integral<ForwardIterator>::value &&
							   is_forward_iterator<ForwardIterator>::value,
						   ForwardIterator>::type* = 0 );

	void assign( size_type n, const_reference val );
	void push_back( const_reference val );
	void pop_back();

	iterator insert( iterator position, const_reference val );
	void     insert( iterator position, size_type n, const_reference val );

	template <class InputIterator>
	void insert(
		iterator position, InputIterator first, InputIterator last,
		typename enable_if<!is_integral<InputIterator>::value &&
							   is_input_iterator<InputIterator>::value &&
							   !is_forward_iterator<InputIterator>::value,
						   InputIterator>::type* = 0 );

	template <class ForwardIterator>
	void insert(
		iterator position, ForwardIterator first, ForwardIterator last,
		typename enable_if<!is_integral<ForwardIterator>::value &&
							   is_forward_iterator<ForwardIterator>::value,
						   ForwardIterator>::type* = 0 );

	iterator erase( iterator position );
	iterator erase( iterator first, iterator last );
	void     swap( vector& x );
	void     clear();

	// Allocator
	allocator_type get_allocator() const;

	// Iterators
	iterator               begin();
	const_iterator         begin() const;
	iterator               end();
	const_iterator         end() const;
	reverse_iterator       rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator       rend();
	const_reverse_iterator rend() const;
};

template <class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::recommand_size(
	size_type n ) const {
	const size_type max_size = this->max_size();
	if ( max_size < n )
		throw std::length_error( "vector: length error" );
	const size_type cap = this->capacity();
	if ( cap > max_size / 2 )
		return max_size;
	return std::max<size_type>( cap * 2, n );
}

template <class T, class Allocator>
void vector<T, Allocator>::vec_allocate( size_type n ) {
	if ( n > this->max_size() )
		throw std::length_error( "vector: length error" );
	if ( n > 0 ) {
		_begin = _end = _alloc.allocate( n );
		_end_cap = _begin + n;
	}
}

template <class T, class Allocator>
void vector<T, Allocator>::vec_reallocate( size_type n ) {
	if ( n > this->max_size() )
		throw std::length_error( "vector: length error" );

	pointer new_begin, new_end, new_end_cap;

	new_begin = new_end = _alloc.allocate( n );
	new_end_cap = new_begin + n;
	for ( pointer tmp = _begin; tmp < _end; ++tmp, ++new_end ) {
		_alloc.construct( new_end, *tmp );
		_alloc.destroy( tmp );
	}
	_alloc.deallocate( _begin, _end_cap - _begin );
	_begin = new_begin;
	_end = new_end;
	_end_cap = new_end_cap;
}

template <class T, class Allocator>
typename vector<T, Allocator>::pointer vector<T, Allocator>::range_construct(
	pointer start, pointer end, const_reference val ) {
	for ( ; start != end; ++start ) {
		_alloc.construct( start, val );
	}
	return end;
}

// Capacity
template <class T, class Allocator>
void vector<T, Allocator>::resize( size_type n, value_type val ) {
	if ( this->size() >= n ) {
		for ( ; _end != _begin + n; ) {
			_alloc.destroy( --_end );
		}
	} else {
		if ( this->capacity() == 0 ) {
			this->vec_allocate( n );
		} else if ( this->capacity() < n ) {
			this->vec_reallocate( this->recommand_size( n ) );
		}
		for ( ; this->size() != n; ++_end ) {
			_alloc.construct( _end, val );
		}
	}
}

template <class T, class Allocator>
void vector<T, Allocator>::reserve( size_type n ) {
	if ( this->capacity() == 0 ) {
		this->vec_allocate( n );
	} else if ( this->capacity() < n ) {
		this->vec_reallocate( n );
	}
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size(
	void ) const {
	return std::min<size_type>( _alloc.max_size(),
								std::numeric_limits<difference_type>::max() );
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::size(
	void ) const {
	return static_cast<size_type>( _end - _begin );
}

template <class T, class Allocator>
typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity(
	void ) const {
	return static_cast<size_type>( _end_cap - _begin );
}

template <class T, class Allocator>
bool vector<T, Allocator>::empty() const {
	return this->size() == size_type( 0 );
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
	typename enable_if<!is_integral<InputIterator>::value &&
						   is_input_iterator<InputIterator>::value &&
						   !is_forward_iterator<InputIterator>::value,
					   InputIterator>::type* ) {
	if ( this->capacity() == 0 ) {
		this->vec_allocate( 1 );
	} else if ( this->size() > 0 ) {
		this->clear();
	}
	for ( ; first != last; ++first ) {
		this->push_back( *first );
	}
}

template <class T, class Allocator>
template <class ForwardIterator>
void vector<T, Allocator>::assign(
	ForwardIterator first, ForwardIterator last,
	typename enable_if<!is_integral<ForwardIterator>::value &&
						   is_forward_iterator<ForwardIterator>::value,
					   ForwardIterator>::type* ) {
	size_type input_len = static_cast<size_type>( ft::distance( first, last ) );
	if ( this->capacity() == 0 ) {
		this->vec_allocate( input_len );
	} else if ( this->capacity() < input_len ) {
		this->vec_reallocate( this->recommand_size( input_len ) );
	}
	if ( this->size() ) {
		this->clear();
	}
	for ( ; first != last; ++first, ++_end ) {
		_alloc.construct( _end, *first );
	}
}

template <class T, class Allocator>
void vector<T, Allocator>::assign( size_type n, const_reference val ) {
	this->clear();
	if ( this->capacity() == 0 ) {
		this->reserve( n );
	} else if ( this->capacity() < n ) {
		this->vec_reallocate( this->recommand_size( n ) );
	}
	_end = this->range_construct( _end, _end + n, val );
}

template <class T, class Allocator>
void vector<T, Allocator>::push_back( const_reference val ) {
	if ( this->capacity() == 0 ) {
		this->reserve( 1 );
	} else if ( this->capacity() == this->size() ) {
		this->vec_reallocate( this->recommand_size( this->size() + 1 ) );
	}
	_alloc.construct( _end++, val );
}

template <class T, class Allocator>
void vector<T, Allocator>::pop_back() {
	_alloc.destroy( --_end );
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
	iterator position, const_reference val ) {
	size_type pos_index = position.base() - _begin;
	iterator  ret;
	if ( this->capacity() == 0 ) {
		this->vec_allocate( 1 );
		ret = iterator( _end );
		_alloc.construct( _end++, val );
	} else if ( this->capacity() == this->size() ) {
		size_type n = this->recommand_size( this->capacity() + 1 );
		if ( n > this->max_size() )
			throw std::length_error( "vector: length error" );

		pointer new_begin, new_end, new_end_cap;

		new_begin = new_end = _alloc.allocate( n );
		new_end_cap = new_begin + n;
		pointer p( _begin );
		for ( ; new_end != new_begin + pos_index; ++new_end, ++p ) {
			_alloc.construct( new_end, *( p ) );
			_alloc.destroy( p );
		}
		ret = iterator( new_end );
		_alloc.construct( new_end++, val );
		for ( ; p != _end; ++new_end, ++p ) {
			_alloc.construct( new_end, *( p ) );
			_alloc.destroy( p );
		}
		_alloc.deallocate( _begin, _end_cap - _begin );
		_begin = new_begin;
		_end = new_end;
		_end_cap = new_end_cap;
	} else {
		pointer p = position.base();
		if ( _end != p ) {
			for ( pointer tmp( _end ); p != tmp; --tmp ) {
				_alloc.construct( tmp, *( tmp - 1 ) );
				_alloc.destroy( tmp - 1 );
			}
		}
		++_end;
		_alloc.construct( p, val );
		ret = position;
	}
	return ret;
}

template <class T, class Allocator>
void vector<T, Allocator>::insert( iterator position, size_type n,
								   const_reference val ) {
	size_type pos_index = position.base() - _begin;
	if ( n == 0 ) {
		return;
	}
	if ( this->capacity() == 0 ) {
		this->vec_allocate( n );
		for ( pointer tmp( _begin + pos_index ),
			  tmp_end( _begin + pos_index + n );
			  tmp != tmp_end; ++tmp, ++_end ) {
			_alloc.construct( tmp, val );
		}
	} else if ( this->capacity() < this->size() + n ) {
		size_type rec_size = this->recommand_size( this->size() + n );
		if ( rec_size > this->max_size() )
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
	typename enable_if<!is_integral<InputIterator>::value &&
						   is_input_iterator<InputIterator>::value &&
						   !is_forward_iterator<InputIterator>::value,
					   InputIterator>::type* ) {
	size_type mov_len = _end - position.base();
	pointer   tmp_begin = _alloc.allocate( mov_len );
	pointer   tmp_end = tmp_begin;
	pointer   tmp_end_cap = tmp_begin + mov_len;

	for ( pointer tmp( position.base() ); tmp != position.base() + mov_len;
		  ++tmp, ++tmp_end ) {
		_alloc.construct( tmp_end, *tmp );
		_alloc.destroy( tmp );
	}
	_end -= mov_len;
	pointer recov_begin( _end );
	try {
		for ( ; first != last; ++first ) {
			this->push_back( *first );
		}
	} catch ( ... ) {
		while ( recov_begin != _end ) {
			_alloc.destroy( --_end );
		}
		for ( pointer tmp( tmp_begin ); tmp != tmp_end; ++tmp, ++_end ) {
			_alloc.construct( _end, *tmp );
			_alloc.destroy( tmp );
		}
		_alloc.deallocate( tmp_begin, tmp_end_cap - tmp_begin );
		throw;
	}
	if ( this->capacity() < this->size() + mov_len ) {
		this->vec_reallocate( this->size() + mov_len );
	}
	for ( pointer tmp( tmp_begin ); tmp != tmp_end; ++tmp, ++_end ) {
		_alloc.construct( _end, *tmp );
		_alloc.destroy( tmp );
	}
	_alloc.deallocate( tmp_begin, tmp_end_cap - tmp_begin );
}

template <class T, class Allocator>
template <class ForwardIterator>
void vector<T, Allocator>::insert(
	iterator position, ForwardIterator first, ForwardIterator last,
	typename enable_if<!is_integral<ForwardIterator>::value &&
						   is_forward_iterator<ForwardIterator>::value,
					   ForwardIterator>::type* ) {
	size_type input_len = static_cast<size_type>( ft::distance( first, last ) );
	size_type pos_index = position.base() - _begin;

	if ( input_len == 0 ) {
		return;
	}
	if ( this->capacity() < this->size() + input_len ) {
		size_type rec_size = this->recommand_size( this->size() + input_len );
		if ( rec_size > this->max_size() )
			throw std::length_error( "vector: length error" );

		pointer new_begin, new_end, new_end_cap;

		new_begin = new_end = _alloc.allocate( rec_size );
		new_end_cap = new_begin + rec_size;
		pointer p( _begin );
		for ( ; new_end != new_begin + pos_index; ++new_end, ++p ) {
			_alloc.construct( new_end, *( p ) );
			_alloc.destroy( p );
		}
		try {
			for ( ; first != last; ++first, ++new_end ) {
				_alloc.construct( new_end, *first );
			}
		} catch ( ... ) {
			for ( ; new_end != new_begin; ) {
				_alloc.destroy( --new_end );
			}
			_alloc.deallocate( new_begin, new_end_cap - new_begin );
			throw;
		}
		for ( ; p != _end; ++new_end, ++p ) {
			_alloc.construct( new_end, *( p ) );
			_alloc.destroy( p );
		}
		if ( _begin ) {
			_alloc.deallocate( _begin, _end_cap - _begin );
		}
		_begin = new_begin;
		_end = new_end;
		_end_cap = new_end_cap;
	} else {
		pointer tmp_end = _end - 1;
		pointer tmp_cpy_end = tmp_end + input_len;
		pointer recov_end = tmp_cpy_end;
		for ( ; tmp_end + 1 != position.base(); --tmp_cpy_end, --tmp_end ) {
			_alloc.construct( tmp_cpy_end, *( tmp_end ) );
			_alloc.destroy( tmp_end );
		}
		pointer new_alloc_end( position.base() );
		try {
			for ( ; first != last; ++first, ++new_alloc_end ) {
				_alloc.construct( new_alloc_end, *first );
			}
		} catch ( ... ) {
			for ( ; new_alloc_end != position.base(); ) {
				_alloc.destroy( --new_alloc_end );
			}
			for ( pointer recov_begin( position.base() + input_len ),
				  recov_to( position.base() );
				  recov_begin != recov_end; ++recov_begin, ++recov_to ) {
				_alloc.construct( recov_to, *recov_begin );
				_alloc.destroy( recov_begin );
			}
			throw;
		}
		_end += input_len;
	}
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(
	iterator position ) {
	_end = std::copy( position.base() + 1, _end, position.base() );
	_alloc.destroy( _end );
	return position;
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(
	iterator first, iterator last ) {
	size_type move_len = static_cast<size_type>( _end - last.base() );
	pointer   new_end =
		_end - static_cast<size_type>( last.base() - first.base() );
	for ( pointer to( first.base() ), from( last.base() ); move_len;
		  ++to, ++from, --move_len ) {
		*to = *from;
	}
	while ( new_end != _end ) {
		_alloc.destroy( --_end );
	}
	return first;
}

template <class T, class Allocator>
void vector<T, Allocator>::swap( vector<T, Allocator>& x ) {
	pointer tmp_begin = _begin;
	pointer tmp_end = _end;
	pointer tmp_end_cap = _end_cap;

	_begin = x._begin;
	_end = x._end;
	_end_cap = x._end_cap;
	x._begin = tmp_begin;
	x._end = tmp_end;
	x._end_cap = tmp_end_cap;
}

template <class T, class Allocator>
void vector<T, Allocator>::clear() {
	while ( _begin != _end ) {
		_alloc.destroy( --_end );
	}
}

// Constructor, Copy Assignment Operator, Destructor
template <class T, class Allocator>
vector<T, Allocator>::vector( const allocator_type& alloc )
	: _begin( NULL ), _end( NULL ), _end_cap( NULL ), _alloc( alloc ) {
}

template <class T, class Allocator>
vector<T, Allocator>::vector( size_type n, const_reference val,
							  const allocator_type& alloc )
	: _begin( NULL ), _end( NULL ), _end_cap( NULL ), _alloc( alloc ) {
	if ( n > 0 ) {
		this->vec_allocate( n );
		pointer tmp( _end + n );
		for ( ; _end < tmp; ++_end ) {
			_alloc.construct( _end, val );
		}
	}
}

template <class T, class Allocator>
template <class InputIterator>
vector<T, Allocator>::vector(
	InputIterator first, InputIterator last, const allocator_type& alloc,
	typename enable_if<!is_integral<InputIterator>::value &&
						   is_input_iterator<InputIterator>::value &&
						   !is_forward_iterator<InputIterator>::value,
					   InputIterator>::type* )
	: _begin( NULL ), _end( NULL ), _end_cap( NULL ), _alloc( alloc ) {
	this->vec_allocate( 1 );
	for ( ; first != last; ++first ) {
		this->push_back( *first );
	}
}

template <class T, class Allocator>
template <class ForwardIterator>
vector<T, Allocator>::vector(
	ForwardIterator first, ForwardIterator last, const allocator_type& alloc,
	typename enable_if<!is_integral<ForwardIterator>::value &&
						   is_forward_iterator<ForwardIterator>::value,
					   ForwardIterator>::type* )
	: _begin( NULL ), _end( NULL ), _end_cap( NULL ), _alloc( alloc ) {
	size_type input_len = static_cast<size_type>( ft::distance( first, last ) );

	if ( input_len > 0 ) {
		this->vec_allocate( input_len );
		for ( ; first != last; ++first, ++_end ) {
			_alloc.construct( _end, *first );
		}
	}
}

template <class T, class Allocator>
vector<T, Allocator>::vector( const vector<T, Allocator>& x )
	: _begin( NULL ), _end( NULL ), _end_cap( NULL ), _alloc( x._alloc ) {
	size_type n = x.size();
	if ( n > 0 ) {
		this->vec_allocate( n );
		for ( pointer x_begin = x._begin; _end < _begin + n;
			  ++_end, ++x_begin ) {
			_alloc.construct( _end, *x_begin );
		}
	}
}

template <class T, class Allocator>
vector<T, Allocator>::~vector() {
	if ( _begin ) {
		for ( pointer tmp( _begin ); tmp < _end; ++tmp ) {
			_alloc.destroy( tmp );
		}
		_alloc.deallocate( _begin, _end_cap - _begin );
		_begin = _end = _end_cap = NULL;
	}
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(
	const vector<T, Allocator>& x ) {
	if ( this != &x ) {
		if ( this->size() > 0 ) {
			this->clear();
		}
		if ( this->capacity() < x.capacity() ) {
			if ( _begin ) {
				_alloc.deallocate( _begin, _end_cap - _begin );
				_begin = _end = _end_cap = NULL;
			}
			size_type n = x.size();
			this->vec_allocate( n );
		}
		if ( x.size() > 0 ) {
			for ( pointer tmp( x._begin ); tmp != x._end; ++tmp, ++_end ) {
				_alloc.construct( _end, *tmp );
			}
		}
	}
	return *this;
}

// Allocator
template <class T, class Allocator>
typename vector<T, Allocator>::allocator_type
vector<T, Allocator>::get_allocator() const {
	return _alloc;
}

// Iterators
template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() {
	return iterator( _begin );
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin()
	const {
	return const_iterator( _begin );
}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end() {
	return iterator( _end );
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end()
	const {
	return const_iterator( _end );
}

template <class T, class Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() {
	return reverse_iterator( this->end() );
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rbegin() const {
	return const_reverse_iterator( this->end() );
}

template <class T, class Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend() {
	return reverse_iterator( this->begin() );
}

template <class T, class Allocator>
typename vector<T, Allocator>::const_reverse_iterator
vector<T, Allocator>::rend() const {
	return const_reverse_iterator( this->begin() );
}

// Comparison operator
template <class T, class Alloc>
bool operator==( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) {
	if ( lhs.size() != rhs.size() )
		return false;
	typename vector<T, Alloc>::const_pointer lbegin = lhs.begin().base();
	typename vector<T, Alloc>::const_pointer lend = lhs.end().base();
	typename vector<T, Alloc>::const_pointer rbegin = rhs.begin().base();
	typename vector<T, Alloc>::const_pointer rend = rhs.end().base();
	for ( ; lbegin != lend; ++lbegin, ++rbegin ) {
		if ( rbegin == rend || *lbegin != *rbegin )
			return false;
	}
	return true;
}

template <class T, class Alloc>
bool operator!=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) {
	return !( lhs == rhs );
}

template <class T, class Alloc>
bool operator<( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) {
	return ft::lexicographical_compare( lhs.begin(), lhs.end(), rhs.begin(),
										rhs.end() );
}

template <class T, class Alloc>
bool operator<=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) {
	return ( lhs < rhs || lhs == rhs );
}
template <class T, class Alloc>
bool operator>( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) {
	return !( lhs <= rhs );
}

template <class T, class Alloc>
bool operator>=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs ) {
	return !( lhs < rhs );
}

template <class T, class Allocator>
void swap( vector<T, Allocator>& x, vector<T, Allocator>& y ) {
	x.swap( y );
}
}  // namespace ft

#endif
