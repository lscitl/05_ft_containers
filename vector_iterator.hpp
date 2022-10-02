/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:16:05 by seseo             #+#    #+#             */
/*   Updated: 2022/10/02 21:36:58 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __VECTOR_ITERATOR_H__
#define __VECTOR_ITERATOR_H__

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

template <class Iter>
class vector_iterator {
   public:
	typedef Iter                                              iterator_type;
	typedef typename iterator_traits<Iter>::value_type        value_type;
	typedef typename iterator_traits<Iter>::pointer           pointer;
	typedef typename iterator_traits<Iter>::reference         reference;
	typedef typename iterator_traits<Iter>::difference_type   difference_type;
	typedef typename iterator_traits<Iter>::iterator_category iterator_category;

   protected:
	pointer _current;

   public:
	vector_iterator() : _current( NULL ) {
	}

	explicit vector_iterator( pointer x ) : _current( x ) {
	}

	template <class U>
	vector_iterator( const vector_iterator<U>& u ) : _current( u.base() ) {
	}

	template <class U>
	vector_iterator& operator=( const vector_iterator<U>& u ) {
		_current = u.base();
		return *this;
	}

	pointer base() const {
		return _current;
	};

	reference operator*() const {
		return *_current;
	}

	pointer operator->() const {
		return _current;
	}

	vector_iterator& operator++() {
		++_current;
		return *this;
	}

	vector_iterator operator++( int ) {
		vector_iterator ret( *this );
		++_current;
		return ret;
	}

	vector_iterator& operator--() {
		--_current;
		return *this;
	}

	vector_iterator operator--( int ) {
		vector_iterator ret( *this );
		--_current;
		return ret;
	}

	vector_iterator operator+( difference_type n ) const {
		return vector_iterator( _current + n );
	}

	vector_iterator& operator+=( difference_type n ) {
		_current += n;
		return *this;
	}

	vector_iterator operator-( difference_type n ) const {
		return vector_iterator( _current - n );
	}

	vector_iterator& operator-=( difference_type n ) {
		_current -= n;
		return *this;
	}

	reference operator[]( difference_type n ) const {
		return this->base()[n];
	}
};

template <class Iterator>
vector_iterator<Iterator> operator+(
	typename vector_iterator<Iterator>::difference_type n,
	const vector_iterator<Iterator>&                    iter ) {
	return iter + n;
}

template <class Iterator>
typename vector_iterator<Iterator>::difference_type operator-(
	const vector_iterator<Iterator>& lhs,
	const vector_iterator<Iterator>& rhs ) {
	return lhs.base() - rhs.base();
}

template <class Iterator1, class Iterator2>
typename vector_iterator<Iterator1>::difference_type operator-(
	const vector_iterator<Iterator1>& lhs,
	const vector_iterator<Iterator2>& rhs ) {
	return lhs.base() - rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator==( const vector_iterator<Iterator1>& lhs,
				 const vector_iterator<Iterator2>& rhs ) {
	return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=( const vector_iterator<Iterator1>& lhs,
				 const vector_iterator<Iterator2>& rhs ) {
	return lhs.base() != rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<( const vector_iterator<Iterator1>& lhs,
				const vector_iterator<Iterator2>& rhs ) {
	return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=( const vector_iterator<Iterator1>& lhs,
				 const vector_iterator<Iterator2>& rhs ) {
	return lhs.base() <= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>( const vector_iterator<Iterator1>& lhs,
				const vector_iterator<Iterator2>& rhs ) {
	return lhs.base() > rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=( const vector_iterator<Iterator1>& lhs,
				 const vector_iterator<Iterator2>& rhs ) {
	return lhs.base() >= rhs.base();
}

}  // namespace ft

#endif
