/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/10/05 23:12:17 by seseo            ###   ########.fr       */
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

struct rbtree_node_base {
	typedef color_t           color_type;
	typedef rbtree_node_base* base_ptr;

	color_type color;
	base_ptr   parent;
	base_ptr   left;
	base_ptr   right;

	static base_ptr minimum( base_ptr x ) {
		while ( x->left != NULL ) {
			x = x->left;
		}
		return x;
	}

	static base_ptr maximum( base_ptr x ) {
		while ( x->right != NULL ) {
			x = x->right;
		}
		return x;
	}
};

template <class value>
class rbtree_node : public rbtree_node_base {
   public:
	typedef rbtree_node<value>* link_type;

   public:
	value value_field;

   public:
	rbtree_node()
		: color( RED ),
		  left( NULL ),
		  right( NULL ),
		  parent( NULL ),
		  value_field() {
	}
	rbtree_node( const value& val )
		: color( RED ),
		  left( NULL ),
		  right( NULL ),
		  parent( NULL ),
		  value_field( val ) {
	}
	rbtree_node( const rbtree_node& node )
		: color( node.color ),
		  left( node.left ),
		  right( node.right ),
		  parent( node.parent ),
		  value_field( node.value_field ) {
	}
};

template <class T, bool = ft::is_pair<T>::value>
class get_node_type {
   public:
	typedef rbtree_node<T>          node_type;
	typedef typename T::first_type  key_type;
	typedef typename T::second_type value_type;
};

template <class T>
class get_node_type<T, false> {
   public:
	typedef rbtree_node<T> node_type;
	typedef T              key_type;
	typedef T              value_type;
};

template <class T, class NodePtr, class DiffType>
class rbtree_iterator {
   public:
	typedef NodePtr                             link_type;
	typedef typename rbtree_node<T>::node_type  node_type;
	typedef typename rbtree_node<T>::value_type value_type;
	typedef typename rbtree_node<T>::key_type   key_type;
	typedef DiffType                            difference_type;
	typedef std::bidirectional_iterator_tag     iterator_category;

	link_type node;

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
			if ( node->right != tmp )
				node = tmp;
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
			if ( node->left != tmp )
				node = tmp;
		}
	}
};

template <class T,
		  class Compare = std::less<typename get_node_type<T>::key_type>,
		  class Allocator = std::allocator<T> >
class rbtree {
   public:
	typedef typename get_node_type<T>::key_type   key_type;
	typedef typename get_node_type<T>::value_type value_type;
	typedef Compare                               value_compare;
	typedef typename Allocator::template rebind<rbtree_node<T> >::other
													 allocator_type;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef rbtree_iterator_base<T>                  iterator;
	typedef const iterator                           const_iterator;

   protected:
	typedef typename get_node_type<T>::node_type node_type;
	typedef node_type*                           link_type;
	typedef const node_type*                     const_link_type;

   private:
	node_type      __end_node;
	link_type      _root_node;
	link_type      _begin_node;
	link_type      _end_node;
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
		  _begin_node( &__end_node ),
		  _end_node( &__end_node ),
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
		__end_node.color = BLACK;
		__end_node.left = &__end_node;
		__end_node.right = &__end_node;
		__end_node.parent = &__end_node;
	}
	~rbtree() {
		this->clear();
	}

	bool is_right_child( link_type target_node ) {
		return target_node->parent->right == target_node;
	}

	void rotate_left( link_type target_node ) {
		if ( target_node == NULL || target_node == _end_node ) {
			return;
		}
		link_type r_child_node = target_node->right;
		if ( r_child_node == _end_node ) {
			return;
		}
		link_type parent_node = target_node->parent;
		link_type g_child_node = r_child_node->left;

		if ( parent_node != _end_node ) {
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
		if ( g_child_node != _end_node ) {
			g_child_node->parent = target_node;
		}
	}

	void rotate_right( link_type target_node ) {
		if ( target_node == NULL || target_node == _end_node ) {
			return;
		}
		link_type l_child_node = target_node->right;
		if ( l_child_node == _end_node ) {
			return;
		}
		link_type parent_node = target_node->parent;
		link_type g_child_node = l_child_node->right;

		if ( parent_node != _end_node ) {
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
		if ( g_child_node != _end_node ) {
			g_child_node->parent = target_node;
		}
	}

	link_type find_node( const value_type& val ) {
		link_type cur = _root_node;
		if ( _comp( val, cur->value_field ) ) {
			cur = cur->left;
		} else {
			if ( _comp( cur->value_field, val ) ) {
				cur = cur->right;
			} else {
				return cur;
			}
		}
		while ( cur != _end_node ) {
			if ( _comp( val, cur->value_field ) ) {
				cur = cur->left;
			} else {
				if ( _comp( cur->value_field, val ) ) {
					cur = cur->right;
				} else {
					return cur;
				}
			}
		}
		return _end_node;
	}

	ft::pair<iterator, bool> insert( const value_type& val ) {
		if ( this->_size == 0 ) {
			node_type __new_node( val );
			link_type new_node = _alloc.allocate( 1 );
			_alloc.construct( new_node, __new_node );

			_root_node = new_node;
			_end_node->left = _root_node;
			_begin_node = _root_node;
			++_size;
			return make_pair( iterator( _root_node ), true );
		}

		link_type child_node = find_node( val );
		if ( child_node != _end_node ) {
			return make_pair( iterator( child_node ), false );
		}

		link_type cur_node = _root_node;
		link_type prev_node = _root_node;
		if ( _comp( cur_node->value_field, val ) ) {
			cur_node = cur_node->right;
		}

		while ( cur_node && _comp( cur_node->value_field, val ) ) {
			prev_node = cur_node;
			cur_node = cur_node->right;
		}

		_begin_node->left = _end_node;
		_begin_node->right = _end_node;
		return make_pair( iterator( new_node ), true );
	}

	link_type get_begin_node() {
		return ( _begin_node );
	}
	//    public:
	// 	rbtree();
	// 	~rbtree();
	// 	rbtree( const rbtree& ref );

	void clear() {
		if ( _root_node == _end_node ) {
		}
		del_node( _root_node->left );
	}

	void del_node( link_type node ) {
	}
};

}  // namespace ft

#endif
