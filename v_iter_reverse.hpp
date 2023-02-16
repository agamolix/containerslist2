/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_iter_reverse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/25 14:08:11 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_ITER_REVERSE_HPP
#define V_ITER_REVERSE_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class v_iter_reverse
	{
	public:
// est ce quon est oblige decrire ft::???

/*		typedef Iterator							iterator_type;
		typedef ft::iterator_traits<Iterator> 		iterator_traits;
		typedef typename iterator_traits::value_type		value_type;
		typedef typename iterator_traits::difference_type	difference_type;
		typedef typename iterator_traits::pointer			pointer;
		typedef typename iterator_traits::reference			reference;
		typedef typename iterator_traits::iterator_category	iterator_category;
*/

		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

	private:
		iterator_type _it;

	public:

		
		// ----- CONST, DESTR -----
		v_iter_reverse() : _it(){};

		explicit v_iter_reverse(iterator_type it) { _it = it; };

		template <class Iter>
		v_iter_reverse(const v_iter_reverse<Iter> &it) { _it = it.base(); };

		// ----- OPERATOR CONST -----
		operator v_iter_reverse<const Iterator>() const { return _it; };

		// ----- OPERATOR= -----
		v_iter_reverse &operator=(const v_iter_reverse & it)
		{
			_it = it.base();
			return *this;
		}

		// ----- BASE -----
		iterator_type base() const { return _it; };

//		reference operator*() const {
//			return (*--iterator_type(it));
//		}

		// ----- DEREFERENCE -----
		reference operator*() const { 	return (*--iterator_type(_it));};


		pointer operator->() const { return & operator*(); }
//		pointer operator->() const { return &(_it); };
//		reference operator[](difference_type d) const { return *(_it - d); };

		reference operator[](difference_type n) const { return base()[- n - 1]; }

//		pointer operator->() const { return &operator*(); }
//		reference operator[](difference_type n) const { return this->base()[-n-1]; }

		// ----- +/- -----
		v_iter_reverse operator+(difference_type d) { return v_iter_reverse(_it - d); };
		v_iter_reverse operator-(difference_type d) { return v_iter_reverse(_it + d); };

//ReverseIter operator-(int n) { 
//			return (ReverseIter(this->it + n));

//		ReverseIter operator+(int n) { return (ReverseIter(this->it - n));}
//     	ReverseIter operator-(int n) { return (ReverseIter(this->it + n));}

		template<class Iter>
		friend v_iter_reverse operator+(difference_type d, v_iter_reverse<Iter>& it) 
		{
			return v_iter_reverse(it + d);
		}

		template<class Iter>
		friend v_iter_reverse operator-(difference_type d, v_iter_reverse<Iter>& it) {
			return v_iter_reverse(it - d); 
		}


		
/*		template<class Iter>
		friend v_iter_reverse operator+(difference_type d, v_iter_reverse<Iter>& it) 
		{
			return v_iter_reverse(it.base() - d);
		}

		template<class Iter>
		friend v_iter_reverse operator-(difference_type d, v_iter_reverse<Iter>& it) {
			return v_iter_reverse(it.base() + d); 
		}
*/
		// ----- INCREMENT -----
		v_iter_reverse &operator++() { --_it; return *this; };
		v_iter_reverse operator++(int)
		{
			v_iter_reverse temp = *this;
			--_it;
			return temp;
		};

		v_iter_reverse &operator--() { ++_it; return *this; };
		v_iter_reverse operator--(int)
		{
			v_iter_reverse temp = *this;
			++_it;
			return temp;
		};

		// ----- +=/-= -----
//		v_iter_reverse &operator+=(difference_type n) { return (_it -= n); };
//		v_iter_reverse &operator-=(difference_type n) { return (_it += n); };

		v_iter_reverse & operator+=(difference_type d) { _it -= d; return *this; };
		v_iter_reverse & operator-=(difference_type d) { _it += d; return *this; };
	};

template< class Iterator1, class Iterator2 >
bool operator==( const v_iter_reverse<Iterator1>& lhs, const v_iter_reverse<Iterator2>& rhs )
{ return (lhs.base() == rhs.base()); };

template< class Iterator1, class Iterator2 >
bool operator!=( const v_iter_reverse<Iterator1>& lhs, const v_iter_reverse<Iterator2>& rhs )
{ return (lhs.base() != rhs.base()); };

template< class Iterator1, class Iterator2 >
bool operator<( const v_iter_reverse<Iterator1>& lhs, const v_iter_reverse<Iterator2>& rhs )
{ return (lhs.base() > rhs.base()); };

template< class Iterator1, class Iterator2 >
bool operator<=( const v_iter_reverse<Iterator1>& lhs, const v_iter_reverse<Iterator2>& rhs )
{ return (lhs.base() >= rhs.base()); };

template< class Iterator1, class Iterator2 >
bool operator>( const v_iter_reverse<Iterator1>& lhs, const v_iter_reverse<Iterator2>& rhs )
{ return (lhs.base() < rhs.base()); };

template< class Iterator1, class Iterator2 >
bool operator>=( const v_iter_reverse<Iterator1>& lhs, const v_iter_reverse<Iterator2>& rhs )
{ return (lhs.base() <= rhs.base()); };

template< class Iterator1, class Iterator2 >
ptrdiff_t operator-( const v_iter_reverse<Iterator1>& lhs, const v_iter_reverse<Iterator2>& rhs )
{ return (rhs.base() - lhs.base()); };


}

#endif