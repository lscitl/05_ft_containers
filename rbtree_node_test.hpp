/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_node_test.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/10/14 00:15:31 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__

#include <iterator>
// #include <__tree>
#include <memory>
#include "pair.hpp"

// 1. Every node is either red or black.
// 2. Root node is black.
// 3. All NIL nodes(leaf) are considered black.
// 4. A red node does not have a red child.
// 5. Every path from a given node to any of its descendant NIL nodes goes
// through the same number of black nodes.

namespace ft {

typedef enum { RED, BLACK } color_t;

template <class VoidPtr>
class rbtree_end_node;

template <class VoidPtr>
class rbtree_node_base;

template <class T, class VoidPtr>
class rbtree_node;

template <class Key, class Value>
struct _value_type;

template <class T>
struct rbtree_key_value_types;

template <class NodePtr>
struct get_element_type {
	typedef NodePtr element_type;
};

template <class T>
struct get_element_type<T*> {
	typedef T element_type;
};

template <class Ptr>
struct pointer_traits {
	typedef Ptr                                          pointer;
	typedef typename get_element_type<Ptr>::element_type get_element_type;

	// template<class
};

template <class T>
struct pointer_traits<T*> {
	typedef T*                                         pointer;
	typedef typename get_element_type<T>::element_type get_element_type;

	template <class U>
	struct rebind {
		typedef U* other;
	};
};

template <class From, class To>
struct rebind_pointer {
	typedef typename pointer_traits<From>::template rebind<To>::other type;
};

template <class VoidPtr>
struct rbtree_node_base_types {
	typedef VoidPtr                        void_pointer;
	typedef rbtree_node_base<void_pointer> node_base_type;
	typedef typename rebind_pointer<VoidPtr, node_base_type>::type
											   node_base_pointer;
	typedef rbtree_end_node<node_base_pointer> end_node_type;
	typedef end_node_type*                     end_node_pointer;
};

template <class NodePtr,
		  class NodeT = typename get_element_type<NodePtr>::element_type>
struct rbtree_node_types;

template <class NodePtr, class T, class VoidPtr>
struct rbtree_node_types<NodePtr, rbtree_node<T, VoidPtr> >
	: public rbtree_node_base_types<VoidPtr>, rbtree_key_value_types<T> {
	typedef rbtree_node_base_types<VoidPtr> _base;
	typedef rbtree_key_value_types<T>       _key_base;

   public:
	typedef typename get_element_type<NodePtr>::element_type node_type;
	typedef NodePtr                                          node_pointer;

	typedef T                      node_value_type;
	typedef node_value_type*       node_value_type_pointer;
	typedef const node_value_type* const_node_value_type_pointer;
};

template <class T>
struct rbtree_key_value_types {
	typedef T         key_type;
	typedef T         value_type;
	typedef T         node_value_type;
	typedef T         container_value_type;
	static const bool _is_map = false;

	static key_type const& _get_key( T const& _v ) {
		return _v;
	}

	static container_value_type const& _get_value( node_value_type const& _v ) {
		return _v;
	}
};

template <class Key, class Value>
struct rbtree_key_value_types<_value_type<Key, Value> > {
	typedef Key                        key_type;
	typedef Value                      value_type;
	typedef _value_type<Key, Value>    node_value_type;
	typedef ft::pair<const Key, Value> container_value_type;
	typedef container_value_type       map_value_type;
	static const bool                  _is_map = true;

	static key_type const& _get_key( node_value_type const& _v ) {
		return _v._get_value().first;
	}

	static container_value_type const& _get_value( node_value_type const& _v ) {
		return _v._get_value();
	}
};

template <class ValueT, class VoidPtr>
struct make_rbtree_node_types {
	typedef typename rebind_pointer<ValueT, VoidPtr>::type NodePtr;
	typedef rbtree_node_types<NodePtr>                     type;
};

template <class Pointer>
class rbtree_end_node {
   public:
	typedef Pointer pointer;

	pointer left;

	rbtree_end_node() : left( NULL ) {
	}
};

template <class VoidPtr>
class rbtree_node_base : public rbtree_node_base_types<VoidPtr>::end_node_type {
	typedef rbtree_node_base_types<VoidPtr> NodeBaseTypes;

   public:
	typedef typename NodeBaseTypes::node_base_pointer pointer;
	typedef color_t                                   color_type;

	color_type color;
	pointer    right;
	pointer    parent;

   private:
	~rbtree_node_base();
	rbtree_node_base( const rbtree_node_base& ref );
	rbtree_node_base& operator=( const rbtree_node_base& ref );
};

template <class T, class VoidPtr>
class rbtree_node : public rbtree_node_base<VoidPtr> {
   public:
	typedef T            node_value_type;
	typedef rbtree_node* node_pointer;

	node_value_type value;

   private:
	~rbtree_node();
	rbtree_node( const rbtree_node& ref );
	rbtree_node& operator=( const rbtree_node& ref );
};

template <class T, class Compare, class Allocator>
class rbtree {
   public:
	typedef T         value_type;
	typedef Compare   value_compare;
	typedef Allocator allocator_type;

   private:
	typedef typename make_rbtree_node_types<value_type, void*>::type NodeTypes;
	typedef typename NodeTypes::key_type                             key_type;

   public:
	typedef typename NodeTypes::node_value_type      node_value_type;
	typedef typename NodeTypes::container_value_type container_value_type;

	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;

   public:
	typedef typename NodeTypes::void_pointer void_pointer;

	typedef typename NodeTypes::node_type    node;
	typedef typename NodeTypes::node_pointer node_pointer;

	typedef typename NodeTypes::node_base_type    node_base;
	typedef typename NodeTypes::node_base_pointer node_base_pointer;

	typedef typename NodeTypes::end_node_type    end_node_t;
	typedef typename NodeTypes::end_node_pointer end_node_ptr;

	typedef end_node_ptr iter_pointer;

	typedef
		typename allocator_type::template rebind<node>::other node_allocator;

   private:
	end_node_t     __end_node;
	iter_pointer   _root_node;
	iter_pointer   _begin_node;
	value_compare  _comp;
	size_type      _size;
	allocator_type _alloc;

   public:
	rbtree()
		: __end_node(),
		  _root_node( &__end_node ),
		  _begin_node( &__end_node ),
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
		__end_node.left = static_cast<iter_pointer>( &__end_node );
	}

	// rbtree( const rbtree& x )
	// 	: __end_node(),
	// 	  _root_node( &__end_node ),
	// 	  _begin_node( &__end_node ),
	// 	  _comp( Compare() ),
	// 	  _size( 0 ),
	// 	  _alloc( Allocator() ) {
	// 	__end_node.left = &__end_node;
	// 	iterator x_begin = x.begin();
	// 	for ( ; x_begin != x.end(); ++x_begin ) {
	// 		insert( *x_begin );
	// 	}
	// }

	// rbtree( value_compare comp, allocator_type alloc )
	// 	: __end_node(),
	// 	  _root_node( &__end_node ),
	// 	  _begin_node( &__end_node ),
	// 	  _comp( comp ),
	// 	  _size( 0 ),
	// 	  _alloc( alloc ) {
	// }

	~rbtree() {
		// this->clear();
	}
};

}  // namespace ft

#endif
