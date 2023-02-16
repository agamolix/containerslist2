/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/25 14:08:18 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef map_HPP
#define map_HPP

#include <cstddef>
#include <limits>
#include <iostream>

#include "m_iter.hpp"
#include "m_iter_rev.hpp"
//#include "m_iter_const.hpp"
#include "rbtree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			  class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef m_iter<Key, T> iterator;
		typedef m_iter_const<Key, T> const_iterator;

//		typedef typename ft::m_iter<const Key, T> const_iterator;
		typedef m_iter_rev<Key, T> reverse_iterator;
		typedef m_iter_rev_const<Key, T> const_reverse_iterator;

		typedef node<Key, T>			node_type;
		typedef node<const Key, T> 		const_node_type;
/*		typedef ft::IterTree<value_type>		iterator;
		typedef ft::IterTree<const value_type>	const_iterator;
		typedef ft::ReverseIter<iterator> 		reverse_iterator;
		typedef ft::ReverseIter<const_iterator> const_reverse_iterator;
*/
		class value_compare
		{
			friend class map;
		protected:
			Compare comp;

		public:
			value_compare() {};
			value_compare(Compare c) : comp(c){};
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};



	private:
		size_t _size;					   // map size
		key_compare _keycomp;			   
		value_compare _valuecomp;			
		rbtree<key_type, mapped_type> _tree; // tree
		allocator_type _alloc;			   // allocator memoire
		bool _hastree;

	public:
		// ----- CONST, DESTR -----
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type())
		{
			_size = 0;
			_keycomp = comp;
			_alloc = alloc;
			_hastree = false;
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
//			std::cout << "start mp first last" << std::endl;
			_size = 0;
			_keycomp = comp;
			_alloc = alloc;
			_hastree = false;
//			std::cout << "mid mp first last" << std::endl;
			while (first != last)
			{
//				std::cout << "first =  " << first->first << std::endl;
				insert(*first);
//				std::cout << "inserted " << first->first << std::endl;
				first++;
//				std::cout << "end first++ "<< std::endl;
//				std::cout << "first =  " << first->first << std::endl;
			}
//			std::cout << "end mp first last" << std::endl;
		}

		map(const map &x)
		{
//			std::cout << "copy constr" << std::endl;
//			_size = x._size;
//			_keycomp = x._keycomp;
//			_alloc = x._alloc;
//			_hastree = x._hastree;
//			_tree = x._tree;
			_size = 0;
			_keycomp = key_compare();
			_alloc = allocator_type();
			_hastree = false;
			insert(x.begin(), x.end());


//			*this = x;
		}

		~map(){};

		// ----- OPERATOR = -----
		map &operator=(const map &x)
		{
			if (this == & x)
					return (*this);
			this->clear();
			this->insert(x.begin(), x.end());
			return (*this);
		}

		// ----- ITERATORS -----
		iterator begin() { return iterator(_tree.min()); };
		iterator end() { return iterator(_tree.end()); };
		const_iterator begin() const { return const_iterator(_tree.min()); };
		const_iterator end() const { return const_iterator(_tree.end()); };
		const_iterator cbegin() const { return const_iterator(_tree.min()); };
		const_iterator cend() const { return const_iterator(_tree.end()); };
		reverse_iterator rbegin() { return reverse_iterator(_tree.max()); };
		reverse_iterator rend() { return rbegin() + (_size); };

		// ----- CAPACITY -----
		size_type size() const { return _size; };
		size_type max_size() const 
		{
//			return _alloc.max_size(); 
			return (std::numeric_limits<size_type>::max() / 2 / sizeof(node<Key, T>));
		}
		bool empty() const { return (_size == 0); };

		// ----- ELEMENT ACCESS -----
		mapped_type &operator[](const key_type &k)
		{
			insert_value(k);
			return (find(k)->second);
		}

		mapped_type &at(const key_type &k)
		{
			if (find(k) == end())
				throw std::out_of_range("Out of range");
			return find(k)->second;
		}

		const mapped_type &at(const key_type &k) const
		{
			if (find(k) == end())
				throw std::out_of_range("Out of range");
			return find(k)->second;
		}

		// ----- MODIFIERS -----

		// Insert
		ft::pair<iterator, bool> insert(const value_type &val)
		{
//			std::cout << "start insert val" << std::endl;
			if (find(val.first) == end())
			{
//				std::cout << "val first == end" << std::endl;
				insert_pair(val);
//				std::cout << "val first == end inserted" << std::endl;
				ft::pair<iterator, bool> p = ft::make_pair(find(val.first), true);
				return (p);
			}
			else
			{
//				std::cout << "else" << std::endl;
				ft::pair<iterator, bool> p = ft::make_pair(find(val.first), false);
				return (p);
			}
//			std::cout << "end insert val" << std::endl;
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			if (find(val.first) == end())
			{
				insert_pair(val);
				return (find(val.first));
			}
			else
			{
				return (find(val.first));
			}
		}

		template<class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			
//			std::cout << "start insert" << std::endl;
			
			while (first != last)
			{
//				std::cout << "insert" << std::endl;
				insert(*first);
				first++;
			}
//			_tree.print();
		}
/*		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			iterator it;
			for (it = first; it != last; it++)
			{
				if (find(it->first) == end())
				{
					ft::pair<key_type, mapped_type> p = ft::make_pair(it->first, it->second);
					insert_pair(p);
				}
			}
		}
*/
		// Erase
		void erase(iterator position)
		{
			if (find(position->first) != end())
			{
				_tree.remove_node(position->first);
				_size--;
			}
		}

		size_type erase(const key_type &k)
		{
			if (find(k) != end())
			{
				_tree.remove_node(k);
				_size--;
				return 1;
			}
			return 0;
		}

		void erase(iterator first, iterator last)
		{
			std::cout << "start erase" << std::endl;
			iterator it = first;
			iterator next;
			key_type last_key = last->first;
			key_type next_key;
			while (it->first != last_key && it != end())
			{
				next = it + 1;
				next_key = next->first;
				erase(it);
				if (next_key != end()->first)
					it = find(next_key);
				else
					break;
			}
		}

		// Swap
		void swap(map &x)
		{
			size_t temp_size = _size;
			rbtree<key_type, mapped_type> temp_tree = _tree;
			key_compare temp_keycomp = _keycomp;

			_size = x._size;
			_tree = x._tree;
			_keycomp = x._keycomp;

			x._size = temp_size;
			x._tree = temp_tree;
			x._keycomp = temp_keycomp;
		}

		// Clear
		void clear()
		{
			_tree.remove_all();
			_size = 0;
		}

		// ----- OBSERVERS -----

		key_compare key_comp() const { return key_compare(); };
		value_compare value_comp() const { return (value_compare(key_compare())); };

		// ----- OPERATIONS -----

		// Find
		iterator find(const key_type &k)
		{
			if (_tree.search(k))
			{
//				std::cout << "found" << std::endl;
				return (_tree.search(k));
			}
			else
			{
//				std::cout << "not found" << std::endl;
				return end();
			}
		}

		const_iterator find(const key_type &k) const
		{
			if (_tree.search(k))
				return (_tree.search(k));
			else
				return end();
		}

		// Count
		size_type count(const key_type &k) // const
		{
			if (find(k) == end())
				return 0;
			return 1;
		}

		// Bounds
		iterator lower_bound(const key_type &k) { return _tree.lower(k); };
		const_iterator lower_bound(const key_type &k) const { return _tree.lower(k); };
		iterator upper_bound(const key_type &k) { return _tree.upper(k); };
		const_iterator upper_bound(const key_type &k) const { return _tree.upper(k); };

		// Equal_range
		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		};

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		};

		// ----- ALLOCATOR -----
		allocator_type get_allocator() const { return _alloc; };

	private:
		// ----- MY FUNCTIONS -----
		void insert_value(const key_type &k)
		{
			if (!_hastree)
			{
				ft::pair<key_type, mapped_type> p = ft::make_pair(k, mapped_type());
				_tree = rbtree<key_type, mapped_type>(p);
				_hastree = true;
				_size++;
			}
			if (find(k) == end())
			{
				ft::pair<key_type, mapped_type> p = ft::make_pair(k, mapped_type());
				_tree.insert(p);
				_size++;
			}
		}

		void insert_pair(const value_type &p)
		{
//				std::cout << "start insert pair" << std::endl;
			
			if (!_hastree)
			{
//				std::cout << "insert pair ! hastree" << std::endl;
				_tree = rbtree<key_type, mapped_type>(p);
				_hastree = true;
				_size++;
			}
			if (find(p.first) == end())
			{
//				std::cout << "find = end" << std::endl;
				_tree.insert(p);
//				std::cout << "tree insert p ok" << std::endl;
				_size++;
			}
//				std::cout << "end insert pair" << std::endl;
		}


	};
}

// ----- OPERATORS -----

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
{
	ft::m_iter_const<Key, T> itlhs = lhs.cbegin();
	ft::m_iter_const<Key, T> itelhs = lhs.cend();
	ft::m_iter_const<Key, T> itrhs = rhs.cbegin();
	ft::m_iter_const<Key, T> iterhs = rhs.cend();

	if (lhs.size() != rhs.size())
		return false;

	while (itlhs != itelhs && itrhs != iterhs)
	{
		if ((itlhs->first != itrhs->first) || (itlhs->second != itrhs->second))
			return false;
		itlhs++;
		itrhs++;
	}
	return true;
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
{
	if (lhs == rhs)
		return false;
	return true;
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
{
	ft::m_iter_const<Key, T> itlhs = lhs.cbegin();
	ft::m_iter_const<Key, T> itelhs = lhs.cend();
	ft::m_iter_const<Key, T> itrhs = rhs.cbegin();
	ft::m_iter_const<Key, T> iterhs = rhs.cend();

	if (lhs == rhs)
		return false;

	while (itlhs != itelhs && itrhs != iterhs)
	{
		if (itlhs->first > itrhs->first)
			return false;
		else if ((itlhs->first == itrhs->first) && (itlhs->second > itrhs->second))
			return false;
		else if ((itlhs->first == itrhs->first) && (itlhs->second < itrhs->second))
			return true;
		itlhs++;
		itrhs++;
	}
	if (itlhs != itelhs && itrhs == iterhs) 
		return false;
	return true;
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
{
	return (lhs == rhs || lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
{
	return !(lhs <= rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
{
	return !(lhs < rhs);
}

#endif