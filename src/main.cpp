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
// #include "../rbtree.hpp"

#define _vector std::vector

#include <functional>

class Base {
   private:
	std::string a;

	Base() : a() {
		std::cout << "Base constructor called!" << std::endl;
	}

   public:
	Base( const std::string& tmp ) : a( tmp ) {
		std::cout << "Base str constructor called!" << std::endl;
	}
	Base( const Base& ref ) : a( ref.a ) {
		std::cout << "Base copy contstructor called!" << std::endl;
	}
	~Base() {
		std::cout << "Base destructor called!" << std::endl;
	}
};

#define NAMESPACE ft
#include <map>
#include <chrono>
#include "../map.hpp"
#include "map_prelude.hpp"

int main( void ) {
	// ft::map<int, char> a;
	// // ft::map<int, Base> a;
	// // Base               b( "b" );
	// // Base                 c( "c" );
	// // ft::pair<int, Base> tmp( 0, b );
	// ft::pair<int, char> tmp( 0, 'b' );

	// // std::cout << "start" << std::endl;
	// for ( int i = 0; i < 1; i++ ) {
	// 	tmp.first = i;
	// 	a.insert( tmp );
	// }
	// // const std::map<int, Base> e( a );
	// // e.find( 0 )->second = c;
	// // std::cout << "end" << std::endl;

	// a.at( 1 );

	SETUP_ARRAYS();

	{
		intmap m1( intstr_arr, intstr_arr + 32 );
		intmap m2;

		std::cout << "1" << std::endl;
		m1.print_tree();
		std::cout << "2" << std::endl;
		m2.print_tree();

		NAMESPACE::swap( m1, m2 );
		std::cout << "1" << std::endl;
		m1.print_tree();
		std::cout << "2" << std::endl;
		m2.print_tree();

		PRINT_ALL( m1 );
		PRINT_ALL( m2 );

		m1.clear();
		m1.swap( m2 );

		PRINT_ALL( m1 );
		PRINT_ALL( m2 );

		m1.clear();
		m2.swap( m1 );

		PRINT_ALL( m1 );
		PRINT_ALL( m2 );

		m1.insert( NAMESPACE::make_pair( 64, "N64" ) );
		NAMESPACE::swap( m1, m2 );

		PRINT_ALL( m1 );
		PRINT_ALL( m2 );

		m2.insert( intstr_arr, intstr_arr + intstr_size );
		m1.swap( m2 );

		PRINT_ALL( m1 );
		PRINT_ALL( m2 );

		m1.clear();
		m1.swap( m2 );
		m1.clear();
		m1.swap( m2 );

		PRINT_ALL( m1 );
		PRINT_ALL( m2 );
	}
}
