/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:11:07 by seseo             #+#    #+#             */
/*   Updated: 2022/10/16 00:09:18 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __MAP_H__
#define __MAP_H__

// #include <map>
// #include <set>
#include <functional>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "equal_lexico_cmp.hpp"
#include "pair.hpp"
#include "rbtree_node_test.hpp"

namespace ft {

template <class Key, class C, class Compare>
class map_value_compare {
   private:
	Compare comp;

   public:
	map_value_compare() : comp() {
	}
	map_value_compare( Compare c ) : comp( c ) {
	}

	Compare& key_comp() {
		return comp;
	}

	bool operator()( const C& x, const C& y ) {
		return comp( x._get_value().first, y._get_value().first );
	}

	bool operator()( const Key& x, const C& y ) {
		return comp( x, y._get_value().first );
	}

	bool operator()( const C& x, const Key& y ) {
		return comp( x._get_value().first, y );
	}
};

template <class Key, class Value>
struct _value_type {
	typedef Key                               key_type;
	typedef Value                             mapped_type;
	typedef ft::pair<key_type, mapped_type>   value_type;
	typedef ft::pair<key_type&, mapped_type&> ref_pair_type;

   protected:
	value_type cc;

   public:
	value_type& _get_value() {
		return cc;
	}

	const value_type& _get_value() const {
		return cc;
	}

	ref_pair_type ref() {
		value_type& v = _get_value();
		return ref_pair_type( const_cast<key_type&>( v.first ), v.second );
	}

	_value_type& operator=( const _value_type& v ) {
		ref() = v._get_value();
		return *this;
	}

   private:
	_value_type( const value_type& val ) : cc( val ) {
	}
	_value_type( const _value_type& v ) : cc( v._get_value() ) {
	}
	~_value_type() {
	}
	_value_type();
};

template <class TreeIterator>
class map_iterator {
	typedef typename TreeIterator::NodeTypes NodeTypes;

	TreeIterator i;

   public:
	typedef typename NodeTypes::value_type           value_type;
	typedef typename NodeTypes::node_base_pointer    pointer;
	typedef value_type&                              reference;
	typedef typename TreeIterator::difference_type   difference_type;
	typedef typename std::bidirectional_iterator_tag iterator_category;

   protected:
	TreeIterator _current;

   public:
	map_iterator() : _current( NULL ) {
	}

	explicit map_iterator( TreeIterator x ) : _current( x ) {
	}

	template <class U>
	map_iterator( const map_iterator<U>& u ) : _current( u.base() ) {
	}

	template <class U>
	map_iterator& operator=( const map_iterator<U>& u ) {
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

	map_iterator& operator++() {
		++_current;
		return *this;
	}

	map_iterator operator++( int ) {
		map_iterator ret( *this );
		++_current;
		return ret;
	}

	map_iterator& operator--() {
		--_current;
		return *this;
	}

	map_iterator operator--( int ) {
		map_iterator ret( *this );
		--_current;
		return ret;
	}
};

template <class Key, class T, class Compare = std::less<Key>,
		  class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
   public:
	typedef Key                                   key_type;
	typedef T                                     mapped_type;
	typedef ft::pair<const key_type, mapped_type> value_type;
	typedef Compare                               key_compare;
	typedef Allocator                             allocator_type;
	typedef value_type&                           reference;
	typedef const value_type&                     const_reference;

	class value_compare
		: public std::binary_function<value_type, value_type, bool> {
		friend class map;

	   protected:
		key_compare comp;

		value_compare( key_compare c ) : comp( c ) {
		}

	   public:
		bool operator()( const value_type& x, const value_type& y ) const {
			return comp( x.first, y.first );
		}
	};

	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;

   private:
	typedef ft::_value_type<Key, T>                              _value_type;
	typedef ft::map_value_compare<Key, _value_type, key_compare> _vc;
	typedef
		typename Allocator::template rebind<value_type>::other _node_allocator;
	typedef rbtree<_value_type, _vc, _node_allocator>          _base;
	_base                                                      _tree;

   public:
	typedef ft::map_iterator<typename _base::iterator> iterator;
	typedef ft::map_iterator<typename _base::iterator> const_iterator;
	// typedef ft::map_iterator<typename _base::const_iterator> const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// construct/copy/destroy:
	explicit map( const key_compare&    comp = key_compare(),
				  const allocator_type& alloc = allocator_type() )
		: _tree( comp, alloc ) {
	}
	template <class InputIterator>
	map( InputIterator first, InputIterator last,
		 const key_compare&    comp = key_compare(),
		 const allocator_type& alloc = allocator_type() );
	map( const map& x );

	~map() {
		_tree.clear();
	}

	map& operator=( const map& m );

	// iterators:
	iterator begin() {
		return iterator( _tree.begin() );
	}
	const_iterator begin() const;
	iterator       end();
	const_iterator end() const;

	reverse_iterator       rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator       rend();
	const_reverse_iterator rend() const;

	// capacity:
	bool      empty() const;
	size_type size() const;
	size_type max_size() const;

	// element access:
	mapped_type& operator[]( const key_type& k );

	// modifiers:
	ft::pair<iterator, bool> insert( const value_type& val ) {
		ft::pair<typename _base::iterator, bool> ret = _tree.insert( val );
		return ft::make_pair( ret.first, ret.second );
	}

	iterator insert( iterator position, const value_type& val );
	template <class InputIterator>
	void insert( InputIterator first, InputIterator last );

	void      erase( iterator position );
	size_type erase( const key_type& k );
	void      erase( iterator first, iterator last );

	void clear();

	// observers:
	allocator_type get_allocator() const;
	key_compare    key_comp() const;
	value_compare  value_comp() const;

	// map operations:
	iterator       find( const key_type& k );
	const_iterator find( const key_type& k ) const;

	iterator       lower_bound( const key_type& k );
	const_iterator lower_bound( const key_type& k ) const;

	iterator       upper_bound( const key_type& k );
	const_iterator upper_bound( const key_type& k ) const;

	pair<iterator, iterator>             equal_range( const key_type& k );
	pair<const_iterator, const_iterator> equal_range( const key_type& k ) const;
};

template <class Key, class T, class Compare, class Allocator>
bool operator==( const map<Key, T, Compare, Allocator>& x,
				 const map<Key, T, Compare, Allocator>& y );

template <class Key, class T, class Compare, class Allocator>
bool operator<( const map<Key, T, Compare, Allocator>& x,
				const map<Key, T, Compare, Allocator>& y );

template <class Key, class T, class Compare, class Allocator>
bool operator!=( const map<Key, T, Compare, Allocator>& x,
				 const map<Key, T, Compare, Allocator>& y );

template <class Key, class T, class Compare, class Allocator>
bool operator>( const map<Key, T, Compare, Allocator>& x,
				const map<Key, T, Compare, Allocator>& y );

template <class Key, class T, class Compare, class Allocator>
bool operator>=( const map<Key, T, Compare, Allocator>& x,
				 const map<Key, T, Compare, Allocator>& y );

template <class Key, class T, class Compare, class Allocator>
bool operator<=( const map<Key, T, Compare, Allocator>& x,
				 const map<Key, T, Compare, Allocator>& y );

// specialized algorithms:
template <class Key, class T, class Compare, class Allocator>
void swap( map<Key, T, Compare, Allocator>& x,
		   map<Key, T, Compare, Allocator>& y );

}  // namespace ft

#endif
