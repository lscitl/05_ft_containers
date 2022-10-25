/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_node.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:20:43 by seseo             #+#    #+#             */
/*   Updated: 2022/10/26 00:32:16 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __RBTREE_NODE_H__
#define __RBTREE_NODE_H__

#include <memory>

namespace ft {

typedef enum { RED, BLACK } color_t;

class rbtree_node_base {
   public:
	typedef rbtree_node_base* pointer;
	typedef color_t           color_type;

	pointer    parent;
	pointer    right;
	pointer    left;
	color_type color;

	rbtree_node_base()
		: parent( NULL ), right( NULL ), left( NULL ), color( RED ) {
	}
	rbtree_node_base( pointer parent, pointer right, pointer left,
					  color_type color )
		: parent( parent ), right( right ), left( left ), color( color ) {
	}
	rbtree_node_base( const rbtree_node_base& x )
		: parent( x.parent ),
		  right( x.right ),
		  left( x.left ),
		  color( x.color ) {
	}
	rbtree_node_base& operator=( const rbtree_node_base& x ) {
		this->parent = x.parent;
		this->right = x.right;
		this->left = x.left;
		this->color = x.color;
		return *this;
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
};

template <class T>
class rbtree_node : public rbtree_node_base {
   public:
	typedef T value_type;

	value_type value;

	rbtree_node( const value_type& x ) : rbtree_node_base(), value( x ) {
	}
	rbtree_node( const rbtree_node& node )
		: rbtree_node_base( node.parent, node.right, node.left, node.color ),
		  value( node.value ) {
	}
	rbtree_node& operator=( const rbtree_node& node ) {
		this->parent = node.parent;
		this->right = node.right;
		this->left = node.left;
		this->color = node.color;
		this->value = node.value;
		return *this;
	}
	~rbtree_node() {
	}

   private:
	rbtree_node();
};

}  // namespace ft

#endif
