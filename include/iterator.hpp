/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 00:09:56 by seseo             #+#    #+#             */
/*   Updated: 2022/09/08 20:27:12 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __ITERATOR_H__
#define __ITERATOR_H__

namespace ft {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Iter>
struct iterator_traits {
	typedef Iter::difference_type   difference_type;
	typedef Iter::value_type        value_type;
	typedef Iter::pointer           pointer;
	typedef Iter::reference         reference;
	typedef Iter::iterator_category iterator_category;
};

template <class _Tp>
struct iterator_traits<_Tp*> {
	typedef std::ptrdiff_t                 difference_type;
	typedef _Tp                            value_type;
	typedef const _Tp*                     pointer;
	typedef const _Tp&                     reference;
	typedef ft::random_access_iterator_tag iterator_category;
};

template <class _Tp>
struct iterator_traits<const _Tp*> {
	typedef std::ptrdiff_t                  difference_type;
	typedef _Tp                             value_type;
	typedef const _Tp*                      pointer;
	typedef const _Tp&                      reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template <class Category, class T, class Distance = ptrdiff_t,
		  class Pointer = T*, class Reference = T&>
struct iterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

template <class Iterator>
class reverse_iterator
	: public iterator<typename iterator_traits<Iterator>::iterator_category,
					  typename iterator_traits<Iterator>::value_type,
					  typename iterator_traits<Iterator>::difference_type,
					  typename iterator_traits<Iterator>::pointer,
					  typename iterator_traits<Iterator>::reference> {
   protected:
	Iterator current;

   public:
	typedef Iterator                                            iterator_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::reference       reference;
	typedef typename iterator_traits<Iterator>::pointer         pointer;

	reverse_iterator();
	explicit reverse_iterator( Iterator x );

	template <class U>
	reverse_iterator( const reverse_iterator<U>& u );

	template <class U>
	reverse_iterator& operator=( const reverse_iterator<U>& u );

	Iterator          base() const;
	reference         operator*() const;
	pointer           operator->() const;
	reverse_iterator& operator++();
	reverse_iterator  operator++( int );
	reverse_iterator& operator--();
	reverse_iterator  operator--( int );
	reverse_iterator  operator+( difference_type n ) const;
	reverse_iterator& operator+=( difference_type n );
	reverse_iterator  operator-( difference_type n ) const;
	reverse_iterator& operator-=( difference_type n );
	reference         operator[]( difference_type n ) const;
};

};  // namespace ft

#endif
