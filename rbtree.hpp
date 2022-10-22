/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/10/22 20:37:09 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__

// #include <iterator>
// #include <__tree>
#include <iostream>  // for test
#include <memory>
#include <algorithm>
#include "iterator.hpp"
#include "rbtree_iterator.hpp"
#include "rbtree_node.hpp"

// 1. Every node is either red or black.
// 2. Root node is black.
// 3. All NIL nodes(leaf) are considered black.
// 4. A red node does not have a red child.
// 5. Every path from a given node to any of its descendant NIL nodes goes
// through the same number of black nodes.

namespace ft {

template <class Key, class Value, class GetKey, class Compare,
		  class Allocator = std::allocator<Value> >
class rbtree {
   public:
	typedef Key                                      key_type;
	typedef Value                                    value_type;
	typedef value_type*                              pointer;
	typedef const value_type*                        const_pointer;
	typedef value_type&                              reference;
	typedef const value_type&                        const_reference;
	typedef Allocator                                allocator_type;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef rbtree_node<Value>                       node;
	typedef node*                                    node_p;
	typedef rbtree_node_base                         node_base;
	typedef rbtree_node_base*                        node_base_p;
	typedef Compare                                  value_compare;

	// typedef end_node_ptr iter_pointer;

	typedef
		typename allocator_type::template rebind<node>::other node_allocator;

	typedef rbtree_iterator<value_type, reference, pointer> iterator;
	typedef rbtree_const_iterator<value_type, reference, pointer>
												 const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

   private:
	node_base      __end_node;
	node_base_p    _root_node;
	node_base_p    _begin_node;
	value_compare  _comp;
	size_type      _size;
	node_allocator _alloc;

   private:
	bool is_right_child( node_base_p target_node ) {
		return target_node->parent->right == target_node;
	}

	void rotate_left( node_base_p target_node ) {
		if ( target_node == NULL || target_node == end_node_ptr() ) {
			return;
		}
		node_base_p r_child_node = target_node->right;
		if ( r_child_node == end_node_ptr() ) {
			return;
		}
		node_base_p parent_node = target_node->parent;
		node_base_p g_child_node = r_child_node->left;

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
		if ( is_null_node( g_child_node ) == false ) {
			g_child_node->parent = target_node;
		}
	}

	void rotate_right( node_base_p target_node ) {
		if ( target_node == NULL || target_node == end_node_ptr() ) {
			return;
		}
		node_base_p l_child_node = target_node->left;
		if ( l_child_node == end_node_ptr() ) {
			return;
		}
		node_base_p parent_node = target_node->parent;
		node_base_p g_child_node = l_child_node->right;

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
		if ( is_null_node( g_child_node ) == false ) {
			g_child_node->parent = target_node;
		}
	}

	node_base_p last_node_ptr() const {
		return __end_node.left;
	}

	node_base_p end_node_ptr() const {
		return const_cast<node_base*>( &__end_node );
	}

	reference get_node_value( const node_base_p& node ) const {
		return static_cast<node_p>( node )->value;
	}

	bool is_null_node( const node_base_p& node ) const {
		return ( node == NULL || node == end_node_ptr() );
	}

	void del_node( node_base_p node ) {
		if ( is_null_node( node ) == true ) {
			return;
		}
		del_node( node->left );
		del_node( node->right );
		_alloc.destroy( static_cast<node_p>( node ) );
		_alloc.deallocate( static_cast<node_p>( node ), 1 );
	}

   public:
	rbtree()
		: __end_node(),
		  _root_node( NULL ),
		  _begin_node( end_node_ptr() ),
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
	}

	rbtree( const rbtree& x )
		: __end_node(),
		  _root_node( NULL ),
		  _begin_node( end_node_ptr() ),
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
		const_iterator x_begin = x.begin();
		while ( x_begin != x.end() ) {
			insert_unique( *x_begin++ );
		}
	}

	rbtree& operator=( const rbtree& x ) {
		if ( this != &x ) {
			this->clear();
			const_iterator x_begin = x.begin();
			while ( x_begin != x.end() ) {
				insert_unique( *x_begin++ );
			}
		}
		return *this;
	}

	rbtree( value_compare comp, allocator_type alloc )
		: __end_node(),
		  _root_node( NULL ),
		  _begin_node( end_node_ptr() ),
		  _comp( comp ),
		  _size( 0 ),
		  _alloc( alloc ) {
	}

	~rbtree() {
		this->clear();
	}

	iterator begin() {
		return iterator( _begin_node );
	}

	const_iterator begin() const {
		return const_iterator( _begin_node );
	}

	iterator end() {
		return iterator( end_node_ptr() );
	}

	const_iterator end() const {
		return const_iterator( const_cast<node_base*>( end_node_ptr() ) );
	}

	size_type size() const {
		return _size;
	}

	size_type max_size() const {
		return std::min<size_type>(
			_alloc.max_size(), std::numeric_limits<difference_type>::max() );
	}

	ft::pair<node_base_p, bool> find_node( const key_type& key ) const {
		if ( this->_size != 0 ) {
			node_base_p cur = _root_node;
			node_base_p parent = _root_node;
			if ( _comp( key, get_node_value( cur ) ) ) {
				cur = cur->left;
			} else {
				if ( _comp( get_node_value( cur ), key ) ) {
					cur = cur->right;
				} else {
					return ft::pair<node_base_p, bool>( cur, true );
				}
			}
			while ( is_null_node( cur ) == false ) {
				if ( _comp( key, get_node_value( cur ) ) ) {
					parent = cur;
					cur = cur->left;
				} else {
					if ( _comp( get_node_value( cur ), key ) ) {
						parent = cur;
						cur = cur->right;
					} else {
						return ft::pair<node_base_p, bool>( cur, true );
					}
				}
			}
			return ft::pair<node_base_p, bool>( parent, false );
		}
		return ft::pair<node_base_p, bool>( end_node_ptr(), false );
	}

	ft::pair<node_base_p, bool> find_node( const_iterator  position,
										   const key_type& key ) const {
		node_base_p cur = position.node;
		node_base_p parent = position.node;
		if ( is_null_node( position.node ) == false ) {
			if ( _comp( key, get_node_value( cur ) ) ) {
				cur = cur->left;
			} else {
				if ( _comp( get_node_value( cur ), key ) ) {
					cur = cur->right;
				} else {
					return ft::pair<node_base_p, bool>( cur, true );
				}
			}
			while ( is_null_node( cur ) == false ) {
				if ( _comp( key, get_node_value( cur ) ) ) {
					parent = cur;
					cur = cur->left;
				} else {
					if ( _comp( get_node_value( cur ), key ) ) {
						parent = cur;
						cur = cur->right;
					} else {
						return ft::pair<node_base_p, bool>( cur, true );
					}
				}
			}
		}
		cur = _root_node;
		parent = _root_node;

		if ( cur == end_node_ptr() ) {
			return ft::pair<node_base_p, bool>( end_node_ptr(), false );
		}
		if ( _comp( key, get_node_value( cur ) ) ) {
			cur = cur->left;
		} else {
			if ( _comp( get_node_value( cur ), key ) ) {
				cur = cur->right;
			} else {
				return ft::pair<node_base_p, bool>( cur, true );
			}
		}
		while ( is_null_node( cur ) == false ) {
			if ( _comp( key, get_node_value( cur ) ) ) {
				parent = cur;
				cur = cur->left;
			} else {
				if ( _comp( get_node_value( cur ), key ) ) {
					parent = cur;
					cur = cur->right;
				} else {
					return ft::pair<node_base_p, bool>( cur, true );
				}
			}
		}
		return ft::pair<node_base_p, bool>( parent, false );
	}

	bool check_uncle_is_red_and_make_balance( node_base_p grand_parent,
											  node_base_p parent ) {
		bool        parent_is_right = is_right_child( parent );
		node_base_p uncle;

		if ( parent_is_right ) {
			uncle = grand_parent->left;
		} else {
			uncle = grand_parent->right;
		}
		// check case1
		if ( is_null_node( uncle ) == false && uncle->color == RED ) {
			if ( grand_parent != _root_node ) {
				grand_parent->color = RED;
			}
			uncle->color = BLACK;
			parent->color = BLACK;
			node_base_p gg_parent = grand_parent->parent;
			if ( gg_parent == NULL || gg_parent->color == BLACK ) {
				return true;
			}
			node_base_p ggg_parent = gg_parent->parent;
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

	void check_rotation_dir_and_make_balance( node_base_p grand_parent,
											  node_base_p parent,
											  node_base_p child ) {
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
	ft::pair<iterator, bool> insert_unique( const value_type& val ) {
		if ( this->_size == 0 ) {
			node        __new_node( val );
			node_base_p new_node = _alloc.allocate( 1 );
			__new_node.color = BLACK;
			__new_node.right = end_node_ptr();
			_alloc.construct( static_cast<node_p>( new_node ), __new_node );

			_root_node = new_node;
			_begin_node = new_node;
			__end_node.left = new_node;
			++_size;
			return ft::make_pair( iterator( static_cast<node_p>( new_node ) ),
								  true );
		}

		ft::pair<node_base_p, bool> result = find_node( GetKey()( val ) );
		if ( result.second == true ) {
			return ft::make_pair(
				iterator( static_cast<node_p>( result.first ) ), false );
		}

		node        __new_node( val );
		node_base_p new_node = _alloc.allocate( 1 );
		_alloc.construct( static_cast<node_p>( new_node ), __new_node );
		++_size;

		node_base_p parent_node = result.first;

		if ( _comp( val, get_node_value( parent_node ) ) ) {
			if ( _begin_node == parent_node ) {
				_begin_node = new_node;
			}
			parent_node->left = new_node;
		} else {
			if ( parent_node->right == end_node_ptr() ) {
				__end_node.left = new_node;
				new_node->right = end_node_ptr();
			}
			parent_node->right = new_node;
		}
		new_node->parent = parent_node;
		if ( parent_node->color == BLACK ) {
			return ft::make_pair( iterator( static_cast<node_p>( new_node ) ),
								  true );
		}
		// Unbalanced state. Check case1 to make balance.
		if ( check_uncle_is_red_and_make_balance( parent_node->parent,
												  parent_node ) ) {
			return ft::make_pair( iterator( static_cast<node_p>( new_node ) ),
								  true );
		}
		// Check case2 or case3, and rotate to make balance.
		check_rotation_dir_and_make_balance( parent_node->parent, parent_node,
											 new_node );
		return ft::make_pair( iterator( static_cast<node_p>( new_node ) ),
							  true );
	}

	ft::pair<iterator, bool> insert_unique_with_parent(
		iterator parent_node_iter, const value_type& val ) {
		node        __new_node( val );
		node_base_p new_node = _alloc.allocate( 1 );
		if ( this->_size == 0 ) {
			__new_node.color = BLACK;
			__new_node.right = end_node_ptr();
			_alloc.construct( static_cast<node_p>( new_node ), __new_node );

			_root_node = new_node;
			_begin_node = new_node;
			__end_node.left = new_node;
			++_size;
			return ft::make_pair( iterator( static_cast<node_p>( new_node ) ),
								  true );
		}

		_alloc.construct( static_cast<node_p>( new_node ), __new_node );
		++_size;

		node_base_p parent_node = parent_node_iter.node;

		if ( _comp( get_node_value( parent_node ), val ) ) {
			if ( parent_node->right == end_node_ptr() ) {
				__end_node.left = new_node;
				new_node->right = end_node_ptr();
			}
			parent_node->right = new_node;
		} else {
			if ( _begin_node == parent_node ) {
				_begin_node = new_node;
			}
			parent_node->left = new_node;
		}
		new_node->parent = parent_node;
		if ( parent_node->color == BLACK ) {
			return ft::make_pair( iterator( static_cast<node_p>( new_node ) ),
								  true );
		}
		// Unbalanced state. Check case1 to make balance.
		if ( check_uncle_is_red_and_make_balance( parent_node->parent,
												  parent_node ) ) {
			return ft::make_pair( iterator( static_cast<node_p>( new_node ) ),
								  true );
		}
		// Check case2 or case3, and rotate to make balance.
		check_rotation_dir_and_make_balance( parent_node->parent, parent_node,
											 new_node );
		return ft::make_pair( iterator( static_cast<node_p>( new_node ) ),
							  true );
	}

	// erase node function.
	void do_erase_cases( node_base_p parent, node_base_p sibling,
						 node_base_p extra_black ) {
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
	void do_erase_sibling_is_black( node_base_p parent, node_base_p sibling,
									node_base_p extra_black ) {
		if ( parent->left == extra_black ) {
			if ( sibling->left != NULL && sibling->left->color == RED ) {
				return erase_case_sibling_other_side_child_red( parent, sibling,
																true );
			} else if ( sibling->right != NULL &&
						sibling->right != end_node_ptr() &&
						sibling->right->color == RED ) {
				return erase_case_sibling_same_side_child_red( parent, sibling,
															   true );
			}
		} else {
			if ( sibling->left != NULL && sibling->left->color == RED ) {
				return erase_case_sibling_same_side_child_red( parent, sibling,
															   false );
			} else if ( sibling->right != NULL &&
						sibling->right != end_node_ptr() &&
						sibling->right->color == RED ) {
				return erase_case_sibling_other_side_child_red( parent, sibling,
																false );
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
		node_base_p new_parent = parent->parent;
		if ( is_right_child( parent ) ) {
			do_erase_cases( new_parent, new_parent->left, parent );
		} else {
			do_erase_cases( new_parent, new_parent->right, parent );
		}
	}

	// erase case3
	void erase_case_sibling_other_side_child_red(
		node_base_p parent, node_base_p sibling, bool sibling_is_right_child ) {
		node_base_p sibling_child;
		sibling->color = BLACK;
		if ( sibling_is_right_child ) {
			sibling_child = sibling->left;
			sibling_child->color = parent->color;
			parent->color = BLACK;
			rotate_right( sibling );
			rotate_left( parent );
		} else {
			sibling_child = sibling->right;
			sibling_child->color = parent->color;
			parent->color = BLACK;
			rotate_left( sibling );
			rotate_right( parent );
		}
	}

	// erase case4
	void erase_case_sibling_same_side_child_red( node_base_p parent,
												 node_base_p sibling,
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
		ft::pair<node_base_p, bool> tmp = find_node( key );
		if ( tmp.second == false ) {
			return 0;
		}
		return erase_from_node_ptr( tmp.first );
	}

	size_type erase_from_node_ptr( const node_base_p& del_node ) {
		node_base_p extra_black_parent = NULL;
		node_base_p extra_black = NULL;
		bool        del_node_color_is_black = del_node->color == BLACK;
		node_base_p swap_node = NULL;
		node_base_p parent = del_node->parent;
		node_base_p left = del_node->left;
		node_base_p right = del_node->right;

		// Two children node.
		if ( del_node->left && del_node->right != NULL &&
			 del_node->right != end_node_ptr() ) {
			swap_node = node_base::maximum( left );
			extra_black = swap_node->left;
			if ( left != swap_node ) {
				extra_black_parent = swap_node->parent;
				swap_node->parent->right = swap_node->left;
				if ( swap_node->left ) {
					swap_node->left->parent = swap_node->parent;
				}
				swap_node->left = left;
				left->parent = swap_node;
			} else {
				extra_black_parent = swap_node;
			}
			swap_node->parent = parent;
			swap_node->right = right;
			right->parent = swap_node;
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
		// One or zero child node.
		else {
			// One right child node.
			if ( left == NULL && is_null_node( right ) == false ) {
				if ( del_node == _root_node ) {
					_root_node = right;
					_begin_node = right;
					_root_node->color = BLACK;
					del_node_color_is_black = false;
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
			else if ( is_null_node( right ) == true && left != NULL ) {
				if ( del_node == _root_node ) {
					_root_node = left;
					__end_node.left = left;
					left->right = end_node_ptr();
					_root_node->color = BLACK;
					del_node_color_is_black = false;
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
					_root_node = NULL;
					_begin_node = end_node_ptr();
					__end_node.left = end_node_ptr();
					del_node_color_is_black = false;
				} else if ( del_node == _begin_node ) {
					_begin_node = parent;
					parent->left = NULL;
				} else if ( del_node == __end_node.left ) {
					__end_node.left = parent;
					parent->right = end_node_ptr();
				} else {
					if ( parent->right == del_node ) {
						parent->right = NULL;
					} else {
						parent->left = NULL;
					}
				}
				extra_black_parent = parent;
			}
			if ( del_node_color_is_black ) {
				extra_black = swap_node;
				if ( swap_node ) {
					extra_black_parent = swap_node->parent;
				}
			}
		}

		--_size;
		_alloc.destroy( static_cast<node_p>( del_node ) );
		_alloc.deallocate( static_cast<node_p>( del_node ), 1 );
		// make balance
		if ( del_node_color_is_black ) {
			if ( extra_black_parent->left == extra_black ) {
				do_erase_cases( extra_black_parent, extra_black_parent->right,
								extra_black );
			} else {
				do_erase_cases( extra_black_parent, extra_black_parent->left,
								extra_black );
			}
		}
		return 1;
	}

	void clear() {
		if ( _root_node == NULL ) {
			return;
		}
		del_node( _root_node );
		_size = 0;
		_root_node = NULL;
		_begin_node = end_node_ptr();
		__end_node.left = end_node_ptr();
	}

	void swap( rbtree& x ) {
		node_base   tmp_end_node( x.__end_node );
		node_base_p tmp_root = x._root_node;
		node_base_p tmp_begin = x._begin_node;
		size_type   tmp_size = x._size;

		if ( this->_size != 0 ) {
			x._root_node = _root_node;
			x._begin_node = _begin_node;
			x._size = _size;
			x.__end_node = __end_node;
			x.__end_node.left->right = x.end_node_ptr();
		} else {
			x._root_node = NULL;
			x._begin_node = x.end_node_ptr();
			x._size = 0;
			x.__end_node.left = x.end_node_ptr();
		}
		if ( tmp_size != 0 ) {
			_root_node = tmp_root;
			_begin_node = tmp_begin;
			_size = tmp_size;
			__end_node = tmp_end_node;
			__end_node.left->right = this->end_node_ptr();
		} else {
			this->_root_node = NULL;
			this->_begin_node = this->end_node_ptr();
			this->_size = 0;
			this->__end_node.left = this->end_node_ptr();
		}
	}

	iterator lower_bound( const key_type& k ) {
		ft::pair<node_base_p, bool> ret = find_node( k );

		if ( ret.second == true || ret.first == end_node_ptr() ) {
			return iterator( ret.first );
		} else {
			if ( _comp( get_node_value( ret.first ), k ) ) {
				return ++iterator( ret.first );
			}
			return iterator( ret.first );
		}
	}

	const_iterator lower_bound( const key_type& k ) const {
		ft::pair<node_base_p, bool> ret = find_node( k );

		if ( ret.second == true || ret.first == end_node_ptr() ) {
			return const_iterator( ret.first );
		} else {
			if ( _comp( get_node_value( ret.first ), k ) ) {
				return ++const_iterator( ret.first );
			}
			return const_iterator( ret.first );
		}
	}

	iterator upper_bound( const key_type& k ) {
		ft::pair<node_base_p, bool> ret = find_node( k );

		if ( ret.second == true ) {
			return ++iterator( ret.first );
		} else if ( ret.first == end_node_ptr() ) {
			return iterator( ret.first );
		} else {
			if ( _comp( get_node_value( ret.first ), k ) ) {
				return ++iterator( ret.first );
			}
			return iterator( ret.first );
		}
	}

	const_iterator upper_bound( const key_type& k ) const {
		ft::pair<node_base_p, bool> ret = find_node( k );

		if ( ret.second == true ) {
			return ++const_iterator( ret.first );
		} else if ( ret.first == end_node_ptr() ) {
			return const_iterator( ret.first );
		} else {
			if ( _comp( get_node_value( ret.first ), k ) ) {
				return ++const_iterator( ret.first );
			}
			return const_iterator( ret.first );
		}
	}

	allocator_type get_allocator() const {
		return _alloc;
	}

	value_compare value_comp() const {
		return _comp;
	}

	// // print
	// void print_tree() const {
	// 	printTree( _root_node, NULL, false );
	// }

	// void print_tree_map() const {
	// 	printTree_map( _root_node, NULL, false );
	// }

	// struct Trunk {
	// 	Trunk*      prev;
	// 	std::string str;

	// 	Trunk( Trunk* prev, std::string str ) {
	// 		this->prev = prev;
	// 		this->str = str;
	// 	}
	// };

	// void showTrunks( Trunk* p ) const {
	// 	if ( p == NULL ) {
	// 		return;
	// 	}

	// 	showTrunks( p->prev );
	// 	std::cout << p->str;
	// }

	// void printTree( node_base_p root, Trunk* prev, bool isLeft ) const
	// { 	if ( root == NULL ) { 		return;
	// 	}

	// 	std::string prev_str = "    ";
	// 	Trunk*      trunk = new Trunk( prev, prev_str );

	// 	printTree_map( root->right, trunk, true );

	// 	if ( !prev ) {
	// 		trunk->str = "---";
	// 	} else if ( isLeft ) {
	// 		trunk->str = ".---";
	// 		prev_str = "   |";
	// 	} else {
	// 		trunk->str = "`---";
	// 		prev->str = prev_str;
	// 	}

	// 	showTrunks( trunk );
	// 	if ( root == end_node_ptr() ) {
	// 		std::cout << " end_node!" << std::endl;
	// 		delete trunk;
	// 		return;
	// 	} else {
	// 		if ( root->color == RED ) {
	// 			std::cout << "\033[0;31m" << get_node_value( root )
	// 					  << "\033[0;49m" << std::endl;
	// 		} else {
	// 			std::cout << get_node_value( root ) << std::endl;
	// 		}
	// 		if ( prev ) {
	// 			prev->str = prev_str;
	// 		}
	// 		trunk->str = "   |";
	// 	}

	// 	printTree( root->left, trunk, false );
	// 	delete trunk;
	// }

	// void printTree_map( node_base_p root, Trunk* prev,
	// 					bool isLeft ) const {
	// 	if ( root == NULL ) {
	// 		return;
	// 	}

	// 	std::string prev_str = "    ";
	// 	Trunk*      trunk = new Trunk( prev, prev_str );

	// 	printTree_map( root->right, trunk, true );

	// 	if ( !prev ) {
	// 		trunk->str = "---";
	// 	} else if ( isLeft ) {
	// 		trunk->str = ".---";
	// 		prev_str = "   |";
	// 	} else {
	// 		trunk->str = "`---";
	// 		prev->str = prev_str;
	// 	}

	// 	showTrunks( trunk );
	// 	if ( root == end_node_ptr() ) {
	// 		std::cout << " end_node!" << std::endl;
	// 		delete trunk;
	// 		return;
	// 	} else {
	// 		if ( root->color == RED ) {
	// 			std::cout << "\033[0;31m" << get_node_value( root ).first
	// 					  << "\033[0;49m" << std::endl;
	// 		} else {
	// 			std::cout << get_node_value( root ).first << std::endl;
	// 		}
	// 		if ( prev ) {
	// 			prev->str = prev_str;
	// 		}
	// 		trunk->str = "   |";
	// 	}

	// 	printTree_map( root->left, trunk, false );

	// 	delete trunk;
	// }

	// void do_tree_debug( void ) const {
	// 	tree_debug( _root_node );
	// }

	// void tree_debug( node_base_p root ) const {
	// 	if ( root == NULL || root == end_node_ptr() ) {
	// 		return;
	// 	}
	// 	if ( root->left ) {
	// 		if ( root != root->left->parent ) {
	// 			std::cout << "Check connection. Parent node key is "
	// 					  << static_cast<node_p>( root )->value.first
	// 					  << std::endl;
	// 		}
	// 	}
	// 	if ( root->right && root->right != end_node_ptr() ) {
	// 		if ( root != root->right->parent ) {
	// 			std::cout << "Check connection. Parent node key is "
	// 					  << static_cast<node_p>( root )->value.first
	// 					  << std::endl;
	// 		}
	// 	}
	// 	tree_debug( root->left );
	// 	tree_debug( root->right );
	// }
};  // namespace ft

}  // namespace ft

#endif
