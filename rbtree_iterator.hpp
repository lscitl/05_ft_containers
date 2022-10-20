#ifndef __RBTREE_ITERATOR_H__
#define __RBTREE_ITERATOR_H__

#include "rbtree_node.hpp"

namespace ft {

template <class T, class Ref, class Ptr>
class rbtree_iterator {
   public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T                               value_type;
	typedef Ref                             reference;
	typedef Ptr                             pointer;
	typedef ptrdiff_t                       difference_type;
	typedef rbtree_node<T>*                 node_pointer;
	typedef rbtree_node_base*               node_base_pointer;

	node_base_pointer node;

   public:
	rbtree_iterator() : node( NULL ) {
	}

	rbtree_iterator( const rbtree_iterator& x ) : node( x.node ) {
	}

	rbtree_iterator( const node_base_pointer node ) : node( node ) {
	}

	reference operator*() const {
		return static_cast<node_pointer>( node )->value;
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
			node_base_pointer tmp = node->parent;
			while ( node == tmp->right ) {
				node = tmp;
				tmp = tmp->parent;
			}
			if ( node->right != tmp ) {
				node = tmp;
			}
		}
	}

	void decrement() {
		if ( node->left != NULL ) {
			node_base_pointer begin = node;
			node = node->left;
			while ( node->right != NULL ) {
				node = node->right;
			}
			if ( begin == node ) {
				node = begin->left;
			}
		} else {
			node_base_pointer tmp = node->parent;
			while ( node == tmp->left ) {
				node = tmp;
				tmp = tmp->parent;
			}
			if ( node->left != tmp ) {
				node = tmp;
			}
		}
	}

	friend bool operator==( const rbtree_iterator& left,
							const rbtree_iterator& right ) {
		return left.node == right.node;
	}
	friend bool operator!=( const rbtree_iterator& left,
							const rbtree_iterator& right ) {
		return left.node != right.node;
	}
};

template <class T, class Ref, class Ptr>
class rbtree_const_iterator {
   public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T                               value_type;
	typedef const T&                        reference;
	typedef const T*                        pointer;
	typedef rbtree_iterator<T, Ref, Ptr>    iterator;
	typedef ptrdiff_t                       difference_type;
	typedef rbtree_node<T>*                 node_pointer;
	typedef rbtree_node_base*               node_base_pointer;

	node_base_pointer node;

   public:
	rbtree_const_iterator() : node( NULL ) {
	}

	rbtree_const_iterator( const rbtree_const_iterator& x ) : node( x.node ) {
	}

	rbtree_const_iterator( const node_base_pointer node ) : node( node ) {
	}

	rbtree_const_iterator( const iterator& iter ) : node( iter.node ) {
	}

	rbtree_const_iterator& operator=( const iterator& iter ) {
		this->node = iter.node;
		return *this;
	}

	reference operator*() const {
		return static_cast<node_pointer>( node )->value;
	}

	pointer operator->() const {
		return &( operator*() );
	}

	rbtree_const_iterator& operator++() {
		this->increment();
		return *this;
	}

	rbtree_const_iterator operator++( int ) {
		rbtree_const_iterator ret( *this );
		++( *this );
		return ret;
	}

	rbtree_const_iterator& operator--() {
		this->decrement();
		return *this;
	}

	rbtree_const_iterator operator--( int ) {
		rbtree_const_iterator ret( *this );
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
			node_base_pointer tmp = node->parent;
			while ( tmp && node == tmp->right ) {
				node = tmp;
				tmp = tmp->parent;
			}
			if ( node->right != tmp ) {
				node = tmp;
			}
		}
	}

	void decrement() {
		if ( node->left != NULL ) {
			node_base_pointer begin = node;
			node = node->left;
			while ( node->right != NULL ) {
				node = node->right;
			}
			if ( begin == node ) {
				node = begin->left;
			}
		} else {
			node_base_pointer tmp = node->parent;
			while ( node == tmp->left ) {
				node = tmp;
				tmp = tmp->parent;
			}
			if ( node->left != tmp ) {
				node = tmp;
			}
		}
	}

	friend bool operator==( const rbtree_const_iterator& left,
							const rbtree_const_iterator& right ) {
		return left.node == right.node;
	}
	friend bool operator!=( const rbtree_const_iterator& left,
							const rbtree_const_iterator& right ) {
		return left.node != right.node;
	}
};

}  // namespace ft

#endif
