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

#include <stdlib.h>
#include <functional>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer {
	int  idx;
	char buff[BUFFER_SIZE];
};

#define COUNT ( MAX_RAM / (int)sizeof( Buffer ) )

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

void vector_test( ft::vector<size_t>& v );
void map_test( ft::vector<size_t>& v, char* file_name );
void set_test( ft::vector<size_t>& v, char* file_name );

class Base {
   public:
	std::string str;
	Base( std::string x ) {
		this->str = x;
	}
	~Base() {
	}

   private:
	Base();
};

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
	std::cout << "set test!" << std::endl;
	set_test( time_recoder, argv[2] );

	std::ofstream outfile( argv[2], std::ios_base::app );
	if ( outfile.is_open() ) {
		ft::vector<size_t>::iterator it = time_recoder.begin();

		for ( ; it != time_recoder.end(); it++ ) {
			outfile << *it << "ms ";
		}
	}

	ft::map<int, Base> base_map;
	// Base               base;

	base_map.insert( ft::make_pair( 1, Base( "test1" ) ) );
	base_map.insert( ft::make_pair( 2, Base( "test2" ) ) );
	base_map.insert( ft::make_pair( 3, Base( "test3" ) ) );
	base_map.insert( ft::make_pair( 4, Base( "test4" ) ) );
	std::cout << base_map.find( 1 )->second.str << std::endl;
	std::cout << base_map.find( 2 )->second.str << std::endl;
	std::cout << base_map.find( 3 )->second.str << std::endl;
	std::cout << base_map.find( 4 )->second.str << std::endl;

	return ( 0 );
}

size_t get_time_diff( struct timeval& t1, struct timeval& t2 ) {
	return ( t2.tv_sec * 1000 + t2.tv_usec / 1000 ) -
		   ( t1.tv_sec * 1000 + t1.tv_usec / 1000 );
}

#define TEST_NUM 5000000

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

template <class T, class C>
void fillSet( ft::set<T, C>& mp, int num ) {
	mp.insert( num + 16 );
	mp.insert( num + 8 );
	mp.insert( num + 23 );
	mp.insert( num + 7 );
	mp.insert( num + 19 );
	mp.insert( num + 29 );
	mp.insert( num + 41 );
	mp.insert( num + 4 );
	mp.insert( num + 11 );
}

void map_test( ft::vector<size_t>& v, char* file_name ) {
	ft::map<int, int>  int_map;
	ft::pair<int, int> elem;

	struct timeval t1;
	struct timeval t2;

	int_map.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 50000; i++ ) {
		fillMap( int_map, i * 50 );
		int_map.clear();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );
	std::cout << "map test 1 done!" << std::endl;

	int_map.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 50000; i++ ) {
		fillMap( int_map, i * 50 );
		int_map.erase( ++( ++int_map.begin() ), --( --int_map.end() ) );
		int_map.clear();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );
	std::cout << "map test 2 done!" << std::endl;

	int_map.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 20; i++ ) {
		fillMap( int_map, i * 50 );
	}

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

void set_test( ft::vector<size_t>& v, char* file_name ) {
	ft::set<int>       int_set;
	ft::pair<int, int> elem;

	struct timeval t1;
	struct timeval t2;

	int_set.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 50000; i++ ) {
		fillSet( int_set, i * 50 );
		int_set.clear();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );
	std::cout << "set test 1 done!" << std::endl;

	int_set.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 50000; i++ ) {
		fillSet( int_set, i * 50 );
		int_set.erase( ++( ++int_set.begin() ), --( --int_set.end() ) );
		int_set.clear();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );
	std::cout << "set test 2 done!" << std::endl;

	int_set.clear();
	gettimeofday( &t1, NULL );
	for ( int i = 0; i < 20; i++ ) {
		fillSet( int_set, i * 50 );
	}

	std::ofstream outfile( file_name, std::ios_base::app );
	if ( outfile.is_open() ) {
		for ( ft::set<int>::iterator it = int_set.begin(); it != int_set.end();
			  ++it ) {
			outfile << "key: " << *it << "\n";
		}
		outfile.close();
	}
	gettimeofday( &t2, NULL );
	v.push_back( get_time_diff( t1, t2 ) );
	std::cout << "set test 3 done!" << std::endl;
}
