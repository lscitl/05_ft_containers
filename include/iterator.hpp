/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 00:09:56 by seseo             #+#    #+#             */
/*   Updated: 2022/09/13 00:55:09 by seseo            ###   ########.fr       */
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
	typedef typename Iter::difference_type   difference_type;
	typedef typename Iter::value_type        value_type;
	typedef typename Iter::pointer           pointer;
	typedef typename Iter::reference         reference;
	typedef typename Iter::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
	typedef std::ptrdiff_t             difference_type;
	typedef T                          value_type;
	typedef const T*                   pointer;
	typedef const T&                   reference;
	typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
	typedef std::ptrdiff_t             difference_type;
	typedef T                          value_type;
	typedef const T*                   pointer;
	typedef const T&                   reference;
	typedef random_access_iterator_tag iterator_category;
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
		if ( this != u ) {
			current = u.base();
		}
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
		return std::addressof( operator*() );
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
		reverse_iterator ret( current - n );
		return ret;
	}

	reverse_iterator& operator+=( difference_type n ) {
		current -= n;
		return *this;
	}

	reverse_iterator operator-( difference_type n ) const {
		reverse_iterator ret( current + n );
		return ret;
	}

	reverse_iterator& operator-=( difference_type n ) {
		current += n;
		return *this;
	}

	reference operator[]( difference_type n ) const {
		return base()[n - 1];
	}
};

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
	return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
				 const ft::reverse_iterator<Iterator2>& rhs ) {
	return lhs.base() <= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
	return lhs.base() > rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
				 const ft::reverse_iterator<Iterator2>& rhs ) {
	return lhs.base() >= rhs.base();
}

};  // namespace ft

#endif
