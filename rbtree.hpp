/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/25 14:08:07 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "node.hpp"

int verbiose = 0;

template <class Tkey, class Tvalue, class Compare>
class rbtree
{
private:
	node<Tkey, Tvalue> *root;
	node<Tkey, Tvalue> *x;
	Compare comp;
	
public:

	// ----- CONST, DESTR -----
	rbtree<Tkey, Tvalue>() { root = NULL; comp = Compare(); };
	rbtree(ft::pair<Tkey, Tvalue> p) { set_new_root(p); };
	~rbtree(){};
	rbtree(rbtree const &t) { *this = t; };
	rbtree &operator=(rbtree const &t)
	{
		root = t.root;
		comp = t.comp;
		return *this;
	};

	// ----- FAMILY -----
	node<Tkey, Tvalue> *gdparent(node<Tkey, Tvalue> *n)
	{
		if (is_root(n))
			return 0;
		if (is_root(n->get_parent()))
			return 0;
		return n->get_parent()->get_parent();
	}

	node<Tkey, Tvalue> *brother(node<Tkey, Tvalue> *n)
	{
		if (is_root(n))
			return 0;
		if (n == n->get_parent()->get_left())
			return n->get_parent()->get_right();
		return n->get_parent()->get_left();
	}

	node<Tkey, Tvalue> *uncle(node<Tkey, Tvalue> *n)
	{
		if (gdparent(n))
			return brother(n->get_parent());
		return 0;
	}

	// ----- ROTATIONS -----
	node<Tkey, Tvalue> *rot_left(node<Tkey, Tvalue> *father)
	{
//		std::cout << "ROT LEFT" << std::endl;
		node<Tkey, Tvalue> *son = father->get_right();
		node<Tkey, Tvalue> *gp = 0;
		if (father->get_parent())
			gp = father->get_parent();
		father->set_right(son->get_left());
		if (son->get_left())
			son->get_left()->set_parent(father);
		if (is_root(father))
			set_root(son);
		else if (father == father->get_parent()->get_left())
		{
			son->set_parent(gp);	
			gp->set_left(son);
		}
		else 
		{
			son->set_parent(gp);	
			gp->set_right(son);
		}		
		son->set_left(father);
		father->set_parent(son);

/*		std::cout << "father = " << father->get_key().first << std::endl;
		if (father->get_parent())
			std::cout << "father parent = " << father->get_parent()->get_key().first << std::endl;
		if (father->get_left())
			std::cout << "father left = " << father->get_left()->get_key().first << std::endl;
		if (father->get_right())
			std::cout << "father right = " << father->get_right()->get_key().first << std::endl;
		std::cout << "son = " << son->get_key().first << std::endl;
		if (son->get_parent())
			std::cout << "son parent = " << son->get_parent()->get_key().first << std::endl;
		if (son->get_left())
			std::cout << "son left = " << son->get_left()->get_key().first << std::endl;
		if (son->get_right())
			std::cout << "son right = " << son->get_right()->get_key().first << std::endl;
*/
		return father;
	}

	node<Tkey, Tvalue> *rot_right(node<Tkey, Tvalue> *father)
	{
//		std::cout << "ROT RIGHT" << std::endl;
		node<Tkey, Tvalue> *son = father->get_left();
		node<Tkey, Tvalue> *gp = 0;
		if (father->get_parent())
			gp = father->get_parent();
		father->set_left(son->get_right());
		if (son->get_right())
			son->get_right()->set_parent(father);
		if (father == root)
			set_root(son);
		else if (father == father->get_parent()->get_right())
		{
			son->set_parent(gp);	
			gp->set_right(son);
		}
		else 
		{
			son->set_parent(gp);	
			gp->set_left(son);
		}		
		son->set_right(father);
		father->set_parent(son);
		return father;
	}

	// ----- ROOT -----
	node<Tkey, Tvalue> *set_new_root(ft::pair<Tkey, Tvalue> p)
	{
		node<Tkey, Tvalue> *n = new node<Tkey, Tvalue>(p);
		n->set_key(p);
		n->set_left(NULL);
		n->set_parent(NULL);
		n->set_is_end(false);
//		n->set_is_beg(false);

		node<Tkey, Tvalue> *end = new node<Tkey, Tvalue>;
		end->set_parent(n);
		end->set_is_end(true);
		end->set_key_first(1);
		n->set_right(end);
/*
		node<Tkey, Tvalue> *beg = new node<Tkey, Tvalue>;
		beg->set_parent(n);
		beg->set_is_beg(true);
		end->set_key_first(1);
		n->set_left(beg);
*/
		set_root(n);
		return root;
	}

	// ----- END -----
	void set_end()
	{
//		std::cout << "start set end " << std::endl;
		node<Tkey, Tvalue> *end = new node<Tkey, Tvalue>;
		end->set_parent(max());
		end->set_is_end(true);
//		std::cout << "3 " << std::endl;
		end->set_key_first(size());
//		std::cout << "4 " << std::endl;
//		end->set_key_second(NULL);
//		std::cout << "5 " << std::endl;
		max()->set_right(end);
//		std::cout << "end set end " << std::endl;
	}

	void remove_end()
	{
		node<Tkey, Tvalue> *end = next(max());
		delete (end);
		max()->set_right(NULL);
	}

/*	// ----- BEG -----
	void set_beg()
	{
		node<Tkey, Tvalue> *beg = new node<Tkey, Tvalue>;
		beg->set_parent(min());
		beg->set_is_beg(true);
		beg->set_key_first(size());
		beg->set_key_second(0);
		min()->set_left(beg);
	}

	void remove_beg()
	{
		node<Tkey, Tvalue> *beg = previous(min());
		delete (beg);
		min()->set_left(NULL);
	}
*/
	// ----- INSERT -----
	node<Tkey, Tvalue> *insert(ft::pair<Tkey, Tvalue> k)
	{
//		std::cout << "start insert tree " << std::endl;
		if (!root)
		{
//			std::cout << "insert tree !root" << std::endl;
			return (set_new_root(k));
		}
		node<Tkey, Tvalue> *n = insert(root, k);
		node<Tkey, Tvalue> *res = n;
		balance_insert(search(k.first));
		return res;
	}

	node<Tkey, Tvalue> *insert(node<Tkey, Tvalue> *n, ft::pair<Tkey, Tvalue> k)
	{
//		std::cout << "start insert tree node " << std::endl;
//		remove_beg();
		remove_end();
		node<Tkey, Tvalue> *res = insert(n, k, 0);
//		std::cout << "start insert tree node inserted " << std::endl;
//		set_beg();
		set_end();
//		std::cout << "end insert tree node " << std::endl;
		return res;
	}

	node<Tkey, Tvalue> *insert(node<Tkey, Tvalue> *n, ft::pair<Tkey, Tvalue> k, node<Tkey, Tvalue> *p)
	{
		if (!n)
		{
			n = new node<Tkey, Tvalue>;
			n->set_key(k);
			n->set_left(NULL);
			n->set_right(NULL);
			n->set_parent(p);
			n->set_is_beg(false);
			n->set_is_end(false);
			n->set_color(1);
		}
		else if (k.first < n->get_key().first)
			n->set_left(insert(n->get_left(), k, n));
		else
			n->set_right(insert(n->get_right(), k, n));
		return n;
	}

	bool is_root(node<Tkey, Tvalue> *n) { return !(n->get_parent()); };

	void balance_insert(node<Tkey, Tvalue> *n)
	{
		if (is_root(n))
			case_root(n);
		else if (n->get_parent()->get_color() == 0)
			case_black_parent(n);
		else if (!uncle(n))
			case_black_uncle(n);
		else if (uncle(n) && uncle(n)->get_color() == 1)
			case_red_uncle(n);
		else
			case_black_uncle(n);
 	}

	void case_root(node<Tkey, Tvalue> *n) 
	{
//		std::cout << "case root" << std::endl;
		n->set_color(0);
	}

	void case_black_parent(node<Tkey, Tvalue> *n) 
	{
//		std::cout << "case black parent" << std::endl;
		(void) n;
		return;
	}

	void case_no_uncle(node<Tkey, Tvalue> *n) 
	{
//		std::cout << "case no uncle" << std::endl;
		n->get_parent()->set_color(0);
		if (gdparent(n))
		{
			gdparent(n)->set_color(1);
			balance_insert(gdparent(n));
		}
	}

	void case_red_uncle(node<Tkey, Tvalue> *n) 
	{
//		std::cout << "case red uncle" << std::endl;
		n->get_parent()->set_color(0);
		uncle(n)->set_color(0);
		gdparent(n)->set_color(1);
//		std::cout << "parent = " << n->get_parent()->get_key().first << " " << n->get_parent()->get_color() << std::endl;
//		std::cout << "uncle = " << uncle(n)->get_key().first << " " << uncle(n)->get_color() << std::endl;
//		std::cout << "gdp = " << gdparent(n)->get_key().first << " " << gdparent(n)->get_color() << std::endl;
		balance_insert(gdparent(n));
	}

	void case_black_uncle(node<Tkey, Tvalue> *n) 
	{
//		std::cout << "case black uncle" << std::endl;
		node<Tkey, Tvalue> *p = n->get_parent();
		node<Tkey, Tvalue> *g = p->get_parent();

		if (g->get_left() && n == g->get_left()->get_right())
		{
			std::cout << "rot left 1" << std::endl;
			rot_left(p);
			n = n->get_left();
		}
		else if (g->get_right() && n == g->get_right()->get_left())
		{
			std::cout << "rot right 1" << std::endl;
			rot_right(p);
			n = n->get_right();
		}
		p = n->get_parent();
		g = p->get_parent();
		if (n == p->get_left())
			rot_right(g);
		else
			rot_left(g);
		p->set_color(0);
		g->set_color(1);
	}

	// ----- SEARCH -----
	node<Tkey, Tvalue> *search(Tkey k)
	{
//		node<Tkey, Tvalue> * res = search(root, k);
		return (search(root, k));
	}

	node<Tkey, Tvalue> *search(node<Tkey, Tvalue> *n, Tkey k)
	{
		if (!n)
			return 0;
		else if (n->get_key().first == k)
			return n;
		else if (k < n->get_key().first)
		{
			if (n->get_left())
				return (search(n->get_left(), k));
			else
				return 0;
		}
		else
		{
			if (n->get_right() && !(n->get_right()->get_is_end()))
				return (search(n->get_right(), k));
			else
				return 0;
		}
		return 0;
	}

/*	node<Tkey, Tvalue> *search(node<Tkey, Tvalue> *n, Tkey k)
	{
		if (!n)
			return 0;
		else if (n->get_key().first == k)
			return n;
		else if (k < n->get_key().first)
		{
			if (n->get_left() && !(n->get_left()->get_is_beg()))
				return (search(n->get_left(), k));
			else
				return 0;
		}
		else
		{
			if (n->get_right() && !(n->get_right()->get_is_end()))
				return (search(n->get_right(), k));
			else
				return 0;
		}
		return 0;
	}
*/
	// ----- REMOVE -----
	void remove_all()
	{
		remove_branch(root);
	}

	void remove_branch(node<Tkey, Tvalue> *(&(n)))
	{
		if (n)
		{
			remove_branch_ptr(n->get_left());
			remove_branch_ptr(n->get_right());
			delete n;
			n = NULL;
		}
	}

	void remove_branch_ptr(node<Tkey, Tvalue> *n)
	{
		if (n)
		{
			remove_branch_ptr(n->get_left());
			remove_branch_ptr(n->get_right());
			delete n;
			n = NULL;
		}
	}

	node<Tkey, Tvalue> *remove_node(Tkey k)
	{
//		remove_beg();
		remove_end();
		node<Tkey, Tvalue> *n = search(k);
/*		int c = n->get_color();
		int cas;
		node<Tkey, Tvalue> *p = 0;
		if (n == root)
			cas = 0;
		else
		{
			p = n->get_parent();
			if (n->is_left())
				cas = 1;
			else
				cas = 2;
		}
*/


//		node<Tkey, Tvalue> *res = remove_node(root, n->get_key().first, NULL);
		remove_node3(n);
//(void)res;

/*		if (cas == 0)
			root->set_color(c);
		else if (cas == 1)
			p->get_left()->set_color(c);
		else
			p->get_right()->set_color(c);
*/
//		set_beg();
		set_end();


/*
		if (c == 0)
		{
			balance_delete(search(k.first));
		}
*/
//			std::cout << "end remove" << std::endl;

//		std::cout << "res = " << res->get_key().first << std::endl; 
		return 0;
//		return res;
	}

	void delete_node_for_parent(node<Tkey, Tvalue> *n, node<Tkey, Tvalue> *r, node<Tkey, Tvalue> *x, node<Tkey, Tvalue> *b)
	{
		if (verbiose)

		{
			std::cout << "start delete node for parent" << std::endl;
		std::cout << "n = " << n->get_key().first << std::endl;
		std::cout << "r = " << n->get_key().first << std::endl;
		std::cout << "x = " << x->get_key().first << std::endl;
		if (verbiose) std::cout << "x color = " << x->get_color() << std::endl;
		if (n->get_parent())
			std::cout << "n parent = " << n->get_parent()->get_key().first << std::endl; 
		if (n->get_parent()->get_left())
			std::cout << "n parent left = " << n->get_parent()->get_left()->get_key().first << std::endl; 
		if (n->get_parent()->get_right())
			std::cout << "n parent right= " << n->get_parent()->get_right()->get_key().first << std::endl; 
		if (n->get_left())
			std::cout << "n left = " << n->get_left()->get_key().first << std::endl; 
		if (n->get_right())
			std::cout << "n right = " << n->get_right()->get_key().first << std::endl; 
		}


		int ncolor = n->get_color();
		if (n->get_parent() && n->get_parent()->get_left() == n)
			n->get_parent()->set_left(0);
		if (n->get_parent() && n->get_parent()->get_right() == n)
			n->get_parent()->set_right(0);
		n = 0;
		delete (n);

		if (ncolor == 1 && (!r || r->get_color() == 1))
		{
			if (verbiose) std::cout << "case n red && r red or nil" << std::endl;
			delete_x(x);
		}
		else if (ncolor == 1 && r && r->get_color() == 0)
		{
			if (verbiose) std::cout << "case n red && r black" << std::endl;
			r->set_color(1);
			balance_delete(x, b);
		}
		else if (ncolor == 0 && r && r->get_color() == 1)
		{
			if (verbiose) std::cout << "case n black && r red" << std::endl;
			r->set_color(0);
			delete_x(x);
		}
		else if (ncolor == 0 && r->get_color() == 0 && x->is_root())
		{
			if (verbiose) std::cout << "case n black && r black and x root" << std::endl;
			delete_x(x);
		}		
		else if (ncolor == 0 && r->get_color() == 0 && !x->is_root())
		{
			if (verbiose) std::cout << "case n black && r black and x !root" << std::endl;
			balance_delete(x, b);
		}
		if (verbiose) std::cout << "end delete node for parent" << std::endl;
	}

	void balance_delete(node<Tkey, Tvalue> *x, node<Tkey, Tvalue> *b)
	{
		if (verbiose) std::cout << "start balance delete x = " << x->get_key().first << std::endl;
		if (verbiose) std::cout << "x color = " << x->get_color() << std::endl;
		if (verbiose) std::cout << "x is null = " << x->get_is_null() << std::endl;
		if (x && x->get_color() == 1)
		{
			if (verbiose) std::cout << "case0 x red DONE" << std::endl;
			x->set_color(0);
		}
		else
		{
			if (verbiose) std::cout << "start else" << std::endl;
//			std::cout << "x parent = " << x->get_parent()->get_key().first << std::endl;
//			std::cout << "x parent left= " << x->get_parent()->get_left()->get_key().first << std::endl;
			b = brother(x);
//			std::cout << "b = " << b->get_key().first << std::endl;
			if (b && b->get_color() == 1)
				case1(x, b);
			else if (b == NULL)
				case2(x, b);
			else if ((!b->get_left() || b->get_left()->get_color() == 0)
				&& (!b->get_right() || b->get_right()->get_color() == 0))
				case2(x, b);
			else
				case3_4(x, b);
//		std::cout << "end else x = " << x->get_key().first << std::endl;

		}
		if (verbiose) std::cout << "balance delete before delete" << std::endl;
		if (verbiose) std::cout << "x is null = " << x->get_is_null() << std::endl;
		if (x->get_is_null())
			delete_x(x);
		if (verbiose) std::cout << "balance delete after delete" << std::endl;
	}

	void case1(node<Tkey, Tvalue> *x, node<Tkey, Tvalue> *b)
	{
		if (verbiose) std::cout << "case1 x black and brother red" << std::endl;
		b->set_color(0);
		x->get_parent()->set_color(1);
		if (x->is_left())
			rot_left(x->get_parent());
		else
			rot_right(x->get_parent());
		if (x->is_left())
			b = x->get_parent()->get_right();
		else
			b = x->get_parent()->get_left();
		if (b == 0)
		{
			case2(x, b);
		}
		else if ((!b->get_left() || b->get_left()->get_color() == 0)
			&& (!b->get_right() || b->get_right()->get_color() == 0))
		{
			case2(x, b);
		}
		else
		{
			case3_4(x, b);
		}
	}

	void case2(node<Tkey, Tvalue> *x, node<Tkey, Tvalue> *b)
	{
		if (verbiose) std::cout << "case2 x black and brother null DONE" << std::endl;
		b->set_color(1);
//		node<Tkey, Tvalue> * temp = x;
		x = x->get_parent();
//		delete_x(temp);
		if (x->get_color() == 1)
		{
			if (verbiose) std::cout << "case x red FINISHED" << std::endl;
			x->set_color(0);
		}
		else if (x->is_root())
		{
			if (verbiose) std::cout << "case x black and root FINISHED" << std::endl;
		}
		else
		{
			if (verbiose) std::cout << "case x black and not root REBALANCE" << std::endl;
			balance_delete(x, b);
		}
	}

	void case3_4(node<Tkey, Tvalue> *x, node<Tkey, Tvalue> *b)
	{
		if (x->is_left())
		{
			if (verbiose) std::cout << "x is left" << std::endl;
			if (b->get_left() && b->get_left()->get_color() == 1
				&& (!b->get_right() || b->get_right()->get_color() == 0))
			{
				if (verbiose) std::cout << "case3 x black and brother black and child red" << std::endl;
				b->get_left()->set_color(0);
				b->set_color(1);
				rot_right(b);
				b = x->get_parent()->get_right();
				case4(x, b);
			}
			else
			{
				if (verbiose) std::cout << "case4 x black and brother black and child red" << std::endl;
				b->set_color(x->get_parent()->get_color());	
				x->get_parent()->set_color(0);
				b->get_right()->set_color(0);
				rot_left(x->get_parent());
			}
		}							
		else
		{
			if (verbiose) std::cout << "x is right" << std::endl;
			if (b->get_right() && b->get_right()->get_color() == 1
				&& (!b->get_left() || b->get_left()->get_color() == 0))
			{
				if (verbiose) std::cout << "case3 x black and brother black and child red" << std::endl;
				b->get_right()->set_color(0);
				b->set_color(1);
				rot_left(b);
				b = x->get_parent()->get_left();
//				std::cout << "b = " << b->get_key().first << std::endl;						
				case4(x, b);						
			}
			else
			{
				if (verbiose) std::cout << "case4 x black and brother black and child red" << std::endl;
				b->set_color(x->get_parent()->get_color());	
				x->get_parent()->set_color(0);
				b->get_left()->set_color(0);
				rot_right(x->get_parent());
			}
		}							
		if (verbiose) std::cout << "end case 3_4" << std::endl;
	}

	void case4(node<Tkey, Tvalue> * x, node<Tkey, Tvalue> * b)
	{
		if (x->is_left())
		{
			if (verbiose) std::cout << "case4 after case3" << std::endl;
			b->set_color(x->get_parent()->get_color());	
			x->get_parent()->set_color(0);
			b->get_right()->set_color(0);
			rot_left(x->get_parent());
		}
		else
		{
			if (verbiose) std::cout << "case4 after case3" << std::endl;
			b->set_color(x->get_parent()->get_color());	
			x->get_parent()->set_color(0);
			b->get_left()->set_color(0);
			rot_right(x->get_parent());
		}
	}

	void delete_x(node<Tkey, Tvalue> * x)
	{
		if (verbiose) std::cout << "start delete x" << std::endl;
		if (!x || !x->get_is_null())
		{
			if (verbiose) std::cout << "end delete !x" << std::endl;
			return;
		}
		if (verbiose) std::cout << "mid delete x = " << x->get_key().first << std::endl;
		if (x->is_left())
			x->get_parent()->set_left(0);
		if (x->is_right())
			x->get_parent()->set_right(0);
		x->set_parent(0);
		x->set_is_null(true);
		if (root == x)
			root = 0;
		delete (x);
		if (verbiose) std::cout << "end delete x" << std::endl;
	}  

	node<Tkey, Tvalue> * set_x(node<Tkey, Tvalue> * p, int dirx)
	{
		if (verbiose) std::cout << "start set x " << std::endl;
	
		node<Tkey, Tvalue> * res = new node<Tkey, Tvalue>;
		res->set_parent(p);
		if (dirx == 0)
			p->set_left(res);
		else
			p->set_right(res);
		res->set_is_null(true);
		res->set_color(0);
		if (verbiose) std::cout << "end set x = " << std::endl;
		return res;	
	}  

	void print()
	{
		node<Tkey, Tvalue> * n = min();
		while (n != max())
		{
			print(n);
			n = n->next();
		}
		print(n);
	}

	void print(node<Tkey, Tvalue> *x)
	{
		std::cout << "x = " << x->get_key().first << " c=" << x->get_color() << std::endl;
		if (x->get_parent())
		{
			std::cout << "x parent = " << x->get_parent()->get_key().first << std::endl;
			if (x->get_parent()->get_left())
				std::cout << "x parent left = " << x->get_parent()->get_left()->get_key().first << std::endl;
			if (x->get_parent()->get_right())
				std::cout << "x parent right = " << x->get_parent()->get_right()->get_key().first << std::endl;
		}
		if (x->get_left())
			std::cout << "x left = " << x->get_left()->get_key().first << std::endl;
		if (x->get_right())
			std::cout << "x right = " << x->get_right()->get_key().first << std::endl;

	}

	void remove_node3(node<Tkey, Tvalue> *n)
	{
		node<Tkey, Tvalue> * r;
		node<Tkey, Tvalue> * x;
		node<Tkey, Tvalue> * b;
		if (!n->get_left() && !n->get_right())
		{
			if (verbiose) std::cout << "case 1" << std::endl;
			x = set_x(n, 1);
			if (verbiose) std::cout << "x color = " << x->get_color() << std::endl;
			r = x;
			b = 0;
			if (root == n)
				set_root(n->get_right());
			else
			{
				n->get_right()->set_parent(n->get_parent());
				if (n->is_left())
					n->get_parent()->set_left(n->get_right());
				else
					n->get_parent()->set_right(n->get_right());
			}
//			print(n);
//			print(x);
			delete_node_for_parent(n, r, x, b);
		}
		else if (n->get_left() && !n->get_right())
		{
			if (verbiose)  std::cout << "case 2" << std::endl;
			x = n->get_left();
			r = x;
			b = 0;
			if (root == n)
				set_root(n->get_left());
			else
			{
				n->get_left()->set_parent(n->get_parent());
				if (n->is_left())
					n->get_parent()->set_left(n->get_left());
				else
					n->get_parent()->set_right(n->get_left());
			}
			delete_node_for_parent(n, r, x, b);
		}
		else if (n->get_right() && !n->get_left())
		{
			if (verbiose)  std::cout << "case 3" << std::endl;
			x = n->get_right();
			r = x;
			b = 0;
			if (root == n)
				set_root(n->get_right());
			else
			{
				n->get_right()->set_parent(n->get_parent());
				if (n->is_left())
					n->get_parent()->set_left(n->get_right());
				else
					n->get_parent()->set_right(n->get_right());
			}
			delete_node_for_parent(n, r, x, b);
		}
		else
		{
			if (verbiose) std::cout << "case 4" << std::endl;
			node<Tkey, Tvalue> * m = min(n->get_right());
//			std::cout << "n = " << n->get_key().first << std::endl;
//			std::cout << "m = " << m->get_key().first << std::endl;
			r = m;
//			std::cout << "r = " << r->get_key().first << std::endl;
//		std::cout << "case 4 m = " << m->get_key().first << std::endl;
			x = m->get_right();
//		std::cout << "case 4 x = " << x->get_key().first << std::endl;
			if (!x)
				x = set_x(m, 1);
			b = m->get_left();

			//case min is child 
			if (m->get_parent() == n)
			{
//				std::cout << "case 41" << std::endl;
				branch_up_leftside(n, m);
				if (root == n)
					set_root(m);
				else
					m->set_parent(n->get_parent());
			}
			// case min is sub and has no child
			else if (!m->get_right())
			{
//				std::cout << "case 42" << std::endl;
				node<Tkey, Tvalue> * pm = m->get_parent();
				branch_up_leftside(n, m);
				m->set_right(n->get_right());
				n->get_right()->set_parent(m);
				pm->set_left(0);
				if (root == n)
					set_root(m);
				else
					m->set_parent(n->get_parent());
			}
			// case min is sub and has right
			else
			{
//				std::cout << "case 43" << std::endl;
				node<Tkey, Tvalue> * pm = m->get_parent();
				node<Tkey, Tvalue> * rm = m->get_right();
				branch_up_leftside(n, m);
				m->set_right(n->get_right());
				n->get_right()->set_parent(m);
				pm->set_left(rm);
				rm->set_parent(pm);
				if (root == n)
					set_root(m);
				else
					m->set_parent(n->get_parent());
			}
			delete_node_for_parent(n, r, x, b);
		}
//		std::cout << "end remove node3" << std::endl;
	}

	void branch_up_leftside(node<Tkey, Tvalue> *n, node<Tkey, Tvalue> *m)
	{
		m->set_parent(n->get_parent());
		if (n->is_left())
			n->get_parent()->set_left(m);
		else if (n->is_right())
			n->get_parent()->set_right(m);
		if (n->get_left())
		{
			m->set_left(n->get_left());
			n->get_left()->set_parent(m);
		}
	}

	// ----- MIN, MAX -----
	node<Tkey, Tvalue> *min()
	{
		if (root)
			return min(root);
		else
			return NULL;
	}

	node<Tkey, Tvalue> *min() const
	{
		if (root)
			return min(root);
		else
			return NULL;
	}

	node<Tkey, Tvalue> *min(node<Tkey, Tvalue> *n)
	{
		if (!n)
			return 0;
		if (!(n->get_left()) || (n->get_left() && n->get_left()->get_is_beg()))
			return n;
		return min(n->get_left());
	}

	node<Tkey, Tvalue> *min(node<Tkey, Tvalue> *n) const
	{
		if (!n)
			return 0;
		if (!(n->get_left()) || (n->get_left() && n->get_left()->get_is_beg()))
			return n;
		return min(n->get_left());
	}

	node<Tkey, Tvalue> * end()
	{
		if (root)
		{
			return max(root)->next();
		}
		else
		{
			return NULL;
		}
	}

	node<Tkey, Tvalue> * end() const
	{
		if (root)
		{
			return max(root)->next();
		}
		else
		{
			return NULL;
		}
	}

	node<Tkey, Tvalue> *max()
	{
		if (root)
		{
			return max(root);
		}
		else
		{
			return NULL;
		}
	}


	node<Tkey, Tvalue> *max(node<Tkey, Tvalue> *n)
	{
		if (!n)
			return 0;
		if (!(n->get_right()) || (n->get_right() && n->get_right()->get_is_end()))
			return n;
		return max(n->get_right());
	}

	node<Tkey, Tvalue> *max(node<Tkey, Tvalue> *n) const
	{
		if (!n)
			return 0;
		if (!(n->get_right()) || (n->get_right() && n->get_right()->get_is_end()))
			return n;
		return max(n->get_right());
	}

	// ----- PREVIOUS, NEXT -----
	node<Tkey, Tvalue> *previous(node<Tkey, Tvalue> *n)
	{
		if (!n || n->is_min())
			return 0;
		if (n->get_left())
			return max(n->get_left());
		if (n->is_right())
			return n->get_parent();
		node<Tkey, Tvalue> *temp = n;
		while (temp->get_key().first < n->get_parent()->get_key().first)
			n = n->get_parent();
		return n->get_parent();
	}

	node<Tkey, Tvalue> *next(node<Tkey, Tvalue> *n)
	{
		if (!n)
			return 0;
		if (n->is_max())
		{
			return n->get_right();
		}
		if (n->get_right())
		{
			return min(n->get_right());
		}
		if (n->is_left())
		{
//			std::cout << "next: is left" << std::endl;
			return n->get_parent();
		}
		node<Tkey, Tvalue> *temp = n;
//		std::cout << "next: n = " << n->get_key().first << std::endl;
		while (temp->get_key().first > n->get_parent()->get_key().first)
			n = n->get_parent();
		return n->get_parent();
	}

	node<Tkey, Tvalue> *next(node<Tkey, Tvalue> *n) const
	{
		if (!n)
			return 0;
		if (n->is_max())
		{
			return n->get_right();
		}
		if (n->get_right())
		{
			return min(n->get_right());
		}
		if (n->is_left())
		{
//			std::cout << "next: is left" << std::endl;
			return n->get_parent();
		}
		node<Tkey, Tvalue> *temp = n;
//		std::cout << "next: n = " << n->get_key().first << std::endl;
		while (temp->get_key().first > n->get_parent()->get_key().first)
			n = n->get_parent();
		return n->get_parent();
	}

	// ----- LOWER, UPPER -----
	node<Tkey, Tvalue> *lower(Tkey k)
	{
		node<Tkey, Tvalue> *res = min();
		while (res->get_key().first < k)
		{
			res = next(res);
			if (res->get_is_end())
				break;
		}
		return res;
	}

	node<Tkey, Tvalue> *lower(Tkey k) const
	{
		node<Tkey, Tvalue> *res = min();
		while (res->get_key().first < k)
		{
			res = next(res);
			if (res->get_is_end())
				break;
		}
		return res;
	}

	node<Tkey, Tvalue> *upper(Tkey k)
	{
		node<Tkey, Tvalue> *res = min();
		while (res->get_key().first <= k)
		{
			res = next(res);
			if (res->get_is_end())
				break;
		}
		return res;
	}

	node<Tkey, Tvalue> *upper(Tkey k) const
	{
		node<Tkey, Tvalue> *res = min();
		while (res->get_key().first <= k)
		{
			res = next(res);
			if (res->get_is_end())
				break;
		}
		return res;
	}

	// -----SIZE -----
	int size()
	{
		int res = 1;
		node<Tkey, Tvalue> *n = min();
		while (n != max())
		{
			n = next(n);
			res++;
		}
		return res;
	}

	// ----- GET, SET -----
	void set_root(node<Tkey, Tvalue> *n) { root = n; root->set_parent(0); };
	node<Tkey, Tvalue> *get_root() { return root; };
};

#endif