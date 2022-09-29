/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:59:01 by seseo             #+#    #+#             */
/*   Updated: 2022/09/29 22:48:00 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __TYPE_TRAITS_H__
#define __TYPE_TRAITS_H__

#include <iterator>  // for iterator_tag
// #include <stdint.h>

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

template <class T>
struct remove_const {
	typedef T type;
};
template <class T>
struct remove_const<const T> {
	typedef T type;
};

template <class T>
struct remove_volatile {
	typedef T type;
};
template <class T>
struct remove_volatile<volatile T> {
	typedef T type;
};

template <class T>
struct remove_cv {
	typedef typename remove_volatile<typename remove_const<T>::type>::type type;
};

template <class T>
struct is_integral : public ft_is_integral<typename remove_cv<T>::type> {};

template <bool Cond, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
	typedef T type;
};

}  // namespace ft

#endif
