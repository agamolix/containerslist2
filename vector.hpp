/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/26 15:19:05 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include <iostream>

#include "v_iter.hpp"
#include "v_iter_reverse.hpp"
//#include "v_iter_rev.hpp"
//#include "v_iter_const.hpp"
//#include "v_iter_rev_const.hpp"
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"
#include "is_same.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef v_iter<T> iterator;
		typedef typename ft::v_iter<const T> const_iterator;
//		typedef v_iter_const<T> const_iterator;
//		typedef v_iter_rev<T> reverse_iterator;
  		typedef v_iter_reverse<v_iter<T> > reverse_iterator;
		typedef typename ft::v_iter_reverse<const_iterator> const_reverse_iterator;
//		typedef v_iter_rev_const<T> const_reverse_iterator;

	private:
		size_t _size;		   // vector size
		size_t _capacity;	   // vector capacity
		value_type *_data;	   // pointeur sur début du vector
		allocator_type _alloc; // allocator memoire

	public:
		// ----- CONST, DESTR -----

		// Default
		explicit vector(const allocator_type &alloc = allocator_type())
		{
			_size = 0;
			_capacity = 0;
			_alloc = alloc;
			_data = _alloc.allocate(0);
		}

		// Int, val
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
		{
			_size = n;
			_capacity = n;
			_alloc = alloc;
			_data = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data + i, val);
		}

		// Range
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type(),
			   typename enable_if<!is_same<InputIterator, int>::value>::type * = 0)
		{
			_alloc = alloc;
			size_t n = 0;
			InputIterator it;
			for (it = first; it != last; it++)
				n++;
			_data = _alloc.allocate(n);
			_capacity = n;
			it = first;
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data + i, *(it++));
//				_alloc.construct(_data + i, *(it + i));
			_size = n;
		}

		// Copy
		vector(const vector &x)
		{
			_alloc = x._alloc;
			_size = x._size;
			_capacity = x._capacity;
			_data = _alloc.allocate(_capacity);

			const_iterator it = x.cbegin();
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, *(it + i));
		}

		// Destructor
		~vector()
		{
			clear();
			_alloc.deallocate(_data, _capacity);
		}

		// ----- OPERATOR = -----

		vector &operator=(const vector &x)
		{
//			std::cout << "op =" << std::endl;
			clear();
			_alloc.deallocate(_data, _capacity);
			_alloc = x._alloc;
			_size = x._size;
			_capacity = x._capacity;
			_data = _alloc.allocate(_capacity);

			const_iterator it = x.cbegin();
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_data + i, *(it + i));
			return *this;
		}

		// ----- ITERATORS -----

		iterator begin() { return iterator(_data); };
		const_iterator begin() const { return const_iterator(_data); };
		iterator end() { return iterator(_data) + _size; };
		const_iterator end() const { return const_iterator(_data) + _size; };

		const_iterator cbegin() const { return const_iterator(_data); };
		const_iterator cend() const { return const_iterator(_data) + _size; };

		reverse_iterator rbegin() { return reverse_iterator(end()); };
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); };
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// ----- CAPACITY -----

		size_type size() const { return _size; };
		size_type max_size() const { return _alloc.max_size(); };
		size_type capacity() const { return _capacity; };
		bool empty() const { return (_size == 0); };

		// Reserve
		void reserve(size_type n)
		{
			if (n > _capacity)
				extend_capacity(n);
		};

		// Resize
		void resize(size_type n, value_type val = value_type())
		{
			if (n > _capacity)
				extend_capacity(n);
			if (n < _size)
				for (size_t i = n; i < _size; i++)
					_alloc.destroy(&_data[i]);
			if (n > _size)
				for (size_t i = _size; i < n; i++)
					_alloc.construct(&_data[i], val);
			_size = n;
		}

		// ----- ELEMENT ACCESS -----

		reference operator[](size_type n) { return _data[n]; };
		const_reference operator[](size_type n) const { return _data[n]; };

		reference front() { return (_data[0]); };
		const_reference front() const { return (_data[0]); };

		reference back() { return (_data[_size - 1]); };
		const_reference back() const { return (_data[_size - 1]); };

		value_type *data() { return &_data[0]; };
		const value_type *data() const { return &_data[0]; };

		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("Out of range");
			return _data[n];
		}

		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("Out of range");
			return _data[n];
		}

		// ----- MODIFIERS -----

		// Assign
		void assign(size_type n, const value_type &val)
		{
			if (n > _capacity)
				dealloc_allocnew(n);
			else
				clear();
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data + i, val);
			_size = n;
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
			typename enable_if<!is_same<InputIterator, int>::value>::type * = 0)
		{

			size_t n = 0;
			for (InputIterator it = first; it != last; it++)
				n++;
			if (n > _capacity)
				dealloc_allocnew(n);
			else
				clear();
			InputIterator it = first;
			for (size_type i = 0; i < n; i++)
				_alloc.construct(_data + i, *(it++));
//				_alloc.construct(_data + i, *(it + i));
			_size = n;
		}

		// Push_back
		void push_back(value_type v)
		{
			if (_size == 0)
			{
				_data = _alloc.allocate(1);
				_capacity++;
				_size++;
				_alloc.construct(&_data[_size - 1], v);
				return;
			}
			if (_size == _capacity)
				extend_capacity(_size + 1);
			_size++;
			_alloc.construct(&_data[_size - 1], v);
		}

		// Pop_back
		void pop_back()
		{
			_alloc.destroy(&_data[_size - 1]);
			_size--;
		}

		// Insert
		iterator insert(iterator position, const value_type &val)
		{
			if (position == end())
			{
				push_back(val);
				return (end() - 1);
			}
			else
			{

//			std::cout << "insert" << std::endl;
			value_type v = *(end() - 1);
//std::cout << v << std::endl;

//std::cout << 1 << std::endl;
			iterator it;
			it = end() - 1;
//std::cout << 2 << std::endl;
			for (it = end() - 1; it != position; it--)
				*it = *(it - 1);
//std::cout << 3 << std::endl;
			*(it) = val;
//std::cout << 4 << std::endl;
			push_back(v);
//std::cout << 5 << std::endl;
			
			return position;
			}
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			difference_type d = position - begin();
			if (_size + n > _capacity)
				extend_capacity(_size + n);
			position = begin() + d;
			_size += n;
			iterator it;
			for (it = end() - 1; it != position; it--)
				*it = *(it - n);
			for (it = position; it != position + n; it++)
				*(it) = val;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename enable_if<!is_same<InputIterator, int>::value>::type * = 0)
		{
			InputIterator itf = first;
			vector v;
			iterator it;
			size_t steps = step(first, last);
			difference_type d_pos = position - begin();

			for (; itf != last; itf++)
				v.push_back(*itf);
			if (_size + steps > _capacity)
				extend_capacity(_size + steps);

			position = begin() + d_pos;
			_size += steps;

			for (it = end() - 1; it != position; it--)
				*it = *(it - steps);
			for (size_t i = 0; i < steps; i++)
				*(it + i) = *(v.begin() + i);
		}

		// Erase
		iterator erase(iterator position)
		{
			iterator pos = position;
			iterator it;
			for (it = position; it != end() - 1; it++)
				*(it) = *(it + 1);
			_alloc.destroy(&(*it));
			_size--;
			return pos;
		}

		iterator erase(iterator first, iterator last)
		{
			iterator pos = first;
			iterator it;
			difference_type d = last - first;
			for (it = first; it != end() - d; it++)
				*it = *(it + d);
			for (it = end() - d; it != end(); it++)
				_alloc.destroy(&(*it));
			_size = _size - d;
			return pos;
		}

		// Swap
		void swap(vector &v)
		{
			size_t v_size = v._size;
			size_t v_capacity = v._capacity;
			value_type *v_data = v._data;
			allocator_type v_alloc = v._alloc;

			v._size = _size;
			v._capacity = _capacity;
			v._data = _data;
			v._alloc = _alloc;

			_size = v_size;
			_capacity = v_capacity;
			_data = v_data;
			_alloc = v_alloc;

/*			
			temp.assign(x.begin(), x.end());
			temp._capacity = x._capacity;
			temp._size = x._size;
			x.assign(begin(), end());
			x._capacity = _capacity;
			x._size = _size;
			assign(temp.begin(), temp.end());
			_capacity = temp._capacity;
			_size = temp._size;
*/		}

		// Clear
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			_size = 0;
		}

		// ----- ALLOCATOR -----

		allocator_type get_allocator() const { return _alloc; };

	private:
		// ----- MY FUNCTIONS -----
		void extend_capacity(size_t n)
		{
			value_type *temp = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(&temp[i], _data[i]);
				_alloc.destroy(&_data[i]);
			}
			_alloc.deallocate(_data, _capacity);
			_data = temp;
			_capacity = n;
		}

		void dealloc_allocnew(size_t n)
		{
			clear();
			_alloc.deallocate(_data, _capacity);
			_data = _alloc.allocate(n);
			_capacity = n;
		}

		template <class InputIterator>
		size_t step(InputIterator first, InputIterator last)
		{
			size_t res = 0;
			for (; first != last; first++)
				res++;
			return res;
		}
	};
}

// ----- OPERATORS -----

template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	bool b1 = lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
	bool b2 = lexicographical_compare(rhs.cbegin(), rhs.cend(), lhs.cbegin(), lhs.cend());

	if (b1 == false && b2 == false)
		return true;
	else
		return false;
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	if (lhs == rhs)
		return false;
	return true;
}

template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend()));
}

template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (lhs < rhs || lhs == rhs);
}

template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (!(lhs <= rhs));
}

template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	return (!(lhs < rhs));
}

#endif