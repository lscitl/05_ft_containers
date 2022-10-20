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

#define NAMESPACE std
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
		strmap m( strstr_arr, strstr_arr + 16 );

		strmap::iterator it = m.find( "Hello" );

		if ( it != m.end() ) {
			PRINT_PAIR_REF( *it );
		}

		try {
			std::string& ref = m.at( "World!" );

			PRINT_LINE( "Val:", ref );
		} catch ( std::out_of_range& e ) {
			PRINT_MSG( "Exception" );
		}
		CATCH_UNHANDLED_EX();

		PRINT_ALL( m );

		m.insert( strstr_arr, strstr_arr + strstr_size );

		PRINT_ALL( m );

		m.erase( m.begin() );

		PRINT_ALL( m );

		it = m.begin();
		std::advance( it, 10 );

		m.erase( it, m.end() );

		PRINT_ALL( m );

		strmap::size_type s = m.erase( "1234" );

		PRINT_ALL( m );
		PRINT_LINE( "S:", s );

		m.clear();

		PRINT_ALL( m );

		it = m.insert( m.begin(), NAMESPACE::make_pair( "", "test" ) );

		PRINT_LINE( "Count:", m.count( "" ) );

		PRINT_PAIR_REF( *it );
		PRINT_ALL( m );

		m.insert( strstr_arr, strstr_arr + strstr_size );

		strmap n( strstr_arr, strstr_arr + 10 );

		m.swap( n );

		PRINT_ALL( m );
		PRINT_ALL( n );

		PRINT_EQ_RANGE( m.equal_range( "abcd" ), m.end() );
		// PRINT_BOUND( m.lower_bound( "123" ), m.end() );
		// PRINT_BOUND( m.upper_bound( "jhg456" ), m.end() );

		// PRINT_LINE( "Find:", m.find( "hello" ) != m.end()
		// 						 ? m.find( "hello" )->first
		// 						 : "End" );

		// m["hello"] = "world";

		// PRINT_LINE( "Find:", m.find( "hello" ) != m.end()
		// 						 ? m.find( "hello" )->first
		// 						 : "End" );
	}

	// {
	// 	NAMESPACE::map<int, int, std::less<int>,
	// 				   track_allocator<NAMESPACE::pair<const int, int> > >
	// 		m;

	// 	for ( int i = 0; i < 50000; ++i ) {
	// 		m.insert( NAMESPACE::make_pair( rand(), rand() ) );
	// 	}

	// 	PRINT_ALL( m );

	// 	m.erase( m.begin(), m.end() );

	// 	PRINT_ALL( m );
	// }
}
