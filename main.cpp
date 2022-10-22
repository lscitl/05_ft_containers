#include <iostream>
#include <string>
#include <deque>
#if 0  // CREATE A REAL STL EXAMPLE
#include <map>
#include <set>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"
#endif

#include <functional>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer {
	int  idx;
	char buff[BUFFER_SIZE];
};

#define COUNT ( MAX_RAM / (int)sizeof( Buffer ) )

// #define NAMESPACE ft
// #include <map>
// #include <set>
// #include <chrono>
// #include "../map.hpp"
// #include "map_prelude.hpp"

#define _make_pair ft::make_pair
#define _map ft::map

template <class T, class V, class C>
void fillMap( ft::map<T, V, C>& mp, int num ) {
	mp.insert( ft::make_pair( num + 16, 3 ) );
	mp.insert( ft::make_pair( num + 8, 1 ) );
	mp.insert( ft::make_pair( num + 23, 6 ) );
	mp.insert( ft::make_pair( num + 7, 4 ) );
	mp.insert( ft::make_pair( num + 19, 5 ) );
	mp.insert( ft::make_pair( num + 29, 7 ) );
	mp.insert( ft::make_pair( num + 41, 2 ) );
	mp.insert( ft::make_pair( num + 4, 9 ) );
	mp.insert( ft::make_pair( num + 11, 8 ) );
}

// void leak_check() {
// 	system( "leaks containers" );
// }

#include <vector>

// int main( void ) {
// 	// atexit( &leak_check );
// 	_map<int, int>   mp;
// 	std::vector<int> v;
// 	fillMap( mp );
// 	for ( _map<int, int>::iterator it = mp.begin(); it != mp.end(); it++ ) {
// 		v.push_back( it->first );
// 	}
// 	for ( _map<int, int>::iterator it = --mp.end(); it != mp.begin(); it-- ) {
// 		v.push_back( it->first );
// 	}
// 	_map<int, int, std::greater<int> > mp1;
// 	fillMap( mp1 );
// 	v.push_back( mp1.begin()->first );
// 	mp1.erase( 41 );
// 	v.push_back( mp1.begin()->first );
// 	mp1.erase( 29 );
// 	v.push_back( mp1.begin()->first );
// 	_map<int, int, std::greater<int> > mp2;
// 	mp2.insert( _make_pair( 3, 3 ) );
// 	v.push_back( mp2.begin()->first );
// 	mp2.erase( 3 );
// 	if ( mp2.begin() == mp2.end() ) v.push_back( 1 );
// 	_map<int, int, std::plus<int> > mp3;
// }

// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

template <typename T>
class MutantStack : public ft::stack<T> {
   public:
	MutantStack() {
	}
	MutantStack( const MutantStack<T>& src ) {
		*this = src;
	}
	MutantStack<T>& operator=( const MutantStack<T>& rhs ) {
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {
	}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() {
		return this->c.begin();
	}
	iterator end() {
		return this->c.end();
	}
};

#include <sys/time.h>
#include <fstream>
void map_test( ft::vector<size_t>& v, char* file_name );
void vector_test( ft::vector<size_t>& v );

int main( int argc, char** argv ) {
	if ( argc != 3 ) {
		std::cerr << "Usage: ./test seed outfile_name" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi( argv[1] );
	srand( seed );

	ft::vector<std::string>                vector_str;
	ft::vector<int>                        vector_int;
	ft::stack<int>                         stack_int;
	ft::vector<Buffer>                     vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int>                      map_int;
	ft::set<int>                           set_int;

	for ( int i = 0; i < COUNT; i++ ) {
		vector_buffer.push_back( Buffer() );
	}

	for ( int i = 0; i < COUNT; i++ ) {
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap( vector_buffer );

	try {
		for ( int i = 0; i < COUNT; i++ ) {
			const int idx = rand() % COUNT;
			vector_buffer.at( idx );
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
		}
	} catch ( const std::exception& e ) {
		// NORMAL ! :P
	}

	for ( int i = 0; i < COUNT; ++i ) {
		map_int.insert( ft::make_pair( rand(), rand() ) );
	}

	int sum = 0;
	for ( int i = 0; i < 10000; i++ ) {
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{ ft::map<int, int> copy = map_int; }
	MutantStack<char> iterable_stack;
	for ( char letter = 'a'; letter <= 'z'; letter++ )
		iterable_stack.push( letter );
	for ( MutantStack<char>::iterator it = iterable_stack.begin();
		  it != iterable_stack.end(); it++ ) {
		std::cout << *it;
	}
	std::cout << std::endl;

	std::ofstream tmpfile( argv[2] );
	tmpfile.close();

	ft::vector<size_t> time_recoder;
	std::cout << "vector test!" << std::endl;
	vector_test( time_recoder );
	std::cout << "map test!" << std::endl;
	map_test( time_recoder, argv[2] );

	std::ofstream outfile( argv[2], std::ios_base::app );
	if ( outfile.is_open() ) {
		ft::vector<size_t>::iterator it = time_recoder.begin();

		for ( ; it != time_recoder.end(); it++ ) {
			outfile << *it << "ms ";
		}
	}

	return ( 0 );
}

size_t get_time_diff( struct timeval& t1, struct timeval& t2 ) {
	return ( t2.tv_sec * 1000 + t2.tv_usec / 1000 ) -
		   ( t1.tv_sec * 1000 + t1.tv_usec / 1000 );
}

#define TEST_NUM 1000000

void vector_test( ft::vector<size_t>& v ) {
	ft::vector<int> int_vec;
	struct timeval  t1;
	struct timeval  t2;

	int_vec.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < TEST_NUM; j++ ) {
			int_vec.push_back( j );
		}
		for ( ft::vector<int>::iterator i = int_vec.end(); i < int_vec.begin();
			  --i ) {
			int_vec.erase( i );
		}
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );

	std::cout << "vector test 1 done!" << std::endl;

	int_vec.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < TEST_NUM / 100; j++ ) {
			int_vec.insert( int_vec.end(), j );
		}
		int_vec.erase( int_vec.begin() + 20, int_vec.end() - 50 );
		int_vec.clear();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );

	std::cout << "vector test 2 done!" << std::endl;

	int_vec.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 5; i++ ) {
		int_vec.assign( TEST_NUM, TEST_NUM );
		int_vec.erase( int_vec.begin() + 20, int_vec.end() - 50 );
		int_vec.clear();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );

	std::cout << "vector test 3 done!" << std::endl;
}

void map_test( ft::vector<size_t>& v, char* file_name ) {
	ft::map<int, int>  int_map;
	ft::pair<int, int> elem;

	struct timeval t1;
	struct timeval t2;

	int_map.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 5000; i++ ) {
		fillMap( int_map, i * 50 );
		// for ( ft::map<int, int>::iterator i = int_map.begin();
		// 	  i != int_map.end(); ++i ) {
		// 	int_map.erase( i->first );
		// }
		int_map.clear();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );
	std::cout << "map test 1 done!" << std::endl;

	int_map.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 5000; i++ ) {
		fillMap( int_map, i * 50 );
		int_map.erase( ++( ++int_map.begin() ), --( --int_map.end() ) );
		int_map.clear();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );
	std::cout << "map test 2 done!" << std::endl;

	int_map.clear();
	gettimeofday( &t1, NULL );
	fillMap( int_map, 0 );
	fillMap( int_map, 50 );
	fillMap( int_map, 100 );
	fillMap( int_map, 150 );
	fillMap( int_map, 200 );

	std::ofstream outfile( file_name, std::ios_base::app );
	if ( outfile.is_open() ) {
		for ( ft::map<int, int>::iterator it = int_map.begin();
			  it != int_map.end(); ++it ) {
			outfile << "key: " << it->first << "\n";
		}
		outfile.close();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );
	std::cout << "map test 3 done!" << std::endl;
}
