/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_node_test.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/10/16 00:08:02 by seseo            ###   ########.fr       */
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
	typedef
		typename rebind_pointer<VoidPtr, end_node_type>::type end_node_pointer;
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

	typedef T node_value_type;
	typedef typename rebind_pointer<VoidPtr, node_value_type>::type
		node_value_type_pointer;
	typedef typename rebind_pointer<VoidPtr, const node_value_type>::type
		const_node_value_type_pointer;
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
	typedef
		typename rebind_pointer<VoidPtr, rbtree_node<ValueT, VoidPtr> >::type
									   NodePtr;
	typedef rbtree_node_types<NodePtr> type;
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

	rbtree_node_base() : color( RED ), right( NULL ), parent( NULL ) {
	}
	~rbtree_node_base() {
	}

	static pointer minimum( pointer x ) {
		while ( x->left != NULL ) {
			x = x->left;
		}
		return x;
	}

	static pointer maximum( pointer x ) {
		while ( x->right != NULL ) {
			x = x->right;
		}
		return x;
	}

   private:
	rbtree_node_base( const rbtree_node_base& ref );
	rbtree_node_base& operator=( const rbtree_node_base& ref );
};

template <class T, class VoidPtr>
class rbtree_node : public rbtree_node_base<VoidPtr> {
   public:
	typedef T node_value_type;
	// typedef rbtree_node* node_pointer;

	node_value_type value;

	rbtree_node( const node_value_type& val ) : value( val ) {
	}
	~rbtree_node() {
	}
	rbtree_node( const rbtree_node& ref ) : value( ref.value ) {
		if ( this != &ref ) {
			this->color = ref.color;
			this->parent = ref.parent;
			this->right = ref.right;
			this->left = ref.left;
		}
	}

   private:
	rbtree_node& operator=( const rbtree_node& ref );
};

template <class T, class NodePtr, class DiffType>
class rbtree_iterator {
   private:
	typedef rbtree_node_types<NodePtr>            NodeTypes;
	typedef NodePtr                               node_pointer;
	typedef typename NodeTypes::node_base_pointer node_base_pointer;
	typedef typename NodeTypes::end_node_pointer  end_node_pointer;
	typedef node_pointer                          iter_pointer;
	// typedef typename NodeTypes::iter_pointer      iter_pointer;

	iter_pointer node;

   public:
	typedef std::bidirectional_iterator_tag             iterator_category;
	typedef T                                           value_type;
	typedef DiffType                                    difference_type;
	typedef value_type&                                 reference;
	typedef typename NodeTypes::node_value_type_pointer pointer;

   public:
	rbtree_iterator() : node( NULL ) {
	}

	rbtree_iterator( iter_pointer node ) : node( node ) {
	}

	reference operator*() const {
		return static_cast<node_pointer>( node )->value;
	}

	pointer operator->() const {
		return &( static_cast<node_pointer>( node )->value );
	}

	void incremet() {
		if ( node->right != NULL ) {
			node = node->right;
			while ( node->left != NULL ) {
				node = node->left;
			}
		} else {
			iter_pointer tmp = node->parent;
			while ( node == tmp->right ) {
				node = tmp;
				tmp = tmp->parent;
			}
			if ( node->right != tmp ) node = tmp;
		}
	}

	void decremet() {
		if ( node->left != NULL ) {
			node = node->left;
			while ( node->right != NULL ) {
				node = node->right;
			}
		} else {
			iter_pointer tmp = node->parent;
			while ( node == tmp->left ) {
				node = tmp;
				tmp = tmp->parent;
			}
			if ( node->left != tmp ) node = tmp;
		}
	}
	// template <class, class, class>
	// friend class rbtree;
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

	// typedef end_node_ptr iter_pointer;

	typedef
		typename allocator_type::template rebind<node>::other node_allocator;

	typedef rbtree_iterator<value_type, node_pointer, difference_type> iterator;

   private:
	end_node_t        __end_node;
	node_base_pointer _root_node;
	node_base_pointer _begin_node;
	value_compare     _comp;
	size_type         _size;
	node_allocator    _alloc;

   private:
	bool is_right_child( node_base_pointer target_node ) {
		return target_node->parent->right == target_node;
	}

	void rotate_left( node_base_pointer target_node ) {
		if ( target_node == NULL || target_node == end_ptr() ) {
			return;
		}
		node_base_pointer r_child_node = target_node->right;
		if ( r_child_node == end_ptr() ) {
			return;
		}
		node_base_pointer parent_node = target_node->parent;
		node_base_pointer g_child_node = r_child_node->left;

		if ( parent_node != NULL ) {
			if ( is_right_child( target_node ) ) {
				parent_node->right = r_child_node;
			} else {
				parent_node->left = r_child_node;
			}
		} else {
			_root_node = r_child_node;
		}
		r_child_node->parent = parent_node;
		r_child_node->left = target_node;
		target_node->parent = r_child_node;
		target_node->right = g_child_node;
		if ( g_child_node != NULL && g_child_node != end_ptr() ) {
			g_child_node->parent = target_node;
		}
	}

	void rotate_right( node_base_pointer target_node ) {
		if ( target_node == NULL || target_node == end_ptr() ) {
			return;
		}
		node_base_pointer l_child_node = target_node->left;
		if ( l_child_node == end_ptr() ) {
			return;
		}
		node_base_pointer parent_node = target_node->parent;
		node_base_pointer g_child_node = l_child_node->right;

		if ( parent_node != NULL ) {
			if ( is_right_child( target_node ) ) {
				parent_node->right = l_child_node;
			} else {
				parent_node->left = l_child_node;
			}
		} else {
			_root_node = l_child_node;
		}
		l_child_node->parent = parent_node;
		l_child_node->right = target_node;
		target_node->parent = l_child_node;
		target_node->left = g_child_node;
		if ( g_child_node != NULL && g_child_node != end_ptr() ) {
			g_child_node->parent = target_node;
		}
	}

   public:
	rbtree()
		: __end_node(),
		  _root_node( static_cast<node_base_pointer>( &__end_node ) ),
		  _begin_node( static_cast<node_base_pointer>( &__end_node ) ),
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
		__end_node.left = static_cast<node_base_pointer>( &__end_node );
	}

	rbtree( const rbtree& x )
		: __end_node(),
		  _root_node( static_cast<node_base_pointer>( &__end_node ) ),
		  _begin_node( static_cast<node_base_pointer>( &__end_node ) ),
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
		__end_node.left = static_cast<node_base_pointer>( &__end_node );
		iterator x_begin = x.begin();
		for ( ; x_begin != x.end(); ++x_begin ) {
			insert( *x_begin );
		}
	}

	iterator begin() {
		return iterator( _begin_node );
	}

	iterator end() {
		return iterator( get_end() );
	}

	node_base_pointer get_end() {
		return static_cast<node_base_pointer>( __end_node.left );
	}

	node_base_pointer end_ptr() {
		return static_cast<node_base_pointer>( &__end_node );
	}

	value_type& get_node_value( node_base_pointer node ) {
		return static_cast<node_pointer>( node )->value;
	}

	rbtree( value_compare comp, allocator_type alloc )
		: __end_node(),
		  _root_node( NULL ),
		  _begin_node( NULL ),
		  _comp( comp ),
		  _size( 0 ),
		  _alloc( alloc ) {
	}

	ft::pair<node_base_pointer, bool> find_node( const key_type& key ) {
		node_base_pointer cur = _root_node;
		node_base_pointer parent = _root_node;
		if ( _comp( key, get_node_value( cur ) ) ) {
			cur = cur->left;
		} else {
			if ( _comp( get_node_value( cur ), key ) ) {
				cur = cur->right;
			} else {
				return ft::pair<node_base_pointer, bool>( cur, true );
			}
		}
		while ( cur != NULL && cur != end_ptr() ) {
			if ( _comp( key, get_node_value( cur ) ) ) {
				parent = cur;
				cur = cur->left;
			} else {
				if ( _comp( get_node_value( cur ), key ) ) {
					parent = cur;
					cur = cur->right;
				} else {
					return ft::pair<node_base_pointer, bool>( cur, true );
				}
			}
		}
		return ft::pair<node_base_pointer, bool>( parent, false );
	}

	// ft::pair<end_node_ptr, bool> find_node( const key_type& key ) {
	// 	end_node_ptr cur = _root_node;
	// 	end_node_ptr parent = _root_node;
	// 	if ( _comp( key, static_cast<node_pointer>( cur )->value ) ) {
	// 		cur = cur->left;
	// 	} else {
	// 		if ( _comp( static_cast<node_pointer>( cur )->value, key ) ) {
	// 			cur = static_cast<node_pointer>( cur )->right;
	// 		} else {
	// 			return ft::pair<end_node_ptr, bool>( cur, true );
	// 		}
	// 	}
	// 	while ( cur != NULL && cur != end_node_ptr() ) {
	// 		if ( _comp( key, static_cast<node_pointer>( cur )->value ) ) {
	// 			parent = cur;
	// 			cur = cur->left;
	// 		} else {
	// 			if ( _comp( static_cast<node_pointer>( cur )->value, key ) ) {
	// 				parent = cur;
	// 				cur = static_cast<node_pointer>( cur )->right;
	// 			} else {
	// 				return ft::pair<end_node_ptr, bool>( cur, true );
	// 			}
	// 		}
	// 	}
	// 	return ft::pair<end_node_ptr, bool>( parent, false );
	// }

	bool check_uncle_is_red_and_make_balance( node_base_pointer grand_parent,
											  node_base_pointer parent ) {
		bool              parent_is_right = is_right_child( parent );
		node_base_pointer uncle;

		if ( parent_is_right ) {
			uncle = grand_parent->left;
		} else {
			uncle = grand_parent->right;
		}
		if ( uncle != NULL && uncle->color == RED ) {
			if ( grand_parent != _root_node ) {
				grand_parent->color = RED;
			}
			uncle->color = BLACK;
			parent->color = BLACK;
			node_base_pointer gg_parent = grand_parent->parent;
			if ( gg_parent == NULL || gg_parent->color == BLACK ) {
				return true;
			}
			node_base_pointer ggg_parent = gg_parent->parent;
			if ( check_uncle_is_red_and_make_balance( ggg_parent,
													  gg_parent ) ) {
				return true;
			} else {
				check_rotation_dir_and_make_balance( ggg_parent, gg_parent,
													 grand_parent );
				return true;
			}
		}
		return false;
	}

	void check_rotation_dir_and_make_balance( node_base_pointer grand_parent,
											  node_base_pointer parent,
											  node_base_pointer child ) {
		bool child_is_right = is_right_child( child );
		bool parent_is_right = is_right_child( parent );

		// case 2
		if ( child_is_right ^ parent_is_right ) {
			grand_parent->color = RED;
			child->color = BLACK;
			if ( child_is_right ) {
				rotate_left( parent );
				rotate_right( grand_parent );
			} else {
				rotate_right( parent );
				rotate_left( grand_parent );
			}
		}
		// case 3
		else {
			grand_parent->color = RED;
			parent->color = BLACK;
			if ( parent_is_right ) {
				rotate_left( grand_parent );
			} else {
				rotate_right( grand_parent );
			}
		}
	}

	// // case 1 : grand parent - black, uncle and parent - red, child - red.
	// // case 2 : grand parent - black, parent - red, other side child - red.
	// // case 3 : grand parent - black, parent - red, same side child - red.
	// // case 4 : root - red.
	ft::pair<iterator, bool> insert( const node_value_type& val ) {
		if ( this->_size == 0 ) {
			node              __new_node( val );
			node_base_pointer new_node = _alloc.allocate( 1 );
			__new_node.color = BLACK;
			_alloc.construct( static_cast<node_pointer>( new_node ),
							  __new_node );

			_root_node = new_node;
			__end_node.left = _root_node;
			_begin_node = _root_node;
			++_size;
			return ft::make_pair(
				iterator( static_cast<node_pointer>( new_node ) ), true );
		}

		ft::pair<node_base_pointer, bool> result =
			find_node( NodeTypes::_get_key( val ) );
		if ( result.second == true ) {
			return ft::make_pair(
				iterator( static_cast<node_pointer>( result.first ) ), false );
		}

		node              __new_node( val );
		node_base_pointer new_node = _alloc.allocate( 1 );
		_alloc.construct( static_cast<node_pointer>( new_node ), __new_node );

		if ( _comp( get_node_value( get_end() ), val ) ) {
			__end_node.left->right = new_node;
			__new_node.right = end_ptr();
			__end_node.left = new_node;
		} else if ( _comp( val, get_node_value( _begin_node ) ) ) {
			_begin_node = new_node;
		}
		++_size;

		node_base_pointer parent_node = result.first;

		if ( _comp( get_node_value( parent_node ), val ) ) {
			parent_node->right = new_node;
		} else {
			parent_node->left = new_node;
		}
		new_node->parent = parent_node;
		if ( parent_node->color == BLACK ) {
			return ft::make_pair(
				iterator( static_cast<node_pointer>( new_node ) ), true );
		}
		node_base_pointer g_parent = parent_node->parent;

		// Unbalanced state. Check case1 to make balance.
		if ( check_uncle_is_red_and_make_balance( g_parent, parent_node ) ) {
			return ft::make_pair(
				iterator( static_cast<node_pointer>( new_node ) ), true );
		}
		// Check case2 or case3 and rotate to make balance.
		check_rotation_dir_and_make_balance( g_parent, parent_node, new_node );
		return ft::make_pair( iterator( static_cast<node_pointer>( new_node ) ),
							  true );
	}

	ft::pair<iterator, bool> insert( const container_value_type& val ) {
		if ( this->_size == 0 ) {
			node              __new_node( value_type( val ) );
			node_base_pointer new_node = _alloc.allocate( 1 );
			__new_node.color = BLACK;
			_alloc.construct( static_cast<node_pointer>( new_node ),
							  __new_node );

			_root_node = new_node;
			__end_node.left = _root_node;
			_begin_node = _root_node;
			++_size;
			return ft::make_pair(
				iterator( static_cast<node_pointer>( new_node ) ), true );
		}

		ft::pair<node_base_pointer, bool> result =
			find_node( NodeTypes::_get_key( val ) );
		if ( result.second == true ) {
			return ft::make_pair(
				iterator( static_cast<node_pointer>( result.first ) ), false );
		}

		node              __new_node( value_type( val ) );
		node_base_pointer new_node = _alloc.allocate( 1 );
		_alloc.construct( static_cast<node_pointer>( new_node ), __new_node );

		if ( _comp( get_node_value( get_end() ), val ) ) {
			__end_node.left->right = new_node;
			__new_node.right = end_ptr();
			__end_node.left = new_node;
		} else if ( _comp( val, get_node_value( _begin_node ) ) ) {
			_begin_node = new_node;
		}
		++_size;

		node_base_pointer parent_node = result.first;

		if ( _comp( get_node_value( parent_node ), val ) ) {
			parent_node->right = new_node;
		} else {
			parent_node->left = new_node;
		}
		new_node->parent = parent_node;
		if ( parent_node->color == BLACK ) {
			return ft::make_pair(
				iterator( static_cast<node_pointer>( new_node ) ), true );
		}
		node_base_pointer g_parent = parent_node->parent;

		// Unbalanced state. Check case1 to make balance.
		if ( check_uncle_is_red_and_make_balance( g_parent, parent_node ) ) {
			return ft::make_pair(
				iterator( static_cast<node_pointer>( new_node ) ), true );
		}
		// Check case2 or case3 and rotate to make balance.
		check_rotation_dir_and_make_balance( g_parent, parent_node, new_node );
		return ft::make_pair( iterator( static_cast<node_pointer>( new_node ) ),
							  true );
	}

	// erase node function.
	void do_erase_cases( node_base_pointer parent, node_base_pointer sibling,
						 node_base_pointer extra_black ) {
		if ( extra_black ) {
			if ( extra_black->color == RED ) {
				extra_black->color = BLACK;
				return;
			}
		}
		// check case1
		if ( sibling->color == RED ) {
			sibling->color = BLACK;
			parent->color = RED;
			if ( parent->right == sibling ) {
				sibling = sibling->left;
				rotate_left( parent );
			} else {
				sibling = sibling->right;
				rotate_right( parent );
			}
		}
		do_erase_sibling_is_black( parent, sibling, extra_black );
	}

	// case 2
	void do_erase_sibling_is_black( node_base_pointer parent,
									node_base_pointer sibling,
									node_base_pointer extra_black ) {
		if ( parent->right == extra_black ) {
			if ( sibling->left && sibling->left->color == RED ) {
				return erase_case_sibling_same_side_child_red( parent, sibling,
															   false );
			} else if ( sibling->right && sibling->right->color == RED ) {
				return erase_case_sibling_other_side_child_red( parent, sibling,
																false );
			}
		} else {
			if ( sibling->right && sibling->right->color == RED ) {
				return erase_case_sibling_same_side_child_red( parent, sibling,
															   true );
			} else if ( sibling->right && sibling->right->color == RED ) {
				return erase_case_sibling_other_side_child_red( parent, sibling,
																true );
			}
		}
		sibling->color = RED;
		if ( parent->color == RED ) {
			parent->color = BLACK;
			return;
		}
		if ( parent == _root_node ) {
			return;
		}
		node_base_pointer new_parent = parent->parent;
		if ( is_right_child( parent ) ) {
			do_erase_cases( new_parent, new_parent->left, parent );
		} else {
			do_erase_cases( new_parent, new_parent->right, parent );
		}
	}

	// erase case3
	void erase_case_sibling_other_side_child_red(
		node_base_pointer parent, node_base_pointer sibling,
		bool sibling_is_right_child ) {
		node_base_pointer sibling_child;
		sibling->color = BLACK;
		if ( sibling_is_right_child ) {
			sibling_child = sibling->left;
			sibling_child->color = parent->color;
			rotate_right( sibling );
			rotate_left( parent );
		} else {
			sibling_child = sibling->right;
			sibling_child->color = parent->color;
			rotate_left( sibling );
			rotate_right( parent );
		}
	}

	// erase case4
	void erase_case_sibling_same_side_child_red( node_base_pointer parent,
												 node_base_pointer sibling,
												 bool sibling_is_right_child ) {
		sibling->color = parent->color;
		parent->color = BLACK;
		if ( sibling_is_right_child ) {
			sibling->right->color = BLACK;
			rotate_left( parent );
		} else {
			sibling->left->color = BLACK;
			rotate_right( parent );
		}
	}

	// case1: sibling - red.
	// case2: sibling - black, sibling's children - black
	// case3: sibling - black, other side sibling's child - red
	// case4: sibling - black, same side sibling's child - red
	size_type erase( const key_type& key ) {
		ft::pair<node_base_pointer, bool> tmp = find_node( key );
		if ( tmp.second == false ) {
			return 0;
		}
		node_base_pointer extra_black_parent = NULL;
		node_base_pointer extra_black = NULL;
		// bool      extra_black_is_right_child;
		bool              del_node_color_is_black;
		node_base_pointer swap_node = NULL;
		node_base_pointer del_node = tmp.first;
		node_base_pointer parent = del_node->parent;
		node_base_pointer left = del_node->left;
		node_base_pointer right = del_node->right;
		// One or zero child node.
		if ( left == NULL || right == NULL || right == end_ptr() ) {
			// One right child node.
			if ( left == NULL && right != NULL && right != end_ptr() ) {
				if ( del_node == _root_node ) {
					_root_node = right;
					_begin_node = right;
				} else {
					if ( parent->right == del_node ) {
						parent->right = right;
					} else {
						parent->left = right;
						if ( _begin_node == del_node ) {
							_begin_node = right;
						}
					}
				}
				right->parent = parent;
				swap_node = right;
			}
			// One left child node.
			else if ( ( right == NULL || right == end_ptr() ) && left ) {
				if ( del_node == _root_node ) {
					_root_node = left;
					__end_node.left = left;
					left->right = end_ptr();
				} else {
					if ( parent->right == del_node ) {
						parent->right = left;
						if ( right == end_ptr() ) {
							left->right = end_ptr();
							__end_node.left = left;
						}
					} else {
						parent->left = left;
					}
				}
				left->parent = parent;
				swap_node = left;
			}
			// Zero child node.
			else {
				if ( del_node == _root_node ) {
					_root_node = end_ptr();
					_begin_node = end_ptr();
					__end_node.left = end_ptr();
				} else {
					if ( parent->right == del_node ) {
						parent->right = del_node->right;
					} else {
						parent->left = NULL;
					}
				}
			}
			del_node_color_is_black = ( del_node->color == BLACK );
			if ( del_node_color_is_black ) {
				extra_black = swap_node;
				if ( swap_node ) {
					extra_black_parent = swap_node->parent;
				}
			}
		}
		// Two children node.
		else {
			swap_node = left->maximum( left );
			if ( swap_node != left ) {
				swap_node->parent->right = NULL;
				swap_node->left = left;
				left->parent = swap_node;
				extra_black_parent = swap_node->parent;
			}
			swap_node->parent = parent;
			swap_node->right = right;
			if ( del_node == _root_node ) {
				_root_node = swap_node;
			} else {
				if ( is_right_child( del_node ) ) {
					parent->right = swap_node;
				} else {
					parent->left = swap_node;
				}
			}
			right->parent = swap_node;
			del_node_color_is_black = ( swap_node->color == BLACK );
			swap_node->color = del_node->color;
			if ( del_node_color_is_black ) {
				if ( swap_node == left ) {
					extra_black = swap_node->left;
					extra_black_parent = swap_node;
				}
			}
		}
		--_size;
		_alloc.destroy( static_cast<node_pointer>( del_node ) );
		_alloc.deallocate( static_cast<node_pointer>( del_node ), 1 );
		if ( del_node_color_is_black ) {
			if ( extra_black_parent->right == extra_black ) {
				do_erase_cases( extra_black_parent, extra_black_parent->left,
								extra_black );
			} else {
				do_erase_cases( extra_black_parent, extra_black_parent->right,
								extra_black );
			}
		}
		return 1;
	}

	~rbtree() {
		this->clear();
	}

	// print
	void print_tree() {
		printTree( _root_node, NULL, false );
	}

	struct Trunk {
		Trunk*      prev;
		std::string str;

		Trunk( Trunk* prev, std::string str ) {
			this->prev = prev;
			this->str = str;
		}
	};

	void showTrunks( Trunk* p ) {
		if ( p == NULL ) {
			return;
		}

		showTrunks( p->prev );
		std::cout << p->str;
	}

	void printTree( node_base_pointer root, Trunk* prev, bool isLeft ) {
		if ( root == NULL ) {
			return;
		}

		std::string prev_str = "    ";
		Trunk*      trunk = new Trunk( prev, prev_str );

		printTree( root->right, trunk, true );

		if ( !prev ) {
			trunk->str = "———";
		} else if ( isLeft ) {
			trunk->str = ".———";
			prev_str = "   |";
		} else {
			trunk->str = "`———";
			prev->str = prev_str;
		}

		showTrunks( trunk );
		if ( root == end_ptr() ) {
			std::cout << " end_node!" << std::endl;
			delete trunk;
			return;
		} else {
			if ( root->color == RED ) {
				std::cout << "\033[0;31m"
						  << get_node_value( root )._get_value().first
						  << "\033[0;49m" << std::endl;
			} else {
				std::cout << get_node_value( root )._get_value().first
						  << std::endl;
			}
			if ( prev ) {
				prev->str = prev_str;
			}
			trunk->str = "   |";
		}

		printTree( root->left, trunk, false );
		delete trunk;
	}

	void clear() {
		if ( _root_node == end_ptr() ) {
			return;
		}
		del_node( _root_node );
		_size = 0;
		_root_node = end_ptr();
		_begin_node = end_ptr();
		__end_node.left = end_ptr();
	}

	void del_node( node_base_pointer node ) {
		if ( node == NULL || node == end_ptr() ) {
			return;
		}
		del_node( node->left );
		del_node( node->right );
		_alloc.destroy( static_cast<node_pointer>( node ) );
		_alloc.deallocate( static_cast<node_pointer>( node ), 1 );
	}
};

}  // namespace ft

#endif
