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

int main( void ) {
	std::map<int, Base> a;
	Base                b( "b" );
	// Base                 c( "c" );
	std::pair<int, Base> tmp( 0, b );

	// std::cout << "start" << std::endl;
	for ( int i = 0; i < 1; i++ ) {
		tmp.first = i;
		a.insert( tmp );
	}
	// const std::map<int, Base> e( a );
	// e.find( 0 )->second = c;
	// std::cout << "end" << std::endl;

	std::cout << a.lower_bound( 0 )->first << std::endl;

	// a[19];
}

// template <typename T>
// std::string printPair( const T &iterator, bool nl = true,
// 					   std::ostream &o = std::cout ) {
// 	o << "key: " << iterator->first << " | value: " << iterator->second;
// 	if ( nl ) o << std::endl;
// 	return ( "" );
// }

// template <typename T_MAP>
// void printSize( T_MAP const &mp, bool print_content = 1 ) {
// 	std::cout << "size: " << mp.size() << std::endl;
// 	std::cout << "max_size: " << mp.max_size() << std::endl;
// 	if ( print_content ) {
// 		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
// 		std::cout << std::endl << "Content is:" << std::endl;
// 		for ( ; it != ite; ++it )
// 			std::cout << "- " << printPair( it, false ) << std::endl;
// 	}
// 	std::cout << "###############################################" << std::endl;
// }

// template <typename T1, typename T2>
// void printReverse( ft::map<T1, T2> &mp ) {
// 	typename ft::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

// 	std::cout << "printReverse:" << std::endl;
// 	while ( it != ite ) {
// 		it--;
// 		std::cout << "-> " << printPair( it, false ) << std::endl;
// 	}
// 	std::cout << "_______________________________________________" << std::endl;
// }

// #define T1 int
// #define T2 std::string
// typedef ft::map<T1, T2>::value_type T3;
// typedef ft::map<T1, T2>::iterator   iterator;

// static int iter = 0;

// template <typename MAP, typename U>
// void ft_insert( MAP &mp, U param ) {
// 	ft::pair<iterator, bool> tmp;

// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	tmp = mp.insert( param );
// 	std::cout << "insert return: " << printPair( tmp.first );
// 	std::cout << "Created new node: " << tmp.second << std::endl;
// 	printSize( mp );
// }

// template <typename MAP, typename U, typename V>
// void ft_insert( MAP &mp, U param, V param2 ) {
// 	iterator tmp;

// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	tmp = mp.insert( param, param2 );
// 	std::cout << "insert return: " << printPair( tmp );
// 	printSize( mp );
// }

// int main( void ) {
// 	ft::map<T1, T2> mp, mp2;

// 	ft_insert( mp, T3( 42, "lol" ) );
// 	ft_insert( mp, T3( 42, "mdr" ) );

// 	ft_insert( mp, T3( 50, "mdr" ) );
// 	ft_insert( mp, T3( 35, "funny" ) );

// 	ft_insert( mp, T3( 45, "bunny" ) );
// 	ft_insert( mp, T3( 21, "fizz" ) );
// 	ft_insert( mp, T3( 38, "buzz" ) );

// 	ft_insert( mp, mp.begin(), T3( 55, "fuzzy" ) );

// 	ft_insert( mp2, mp2.begin(), T3( 1337, "beauty" ) );
// 	ft_insert( mp2, mp2.end(), T3( 1000, "Hello" ) );
// 	ft_insert( mp2, mp2.end(), T3( 1500, "World" ) );

// 	return ( 0 );
// }
