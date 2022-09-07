/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 00:09:56 by seseo             #+#    #+#             */
/*   Updated: 2022/09/07 23:18:59 by seseo            ###   ########.fr       */
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
	typedef std::ptrdiff_t                  difference_type;
	typedef _Tp                             value_type;
	typedef const _Tp*                      pointer;
	typedef const _Tp&                      reference;
	typedef std::random_access_iterator_tag iterator_category;
}

};  // namespace ft

template <class Iter>
class iterator {
   public:
	typedef Iter                                         iterator_type;
	typedef ft::iterator_traits<Iter>::iterator_category iterator_category;
	typedef ft::iterator_traits<Iter>::value_type        value_type;
	typedef ft::iterator_traits<Iter>::difference_type   difference_type;
	typedef ft::iterator_traits<Iter>::pointer           pointer;
	typedef ft::iterator_traits<Iter>::reference         reference;

	iterator();
	explicit iterator( iterator_type it );

	template <class Iter>
	iterator( const reverse_iterator<Iter>& rev_it );
};

#endif
