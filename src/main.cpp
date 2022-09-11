#include <iostream>
#include <string>
#include <deque>
#if 1  // CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <map.hpp>
#include <stack.hpp>
#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };

// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

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

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}

// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it !=
// iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }

#include <iostream>
#include <vector>

int main() {
	std::vector<int>::size_type sz;

	std::vector<int> foo;
	sz = foo.capacity();
	std::cout << sz << std::endl;
	std::cout << &( *foo.begin() ) << std::endl;
	std::cout << "making foo grow:\n";
	for ( int i = 0; i < 1; ++i ) {
		foo.push_back( 10 );
		if ( sz != foo.capacity() ) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	foo.pop_back();
	std::cout << "_end - _begin: " << foo.end() - foo.begin() << '\n';
	std::cout << "begin: " << &( *foo.begin() ) << '\n';
	std::cout << "end: " << &( *foo.end() ) << '\n';
	std::cout << "front: " << &foo.front() << '\n';
	std::cout << "back: " << &foo.back() << '\n';

	foo.back() = 5;
	std::cout << "back: " << foo.back() << '\n';
	std::cout << "back: " << &foo.back() << '\n';

	// int *p = new int( 100 );

	// std::cout << "end: " << &p[100] << '\n';
	// std::cout << "begin: " << p << '\n';
	// std::cout << "end - begin: " << static_cast<int>( &p[100] - p ) << '\n';

	// std::vector<int> bar;
	// sz = bar.capacity();
	// std::cout << sz << std::endl;
	// bar.reserve( 100 );  // this is the only difference with foo above
	// sz = bar.capacity();
	// std::cout << sz << std::endl;
	// std::cout << "making bar grow:\n";
	// for ( int i = 0; i < 100; ++i ) {
	// 	// std::cout << "i: " << i << std::endl;
	// 	bar.push_back( i );
	// 	if ( sz != bar.capacity() ) {
	// 		sz = bar.capacity();
	// 		std::cout << "capacity changed: " << sz << '\n';
	// 	}
	// }

	return 0;
}
