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
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer {
	int  idx;
	char buff[BUFFER_SIZE];
};

#define COUNT ( MAX_RAM / (int)sizeof( Buffer ) )

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs)
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main( int argc, char** argv ) {
// 	if ( argc != 2 ) {
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi( argv[1] );
// 	srand( seed );

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int>         vector_int;
// 	// ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	// ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	// ft::map<int, int> map_int;

// 	for ( int i = 0; i < COUNT; i++ ) {
// 		vector_buffer.push_back( Buffer() );
// 	}

// 	for ( int i = 0; i < COUNT; i++ ) {
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer> tmp;
// 	tmp.swap( vector_buffer );

// 	try {
// 		for ( int i = 0; i < COUNT; i++ ) {
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at( idx );
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" << std::endl;
// 		}
// 	} catch ( const std::exception& e ) {
// 		// NORMAL ! :P
// 	}
// 	swap( tmp, vector_buffer );
// 	std::cout << "end" << std::endl;

// 	// 	for (int i = 0; i < COUNT; ++i)
// 	// 	{
// 	// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	// 	}

// 	// 	int sum = 0;
// 	// 	for (int i = 0; i < 10000; i++)
// 	// 	{
// 	// 		int access = rand();
// 	// 		sum += map_int[access];
// 	// 	}
// 	// 	std::cout << "should be constant with the same seed: " << sum <<
// 	// std::endl;

// 	// 	{
// 	// 		ft::map<int, int> copy = map_int;
// 	// 	}
// 	// 	MutantStack<char> iterable_stack;
// 	// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 	// 		iterable_stack.push(letter);
// 	// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it !=
// 	// iterable_stack.end(); it++)
// 	// 	{
// 	// 		std::cout << *it;
// 	// 	}
// 	// 	std::cout << std::endl;
// 	return ( 0 );
// }

#include <vector>

#define TESTED_NAMESPACE ft
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

#include <iostream>
#include <string>

template <typename T>
void printSize( TESTED_NAMESPACE::vector<T> const &vct,
				bool                               print_content = true ) {
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = ( capacity >= size ) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if ( print_content ) {
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for ( ; it != ite; ++it ) std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}
#define TESTED_TYPE int

int main( void ) {
	const int                                               size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE>                   vct( size );
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator ite =
		vct.rbegin();

	for ( int i = 0; i < size; ++i ) it[i] = ( size - i ) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *( it += 2 ) << std::endl;
	std::cout << *( it -= 1 ) << std::endl;

	*( it -= 2 ) = 42;
	*( it += 2 ) = 21;

	std::cout << "const_ite +=/-=: " << *( ite += 2 ) << " | " << *( ite -= 2 )
			  << std::endl;

	std::cout << "(it == const_it): " << ( ite == it ) << std::endl;
	std::cout << "(const_ite - it): " << ( ite - it ) << std::endl;
	std::cout << "(ite + 3 == it): " << ( ite + 3 == it ) << std::endl;

	printSize( vct, true );
	return ( 0 );
}
