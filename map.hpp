/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:11:07 by seseo             #+#    #+#             */
/*   Updated: 2022/09/28 19:39:28 by seseo            ###   ########.fr       */
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
#include "lexico_cmp.hpp"
#include "pair.hpp"
#include "rbtree.hpp"

namespace ft {

template <class TreeIterator>
class map_iterator {
	typedef typename TreeIterator::NodeTypes NodeTypes;

	TreeIterator i;

   public:
	typedef typename NodeType::value_type                value_type;
	typedef typename iterator_traits<T>::pointer         pointer;
	typedef typename iterator_traits<T>::reference       reference;
	typedef typename iterator_traits<T>::difference_type difference_type;
	typedef typename std::bidirectional_iterator_tag     iterator_category;

   protected:
	pointer _current;

   public:
	map_iterator() : _current( NULL ) {
	}

	explicit map_iterator( pointer x ) : _current( x ) {
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
		  class Allocator = std::allocator<pair<const Key, T> > >
class map {
   public:
	// types:
	typedef Key                               key_type;
	typedef T                                 mapped_type;
	typedef pair<const key_type, mapped_type> value_type;
	typedef Compare                           key_compare;
	typedef Allocator                         allocator_type;
	typedef value_type&                       reference;
	typedef const value_type&                 const_reference;

	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;

	typedef ft::map_iterator<_base::iterator>       iterator;
	typedef ft::map_iterator<_base::const_iterator> const_iterator;
	typedef ft::reverse_iterator<iterator>          reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

   private:
	typedef typename rbtree_node<value_type>::node_type _node_type;
	typedef
		typename Allocator::template rebind<_node_type>::other _node_allocator;
	typedef typename rbtree<key_type, value_type, key_compare, _node_allocator>
		_base;

	_base _tree;

	class value_compare : public binary_function<value_type, value_type, bool> {
		friend class map;

	   protected:
		key_compare comp;

		value_compare( key_compare c );

	   public:
		bool operator()( const value_type& x, const value_type& y ) const;
	};

	// construct/copy/destroy:
	explicit map( const key_compare&    comp = key_compare(),
				  const allocator_type& alloc = allocator_type() );
	template <class InputIterator>
	map( InputIterator first, InputIterator last,
		 const key_compare&    comp = key_compare(),
		 const allocator_type& alloc = allocator_type() );
	map( const map& x );
	~map();

	map& operator=( const map& m );

	// iterators:
	iterator       begin();
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
	pair<iterator, bool> insert( const value_type& val );
	iterator             insert( iterator position, const value_type& val );
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
