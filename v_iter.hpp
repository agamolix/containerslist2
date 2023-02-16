/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_iter.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/26 16:23:50 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V_ITER_HPP
#define V_ITER_HPP

//#include "v_iter_const.hpp"
//class v_iter_const;

namespace ft
{
	template <typename T>
	class v_iter
	{
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag	iterator_category;
	
	private:
		pointer _ptr;

	public:

		operator v_iter<const T>() const { return (this->_ptr); }

		v_iter() : _ptr(0){};
		v_iter(pointer ptr) : _ptr(ptr){};
		v_iter(v_iter const &v) { *this = v; };
		~v_iter(){};

		v_iter &operator=(const v_iter &v )
		{
			if (this != &v)
				_ptr = v._ptr;
			return *this;
		}

		pointer	getPtr() const { return _ptr; }
		reference operator*() const { return *_ptr; };
//		pointer operator->() { return _ptr; };
		pointer operator->() const { return _ptr; };
		reference operator[](size_t d) const { return *(_ptr + d); };
		pointer base() const { return (_ptr); }

		v_iter & operator++() { _ptr++; return *this; };
		v_iter & operator--() { _ptr--; return *this; };
		v_iter operator++(int) { v_iter temp = *this; _ptr++; return temp; };
		v_iter operator--(int) { v_iter temp = *this; _ptr--; return temp; };

		v_iter operator+=(difference_type d) { _ptr += d; return _ptr; };
		v_iter operator-=(difference_type d) { _ptr -= d; return _ptr; };
//		void operator+=(difference_type d) { _ptr += d; };
//		void operator-=(difference_type d) { _ptr -= d; };

		v_iter operator+(difference_type d) { return (_ptr + d); };
		v_iter operator-(difference_type d) { return (_ptr - d); };



		friend v_iter operator+( difference_type d, const v_iter& rhs )
		{ return v_iter(rhs._ptr + d); }
		friend v_iter operator-( difference_type d, const v_iter& rhs )
		{ return v_iter(rhs._ptr - d); }

		difference_type operator+(v_iter v) { return (_ptr + v._ptr); };
		difference_type operator-(v_iter v) { return (_ptr - v._ptr); };
//		difference_type operator-(v_iter <const value_type> v) const { return (_ptr - v._ptr); };

//		difference_type operator-(v_iter v) { return (_ptr - v.base()); };
		difference_type operator-(v_iter <const value_type> v) const 
		{ return (_ptr - v.base()); };

		bool operator==(v_iter const &v) { return (_ptr == v._ptr); };
		bool operator!=(v_iter const &v) { return (_ptr != v._ptr); };
		bool operator>(v_iter const &v) { return (_ptr > v._ptr); };
		bool operator>=(v_iter const &v) { return (_ptr >= v._ptr); };
		bool operator<(v_iter const &v) { return (_ptr < v._ptr); };
		bool operator<=(v_iter const &v) { return (_ptr <= v._ptr); };

		friend bool	operator==(const v_iter & lhs, const v_iter & rhs )
		{ return lhs._ptr == rhs._ptr; }
		friend bool	operator!=(const v_iter & lhs, const v_iter & rhs )
		{ return lhs._ptr != rhs._ptr; }
		friend bool	operator<=(const v_iter & lhs, const v_iter & rhs )
		{ return lhs._ptr <= rhs._ptr; }
		friend bool	operator<(const v_iter & lhs, const v_iter & rhs )
		{ return lhs._ptr < rhs._ptr; }
		friend bool	operator>=(const v_iter & lhs, const v_iter & rhs )
		{ return lhs._ptr >= rhs._ptr; }
		friend bool	operator>(const v_iter & lhs, const v_iter & rhs )
		{ return lhs._ptr > rhs._ptr; }


	};

	
}

#endif