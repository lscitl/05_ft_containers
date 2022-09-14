/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:59:01 by seseo             #+#    #+#             */
/*   Updated: 2022/09/14 22:20:41 by seseo            ###   ########.fr       */
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
template <>
struct is_integral<long long int> : public true_type {};
template <>
struct is_integral<unsigned char> : public true_type {};
template <>
struct is_integral<unsigned short int> : public true_type {};
template <>
struct is_integral<unsigned int> : public true_type {};
template <>
struct is_integral<unsigned long int> : public true_type {};
template <>
struct is_integral<unsigned long long int> : public true_type {};

template <bool Cond, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
	typedef T type;
};

};  // namespace ft

#endif
