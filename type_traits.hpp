/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:59:01 by seseo             #+#    #+#             */
/*   Updated: 2022/09/20 23:48:23 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __TYPE_TRAITS_H__
#define __TYPE_TRAITS_H__

#include <string>

namespace ft {

template <class T, T val>
struct integral_constant {
	static const T                    value = val;
	typedef T                         value_type;
	typedef integral_constant<T, val> type;
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template <class T>
struct is_integral : public false_type {};
template <>
struct is_integral<bool> : public true_type {};
template <>
struct is_integral<char> : public true_type {};
template <>
struct is_integral<wchar_t> : public true_type {};
template <>
struct is_integral<signed char> : public true_type {};
template <>
struct is_integral<short int> : public true_type {};
template <>
struct is_integral<int> : public true_type {};
template <>
struct is_integral<long int> : public true_type {};
// template <>
// struct is_integral<int64_t> : public true_type {};
template <>
struct is_integral<unsigned char> : public true_type {};
template <>
struct is_integral<unsigned short int> : public true_type {};
template <>
struct is_integral<unsigned int> : public true_type {};
template <>
struct is_integral<unsigned long int> : public true_type {};
// template <>
// struct is_integral<uint64_t> : public true_type {};

// template <class T>
// struct is_input_iterator : public false_type {};
// template <>
// struct is_input_iterator<std::input_iterator_tag> : public true_type {};

template <class T>
struct has_iterator_category {
   private:
	struct two {
		char lx;
		char lxx;
	};
	template <class U>
	static two test( ... );
	template <class U>
	static char test( typename U::iterator_category* = 0 );

   public:
	static const bool value = sizeof( test<T>( 0 ) ) == 1;
};

template <class T1, class T2>
struct is_convertible
	: public integral_constant<bool, __is_convertible_to( T1, T2 )> {};

template <class T, class U,
		  bool = has_iterator_category<iterator_traits<T> >::value>
struct has_iterator_tag
	: public integral_constant<
		  bool, is_convertible<typename iterator_traits<T>::iterator_category,
							   U>::value> {};

template <class T>
struct is_input_iterator : public has_iterator_tag<T, std::input_iterator_tag> {
};

template <class T>
struct is_forward_iterator
	: public has_iterator_tag<T, std::forward_iterator_tag> {};

// template <class T>
// struct is_forward_iterator : public false_type {};
// template <>
// struct is_forward_iterator<std::forward_iterator_tag> : public true_type {};

// template <>
// struct is_forward_iterator<std::bidirectional_iterator_tag> : public
// true_type {
// };
// template <>
// struct is_forward_iterator<std::random_access_iterator_tag> : public
// true_type {
// };

template <bool Cond, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
	typedef T type;
};

}  // namespace ft

#endif
