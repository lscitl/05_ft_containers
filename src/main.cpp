#include <iostream>
#include <string>
#include <deque>
#if 0  // CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
// #include <map.hpp>
// #include <stack.hpp>
#include "../vector.hpp"
#include "../stack.hpp"
#endif

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer {
	int  idx;
	char buff[BUFFER_SIZE];
};

#define COUNT ( MAX_RAM / (int)sizeof( Buffer ) )

#include <vector>
// #include "../pair.hpp"

#define _vector std::vector

namespace ft {

template <class T1, class T2>
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;

	first_type  first;
	second_type second;

	// Constructor
	pair();
	template <class U, class V>
	pair( const pair<U, V>& pr );
	pair( const first_type& a, const second_type& b );

	// Assignment operator
	pair& operator=( const pair& pr );
};

// Constructor
template <class T1, class T2>
pair<T1, T2>::pair() : first(), second() {
}

template <class T1, class T2>
template <class U, class V>
pair<T1, T2>::pair( const pair<U, V>& pr )
	: first( pr.first ), second( pr.second ) {
}

template <class T1, class T2>
pair<T1, T2>::pair( const first_type& a, const second_type& b )
	: first( a ), second( b ) {
}

// Assignment operator
template <class T1, class T2>
pair<T1, T2>& pair<T1, T2>::operator=( const pair<T1, T2>& pr ) {
	first = pr.first;
	second = pr.second;
	return *this;
}

// Comparison operator
template <class T1, class T2>
bool operator==( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return ( lhs.first == rhs.first ) && ( lhs.second == rhs.second );
}

template <class T1, class T2>
bool operator!=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return !( lhs == rhs );
}

template <class T1, class T2>
bool operator<( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return lhs.first < rhs.first ||
		   ( !( rhs.first < lhs.first ) && lhs.second < rhs.second );
}

template <class T1, class T2>
bool operator<=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return !( rhs < lhs );
}

template <class T1, class T2>
bool operator>( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return rhs < lhs;
}

template <class T1, class T2>
bool operator>=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ) {
	return !( lhs < rhs );
}

template <class T1, class T2>
pair<T1, T2> make_pair( T1 t, T2 u ) {
	return pair<T1, T2>( t, u );
}

template <typename T>
class is_pair {
	typedef char yes[1];
	typedef struct {
		char x[2];
	} no;
	template <typename C>
	static yes& test( typename C::first_type = 0, typename C::second_type = 0 );

	template <typename C>
	static no& test( ... );

   public:
	static bool const value = sizeof( test<T>( 0, 0 ) ) == sizeof( yes );
};

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

#include <memory>

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
	typedef rbtree_iterator_base                     iterator;
	typedef const iterator                           const_iterator;

   protected:
	typedef typename get_node_type<T>::node_type node_type;
	typedef node_type*                           link_type;
	typedef const node_type*                     const_link_type;

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

	rbtree()
		: _begin_node( NULL ),
		  _end_node( NULL ),
		  _comp( Compare() ),
		  _size( 0 ),
		  _alloc( Allocator() ) {
	}
	~rbtree() {
	}
	// rbtree( const rbtree& ref )
	// 	: _begin_node( NULL ),
	// 	  _end_node( NULL ),
	// 	  _comp( Compare() ),
	// 	  _size( 0 ),
	// 	  _alloc( Allocator() ) {
	// 	rbtree::iterator ref_begin = ref.begin();
	// 	for ( ; ref_begin != ref._end_node; ++ref_begin ) {
	// 		insert( *ref_begin );
	// 	}
	// }

	void insert() {
		_begin_node = _alloc.allocate( 1 );
		// _alloc.construct( _begin_node, rbtree_node<T>() );
		_begin_node->left = _end_node;
		_begin_node->right = _end_node;
	}

	ft::pair<iterator, bool> insert( value_type& x ) {
		rbtree_node* tmp_node = _alloc.allocate( 1 );

		_alloc.construct( _begin_node, x );
		_begin_node->left = _end_node;
		_begin_node->right = _end_node;
		return ( ft::pair<iterator, bool>() )
	}

	link_type get_begin_node() {
		return ( _begin_node );
	}
};

}  // namespace ft

int main() {
	// std::pair<int, char> t( 123, 'a' );
	// int                  b( 3 );

	// ft::rbtree_node<std::pair<int, char> > a;

	// a.value_field.first = 5;
	// a.value_field.second = 'a';

	// ft::pair<int, char> a;
	// int                 c;

	ft::rbtree<int>                  a;
	ft::rbtree<ft::pair<int, char> > b;

	return 0;
}
