/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 00:09:56 by seseo             #+#    #+#             */
/*   Updated: 2022/09/27 01:28:02 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <cstddef>
#include "type_traits.hpp"

namespace ft {

template <class Iter>
struct iterator_traits {
	typedef typename Iter::difference_type   difference_type;
	typedef typename Iter::value_type        value_type;
	typedef typename Iter::pointer           pointer;
	typedef typename Iter::reference         reference;
	typedef typename Iter::iterator_category iterator_category;
};

// template <class T>
// struct iterator_traits {
// 	typedef std::ptrdiff_t difference_type;
// 	typedef T              value_type;
// 	typedef T*             pointer;
// 	typedef T&             reference;
// 	typedef void           iterator_category;
// };

// template <>
// struct iterator_traits<int> {
// 	typedef std::ptrdiff_t difference_type;
// 	typedef int            value_type;
// 	typedef int*           pointer;
// 	typedef int&           reference;
// 	typedef void           iterator_category;
// };

template <class T>
struct iterator_traits<T*> {
	typedef std::ptrdiff_t                  difference_type;
	typedef T                               value_type;
	typedef T*                              pointer;
	typedef T&                              reference;
	typedef std::random_access_iterator_tag iterator_category;
};

// template <class T>
// struct iterator_traits<const T*> {
// 	typedef std::ptrdiff_t                  difference_type;
// 	typedef const T                         value_type;
// 	typedef const T*                        pointer;
// 	typedef const T&                        reference;
// 	typedef std::random_access_iterator_tag iterator_category;
// };

template <class Category, class T, class Distance = ptrdiff_t,
		  class Pointer = T*, class Reference = T&>
struct iterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

template <class RandIter>
typename iterator_traits<RandIter>::difference_type _distance(
	RandIter first, RandIter last, std::random_access_iterator_tag ) {
	return last - first;
}

template <class InputIter>
typename iterator_traits<InputIter>::difference_type _distance(
	InputIter first, InputIter last, std::input_iterator_tag ) {
	typename iterator_traits<InputIter>::difference_type ret( 0 );
	for ( ; first != last; ++first ) {
		++ret;
	}
	return ret;
}

template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type distance(
	InputIterator first, InputIterator last ) {
	return _distance(
		first, last,
		typename iterator_traits<InputIterator>::iterator_category() );
}

template <class Iter>
class reverse_iterator
	: public ft::iterator<typename iterator_traits<Iter>::iterator_category,
						  typename iterator_traits<Iter>::value_type,
						  typename iterator_traits<Iter>::difference_type,
						  typename iterator_traits<Iter>::pointer,
						  typename iterator_traits<Iter>::reference> {
   protected:
	Iter current;

   public:
	typedef Iter                                            iterator_type;
	typedef typename iterator_traits<Iter>::difference_type difference_type;
	typedef typename iterator_traits<Iter>::reference       reference;
	typedef typename iterator_traits<Iter>::pointer         pointer;

	reverse_iterator() : current() {
	}

	explicit reverse_iterator( Iter x ) : current( x ) {
	}

	template <class U>
	reverse_iterator( const reverse_iterator<U>& u ) : current( u.base() ) {
	}

	template <class U>
	reverse_iterator& operator=( const reverse_iterator<U>& u ) {
		current = u.base();
		return *this;
	}

	Iter base() const {
		return current;
	};

	reference operator*() const {
		Iter ret = current;
		return *--ret;
	}

	pointer operator->() const {
		Iter ret = current;
		return &( *--ret );
	}

	reverse_iterator& operator++() {
		--current;
		return *this;
	}

	reverse_iterator operator++( int ) {
		reverse_iterator ret( *this );
		--current;
		return ret;
	}

	reverse_iterator& operator--() {
		++current;
		return *this;
	}

	reverse_iterator operator--( int ) {
		reverse_iterator ret( *this );
		++current;
		return ret;
	}

	reverse_iterator operator+( difference_type n ) const {
		return reverse_iterator( current - n );
	}

	reverse_iterator& operator+=( difference_type n ) {
		current -= n;
		return *this;
	}

	reverse_iterator operator-( difference_type n ) const {
		return reverse_iterator( current + n );
	}

	reverse_iterator& operator-=( difference_type n ) {
		current += n;
		return *this;
	}

	reference operator[]( difference_type n ) const {
		return *( *this + n );
	}
};

template <class Iterator>
reverse_iterator<Iterator> operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator>&                    rev_it ) {
	return reverse_iterator<Iterator>( rev_it.base() - n );
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs ) {
	return rhs.base() - lhs.base();
}

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator-(
	const reverse_iterator<Iterator1>& lhs,
	const reverse_iterator<Iterator2>& rhs ) {
	return rhs.base() - lhs.base();
}

template <class Iterator1, class Iterator2>
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
				 const ft::reverse_iterator<Iterator2>& rhs ) {
	return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
				 const ft::reverse_iterator<Iterator2>& rhs ) {
	return lhs.base() != rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
	return lhs.base() > rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
				 const ft::reverse_iterator<Iterator2>& rhs ) {
	return lhs.base() >= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
	return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
				 const ft::reverse_iterator<Iterator2>& rhs ) {
	return lhs.base() <= rhs.base();
}

// template <typename T>
// class has_iterator_category {
//    private:
// 	typedef char one;
// 	typedef struct {
// 		char x[2];
// 	} two;
// 	template <typename C>
// 	static one test( typename C::* );
// 	template <typename C>
// 	static two test( ... );

//    public:
// 	static const bool value =
// 		sizeof( has_iterator_category<T>::test<T>( 0 ) ) == 1;
// };

template <typename T>
class has_iterator_category {
   private:
	typedef char One;
	typedef struct {
		char x[2];
	} Two;
	template <typename C>
	static One test( int C::* );
	template <typename C>
	static Two test( ... );

   public:
	static const bool value =
		sizeof( has_iterator_category<T>::test<T>( 0 ) ) == 1;
};

template <class T>
struct __is_input_iterator : public false_type {};
template <>
struct __is_input_iterator<std::input_iterator_tag> : public true_type {};
template <>
struct __is_input_iterator<std::forward_iterator_tag> : public true_type {};
template <>
struct __is_input_iterator<std::bidirectional_iterator_tag> : public true_type {
};
template <>
struct __is_input_iterator<std::random_access_iterator_tag> : public true_type {
};

template <class T>
struct __is_forward_iterator : public false_type {};
template <>
struct __is_forward_iterator<std::forward_iterator_tag> : public true_type {};
template <>
struct __is_forward_iterator<std::bidirectional_iterator_tag>
	: public true_type {};
template <>
struct __is_forward_iterator<std::random_access_iterator_tag>
	: public true_type {};

template <class T, bool = has_iterator_category<iterator_traits<T> >::value>
struct _is_input_iterator
	: public integral_constant<
		  bool, __is_input_iterator<
					typename iterator_traits<T>::iterator_category>::value> {};

template <class T>
struct _is_input_iterator<T, false> : public false_type {};

template <class T, bool = has_iterator_category<iterator_traits<T> >::value>
struct _is_forward_iterator
	: public integral_constant<
		  bool, __is_forward_iterator<
					typename iterator_traits<T>::iterator_category>::value> {};

template <class T>
struct _is_forward_iterator<T, false> : public false_type {};

template <class T>
struct is_input_iterator : public _is_input_iterator<T> {};

template <class T>
struct is_forward_iterator : public _is_forward_iterator<T> {};

}  // namespace ft

#endif
