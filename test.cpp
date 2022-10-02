#include <map>
#include <iostream>
#include <iterator>

int main( void ) {
	std::string                 str;
	std::map<std::string, char> a;

	for ( int i = 0; i < 10; i++ ) {
		str += "a";
		std::cout << ( a.insert( std::make_pair( str, 'a' + i ) ) ).second
				  << std::endl;
	}
	str.clear();
	for ( int i = 0; i < 10; i++ ) {
		str += "a";
		std::cout << ( a.insert( std::make_pair( str, 'a' + i ) ) ).second
				  << std::endl;
	}
}
