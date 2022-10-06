/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/10/07 00:25:31 by seseo            ###   ########.fr       */
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

   private:
	link_type node;

   public:
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

   protected:
	typedef typename get_node_type<T>::node_type node_type;
	typedef node_type*                           link_type;
	typedef const node_type*                     const_link_type;

   public:
	typedef rbtree_iterator<T, link_type, difference_type> iterator;
	typedef const iterator                                 const_iterator;

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
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
		__end_node.color = BLACK;
		__end_node.left = &__end_node;
		__end_node.right = NULL;
		__end_node.parent = NULL;
	}

	rbtree( const rbtree& x ) : rbtree() {
		iterator x_begin = x.begin();
		for ( ; x_begin != x.end(); ++x_begin ) {
			insert( *x_begin );
		}
	}

	~rbtree() {
		this->clear();
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
		link_type l_child_node = target_node->right;
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
	ft::pair<link_type, bool> find_node( const value_type& val ) {
		link_type cur = _root_node;
		link_type parent = _root_node;
		if ( _comp( val, cur->value_field ) ) {
			cur = cur->left;
		} else {
			if ( _comp( cur->value_field, val ) ) {
				cur = cur->right;
			} else {
				return ft::pair<link_type, bool>( cur, true );
			}
		}
		while ( cur != NULL || cur != end_node_ptr() ) {
			if ( _comp( val, cur->value_field ) ) {
				prev = cur;
				cur = cur->left;
			} else {
				if ( _comp( cur->value_field, val ) ) {
					prev = cur;
					cur = cur->right;
				} else {
					return ft::pair<link_type, bool>( cur, true );
				}
			}
		}
		return ft::pair<link_type, bool>( prev, false );
	}

	// case 1 : subtree root - black, both child - red, grand child red.
	// case 2 : subtree root - black, left child and left child's right grand
	// child or right child and right child's left grand child - red.
	// case 3 : subtree root - black, left child and left child's left grand
	// child or right child and right child's right grand child - red.
	// case 4 : subtree root - red.
	ft::pair<iterator, bool> insert( const value_type& val ) {
		if ( this->_size == 0 ) {
			node_type __new_node( val );
			link_type new_node = _alloc.allocate( 1 );
			_alloc.construct( new_node, __new_node );

			_root_node = new_node;
			__end_node.left = _root_node;
			_begin_node = _root_node;
			new_node->color = BLACK;
			++_size;
			return make_pair( iterator( _root_node ), true );
		}

		ft::pair<link_type, bool> result = find_node( val );
		if ( result.second == true ) {
			return make_pair( iterator( result.first ), false );
		}

		node_type __new_node( val );
		link_type new_node = _alloc.allocate( 1 );
		_alloc.construct( new_node, __new_node );

		link_type parent_node = result.first;
		bool      child_is_right;

		if ( _comp( parent_node->value_field, val ) ) {
			parent_node->right = new_node;
			child_is_right = true;
		} else {
			parent_node->left = new_node;
			child_is_right = false;
		}
		new_node->parent = parent_node;
		if ( parent_node->color == BLACK ) {
			return make_pair( iterator( new_node ), true );
		}
		// balance check
		link_type grand_parent = parent_node->parent;
		link_type uncle;
		bool      parent_is_right = is_right_child( parent_node );
		if ( parent_is_right ) {
			uncle = grand_parent->left;
		} else {
			uncle = grand_parent->right;
		}

		// case 1 check
		if ( uncle && uncle->color == RED ) {
			grand_parent->color = RED;
			uncle->color = BLACK;
			parent->color = BLACK;
			// case 4 check
			if ( grand_parent == _root_node ) {
				grand_parent->color = BLACK;
			}
			// case 2, 3 check
			else if ( grand_parent->parent->color == RED ) {
				link_type gg_p = grand_parent->parent;
				link_type ggg_p = gg_p->parent;
				bool      g_p_is_right = is_right_child( grand_parent );
				bool      gg_p_is_right = is_right_child( gg_p );
				// case 2 check
				if ( g_p_is_right ^ gg_p_is_right ) {
					if ( g_p_is_right ) {
						rotate_left( gg_p );
						ggg_p->color = RED;
						gg_p->color = BLACK;
						rotate_right( ggg_p );
					} else {
						rotate_right( gg_p );
						ggg_p->color = RED;
						gg_p->color = BLACK;
						rotate_left( ggg_p );
					}
				} else {
					if ( gg_p_is_right ) {
						rotate_left( ggg_p );
					} else {
						rotate_right( ggg_p );
					}
				}
			}
		}
		// case 2 or 3
		else {
			// case 2 check
			if ( parent_is_right ^ child_is_right ) {
				if ( child_is_right ) {
					rotate_left( parent_node );
					grand_parent->color = RED;
					parent_node->color = BLACK;
					rotate_right( grand_parent );
				} else {
					rotate_right( parent_node );
					grand_parent->color = RED;
					parent_node->color = BLACK;
					rotate_left( grand_parent );
				}
			}
			// case 3
			else {
				if ( parent_is_right ) {
					rotate_left( grand_parent );
				} else {
					rotate_right( grand_parent );
				}
			}
		}
		if ( _comp( val, _begin_node->value_field ) ) {
			_begin_node = new_node;
		} else if ( _comp( _end_node->left->value_field, val ) ) {
			_end_node->left = new_node;
			new_node->right = _end_node;
		}
		return make_pair( iterator( new_node ), true );
	}

	link_type get_begin_node() {
		return ( _begin_node );
	}

	void clear() {
		if ( _root_node == _end_node ) {
			return;
		}
		del_node( _root_node->left );
		__end_node.left = NULL;
	}

	void del_node( link_type node ) {
		if ( node == NULL || node == _end_node ) {
			return;
		}
		del_node( node->left );
		del_node( node->right );
		_alloc.deallocate( node, 1 );
	}
};

}  // namespace ft

#endif
