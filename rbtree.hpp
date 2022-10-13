/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/10/13 22:29:24 by seseo            ###   ########.fr       */
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

template <class VoidPtr>
struct rbtree_node_base_types {
	typedef VoidPtr                            void_pointer;
	typedef rbtree_node_base<void_pointer>     node_base_type;
	typedef node_base_type*                    node_base_pointer;
	typedef rbtree_end_node<node_base_pointer> end_node_type;
	typedef end_node_type*                     end_node_pointer;
};

template <class NodePtr>
struct get_element_type {
	typedef NodePtr element_type;
};

template <class T>
struct get_element_type<T*> {
	typedef T element_type;
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
	typedef
		typename __rebind_pointer<VoidPtr, __tree_node<ValueT, VoidPtr> >::type
										_NodePtr;
	typedef __tree_node_types<_NodePtr> type;
};

template <class Pointer>
class rbtree_end_node {
   public:
	typedef Pointer pointer;

	pointer left;

	rbtree_end_node() : left( NULL );
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
	typedef T node_value_type;

	node_value_type value;

   private:
	~rbtree_node();
	rbtree_node( const rbtree_node& ref );
	rbtree_node& operator=( const rbtree_node& ref );
}

// template <class T>
// struct rbtree_node : rbtree_key_value_types<T> {
// 	typedef rbtree_node<T>*                                     link_type;
// 	typedef color_t                                             color_type;
// 	typedef typename rbtree_key_value_types<T>::key_type        key_type;
// 	typedef typename rbtree_key_value_types<T>::value_type      value_type;
// 	typedef typename rbtree_key_value_types<T>::node_value_type node_value_type;
// 	typedef typename rbtree_key_value_types<T>::container_value_type
// 		container_value_type;

// 	T value;

// 	rbtree_node( const T& val )
// 		: color( RED ),
// 		  parent( NULL ),
// 		  left( NULL ),
// 		  right( NULL ),
// 		  value( val ) {
// 	}
// 	rbtree_node( color_type color, link_type parent, link_type left,
// 				 link_type right, const T& val )
// 		: color( color ),
// 		  parent( parent ),
// 		  left( left ),
// 		  right( right ),
// 		  value( val ) {
// 	}

//    private:
// 	rbtree_node()
// 		: color( RED ), parent( NULL ), left( NULL ), right( NULL ), value() {
// 	}
// 	~rbtree_node() {
// 	}
// };

// template <class T>
// struct rbtree_node : public rbtree_node_base<T> {
// 	// typedef rbtree_node* link_type;
// 	// typedef color_t      color_type;
// 	typedef T key_type;
// 	typedef T value_type;
// 	typedef T node_value_type;

// 	rbtree_node() : rbtree_node_base() {
// 	}
// 	rbtree_node( const node_value_type& val )
// 		: rbtree_node_base( val.color, val.parent, val.left, val.right ) {
// 	}
// 	rbtree_node( color_type color, link_type parent, link_type left,
// 				 link_type right, const T& val )
// 		: rbtree_node_base( color, parent, left, right, val ) {
// 	}
// 	rbtree_node( const rbtree_node& node )
// 		: rbtree_node_base( node.color, node.parent, node.left, node.right,
// 							node.value ) {
// 	}
// 	~rbtree_node() {
// 	}

// 	static link_type minimum( link_type x ) {
// 		while ( x->left != NULL ) {
// 			x = x->left;
// 		}
// 		return x;
// 	}

// 	static link_type maximum( link_type x ) {
// 		while ( x->right != NULL ) {
// 			x = x->right;
// 		}
// 		return x;
// 	}

// 	key_type& get_key() {
// 		return this->value;
// 	}

// 	value_type& get_value() {
// 		return this->value;
// 	}

// 	node_value_type& get_node_value() {
// 		return this->value;
// 	}
// };

// template <class Key, class Value>
// struct rbtree_node<_value_type<Key, Value>>
// 	: public rbtree_node_base<_value_type<Key, Value>> {
// 	// typedef rbtree_node*    link_type;
// 	// typedef color_t         color_type;
// 	typedef Key                     key_type;
// 	typedef Value                   value_type;
// 	typedef _value_type<Key, Value> node_value_type;

// 	rbtree_node() : rbtree_node_base() {
// 	}
// 	rbtree_node( const node_value_type& val )
// 		: rbtree_node_base( val.color, val.parent, val.left, val.right ) {
// 	}
// 	rbtree_node( color_type color, link_type parent, link_type left,
// 				 link_type right, const T& val )
// 		: rbtree_node_base( color, parent, left, right, val ) {
// 	}
// 	rbtree_node( const rbtree_node& node )
// 		: rbtree_node_base( node.color, node.parent, node.left, node.right,
// 							node.value ) {
// 	}
// 	~rbtree_node() {
// 	}

// 	static link_type minimum( link_type x ) {
// 		while ( x->left != NULL ) {
// 			x = x->left;
// 		}
// 		return x;
// 	}

// 	static link_type maximum( link_type x ) {
// 		while ( x->right != NULL ) {
// 			x = x->right;
// 		}
// 		return x;
// 	}

// 	key_type& get_key() {
// 		return this->value.first();
// 	}

// 	value_type& get_value() {
// 		return this->value.second();
// 	}

// 	node_value_type& get_node_value() {
// 		return this->value;
// 	}
// };

// template <class T, bool = ft::is_pair<T>::value>
// class get_node_type {
//    public:
// 	typedef rbtree_node<T>                           node_type;
// 	typedef typename rbtree_node<T>::node_value_type node_value_type;
// 	typedef typename rbtree_node<T>::key_type        key_type;
// 	typedef typename rbtree_node<T>::value_type      value_type;
// };

// template <class T>
// class get_node_type<T, false> {
//    public:
// 	typedef rbtree_node<T> node_type;
// 	typedef T              node_value_type;
// 	typedef T              key_type;
// 	typedef T              value_type;
// };

template <class T, class DiffType>
class rbtree_iterator {
   public:
	// typedef typename get_node_type<T>::node_type  node_type;
	// typedef typename get_node_type<T>::value_type value_type;
	// typedef typename get_node_type<T>::key_type   key_type;
	typedef rbtree_node<T>                  node_type;
	typedef node_type*                      link_type;
	typedef node_type&                      reference;
	typedef DiffType                        difference_type;
	typedef std::bidirectional_iterator_tag iterator_category;

   private:
	link_type node;

   public:
	rbtree_iterator() : node( NULL ) {
	}

	rbtree_iterator( link_type node ) : node( node ) {
	}

	link_type base() {
		return node;
	}

	void incremet() {
		if ( node->right != NULL ) {
			node = node->right;
			while ( node->left != NULL ) {
				node = node->left;
			}
		} else {
			link_type tmp = node->parent;
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
			link_type tmp = node->parent;
			while ( node == tmp->left ) {
				node = tmp;
				tmp = tmp->parent;
			}
			if ( node->left != tmp ) node = tmp;
		}
	}
};

template <class T, class Compare, class Allocator>
class rbtree {
   public:
	typedef T         value_type;
	typedef Compare   value_compare;
	typedef Allocator allocator_type;

	typedef typename allocator_type::template rebind<
		rbtree_node<T, VoidPtr> >::other             node_allocator_type;
	typedef typename rbtree_node<T>::node_value_type node_value_type;
	typedef typename rbtree_node<T>::key_type        key_type;
	typedef typename rbtree_node<T>::value_type      value_type;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;

   protected:
	typedef rbtree_node<T>   node_type;
	typedef node_type*       link_type;
	typedef const node_type* const_link_type;

   public:
	typedef rbtree_iterator<T, difference_type>       iterator;
	typedef rbtree_iterator<const T, difference_type> const_iterator;

   private:
	node_type      __end_node;
	link_type      _root_node;
	link_type      _begin_node;
	value_compare  _comp;
	size_type      _size;
	allocator_type _alloc;

   public:
	size_type get_value_type_size() {
		return ( sizeof( value_type ) );
	}
	size_type get_key_type_size() {
		return ( sizeof( key_type ) );
	}

	rbtree()
		: __end_node(),
		  _root_node( &__end_node ),
		  _begin_node( &__end_node ),
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
		__end_node.color = BLACK;
		__end_node.left = &__end_node;
	}

	rbtree( const rbtree& x )
		: __end_node(),
		  _root_node( &__end_node ),
		  _begin_node( &__end_node ),
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
		__end_node.color = BLACK;
		__end_node.left = &__end_node;
		iterator x_begin = x.begin();
		for ( ; x_begin != x.end(); ++x_begin ) {
			insert( *x_begin );
		}
	}

	rbtree( value_compare comp, allocator_type alloc )
		: __end_node(),
		  _root_node( &__end_node ),
		  _begin_node( &__end_node ),
		  _comp( comp ),
		  _size( 0 ),
		  _alloc( alloc ) {
	}

	~rbtree() {
		// this->clear();
	}

	iterator begin() {
		return iterator( _begin_node );
	}

	link_type end_node_ptr() {
		return &__end_node;
	}

	bool is_right_child( link_type target_node ) {
		return target_node->parent->right == target_node;
	}

	void rotate_left( link_type target_node ) {
		if ( target_node == NULL || target_node == end_node_ptr() ) {
			return;
		}
		link_type r_child_node = target_node->right;
		if ( r_child_node == end_node_ptr() ) {
			return;
		}
		link_type parent_node = target_node->parent;
		link_type g_child_node = r_child_node->left;

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
		if ( g_child_node != NULL && g_child_node != end_node_ptr() ) {
			g_child_node->parent = target_node;
		}
	}

	void rotate_right( link_type target_node ) {
		if ( target_node == NULL || target_node == end_node_ptr() ) {
			return;
		}
		link_type l_child_node = target_node->left;
		if ( l_child_node == end_node_ptr() ) {
			return;
		}
		link_type parent_node = target_node->parent;
		link_type g_child_node = l_child_node->right;

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
		if ( g_child_node != NULL && g_child_node != end_node_ptr() ) {
			g_child_node->parent = target_node;
		}
	}

	// return value is input value link_type with true, but if not found, it
	// will return parent node with false.
	// ft::pair<link_type, bool> find_node( const node_value_type& val ) {
	// 	link_type cur = _root_node;
	// 	link_type parent = _root_node;
	// 	if ( _comp( val, cur->value ) ) {
	// 		cur = cur->left;
	// 	} else {
	// 		if ( _comp( cur->value, val ) ) {
	// 			cur = cur->right;
	// 		} else {
	// 			return ft::pair<link_type, bool>( cur, true );
	// 		}
	// 	}
	// 	while ( cur != NULL && cur != end_node_ptr() ) {
	// 		if ( _comp( val, cur->value ) ) {
	// 			parent = cur;
	// 			cur = cur->left;
	// 		} else {
	// 			if ( _comp( cur->value, val ) ) {
	// 				parent = cur;
	// 				cur = cur->right;
	// 			} else {
	// 				return ft::pair<link_type, bool>( cur, true );
	// 			}
	// 		}
	// 	}
	// 	return ft::pair<link_type, bool>( parent, false );
	// }

	ft::pair<link_type, bool> find_node( const key_type& key ) {
		link_type cur = _root_node;
		link_type parent = _root_node;
		if ( _comp() ) {
			cur = cur->left;
		} else {
			if ( _comp( node_type::_get_key( cur->value ), key ) ) {
				cur = cur->right;
			} else {
				return ft::pair<link_type, bool>( cur, true );
			}
		}
		while ( cur != NULL && cur != end_node_ptr() ) {
			if ( _comp( key, node_type::_get_key( cur->value ) ) ) {
				parent = cur;
				cur = cur->left;
			} else {
				if ( _comp( node_type::_get_key( cur->value ), key ) ) {
					parent = cur;
					cur = cur->right;
				} else {
					return ft::pair<link_type, bool>( cur, true );
				}
			}
		}
		return ft::pair<link_type, bool>( parent, false );
	}

	// Search starts from the hint node.
	// If the input value is not found, search agin from the root node.
	ft::pair<link_type, bool> find_node( link_type hint, const key_type& key ) {
		link_type cur = hint;
		link_type parent = hint;
		link_type ret_candidate;
		if ( _comp( key, cur->value ) ) {
			cur = cur->left;
		} else {
			if ( _comp( cur->value, key ) ) {
				cur = cur->right;
			} else {
				return ft::pair<link_type, bool>( cur, true );
			}
		}
		while ( cur != NULL && cur != end_node_ptr() ) {
			if ( _comp( key, cur->value ) ) {
				parent = cur;
				cur = cur->left;
			} else {
				if ( _comp( cur->value, key ) ) {
					parent = cur;
					cur = cur->right;
				} else {
					return ft::pair<link_type, bool>( cur, true );
				}
			}
		}
		ret_candidate = parent;
		cur = _root_node;
		parent = _root_node;
		if ( _comp( key, cur->value ) ) {
			cur = cur->left;
		} else {
			if ( _comp( cur->value, key ) ) {
				cur = cur->right;
			} else {
				return ft::pair<link_type, bool>( cur, true );
			}
		}
		while ( cur != NULL && cur != end_node_ptr() && cur != hint ) {
			if ( _comp( key, cur->value ) ) {
				parent = cur;
				cur = cur->left;
			} else {
				if ( _comp( cur->value, key ) ) {
					parent = cur;
					cur = cur->right;
				} else {
					return ft::pair<link_type, bool>( cur, true );
				}
			}
		}
		return ft::pair<link_type, bool>( ret_candidate, false );
	}

	// ft::pair<link_type, bool> find_node_pair( link_type       hint,
	// 										  const key_type& key ) {
	// 	link_type cur = hint;
	// 	link_type parent = hint;
	// 	link_type ret_candidate;
	// 	if ( _comp( key, ( cur->value ).first() ) ) {
	// 		cur = cur->left;
	// 	} else {
	// 		if ( _comp( ( cur->value ).first(), key ) ) {
	// 			cur = cur->right;
	// 		} else {
	// 			return ft::pair<link_type, bool>( cur, true );
	// 		}
	// 	}
	// 	while ( cur != NULL && cur != end_node_ptr() ) {
	// 		if ( _comp( key, ( cur->value ).first() ) ) {
	// 			parent = cur;
	// 			cur = cur->left;
	// 		} else {
	// 			if ( _comp( cur->value, key ) ) {
	// 				parent = cur;
	// 				cur = cur->right;
	// 			} else {
	// 				return ft::pair<link_type, bool>( cur, true );
	// 			}
	// 		}
	// 	}
	// 	ret_candidate = parent;
	// 	cur = _root_node;
	// 	parent = _root_node;
	// 	if ( _comp( key, ( cur->value ).first() ) ) {
	// 		cur = cur->left;
	// 	} else {
	// 		if ( _comp( cur->value, key ) ) {
	// 			cur = cur->right;
	// 		} else {
	// 			return ft::pair<link_type, bool>( cur, true );
	// 		}
	// 	}
	// 	while ( cur != NULL && cur != end_node_ptr() && cur != hint ) {
	// 		if ( _comp( key, ( cur->value ).first() ) ) {
	// 			parent = cur;
	// 			cur = cur->left;
	// 		} else {
	// 			if ( _comp( cur->value, key ) ) {
	// 				parent = cur;
	// 				cur = cur->right;
	// 			} else {
	// 				return ft::pair<link_type, bool>( cur, true );
	// 			}
	// 		}
	// 	}
	// 	return ft::pair<link_type, bool>( ret_candidate, false );
	// }

	bool check_uncle_is_red_and_make_balance( link_type grand_parent,
											  link_type parent ) {
		bool      parent_is_right = is_right_child( parent );
		link_type uncle;

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
			link_type gg_parent = grand_parent->parent;
			if ( gg_parent == NULL || gg_parent->color == BLACK ) {
				return true;
			}
			link_type ggg_parent = gg_parent->parent;
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

	void check_rotation_dir_and_make_balance( link_type grand_parent,
											  link_type parent,
											  link_type child ) {
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

	// case 1 : grand parent - black, uncle and parent - red, child - red.
	// case 2 : grand parent - black, parent - red, other side child - red.
	// case 3 : grand parent - black, parent - red, same side child - red.
	// case 4 : root - red.
	ft::pair<iterator, bool> insert( const node_value_type& val ) {
		if ( this->_size == 0 ) {
			node_type __new_node( BLACK, NULL, NULL, end_node_ptr(), val );
			link_type new_node = _alloc.allocate( 1 );
			_alloc.construct( new_node, __new_node );

			_root_node = new_node;
			__end_node.left = _root_node;
			_begin_node = _root_node;
			++_size;
			return make_pair( iterator( _root_node ), true );
		}

		node_type __new_node( val );

		ft::pair<link_type, bool> result =
			find_node( node_type::_get_key( __new_node.value ) );
		if ( result.second == true ) {
			return make_pair( iterator( result.first ), false );
		}

		link_type new_node = _alloc.allocate( 1 );
		if ( _comp( node_type::_get_key( __end_node.left->value ),
					node_type::_get_key( __new_node.value ) ) ) {
			__end_node.left->right = new_node;
			__new_node.right = end_node_ptr();
			__end_node.left = new_node;
		} else if ( _comp( node_type::_get_key( __new_node.value ),
						   node_type::_get_key( _begin_node->value ) ) ) {
			_begin_node = new_node;
		}
		_alloc.construct( new_node, __new_node );
		++_size;

		link_type parent_node = result.first;

		if ( _comp( node_type::_get_key( parent_node->value ),
					node_type::_get_key( __new_node.value ) ) ) {
			parent_node->right = new_node;
		} else {
			parent_node->left = new_node;
		}
		new_node->parent = parent_node;
		if ( parent_node->color == BLACK ) {
			return make_pair( iterator( new_node ), true );
		}
		link_type g_parent = parent_node->parent;

		// Unbalanced state. Check case1 to make balance.
		if ( check_uncle_is_red_and_make_balance( g_parent, parent_node ) ) {
			return make_pair( iterator( new_node ), true );
		}
		// Check case2 or case3 and rotate to make balance.
		check_rotation_dir_and_make_balance( g_parent, parent_node, new_node );
		return make_pair( iterator( new_node ), true );
	}

	// ft::pair<iterator, bool> insert( const node_value_type& val ) {
	// 	if ( this->_size == 0 ) {
	// 		node_type __new_node( BLACK, NULL, NULL, end_node_ptr(), val );
	// 		link_type new_node = _alloc.allocate( 1 );
	// 		_alloc.construct( new_node, __new_node );

	// 		_root_node = new_node;
	// 		__end_node.left = _root_node;
	// 		_begin_node = _root_node;
	// 		++_size;
	// 		return make_pair( iterator( _root_node ), true );
	// 	}

	// 	ft::pair<link_type, bool> result = find_node( val );
	// 	if ( result.second == true ) {
	// 		return make_pair( iterator( result.first ), false );
	// 	}

	// 	node_type __new_node( val );
	// 	link_type new_node = _alloc.allocate( 1 );
	// 	if ( _comp( __end_node.value, val ) ) {
	// 		__new_node.right = end_node_ptr();
	// 		__end_node.left = new_node;
	// 	} else if ( _comp( val, _begin_node->value ) ) {
	// 		_begin_node = new_node;
	// 	}
	// 	_alloc.construct( new_node, __new_node );
	// 	++_size;

	// 	link_type parent_node = result.first;

	// 	if ( _comp( parent_node->value, val ) ) {
	// 		parent_node->right = new_node;
	// 	} else {
	// 		parent_node->left = new_node;
	// 	}
	// 	new_node->parent = parent_node;
	// 	if ( parent_node->color == BLACK ) {
	// 		return make_pair( iterator( new_node ), true );
	// 	}
	// 	link_type g_parent = parent_node->parent;

	// 	// Unbalanced state. Check case1 to make balance.
	// 	if ( check_uncle_is_red_and_make_balance( g_parent, parent_node ) )
	// { 		return make_pair( iterator( new_node ), true );
	// 	}
	// 	// Check case2 or case3 and rotate to make balance.
	// 	check_rotation_dir_and_make_balance( g_parent, parent_node, new_node
	// ); 	return make_pair( iterator( new_node ), true );
	// }

	// erase node function.
	void do_erase_cases( link_type parent, link_type sibling,
						 link_type extra_black ) {
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
	void do_erase_sibling_is_black( link_type parent, link_type sibling,
									link_type extra_black ) {
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
		link_type new_parent = parent->parent;
		if ( is_right_child( parent ) ) {
			do_erase_cases( new_parent, new_parent->left, parent );
		} else {
			do_erase_cases( new_parent, new_parent->right, parent );
		}
	}

	// erase case3
	void erase_case_sibling_other_side_child_red(
		link_type parent, link_type sibling, bool sibling_is_right_child ) {
		link_type sibling_child;
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
	void erase_case_sibling_same_side_child_red( link_type parent,
												 link_type sibling,
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
	size_type erase( node_value_type val ) {
		ft::pair<iterator, bool> tmp = find_node( val );
		if ( tmp.second == false ) {
			return 0;
		}
		link_type extra_black_parent = NULL;
		link_type extra_black = NULL;
		// bool      extra_black_is_right_child;
		bool      del_node_color_is_black;
		link_type swap_node = NULL;
		link_type del_node = ( tmp.first ).base();
		link_type parent = del_node->parent;
		link_type left = del_node->left;
		link_type right = del_node->right;
		// One or zero child node.
		if ( left == NULL || right == NULL || right == end_node_ptr() ) {
			// One right child node.
			if ( left == NULL && right != NULL && right != end_node_ptr() ) {
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
			else if ( ( right == NULL || right == end_node_ptr() ) && left ) {
				if ( del_node == _root_node ) {
					_root_node = left;
					__end_node.left = left;
					left->right = end_node_ptr();
				} else {
					if ( parent->right == del_node ) {
						parent->right = left;
						if ( right == end_node_ptr() ) {
							left->right = end_node_ptr();
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
					_root_node = end_node_ptr();
					_begin_node = end_node_ptr();
					__end_node.left = end_node_ptr();
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
		_alloc.destroy( del_node );
		_alloc.deallocate( del_node, 1 );
		// if ( extra_black )
		// 	std::cout << "extra_black val:" << extra_black->value <<
		// std::endl; std::cout << extra_black << std::endl; if (
		// extra_black_parent ) 	std::cout << "parent val:" <<
		// extra_black_parent->value
		// 			  << std::endl;
		// std::cout << extra_black_parent << std::endl;
		// print_tree();
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

	link_type get_begin_node() {
		return _begin_node;
	}

	void clear() {
		if ( _root_node == end_node_ptr() ) {
			return;
		}
		del_node( _root_node );
		_size = 0;
		_root_node = end_node_ptr();
		_begin_node = end_node_ptr();
		__end_node.left = end_node_ptr();
	}

	void del_node( link_type node ) {
		if ( node == NULL || node == end_node_ptr() ) {
			return;
		}
		del_node( node->left );
		del_node( node->right );
		_alloc.destroy( node );
		_alloc.deallocate( node, 1 );
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

	void print_tree() {
		printTree( _root_node, NULL, false );
	}

	void printTree( link_type root, Trunk* prev, bool isLeft ) {
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
		if ( root == end_node_ptr() ) {
			std::cout << " end_node!" << std::endl;
			delete trunk;
			return;
		} else {
			if ( root->color == RED ) {
				std::cout << "\033[0;31m" << ( root->value ).first
						  << "\033[0;49m" << std::endl;
			} else {
				std::cout << ( root->value ).first << std::endl;
			}
			if ( prev ) {
				prev->str = prev_str;
			}
			trunk->str = "   |";
		}

		printTree( root->left, trunk, false );
		delete trunk;
	}
};

}  // namespace ft

#endif
