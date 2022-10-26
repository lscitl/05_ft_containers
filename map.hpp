/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:11:07 by seseo             #+#    #+#             */
/*   Updated: 2022/10/26 21:41:05 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __MAP_H__
#define __MAP_H__

#include <limits>  // for numeric_limits
#include <stdexcept>
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

	const key_compare& key_comp() const {
		return comp;
	}

	bool operator()( const argument_type& a, const argument_type& b ) const {
		return comp( a.first, b.first );
	}

	bool operator()( const key_type& a, const argument_type& b ) const {
		return comp( a, b.first );
	}

	bool operator()( const argument_type& a, const key_type& b ) const {
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
	typedef typename _base::node_base_p node_base_p;

	_base _tree;

   public:
	typedef typename _base::iterator               iterator;
	typedef typename _base::const_iterator         const_iterator;
	typedef typename _base::reverse_iterator       reverse_iterator;
	typedef typename _base::const_reverse_iterator const_reverse_iterator;

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
		while ( first != last ) {
			_tree.insert_unique( *first++ );
		}
	}
	map( const map& x ) : _tree( x._tree ) {
	}
	~map() {
		clear();
	}
	map& operator=( const map& m ) {
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

	// element access:
	mapped_type& operator[]( const key_type& k ) {
		ft::pair<iterator, bool> ret = _tree.find_node( k );
		if ( ret.second == false ) {
			return ( *( _tree.insert_unique( ft::make_pair( k, mapped_type() ) )
							.first ) )
				.second;
		} else {
			return ( *( ret.first ) ).second;
		}
	}
	mapped_type& at( const key_type& k ) {
		ft::pair<iterator, bool> ret = _tree.find_node( k );
		if ( ret.second == false ) {
			throw std::out_of_range( "map::at:  key not found" );
		} else {
			return ( *( ret.first ) ).second;
		}
	}
	const mapped_type& at( const key_type& k ) const {
		ft::pair<iterator, bool> ret = _tree.find_node( k );
		if ( ret.second == false ) {
			throw std::out_of_range( "map::at:  key not found" );
		} else {
			return ( *( ret.first ) ).second;
		}
	}

	// modifiers:
	ft::pair<iterator, bool> insert( const value_type& val ) {
		return _tree.insert_unique( val );
	}
	iterator insert( iterator position, const value_type& val ) {
		ft::pair<node_base_p, bool> ret;
		if ( size() != 0 ) {
			ret = _tree.find_node( position, _get_key()( val ) );
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

	// map operations:
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

	void swap( map& x ) {
		_tree.swap( x._tree );
	}
};

template <class Key, class T, class Compare, class Allocator>
bool operator==( const map<Key, T, Compare, Allocator>& x,
				 const map<Key, T, Compare, Allocator>& y ) {
	if ( x.size() == y.size() ) {
		return ft::equal( x.begin(), x.end(), y.begin() );
	}
	return false;
}

template <class Key, class T, class Compare, class Allocator>
bool operator<( const map<Key, T, Compare, Allocator>& x,
				const map<Key, T, Compare, Allocator>& y ) {
	return ft::lexicographical_compare( x.begin(), x.end(), y.begin(),
										y.end() );
}

template <class Key, class T, class Compare, class Allocator>
bool operator!=( const map<Key, T, Compare, Allocator>& x,
				 const map<Key, T, Compare, Allocator>& y ) {
	return !( x == y );
}

template <class Key, class T, class Compare, class Allocator>
bool operator>( const map<Key, T, Compare, Allocator>& x,
				const map<Key, T, Compare, Allocator>& y ) {
	return y < x;
}

template <class Key, class T, class Compare, class Allocator>
bool operator>=( const map<Key, T, Compare, Allocator>& x,
				 const map<Key, T, Compare, Allocator>& y ) {
	return !( x < y );
}

template <class Key, class T, class Compare, class Allocator>
bool operator<=( const map<Key, T, Compare, Allocator>& x,
				 const map<Key, T, Compare, Allocator>& y ) {
	return !( y < x );
}

// specialized algorithms:
template <class Key, class T, class Compare, class Allocator>
void swap( map<Key, T, Compare, Allocator>& x,
		   map<Key, T, Compare, Allocator>& y ) {
	x.swap( y );
}

}  // namespace ft

// // specialized algorithms:
// template <class Key, class T, class Compare, class Allocator>
// void swap( ft::map<Key, T, Compare, Allocator>& x,
// 		   ft::map<Key, T, Compare, Allocator>& y ) {
// 	x.swap( y );
// }

#endif
