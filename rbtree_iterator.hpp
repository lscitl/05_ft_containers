/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:20:49 by seseo             #+#    #+#             */
/*   Updated: 2022/10/25 11:59:03 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __RBTREE_ITERATOR_H__
#define __RBTREE_ITERATOR_H__

#include "rbtree_node.hpp"

namespace ft {

template <class T, class Ref, class Ptr>
class rbtree_iterator {
   public:
	typedef std::bidirectional_iterator_tag        iterator_category;
	typedef T                                      value_type;
	typedef Ref                                    reference;
	typedef Ptr                                    pointer;
	typedef rbtree_iterator<T, T&, T*>             iterator;
	typedef rbtree_iterator<T, const T&, const T*> const_iterator;
	typedef ptrdiff_t                              difference_type;
	typedef rbtree_node<T>*                        node_p;
	typedef rbtree_node_base*                      node_base_p;

	node_base_p node;

   public:
	rbtree_iterator() : node( NULL ) {
	}
	rbtree_iterator( const iterator& x ) : node( x.node ) {
	}
	rbtree_iterator( const node_base_p node ) : node( node ) {
	}
	rbtree_iterator& operator=( const rbtree_iterator& iter ) {
		this->node = iter.node;
		return *this;
	}

	reference operator*() const {
		return static_cast<node_p>( node )->value;
	}
	pointer operator->() const {
		return &( operator*() );
	}

	rbtree_iterator& operator++() {
		this->increment();
		return *this;
	}
	rbtree_iterator operator++( int ) {
		rbtree_iterator ret( *this );
		++( *this );
		return ret;
	}
	rbtree_iterator& operator--() {
		this->decrement();
		return *this;
	}
	rbtree_iterator operator--( int ) {
		rbtree_iterator ret( *this );
		--( *this );
		return ret;
	}

   private:
	void increment() {
		if ( node->right != NULL ) {
			node = node->right;
			if ( node->parent == NULL ) {
				return;
			}
			while ( node->left != NULL ) {
				node = node->left;
			}
		} else {
			node_base_p tmp_node = node->parent;
			while ( node == tmp_node->right ) {
				node = tmp_node;
				tmp_node = tmp_node->parent;
			}
			if ( node->right != tmp_node ) {
				node = tmp_node;
			}
		}
	}

	void decrement() {
		node_base_p tmp_node;
		if ( node->left != NULL ) {
			tmp_node = node;
			node = node->left;
			while ( node->right != NULL ) {
				node = node->right;
			}
			if ( tmp_node == node ) {
				node = tmp_node->left;
			}
		} else {
			tmp_node = node->parent;
			while ( node == tmp_node->left ) {
				node = tmp_node;
				tmp_node = tmp_node->parent;
			}
			if ( node->left != tmp_node ) {
				node = tmp_node;
			}
		}
	}
};

template <class T, class R, class P>
bool operator==( const rbtree_iterator<T, R, P>& left,
				 const rbtree_iterator<T, R, P>& right ) {
	return left.node == right.node;
}

template <class T>
bool operator==( const rbtree_iterator<T, const T&, const T*>& left,
				 const rbtree_iterator<T, T&, T*>&             right ) {
	return left.node == right.node;
}

template <class T>
bool operator==( const rbtree_iterator<T, T&, T*>&             left,
				 const rbtree_iterator<T, const T&, const T*>& right ) {
	return left.node == right.node;
}

template <class T, class R, class P>
bool operator!=( const rbtree_iterator<T, R, P>& left,
				 const rbtree_iterator<T, R, P>& right ) {
	return left.node != right.node;
}

template <class T>
bool operator!=( const rbtree_iterator<T, const T&, const T*>& left,
				 const rbtree_iterator<T, T&, T*>&             right ) {
	return left.node != right.node;
}

template <class T>
bool operator!=( const rbtree_iterator<T, T&, T*>&             left,
				 const rbtree_iterator<T, const T&, const T*>& right ) {
	return left.node != right.node;
}

}  // namespace ft

#endif
