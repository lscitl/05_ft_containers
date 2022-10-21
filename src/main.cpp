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
		intmap m( intstr_arr, intstr_arr + intstr_size );

		m.insert( NAMESPACE::make_pair( 34, "kljd9834iuhwet" ) );
		m.insert( NAMESPACE::make_pair( 3468, "dfghe45sywu4hsr" ) );
		m.insert( NAMESPACE::make_pair( 96533, "sdfghthrdfg5456ik" ) );
		m.insert( NAMESPACE::make_pair( 1954894589, "jtt5454wujtjse" ) );
		m.insert( NAMESPACE::make_pair( 7754322, "w4wt5u4wjhstrhj" ) );
		m.insert( NAMESPACE::make_pair( 3632, "dfgjjkuy56ue5uwyhry5yeh" ) );
		m.insert( NAMESPACE::make_pair( 3, "rtjey5w4u4u5e6kjwj5w4" ) );
		m.insert( NAMESPACE::make_pair( 4, "asdfhfjgh54w3ag" ) );
		m.insert( NAMESPACE::make_pair( -873487, "jw56jw45jsryjsrt5u4w5" ) );
		m.insert( NAMESPACE::make_pair( -95763433, "ws45uhsrtjnsrths54yh" ) );
		m.insert( NAMESPACE::make_pair( 453834782, "juytje54yaerdrj" ) );
		m.insert( NAMESPACE::make_pair( 19458942, "j567uysdts56y6uj5r" ) );
		m.insert( NAMESPACE::make_pair( 1245689793,
										"jr67e5674574668679789ruyerdtadh" ) );

		NAMESPACE::pair<intmap::iterator, intmap::iterator> eq =
			m.equal_range( 98583944 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 209485948 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 19458942 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 19458941 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 19458943 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( -1 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 3 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 4 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 5 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 0 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( std::numeric_limits<int>::max() );

		PRINT_EQ_RANGE( eq, m.end() );

		m.insert(
			NAMESPACE::make_pair( std::numeric_limits<int>::max(), "max" ) );

		eq = m.equal_range( std::numeric_limits<int>::max() );

		PRINT_EQ_RANGE( eq, m.end() );
	}

	{
		intmap temp( intstr_arr, intstr_arr + intstr_size );

		temp.insert( NAMESPACE::make_pair( 34, "kljd9834iuhwet" ) );
		temp.insert( NAMESPACE::make_pair( 3468, "dfghe45sywu4hsr" ) );
		temp.insert( NAMESPACE::make_pair( 96533, "sdfghthrdfg5456ik" ) );
		temp.insert( NAMESPACE::make_pair( 1954894589, "jtt5454wujtjse" ) );
		temp.insert( NAMESPACE::make_pair( 7754322, "w4wt5u4wjhstrhj" ) );
		temp.insert( NAMESPACE::make_pair( 3632, "dfgjjkuy56ue5uwyhry5yeh" ) );
		temp.insert( NAMESPACE::make_pair( 3, "rtjey5w4u4u5e6kjwj5w4" ) );
		temp.insert( NAMESPACE::make_pair( 4, "asdfhfjgh54w3ag" ) );
		temp.insert( NAMESPACE::make_pair( -873487, "jw56jw45jsryjsrt5u4w5" ) );
		temp.insert(
			NAMESPACE::make_pair( -95763433, "ws45uhsrtjnsrths54yh" ) );
		temp.insert( NAMESPACE::make_pair( 453834782, "juytje54yaerdrj" ) );
		temp.insert( NAMESPACE::make_pair( 19458942, "j567uysdts56y6uj5r" ) );
		temp.insert( NAMESPACE::make_pair(
			1245689793, "jr67e5674574668679789ruyerdtadh" ) );

		const intmap m( temp );

		NAMESPACE::pair<intmap::const_iterator, intmap::const_iterator> eq =
			m.equal_range( 98583944 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 209485948 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 19458942 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 19458941 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 19458943 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( -1 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 3 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 4 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 5 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( 0 );

		PRINT_EQ_RANGE( eq, m.end() );

		eq = m.equal_range( std::numeric_limits<int>::max() );

		PRINT_EQ_RANGE( eq, m.end() );

		// m.print_tree();
		// m.tree_debug();
	}

	{
		const intmap m;

		NAMESPACE::pair<intmap::const_iterator, intmap::const_iterator> eq =
			m.equal_range( std::numeric_limits<int>::max() );

		PRINT_EQ_RANGE( eq, m.end() );
	}
}
