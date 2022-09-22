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

#include <stdlib.h>

#include <stack>
#include <vector>
#include <deque>
#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer {
	int  idx;
	char buff[BUFFER_SIZE];
};

#define COUNT ( MAX_RAM / (int)sizeof( Buffer ) )

#define _vector ft::vector
#define _stack ft::stack

int main() {
	_stack<int>      stk;
	std::vector<int> v;
	_vector<int>     deque;
	for ( int i = 0; i < 100 * 10000; ++i ) deque.push_back( i );
	for ( int i = 100 * 10000; i < 200 * 10000; ++i ) stk.push( i );
	_stack<int> stack( deque );
	_stack<int> stack2( stk );
	_stack<int> stack3;
	stack3 = stack2;
	while ( stack.size() > 0 ) {
		v.push_back( stack.top() );
		stack.pop();
	}
	while ( stack2.size() > 0 ) {
		v.push_back( stack2.top() );
		stack2.pop();
	}
	return 0;
}
