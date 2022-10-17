/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:11:07 by seseo             #+#    #+#             */
/*   Updated: 2022/10/17 22:55:56 by seseo            ###   ########.fr       */
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
#include "rbtree.hpp"

namespace ft {

template <class Pair, class Compare>
class map_value_compare {
   private:
	typedef Pair                      argument_type;
	typedef typename Pair::first_type key_type;
	typedef Compare                   key_compare;

	key_compare comp;

   public:
	map_value_compare() : comp() {
	}
	map_value_compare( Compare c ) : comp( c ) {
	}

	bool operator()( const argument_type& a, const argument_type& b ) {
		return comp( a.first, b.first );
	}

	bool operator()( const key_type& a, const argument_type& b ) {
		return comp( a, b.first );
	}

	bool operator()( const argument_type& a, const key_type& b ) {
		return comp( a.first, b );
	}
};

template <class Pair>
struct GetKey {
	typedef Pair                      argument_type;
	typedef typename Pair::first_type result_type;

	const result_type& operator()( const argument_type& x ) const {
		return x.first;
	}
	result_type& operator()( argument_type& x ) const {
		return x.first;
	}
};

template <class TreeIterator>
class map_iterator {
   public:
	typedef typename TreeIterator::value_type        value_type;
	typedef typename TreeIterator::pointer           pointer;
	typedef typename TreeIterator::reference         reference;
	typedef typename TreeIterator::difference_type   difference_type;
	typedef typename TreeIterator::iterator_category iterator_category;

   protected:
	TreeIterator _current;

   public:
	map_iterator() : _current( NULL ) {
	}

	explicit map_iterator( const TreeIterator& x ) : _current( x ) {
	}

	map_iterator( const map_iterator& x ) : _current( x._current ) {
	}

	template <class U>
	map_iterator& operator=( const map_iterator<U>& u ) {
		_current = u._current;
		return *this;
	}

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
		++( *this );
		return ret;
	}

	map_iterator& operator--() {
		--_current;
		return *this;
	}

	map_iterator operator--( int ) {
		map_iterator ret( *this );
		--( *this );
		return ret;
	}

	friend bool operator==( const map_iterator& left,
							const map_iterator& right ) {
		return left._current == right._current;
	}
	friend bool operator!=( const map_iterator& left,
							const map_iterator& right ) {
		return left._current != right._current;
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
	typedef ft::map_value_compare<value_type, key_compare> _vc;
	typedef ft::GetKey<value_type>                         _get_key;
	typedef
		typename Allocator::template rebind<value_type>::other _node_allocator;
	typedef rbtree<key_type, value_type, _get_key, _vc, _node_allocator> _base;

	_base _tree;

   public:
	typedef ft::map_iterator<typename _base::iterator> iterator;
	typedef ft::map_iterator<typename _base::iterator> const_iterator;
	// typedef ft::map_iterator<typename _base::const_iterator> const_iterator;
	// typedef ft::reverse_iterator<iterator>       reverse_iterator;
	// typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// construct/copy/destroy:
	explicit map( const key_compare&    comp = key_compare(),
				  const allocator_type& alloc = allocator_type() )
		: _tree( comp, alloc ) {
	}
	template <class InputIterator>
	map( InputIterator first, InputIterator last,
		 const key_compare&    comp = key_compare(),
		 const allocator_type& alloc = allocator_type() )
		: _tree( comp, alloc ) {
		for ( ; first != last; ++first ) {
			_tree.insert( *first );
		}
	}

	map( const map& x ) : _tree( x._tree ) {
	}

	~map() {
		_tree.clear();
	}

	map& operator=( const map& m );

	// iterators:
	iterator begin() {
		return iterator( _tree.begin() );
	}
	iterator end() {
		return iterator( _tree.end() );
	}
	const_iterator begin() const;
	const_iterator end() const;

	// reverse_iterator       rbegin();
	// const_reverse_iterator rbegin() const;
	// reverse_iterator       rend();
	// const_reverse_iterator rend() const;

	// capacity:
	bool empty() const {
		return this->size() == 0;
	}
	size_type size() const {
		return _tree.size();
	}
	size_type max_size() const {
		return _tree.max_size();
	}

	// element access:
	mapped_type& operator[]( const key_type& k );

	// modifiers:
	ft::pair<iterator, bool> insert( const value_type& val ) {
		ft::pair<typename _base::iterator, bool> ret = _tree.insert( val );
		return ft::make_pair( ret.first, ret.second );
	}

	iterator insert( iterator position, const value_type& val ) {
		if ( _tree.insert( val )->second ) {
		}
	}

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

	// void end_check() {
	// 	std::cout << _tree.end_check().first << std::endl;
	// }
	void print_tree() {
		_tree.print_tree_map();
	}
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
