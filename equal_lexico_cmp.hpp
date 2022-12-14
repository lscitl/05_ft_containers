/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal_lexico_cmp.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:23:01 by seseo             #+#    #+#             */
/*   Updated: 2022/09/30 23:39:16 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __EQUAL_LEXICO_CMP_H__
#define __EQUAL_LEXICO_CMP_H__

namespace ft {

template <class InputIterator1, class InputIterator2>
bool equal( InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2 ) {
	while ( first1 != last1 ) {
		if ( !( *first1 == *first2 ) )
			return false;
		++first1;
		++first2;
	}
	return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
							  InputIterator2 first2, InputIterator2 last2 ) {
	while ( first1 != last1 ) {
		if ( first2 == last2 || *first2 < *first1 )
			return false;
		else if ( *first1 < *first2 )
			return true;
		++first1;
		++first2;
	}
	return ( first2 != last2 );
}

}  // namespace ft

#endif
