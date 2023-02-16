/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_iter_rev.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/25 14:08:26 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_ITER_REV_HPP
#define M_ITER_REV_HPP

#include "node.hpp"

namespace ft
{
	template< class Key, class T >
	class m_iter_rev_const;

	template <class Key, class T>
	class m_iter_rev
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

		m_iter_rev() : _node(0){};
		m_iter_rev(node<Key, T> * n) : _node(n){};
		m_iter_rev(m_iter_rev const &m) { *this = m; };
		m_iter_rev(m_iter_rev_const<Key, T> const &m) { _node = m.get_node(); };
		m_iter_rev(m_iter<Key, T> const &m) { _node = m.get_node(); };
		~m_iter_rev(){};

		reference operator*() const { return _node->get_key(); };
		pointer operator->() const { return &(operator*()); };
//		m_iter<Key, T> base() { m_iter<Key, T>(_node*); };

		m_iter_rev &operator=(m_iter_rev const &m)
		{
			_node = m._node;
			return *this;
		};

		m_iter_rev &operator=(m_iter_rev_const<Key, T> const &m)
		{
			_node = m.get_node();
			return *this;
		};

		m_iter_rev & operator++() { 
			_node = _node->previous();
			return *this;
		}
	
		m_iter_rev & operator--() {
			_node = _node->next();
			return *this;
		}

		m_iter_rev operator++(int)
		{
			m_iter_rev temp = *this;
			_node = _node->previous();
			return temp;
		};

		m_iter_rev operator--(int)
		{
			m_iter_rev temp = *this;
			_node = _node->next();
			return temp;
		};

		m_iter_rev operator+(difference_type d)
		{
			m_iter_rev res = *this;
			for (difference_type dt = d; dt > 0; dt--)
				res = ++res;
			return res;
		}

		m_iter_rev operator-(difference_type d)
		{
			m_iter_rev res = *this;
			for (difference_type dt = d; dt > 0; dt--)
				res = --res;
			return res;
		}

		bool operator==(m_iter_rev const &m) { return (_node == m._node); };
		bool operator!=(m_iter_rev const &m) { return (_node != m._node); };
		bool operator==(m_iter_rev_const<Key, T> const &m) { return (_node == m._node); };
		bool operator!=(m_iter_rev_const<Key, T> const &m) { return (_node != m._node); };
	};

	template <class Key, class T>
	class m_iter_rev_const
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

		m_iter_rev_const() : _node(0){};
		m_iter_rev_const(node<Key, T> *n) : _node(n){};
		m_iter_rev_const(m_iter_rev_const const &m) { *this = m; };
		m_iter_rev_const(m_iter_rev<Key, T> const &m) { _node = m.get_node(); };
		m_iter_rev_const(m_iter<Key, T> const &m) { _node = m.get_node(); };
		~m_iter_rev_const(){};

		reference operator*() const { return _node->get_key(); };
		pointer operator->() const { return &(operator*()); };


		m_iter_rev_const &operator=(m_iter_rev_const const &m)
		{
			_node = m._node;
			return *this;
		};

		m_iter_rev_const &operator=(m_iter_rev<Key, T> const &m)
		{
			_node = m.get_node();
			return *this;
		};

		m_iter_rev_const & operator++() { 
			_node = _node->previous();
			return *this;
		}
	
		m_iter_rev_const & operator--() {
			_node = _node->next();
			return *this;
		}

		m_iter_rev_const operator++(int)
		{
			m_iter_rev_const temp = *this;
			_node = _node->previous();
			return temp;
		};

		m_iter_rev_const operator--(int)
		{
			m_iter_rev_const temp = *this;
			_node = _node->next();
			return temp;
		};

		m_iter_rev_const operator+(difference_type d)
		{
			m_iter_rev_const res = *this;
			for (difference_type dt = d; dt > 0; dt--)
				res = ++res;
			return res;
		}

		m_iter_rev_const operator-(difference_type d)
		{
			m_iter_rev_const res = *this;
			for (difference_type dt = d; dt > 0; dt--)
				res = --res;
			return res;
		}

		bool operator==(m_iter_rev_const const &m) const { return (_node == m._node); };
		bool operator!=(m_iter_rev_const const &m) const { return (_node != m._node); };
		bool operator==(m_iter_rev<Key, T> &m) { return (_node == m._node); };
		bool operator!=(m_iter_rev<Key, T> &m) { return (_node != m._node); };
	};
}
#endif