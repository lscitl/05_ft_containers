/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/09/27 00:37:15 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __RBTREE_H__
#define __RBTREE_H__

// 1. Every node is either red or black.
// 2. Root node is black.
// 3. All NIL nodes(leaf) are considered black.
// 4. A red node does not have a red child.
// 5. Every path from a given node to any of its descendant NIL nodes goes
// through the same number of black nodes.

typedef bool       rbtree_color;
const rbtree_color rbtree_red = false;
const rbtree_color rbtree_black = true;

struct rbtree_node_base {
	typedef rbtree_color      color_type;
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
			ndoe = node->parent;
		}
	}
}

#endif
