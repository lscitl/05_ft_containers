/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:51:25 by seseo             #+#    #+#             */
/*   Updated: 2022/09/30 22:26:41 by seseo            ###   ########.fr       */
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

	value value_field;
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

struct rbtree_iterator_base {
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

template <class T, class Compare, class Allocator>
class rbtree
// : public rbtree_header<T>,
// 			   public rbtree_key_compare<Compare>,
// 			   public rbtree_node_allocator<Allocator>
{
   public:
	typedef typename get_node_type<T>::key_type                key_type;
	typedef typename get_node_type<T>::value_type              value_type;
	typedef Compare                                            value_compare;
	typedef typename Allocator::rebind<rbtree_node<T> >::other allocator_type;
	typedef typename allocator_type::pointer                   pointer;
	typedef typename allocator_type::const_pointer             const_pointer;
	typedef typename allocator_type::size_type                 size_type;
	typedef typename allocator_type::difference_type           difference_type;
	typedef rbtree_iterator_base                               iterator;
	typedef const iterator                                     const_iterator;

   protected:
	typedef rbtree_node_base*                    link_type;
	typedef const rbtree_node_base*              const_link_type;
	typedef typename get_node_type<T>::node_type node_type;

   private:
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

	//    public:
	// 	rbtree();
	// 	~rbtree();
	// 	rbtree( const rbtree& ref );
};

#endif
