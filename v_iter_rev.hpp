/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_iter_rev.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/26 15:49:17 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_ITER_REV_HPP
#define V_ITER_REV_HPP

#include "v_iter.hpp"

namespace ft
{
	template <typename T>
	class v_iter_rev
	{
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;

	private:
		value_type _it;
		pointer _ptr;

	public:
		v_iter_rev() : _ptr(0){};
		v_iter_rev(pointer ptr) : _ptr(ptr){};
		v_iter_rev(v_iter_rev const &src) { *this = src; };
		v_iter_rev(v_iter<T> const &src) { _ptr = src.getPtr(); };
		~v_iter_rev(){};

		value_type base() const { return _ptr; };

		pointer	getPtr() const { return _ptr; }
		
		reference operator*() { return *_ptr; };
		pointer operator->() { return _ptr; };

		v_iter_rev operator++()
		{
			_ptr--;
			return _ptr;
		};
		v_iter_rev operator--()
		{
			_ptr++;
			return _ptr;
		};
		v_iter_rev operator++(int)
		{
			v_iter_rev temp = *this;
			_ptr--;
			return temp;
		};
		v_iter_rev operator--(int)
		{
			v_iter_rev temp = *this;
			_ptr++;
			return temp;
		};

		void operator+=(difference_type d) { _ptr -= d; };
		void operator-=(difference_type d) { _ptr += d; };

		v_iter_rev operator+(difference_type d) { return (_ptr - d - 1); };
		v_iter_rev operator-(difference_type d) { return (_ptr + d); };

		difference_type operator+(v_iter_rev v) { return (_ptr - v._ptr); };
		difference_type operator-(v_iter_rev v) { return (_ptr + v._ptr); };

		bool operator==(v_iter_rev const &v) { return (_ptr == v._ptr); };
		bool operator!=(v_iter_rev const &v) { return (_ptr != v._ptr); };
		bool operator>(v_iter_rev const &v) { return (_ptr < v._ptr); };
		bool operator>=(v_iter_rev const &v) { return (_ptr <= v._ptr); };
		bool operator<(v_iter_rev const &v) { return (_ptr > v._ptr); };
		bool operator<=(v_iter_rev const &v) { return (_ptr >= v._ptr); };

		v_iter_rev operator[](size_t n) { return (_ptr - n); };
	};
}

#endif