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
#include "../rbtree.hpp"

#define _vector std::vector

#include <functional>

class Base {
   public:
	Base() {
		std::cout << "Base constructor called!" << std::endl;
	}
	Base( const Base &ref ) {
		(void)ref;
		std::cout << "Base copy contstructor called!" << std::endl;
	}
	~Base() {
		std::cout << "Base destructor called!" << std::endl;
	}
};

#include <map>
int main() {
	// std::pair<int, char> t( 123, 'a' );
	// int                  b( 3 );

	// ft::rbtree_node<std::pair<int, char> > a;

	// a.value_field.first = 5;
	// a.value_field.second = 'a';

	// ft::pair<int, char> a;
	// int                 c;

	// ft::rbtree<int>                  a;
	// ft::rbtree<ft::pair<int, char> > b;

	// std::cout << a.insert( 3 ).second << std::endl;

	// Base                b;
	// std::map<int, Base> a;

	// std::cout << "pair" << std::endl;
	// std::pair<int, Base> tmp( 1, b );
	// std::cout << "start" << std::endl;
	// a.insert( tmp );
	// std::cout << a.size() << std::endl;
	// a.insert( tmp );
	// std::cout << a.size() << std::endl;

	// std::cout << std::less<int>()( 1, 2 ) << std::endl;

	// ft::rbtree<ft::pair<int, char>, std::less<ft::pair<int, char> > > a;

	// for ( int i = 0; i < 120; i++ ) {
	// 	const ft::pair<int, char> tmp = ft::pair<int, char>( i, i );
	// 	a.insert( tmp );
	// }
	ft::rbtree<int> a;

	for ( int i = 0; i < 120; i++ ) {
		a.insert( i );
	}

	// a.insert( 7 );
	a.print_tree();
	// a.clear();
	// for ( int i = 0; i > -120; i-- ) {
	// 	a.insert( i );
	// }
	// a.print_tree();
	// a.print_tree();
	// std::map<int, Base>::iterator tmp;

	// tmp = a.begin();

	// std::cout << &( *tmp ) << std::endl;

	// int *c = new int( 5 );

	// std::cout << c << std::endl;
	// std::cout << &a << std::endl;
	// std::cout << &b << std::endl;

	return 0;
}
