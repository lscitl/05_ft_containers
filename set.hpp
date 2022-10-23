/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:11:07 by seseo             #+#    #+#             */
/*   Updated: 2022/10/23 19:19:48 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __SET_H__
#define __SET_H__

#include <limits>  // for numeric_limits
#include <stdexcept>
#include <functional>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "equal_lexico_cmp.hpp"
#include "pair.hpp"
#include "rbtree.hpp"

namespace ft {

template <class T, class Compare>
class set_value_compare {
   private:
	typedef T       argument_type;
	typedef Compare key_compare;

	key_compare comp;

   public:
	set_value_compare() : comp() {
	}
	set_value_compare( Compare c ) : comp( c ) {
	}

	const key_compare& key_comp() const {
		return comp;
	}

	bool operator()( const argument_type& a, const argument_type& b ) const {
		return comp( a, b );
	}
};

template <class T>
struct GetKeySet {
	typedef T argument_type;

	const argument_type& operator()( const argument_type& x ) const {
		return x;
	}
	argument_type& operator()( argument_type& x ) const {
		return x;
	}
};

template <class Key, class Compare = std::less<Key>,
		  class Allocator = std::allocator<Key> >
class set {
   public:
	typedef Key               key_type;
	typedef Key               value_type;
	typedef Compare           key_compare;
	typedef key_compare       value_compare;
	typedef Allocator         allocator_type;
	typedef value_type&       reference;
	typedef const value_type& const_reference;

	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;

   private:
	typedef ft::set_value_compare<value_type, key_compare> _vc;
	typedef ft::GetKeySet<value_type>                      _get_key;
	typedef
		typename Allocator::template rebind<value_type>::other _node_allocator;
	typedef rbtree<key_type, value_type, _get_key, _vc, _node_allocator> _base;
	typedef typename _base::node_base_p node_base_p;

	_base _tree;

   public:
	typedef typename _base::const_iterator       iterator;
	typedef typename _base::const_iterator       const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// construct/copy/destroy:
	explicit set( const key_compare&    comp = key_compare(),
				  const allocator_type& alloc = allocator_type() )
		: _tree( comp, alloc ) {
	}
	template <class InputIterator>
	set( InputIterator first, InputIterator last,
		 const key_compare&    comp = key_compare(),
		 const allocator_type& alloc = allocator_type() )
		: _tree( comp, alloc ) {
		while ( first != last ) {
			_tree.insert_unique( *first++ );
		}
	}
	set( const set& x ) : _tree( x._tree ) {
	}
	~set() {
		clear();
	}
	set& operator=( const set& m ) {
		this->_tree = m._tree;
		return *this;
	}

	// iterators:
	iterator begin() {
		return iterator( _tree.begin() );
	}
	const_iterator begin() const {
		return const_iterator( _tree.begin() );
	}
	iterator end() {
		return iterator( _tree.end() );
	}
	const_iterator end() const {
		return const_iterator( _tree.end() );
	}

	reverse_iterator rbegin() {
		return reverse_iterator( end() );
	}
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator( end() );
	}
	reverse_iterator rend() {
		return reverse_iterator( begin() );
	}
	const_reverse_iterator rend() const {
		return const_reverse_iterator( begin() );
	}

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

	// modifiers:
	ft::pair<iterator, bool> insert( const value_type& val ) {
		return _tree.insert_unique( val );
	}
	iterator insert( iterator position, const value_type& val ) {
		ft::pair<node_base_p, bool> ret;
		if ( size() != 0 ) {
			ret = _tree.find_node( position, val );
			if ( ret.second == true ) {
				return ret.first;
			}
			return _tree.insert_unique_with_parent( ret.first, val ).first;
		} else {
			ret = ft::pair<node_base_p, bool>( NULL, false );
			return _tree.insert_unique( val ).first;
		}
	}
	template <class InputIterator>
	void insert( InputIterator first, InputIterator last ) {
		for ( ; first != last; ++first ) {
			_tree.insert_unique( *first );
		}
	}

	void erase( iterator position ) {
		_tree.erase_from_node_ptr( position.node );
	}

	size_type erase( const key_type& k ) {
		return _tree.erase( k );
	}
	void erase( iterator first, iterator last ) {
		while ( first != last ) {
			_tree.erase_from_node_ptr( ( first++ ).node );
		}
	}
	void clear() {
		_tree.clear();
	}

	// observers:
	allocator_type get_allocator() const {
		return _tree.get_allocator();
	}
	key_compare key_comp() const {
		return _tree.value_comp().key_comp();
	}
	value_compare value_comp() const {
		return value_compare( _tree.value_comp().key_comp() );
	}

	// set operations:
	iterator find( const key_type& k ) {
		ft::pair<iterator, bool> ret = _tree.find_node( k );
		if ( ret.second ) {
			return ret.first;
		} else {
			return _tree.end();
		}
	}
	const_iterator find( const key_type& k ) const {
		ft::pair<const_iterator, bool> ret = _tree.find_node( k );
		if ( ret.second ) {
			return ret.first;
		} else {
			return _tree.end();
		}
	}

	size_type count( const key_type& k ) const {
		return _tree.find_node( k ).second == true;
	}
	iterator lower_bound( const key_type& k ) {
		return _tree.lower_bound( k );
	}
	const_iterator lower_bound( const key_type& k ) const {
		return _tree.lower_bound( k );
	}

	iterator upper_bound( const key_type& k ) {
		return _tree.upper_bound( k );
	}
	const_iterator upper_bound( const key_type& k ) const {
		return _tree.upper_bound( k );
	}

	pair<iterator, iterator> equal_range( const key_type& k ) {
		return ft::make_pair( _tree.lower_bound( k ), _tree.upper_bound( k ) );
	}
	pair<const_iterator, const_iterator> equal_range(
		const key_type& k ) const {
		return ft::make_pair( _tree.lower_bound( k ), _tree.upper_bound( k ) );
	}

	void swap( set& x ) {
		_tree.swap( x._tree );
	}
};

template <class Key, class Compare, class Allocator>
bool operator==( const set<Key, Compare, Allocator>& x,
				 const set<Key, Compare, Allocator>& y ) {
	if ( x.size() == y.size() ) {
		return ft::equal( x.begin(), x.end(), y.begin() );
	}
	return false;
}

template <class Key, class Compare, class Allocator>
bool operator<( const set<Key, Compare, Allocator>& x,
				const set<Key, Compare, Allocator>& y ) {
	return ft::lexicographical_compare( x.begin(), x.end(), y.begin(),
										y.end() );
}

template <class Key, class Compare, class Allocator>
bool operator!=( const set<Key, Compare, Allocator>& x,
				 const set<Key, Compare, Allocator>& y ) {
	return !( x == y );
}

template <class Key, class Compare, class Allocator>
bool operator>( const set<Key, Compare, Allocator>& x,
				const set<Key, Compare, Allocator>& y ) {
	return y < x;
}

template <class Key, class Compare, class Allocator>
bool operator>=( const set<Key, Compare, Allocator>& x,
				 const set<Key, Compare, Allocator>& y ) {
	return !( x < y );
}

template <class Key, class Compare, class Allocator>
bool operator<=( const set<Key, Compare, Allocator>& x,
				 const set<Key, Compare, Allocator>& y ) {
	return !( y < x );
}

// specialized algorithms:
template <class Key, class Compare, class Allocator>
void swap( set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y ) {
	x.swap( y );
}

}  // namespace ft

// // specialized algorithms:
// template <class Key, class Compare, class Allocator>
// void swap( ft::set<Key, Compare, Allocator>& x,
// 		   ft::set<Key, Compare, Allocator>& y ) {
// 	x.swap( y );
// }

#endif
