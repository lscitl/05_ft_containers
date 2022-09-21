/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:59:01 by seseo             #+#    #+#             */
/*   Updated: 2022/09/22 01:20:04 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __TYPE_TRAITS_H__
#define __TYPE_TRAITS_H__

#include <string>
#include <stdint.h>

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
struct ft_is_integral : public false_type {};
template <>
struct ft_is_integral<bool> : public true_type {};
template <>
struct ft_is_integral<char> : public true_type {};
template <>
struct ft_is_integral<wchar_t> : public true_type {};
template <>
struct ft_is_integral<signed char> : public true_type {};
template <>
struct ft_is_integral<short int> : public true_type {};
template <>
struct ft_is_integral<int> : public true_type {};
template <>
struct ft_is_integral<long int> : public true_type {};
// template <>
// struct ft_is_integral<int64_t> : public true_type {};
template <>
struct ft_is_integral<unsigned char> : public true_type {};
template <>
struct ft_is_integral<unsigned short int> : public true_type {};
template <>
struct ft_is_integral<unsigned int> : public true_type {};
template <>
struct ft_is_integral<unsigned long int> : public true_type {};
// template <>
// struct ft_is_integral<uint64_t> : public true_type {};

// template <class T>
// struct remove_const {
// 	typedef T type;
// };
// template <class T>
// struct remove_const<const T> {
// 	typedef T type;
// };

// template <class T>
// struct remove_volatile {
// 	typedef T type;
// };
// template <class T>
// struct remove_volatile<volatile T> {
// 	typedef T type;
// };

// template <class T>
// struct remove_cv {
// 	typedef typename remove_volatile<typename remove_const<T>::type>::type type;
// };

// template <class T>
// struct is_integral : public ft_is_integral<typename remove_cv<T>::type> {};

template <class T>
struct is_integral : public ft_is_integral<T> {};

// template <class T>
// struct has_iterator_typedefs {
//    private:
// 	struct two {
// 		char lx;
// 		char lxx;
// 	};
// 	template <class U>
// 	static two test( ... );
// 	template <class U>
// 	static char test(
// 		typename ft::void_t<typename U::iterator_category>::type* = 0,
// 		typename ft::void_t<typename U::difference_type>::type* = 0,
// 		typename ft::void_t<typename U::value_type>::type* = 0,
// 		typename ft::void_t<typename U::reference>::type* = 0,
// 		typename ft::void_t<typename U::pointer>::type* = 0 );

//    public:
// 	static const bool value = sizeof( test<T>( 0, 0, 0, 0, 0 ) ) == 1;
// };

// template <class...>
// using void_t = void;

// template <class T, bool Cond>
// struct is_input_iterator : public false_type {};
// template <class T>
// struct is_input_iterator<T, false> : public false_type {};
// template <class T>
// struct is_input_iterator<T, true> : public false_type {};
// template <>
// struct is_input_iterator<std::input_iterator_tag, true> : public true_type
// {};

// template <class T, bool Cond>
// struct is_forward_iterator : public false_type {};
// template <class T>
// struct is_forward_iterator<T, false> : public false_type {};
// template <class T>
// struct is_forward_iterator<T, true> : public false_type {};
// template <>
// struct is_forward_iterator<std::input_iterator_tag, true> : public false_type
// {
// };
// template <>
// struct is_forward_iterator<std::forward_iterator_tag, true> : public
// true_type {
// };

// template <class T>
// struct has_iterator_category {
//    private:
// 	struct two {
// 		char lx;
// 		char lxx;
// 	};
// 	template <class U>
// 	static two test( ... );
// 	template <class U>
// 	static char test( typename U::iterator_category* = 0 );

//    public:
// 	static const bool value = sizeof( test<T>( 0 ) ) == 1;
// };

// template <class T>
// struct __is_input_iterator : public false_type {};
// template <>
// struct __is_input_iterator<std::input_iterator_tag> : public true_type {};
// template <>
// struct __is_input_iterator<std::forward_iterator_tag> : public true_type {};
// template <>
// struct __is_input_iterator<std::bidirectional_iterator_tag> : public
// true_type {
// };
// template <>
// struct __is_input_iterator<std::random_access_iterator_tag> : public
// true_type {
// };

// template <class T>
// struct __is_forward_iterator : public false_type {};
// template <>
// struct __is_forward_iterator<std::forward_iterator_tag> : public true_type
// {}; template <> struct __is_forward_iterator<std::bidirectional_iterator_tag>
// 	: public true_type {};
// template <>
// struct __is_forward_iterator<std::random_access_iterator_tag>
// 	: public true_type {};

// template <class T, bool = has_iterator_category<iterator_traits<T> >::value>
// struct _is_input_iterator
// 	: public integral_constant<
// 		  bool, __is_input_iterator<
// 					typename iterator_traits<T>::iterator_category>::value> {};

// template <class T>
// struct _is_input_iterator<T, false> : public false_type {};

// template <class T, bool = has_iterator_category<iterator_traits<T> >::value>
// struct _is_forward_iterator
// 	: public integral_constant<
// 		  bool, __is_forward_iterator<
// 					typename iterator_traits<T>::iterator_category>::value> {};

// template <class T>
// struct _is_forward_iterator<T, false> : public false_type {};

// template <class T>
// struct is_input_iterator : public _is_input_iterator<T> {};

// template <class T>
// struct is_forward_iterator : public _is_forward_iterator<T> {};

// template <class T, class U,
// 		  bool = has_iterator_category<iterator_traits<T> >::value>
// struct has_iterator_category_convertible_to
// 	: public integral_constant<bool,
// 							   typename iterator_traits<T>::iterator_category> {
// };

// template <class T, class U>
// struct has_iterator_category_convertible_to<T, false> : public false_type {};

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
