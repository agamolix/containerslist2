/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_iter_rev_const.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/26 16:06:03 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_ITER_REV_CONST_HPP
#define V_ITER_REV_CONST_HPP

#include "v_iter.hpp"

namespace ft
{
	template <typename T>
	class v_iter_rev_const
	{
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const T *pointer;
		typedef const T &reference;

	private:
		pointer _ptr;

	public:
		v_iter_rev_const() : _ptr(0){};
		v_iter_rev_const(pointer ptr) : _ptr(ptr){};
		v_iter_rev_const(v_iter_rev_const const &src) { *this = src; };
		v_iter_rev_const(v_iter_const<T> const &src) { _ptr = src.getPtr(); };
		v_iter_rev_const(v_iter_rev<T> const &src) { _ptr = src.getPtr(); };
		v_iter_rev_const(v_iter<T> const &src) { _ptr = src.getPtr(); };
		~v_iter_rev_const(){};

		reference operator*() const { return *_ptr; };
		pointer operator->() const { return _ptr; };

		v_iter_rev_const operator++()
		{
			_ptr--;
			return _ptr;
		};
		v_iter_rev_const operator--()
		{
			_ptr++;
			return _ptr;
		};
		v_iter_rev_const operator++(int)
		{
			v_iter_rev_const temp = *this;
			_ptr--;
			return temp;
		};
		v_iter_rev_const operator--(int)
		{
			v_iter_rev_const temp = *this;
			_ptr++;
			return temp;
		};

		void operator+=(difference_type d) { _ptr -= d; };
		void operator-=(difference_type d) { _ptr += d; };

		v_iter_rev_const operator+(difference_type d) { return (_ptr - d); };
		v_iter_rev_const operator-(difference_type d) { return (_ptr + d); };

		difference_type operator+(v_iter_rev_const v) const { return (_ptr - v._ptr); };
		difference_type operator-(v_iter_rev_const v) const { return (_ptr + v._ptr); };

		bool operator==(v_iter_rev_const const &v) const { return (_ptr == v._ptr); };
		bool operator!=(v_iter_rev_const const &v) const { return (_ptr != v._ptr); };
		bool operator>(v_iter_rev_const const &v) const { return (_ptr < v._ptr); };
		bool operator>=(v_iter_rev_const const &v) const { return (_ptr <= v._ptr); };
		bool operator<(v_iter_rev_const const &v) const { return (_ptr > v._ptr); };
		bool operator<=(v_iter_rev_const const &v) const { return (_ptr >= v._ptr); };

		v_iter_rev_const operator[](size_t n) const { return (_ptr - n); };
	};
}

#endif