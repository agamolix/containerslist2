/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_iter.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/25 14:08:24 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_ITER_HPP
#define M_ITER_HPP

#include "node.hpp"

namespace ft
{
	template< class Key, class T >
	class m_iter_const;

	template <class Key, class T>
	class m_iter
	{
	private:
		node<Key, T> *_node;

	public:

		typedef node<Key, T> node_type;
		typedef node<const Key, T> const_node_type;

		typedef ft::pair<Key, T> value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type *pointer;
		typedef value_type &reference;
		typedef value_type const & const_reference;
		typedef std::bidirectional_iterator_tag	iterator_category;

		node<Key, T> * get_node() { return _node; };
		node<Key, T> * get_node() const { return _node; };
		void set_node(node<Key, T> * n) { _node = n; };

		m_iter() : _node(0){};
		m_iter(node<Key, T> * n) : _node(n){};
		m_iter(m_iter const &m) { *this = m; };
		m_iter(m_iter_const<Key, T> const &m) { _node = m.get_node(); };
		~m_iter(){};

		reference operator*() const { return _node->get_key(); };
		pointer operator->() const { return &(operator*()); };

		m_iter &operator=(m_iter const &m)
		{
			_node = m._node;
			return *this;
		};

		m_iter &operator=(m_iter_const<Key, T> const &m)
		{
			_node = m.get_node();
			return *this;
		};

		m_iter & operator++() { 
//			std::cout << "++" << std::endl;
			_node = _node->next();
			return *this;
		}
	
		m_iter & operator--() {
//			std::cout << "--" << std::endl;
			_node = _node->previous();
			return *this;
		}

		m_iter operator++(int)
		{
//			std::cout << "++int" << std::endl;
			m_iter temp = *this;
			_node = _node->next();
			return temp;
		};

		m_iter operator--(int)
		{
//			std::cout << "--int" << std::endl;
			m_iter temp = *this;
			_node = _node->previous();
			return temp;
		};

		m_iter operator+(difference_type d)
		{
			m_iter res = *this;
			for (difference_type dt = d; dt > 0; dt--)
				res = ++res;
			return res;
		}

		m_iter operator-(difference_type d)
		{
			m_iter res = *this;
			for (difference_type dt = d; dt > 0; dt--)
				res = --res;
			return res;
		}

		bool operator==(m_iter const &m) { return (_node == m._node); };
		bool operator!=(m_iter const &m) { return (_node != m._node); };
		bool operator==(m_iter_const<Key, T> const &m) { return (_node == m._node); };
		bool operator!=(m_iter_const<Key, T> const &m) { return (_node != m._node); };
	};

	template <class Key, class T>
	class m_iter_const
	{
	private:
		node<Key, T> *_node;

	public:

		typedef node<Key, T> node_type;
		typedef node<const Key, T> const_node_type;

		typedef ft::pair<Key, T> value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type *pointer;
		typedef value_type &reference;
		typedef value_type const & const_reference;
		typedef std::bidirectional_iterator_tag	iterator_category;

// 		operator m_iter<const Key, T>() const 
//		{ return m_iter<const Key, T>(_node); };

// 		operator m_iter<const Key, T>() const 
//		{ return m_iter<const Key, T>((const_node_type *) _node); };

		node<Key, T> * get_node() { return _node; };
		node<Key, T> * get_node() const { return _node; };
		void set_node(node<Key, T> * n) { _node = n; };

		m_iter_const() : _node(0){};
		m_iter_const(node<Key, T> *n) : _node(n){};
		m_iter_const(m_iter_const const &m) { *this = m; };
		m_iter_const(m_iter<Key, T> const &m) { _node = m.get_node(); };
		~m_iter_const(){};

		reference operator*() const { return _node->get_key(); };
		pointer operator->() const { return &(operator*()); };

		m_iter_const &operator=(m_iter_const const &m)
		{
			_node = m._node;
			return *this;
		};

		m_iter_const &operator=(m_iter<Key, T> const &m)
		{
			_node = m.get_node();
			return *this;
		};


		m_iter_const & operator++() { 
//			std::cout << "++" << std::endl;
			_node = _node->next();
			return *this;
		}
	
		m_iter_const & operator--() {
//			std::cout << "--" << std::endl;
			_node = _node->previous();
			return *this;
		}

		m_iter_const operator++(int)
		{
//			std::cout << "++int" << std::endl;
			m_iter_const temp = *this;
			_node = _node->next();
			return temp;
		};

		m_iter_const operator--(int)
		{
//			std::cout << "--int" << std::endl;
			m_iter_const temp = *this;
			_node = _node->previous();
			return temp;
		};

		m_iter_const operator+(difference_type d)
		{
			m_iter_const res = *this;
			for (difference_type dt = d; dt > 0; dt--)
				res = ++res;
			return res;
		}

		m_iter_const operator-(difference_type d)
		{
			m_iter_const res = *this;
			for (difference_type dt = d; dt > 0; dt--)
				res = --res;
			return res;
		}

		bool operator==(m_iter_const const &m) const { return (_node == m._node); };
		bool operator!=(m_iter_const const &m) const { return (_node != m._node); };
		bool operator==(m_iter<Key, T> &m) { return (_node == m._node); };
		bool operator!=(m_iter<Key, T> &m) { return (_node != m._node); };
	};
}
#endif