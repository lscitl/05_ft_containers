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

int main() {
	// std::pair<int, char> t( 123, 'a' );
	// int                  b( 3 );

	// ft::rbtree_node<std::pair<int, char> > a;

	// a.value_field.first = 5;
	// a.value_field.second = 'a';

	// ft::pair<int, char> a;
	// int                 c;

	ft::rbtree<int>                  a;
	ft::rbtree<ft::pair<int, char> > b;
	std::less<int>                   tmp;
	int                              c = 1;
	int                              d = 2;

	std::cout << tmp( c, d ) << std::endl;

	return 0;
}
