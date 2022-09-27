/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/09/28 00:16:29 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__

#include <iterator>
#include <__tree>

// 1. Every node is either red or black.
// 2. Root node is black.
// 3. All NIL nodes(leaf) are considered black.
// 4. A red node does not have a red child.
// 5. Every path from a given node to any of its descendant NIL nodes goes
// through the same number of black nodes.

typedef enum color_t { RED, BLACK };

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
struct rbtree_node : public rbtree_node_base {
	typedef rbtree_node<value>* link_type;

	value value_field;
};

template <class T>
struct rbtree_header {
	rbtree_node_base header;
	size_t           node_cnt;
};

template <class T, class Compare>
struct rbtree_key_compare {
	typedef typename Compare<T> key_comp;
};

template <class T, class Allocator>
struct rbtree_node_allocator {
	typedef typename Allocator<rbtree_node<T> > allocator_type;
};

template <class T, class Compare, class Allocator>
class rbtree : public rbtree_header<T>,
			   public rbtree_key_compare<Compare>,
			   public rbtree_node_allocator<Allocator> {
	typedef Allocator allocator_type;

	// rbtree( const allocator_type& __a ) : _Base( __a ) {
	// 	header = _M_get_node();
	// }
	// ~rbtree() {
	// 	_M_put_node( _M_header );
	// }
};

struct rbtree_base_iterator_base {
	typedef rbtree_node_base::base_ptr      base_ptr;
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t                       difference_type;

	base_ptr node;

	void incremet() {
		if ( node->right != NULL ) {
			node = node->right;
			while ( node->left != NULL ) {
				node = node->left;
			}
		} else {
			base_ptr tmp = node->parent;
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
			base_ptr tmp = node->parent;
			while ( node == tmp->left ) {
				node = tmp;
				tmp = tmp->parent;
			}
			if ( node->left != tmp )
				node = tmp;
		}
	}
};

#endif
