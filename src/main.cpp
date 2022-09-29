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

#define _vector std::vector

template <typename T>
class is_pair {
	typedef char yes[1];
	typedef struct {
		char x[2];
	} no;
	template <typename C>
	static yes& test( typename C::first_type = 0, typename C::second_type = 0 );

	template <typename C>
	static no& test( ... );

   public:
	static bool const value = sizeof( test<T>( 0, 0 ) ) == sizeof( yes );
};

int main() {
	// std::pair<int, char> t( 123, 'a' );
	// int                  b( 3 );

	std::cout << is_pair<std::pair<int, char> >::value << std::endl;
	std::cout << is_pair<int>::value << std::endl;

	return 0;
}
