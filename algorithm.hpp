/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seseo <seseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 00:23:01 by seseo             #+#    #+#             */
/*   Updated: 2022/09/19 22:40:36 by seseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

namespace ft {

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

// template <class InputIterator1, class InputIterator2, class Compare>
// bool lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
// 							  InputIterator2 first2, InputIterator2 last2,
// 							  Compare comp ) {
// 	for ( ; first2 != last2; ++first1, (void)++first2 ) {
// 		if ( first1 == last1 || comp( *first1, *first2 ) )
// 			return true;
// 		if ( comp( *first2, *first1 ) )
// 			return false;
// 	}
// 	return false;
// }

}  // namespace ft

#endif
