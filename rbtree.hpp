/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/10/09 01:06:41 by seseo            ###   ########.fr       */
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

template <class T>
class rbtree_node {
   public:
	typedef rbtree_node<T>* link_type;
	typedef color_t         color_type;

   public:
	color_type color;
	link_type  parent;
	link_type  left;
	link_type  right;
	T          value;

   public:
	rbtree_node()
		: color( RED ), parent( NULL ), left( NULL ), right( NULL ), value() {
	}
	rbtree_node( const T& val )
		: color( RED ),
		  parent( NULL ),
		  left( NULL ),
		  right( NULL ),
		  value( val ) {
	}
	rbtree_node( color_type color, link_type parent, link_type left,
				 link_type right, const T& val )
		: color( color ),
		  parent( parent ),
		  left( left ),
		  right( right ),
		  value( val ) {
	}
	rbtree_node( const rbtree_node& node )
		: color( node.color ),
		  parent( node.parent ),
		  left( node.left ),
		  right( node.right ),
		  value( node.value ) {
	}
	static link_type minimum( link_type x ) {
		while ( x->left != NULL ) {
			x = x->left;
		}
		return x;
	}

	static link_type maximum( link_type x ) {
		while ( x->right != NULL ) {
			x = x->right;
		}
		return x;
	}
};

template <class T, bool = ft::is_pair<T>::value>
class get_node_type {
   public:
	typedef rbtree_node<T>          node_type;
	typedef T                       input_type;
	typedef typename T::first_type  key_type;
	typedef typename T::second_type value_type;
};

template <class T>
class get_node_type<T, false> {
   public:
	typedef rbtree_node<T> node_type;
	typedef T              input_type;
	typedef T              key_type;
	typedef T              value_type;
};

// template<class T, bool = ft::is_pair<T>::value>
// class get_key_from_input {
// 	public:
// 		T val =
// }

template <class T, class NodePtr, class DiffType>
class rbtree_iterator {
   public:
	typedef NodePtr                               link_type;
	typedef typename get_node_type<T>::node_type  node_type;
	typedef typename get_node_type<T>::value_type value_type;
	typedef typename get_node_type<T>::key_type   key_type;
	typedef DiffType                              difference_type;
	typedef std::bidirectional_iterator_tag       iterator_category;

   private:
	link_type node;

   public:
	rbtree_iterator() : node( NULL ) {
	}

	rbtree_iterator( link_type node ) : node( node ) {
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

template <class T,
		  class Compare = std::less<typename get_node_type<T>::key_type>,
		  class Allocator = std::allocator<T> >
class rbtree {
   public:
	typedef typename get_node_type<T>::input_type input_type;
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
	ft::pair<link_type, bool> find_node( const input_type& val ) {
		link_type cur = _root_node;
		link_type parent = _root_node;
		if ( _comp( val, cur->value ) ) {
			cur = cur->left;
		} else {
			if ( _comp( cur->value, val ) ) {
				cur = cur->right;
			} else {
				return ft::pair<link_type, bool>( cur, true );
			}
		}
		while ( cur != NULL && cur != end_node_ptr() ) {
			if ( _comp( val, cur->value ) ) {
				parent = cur;
				cur = cur->left;
			} else {
				if ( _comp( cur->value, val ) ) {
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
	ft::pair<link_type, bool> find_node( link_type         hint,
										 const input_type& val ) {
		link_type cur = hint;
		link_type parent = hint;
		link_type ret_candidate;
		if ( _comp( val, cur->value ) ) {
			cur = cur->left;
		} else {
			if ( _comp( cur->value, val ) ) {
				cur = cur->right;
			} else {
				return ft::pair<link_type, bool>( cur, true );
			}
		}
		while ( cur != NULL && cur != end_node_ptr() ) {
			if ( _comp( val, cur->value ) ) {
				parent = cur;
				cur = cur->left;
			} else {
				if ( _comp( cur->value, val ) ) {
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
		if ( _comp( val, cur->value ) ) {
			cur = cur->left;
		} else {
			if ( _comp( cur->value, val ) ) {
				cur = cur->right;
			} else {
				return ft::pair<link_type, bool>( cur, true );
			}
		}
		while ( cur != NULL && cur != end_node_ptr() && cur != hint ) {
			if ( _comp( val, cur->value ) ) {
				parent = cur;
				cur = cur->left;
			} else {
				if ( _comp( cur->value, val ) ) {
					parent = cur;
					cur = cur->right;
				} else {
					return ft::pair<link_type, bool>( cur, true );
				}
			}
		}
		return ft::pair<link_type, bool>( ret_candidate, false );
	}

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
	ft::pair<iterator, bool> insert( const input_type& val ) {
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

		ft::pair<link_type, bool> result = find_node( val );
		if ( result.second == true ) {
			return make_pair( iterator( result.first ), false );
		}

		node_type __new_node( val );
		link_type new_node = _alloc.allocate( 1 );
		if ( _comp( __end_node.value, val ) ) {
			__new_node.right = end_node_ptr();
			__end_node.left = new_node;
		} else if ( _comp( val, _begin_node->value ) ) {
			_begin_node = new_node;
		}
		_alloc.construct( new_node, __new_node );
		++_size;

		link_type parent_node = result.first;

		if ( _comp( parent_node->value, val ) ) {
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

	void erase( input_type val ) {
		find_node( val );
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
				std::cout << "\033[0;31m" << root->value << "\033[0;49m"
						  << std::endl;
			} else {
				std::cout << root->value << std::endl;
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
