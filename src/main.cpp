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
   private:
	std::string a;

   public:
	Base() : a() {
		std::cout << "Base constructor called!" << std::endl;
	}
	Base( const std::string &tmp ) : a( tmp ) {
		std::cout << "Base str constructor called!" << std::endl;
	}
	Base( const Base &ref ) : a( ref.a ) {
		std::cout << "Base copy contstructor called!" << std::endl;
	}
	~Base() {
		std::cout << "Base destructor called!" << std::endl;
	}
};

#include <map>
#include <chrono>
#include "../map.hpp"

int main() {
	// ft::rbtree<ft::pair<int, Base> > a;
	// ft::rbtree<int> a;
	// std::map<int, Base> a;
	ft::map<int, char> a;
	Base               b;

	a.begin();
	for ( int i = 0; i < 21; i++ ) {
		// a.insert( i );
		std::cout << i << ": " << std::endl;
		a.insert( ft::make_pair( i, 'a' ) );
		// a.insert( std::make_pair( i, b ) );
		std::cout << std::endl;
	}

	// std::cout << a.begin() << std::endl;
	// printf( "%p\n", &a.begin() );
	std::cout << "erase" << std::endl;

	// a.print_tree();
	std::cout << "done!" << std::endl;

	// std::cout << &( a.find( 2 )->second ) << std::endl;

	// a.erase( 3 );
	// std::cout << &( a.find( 3 )->second ) << std::endl;

	// std::map<int, char>::iterator tmp;

	// tmp = a.find( 50 );

	// auto startTime = std::chrono::system_clock::now();
	// // a.insert( tmp, std::make_pair( 600000, 'b' ) );
	// // a.insert( std::make_pair( 600000, 'b' ) );

	// auto endTime = std::chrono::system_clock::now();

	// auto sec = std::chrono::duration_cast<std::chrono::nanoseconds>(
	// 	endTime - startTime );

	// std::cout << sec.count() << std::endl;

	// for ( tmp = a.begin(); tmp != a.end(); tmp++ ) {
	// 	std::cout << tmp->second << std::endl;
	// }

	return 0;
}
