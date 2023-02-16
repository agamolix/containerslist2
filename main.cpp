/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:35:18 by atrilles          #+#    #+#             */
/*   Updated: 2023/01/26 16:16:45 by atrilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "main.hpp"
#include <vector>
#include "vector.hpp"
#include "display.hpp"
#include "rbtree.hpp"
#include <map>
#include "map.hpp"
//#include "common.hpp"
#include "containers_test/srcs/map/common.hpp"

#define T1 int
#define T2 std::string
typedef TESTED_NAMESPACE::map<T1, T2>::value_type T3;

static int iter = 0;

template <typename MAP>
void	ft_erase(MAP &mp, const T1 param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}

void print(node<int, int> *n)
{
	std::cout << "key = " << n->get_key().first << std::endl;
	std::cout << "color = " << n->get_color() << std::endl;
	if (n->get_left())
		std::cout << "left = " << n->get_left()->get_key().first << std::endl;
	if (n->get_right())
		std::cout << "right = " << n->get_right()->get_key().first << std::endl;
	if (n->get_parent())
		std::cout << "parent = " << n->get_parent()->get_key().first << std::endl;
	std::cout << "------------------------" << std::endl;
}


void printstd(std::map<T1, T2> mp)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	std::map<T1, T2>::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << it->first << " " << it->second << std::endl;
}

void printft(ft::map<T1, T2> mp)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	ft::map<T1, T2>::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << it->first << " " << it->second << std::endl;
}




int		main(void)
{
	TESTED_NAMESPACE::map<T1, T2> mp;

	mp[42] = "lol";

	mp[50] = "mdr";
	mp[25] = "funny";

	mp[46] = "bunny";
	mp[21] = "fizz";
	mp[30] = "buzz";
	mp[55] = "fuzzy";

	mp[18] = "bee";
	mp[23] = "coconut";
	mp[28] = "diary";
	mp[35] = "fiesta";
	mp[44] = "hello";
	mp[48] = "world";
	mp[53] = "this is a test";
	mp[80] = "hey";

	mp[12] = "no";
	mp[20] = "idea";
	mp[22] = "123";
	mp[24] = "345";
	mp[27] = "27";
	mp[29] = "29";
	mp[33] = "33";
	mp[38] = "38";

	mp[43] = "1";
	mp[45] = "2";
	mp[47] = "3";
	mp[49] = "4";
	mp[51] = "5";
	mp[54] = "6";
	mp[60] = "7";
	mp[90] = "8";

	printSize(mp);

	/* A classic btree should give this:
	 *                                      42
	 *                     /                                            \
	 *                    25                                            50
	 *           /                 \                         /                       \
	 *          21                 30                       46                       55
	 *      /       \           /      \                /       \             /           \
	 *     18       23        28        35            44         48         53             80
	 *   /   \    /    \    /    \     /   \        /   \       /   \     /    \         /     \
	 *  12   20  22    24  27    29  33    38     43    45    47    49   51    54       60      90
	 *
	 * */

	ft_erase(mp, 25); // right != NULL; left != NULL
	ft_erase(mp, 55); // right != NULL; left != NULL

	/* After deleting 25 and 55, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    24                                            50
	 *           /                 \                         /                      \
	 *          21                 30                       46                      54
	 *      /       \           /      \                /       \             /           \
	 *     18       23        28        35            44         48         53             80
	 *   /   \    /         /    \     /   \        /   \       /   \     /              /     \
	 *  12   20  22        27    29  33    38     43    45    47    49   51             60      90
	 *
	 * */

	ft_erase(mp, 24); // right != NULL; left != NULL
	ft_erase(mp, 54); // right != NULL; left != NULL

	/* After deleting 24 and 54, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          21                 30                       46                      53
	 *      /       \           /      \                /       \             /           \
	 *     18       22        28        35            44         48         51             80
	 *   /   \              /    \     /   \        /   \       /   \                    /     \
	 *  12   20            27    29  33    38     43    45    47    49                  60      90
	 *
	 * */

	ft_erase(mp, 22); // right == NULL; left == NULL
	ft_erase(mp, 51); // right == NULL; left == NULL

	ft_erase(mp, 21); // right == NULL; left != NULL
	ft_erase(mp, 53); // right != NULL; left == NULL

	/* After deleting 22, 51 and then 21, 53, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          20                 30                       46                      80
	 *      /                   /      \                /       \                /        \
	 *     18                 28        35            44         48             60         90
	 *   /                  /    \     /   \        /   \       /   \
	 *  12                 27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 20); // right == NULL; left != NULL

	/* After deleting 20, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          18                 30                       46                      80
	 *      /                   /      \                /       \                /        \
	 *     12                 28        35            44         48             60         90
	 *                      /    \     /   \        /   \       /   \
	 *                     27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 23); // right != NULL; left != NULL

	/* After deleting 23, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        35            44         48             60         90
	 *                      /    \     /   \        /   \       /   \
	 *                     27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 42); // right != NULL; left != NULL; parent == NULL

	/* After deleting 42, I would get:
	 *                                      38
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        35            44         48             60         90
	 *                      /    \     /            /   \       /   \
	 *                     27    29  33           43    45    47    49
	 *
	 * */

	ft_erase(mp, 38); // right != NULL; left != NULL; parent == NULL

	/* After deleting 38, I would get:
	 *                                      35
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        33            44         48             60         90
	 *                      /    \                  /   \       /   \
	 *                     27    29               43    45    47    49
	 *
	 * */

	ft_erase(mp, 35); // right != NULL; left != NULL; parent == NULL

	/* After deleting 35, I would get:
	 *                                      33
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /                       /       \                /        \
	 *                        28                      44         48             60         90
	 *                      /    \                  /   \       /   \
	 *                     27    29               43    45    47    49
	 *
	 * */

	ft_erase(mp, 33); // right != NULL; left != NULL; parent == NULL

	/* After deleting 33, I would get:
	 *                                      30
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 28                       46                      80
	 *                          /      \                /       \                /        \
	 *                        27       29             44         48             60         90
	 *                                              /   \       /   \
	 *                                            43    45    47    49
	 *
	 * */


	return 0;
}

/*
void print2(node<int, int> *n)
{
	if (!n)
		return;
	if (n->is_root())
	std::cout << "R ";
	std::cout << n->get_key().first << ", c " << n->get_color();
	if (n->get_left())
		std::cout << ", l " << n->get_left()->get_key().first;
	if (n->get_right())
		std::cout << ", r " << n->get_right()->get_key().first;
	if (n->get_parent())
		std::cout << ", p " << n->get_parent()->get_key().first;
	std::cout << "\n";
}
*/

/*	std::cout << std::left << std::setw(60) << " " << "m_std  |  m_ft" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;

	std::map<int, int> m1_std;
	ft::map<int, int> m1_ft;
	display_map("Constructor () // m1 = ", m1_std, m1_ft);
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;

	ft::vector<int> v2_ft(3, 10);
	std::vector<int> v2_std(3, 10);
	display("Constructor (3, 10) // v2 = ", v2_std, v2_ft);		
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	v2_ft.push_back(3);
	v2_std.push_back(3);
	v2_std.push_back(7);
	v2_ft.push_back(7);
	v2_std.push_back(8);
	v2_ft.push_back(8);
	display("Push back (3, 7, 8) // v2 = ", v2_std, v2_ft);

	v2_std.pop_back();
	v2_ft.pop_back();
	display("Pop back () // v2 = ", v2_std, v2_ft);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	ft::vector<int> v3_ft(v2_ft.end() - 3, v2_ft.end());
	std::vector<int> v3_std(v2_std.end() - 3, v2_std.end());
	display("Constr (end - 3, end) // v3 =", v3_std, v3_ft);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	ft::vector<int> v4_ft(v3_ft);
	std::vector<int> v4_std(v3_std);
	display("Constructor copy (v3) // v4 = ", v4_std, v4_ft);		
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	ft::vector<int> v5_ft = v4_ft;
	std::vector<int> v5_std = v4_std;
	display("Operator = (v4) // v5 = ", v5_std, v5_ft);		
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	display("Begin (v5) = ", *(v5_std.begin()), *(v5_ft.begin()));
	display("End (v5) = ", *(v5_std.end()), *(v5_ft.end()));
	display("End - 1 (v5) = ", *(v5_std.end() - 1), *(v5_ft.end() - 1));

	display("Rbegin (v5) = ", *(v5_std.rbegin()), *(v5_ft.rbegin()));
	display("Rend (v5) = ", *(v5_std.rend()), *(v5_ft.rend()));
	display("Rend - 1 (v5) = ", *(v5_std.rend() - 1), *(v5_ft.rend() - 1));
	
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	display("Size (v5) = ", v2_std.size(), v2_ft.size());		
	display("Capacity (v5) = ", v2_std.capacity(), v2_ft.capacity());		
	display_sizet("Max size (v5) = ", v2_std.max_size(), v2_ft.max_size());		
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	v5_ft.clear();
	v5_std.clear();
	display("Clear (v5) // v5 =", v5_std, v5_ft);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	v5_ft.assign(5, 100);
	v5_std.assign(5, 100);
	display("Assign (5, 100) // v5 =", v5_std, v5_ft);

	v5_ft.assign(4, 10);
	v5_std.assign(4, 10);
	display("Assign (4, 10) // v5 =", v5_std, v5_ft);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	v5_ft.push_back(5);
	v5_std.push_back(5);
	display("Push back (5) // v5 =", v5_std, v5_ft);
	v5_ft.assign(v5_ft.begin() + 2, v5_ft.end());
	v5_std.assign(v5_std.begin() + 2, v5_std.end());
	display("Assign (begin + 2, end) // v5 =", v5_std, v5_ft);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	v5_ft.clear();
	v5_ft.push_back(1);
	v5_ft.push_back(2);
	v5_ft.push_back(3);
	v5_std.clear();
	v5_std.push_back(1);
	v5_std.push_back(2);
	v5_std.push_back(3);
	display("Clear + Push back (1, 2, 3) // v5 =", v5_std, v5_ft);
	v5_ft.insert(v5_ft.begin() + 1, 6);
	v5_std.insert(v5_std.begin() + 1, 6);
	display("Insert (begin + 1, 6) // v5 =", v5_std, v5_ft);

	v5_ft.insert(v5_ft.begin() + 1, 2, 4);
	v5_std.insert(v5_std.begin() + 1, 2, 4);
	display("Insert (begin + 1, 2, 4) // v5 =", v5_std, v5_ft);

	v5_ft.insert(v5_ft.begin() + 4, v5_ft.begin() + 1, v5_ft.begin() + 3);
	v5_std.insert(v5_std.begin() + 4, v5_std.begin() + 1, v5_std.begin() + 3);
	display("Insert (beg + 4, beg + 1, beg + 3) // v5 =", v5_std, v5_ft);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	v5_ft.erase(v5_ft.begin() + 4);
	v5_std.erase(v5_std.begin() + 4);
	display("Erase (begin + 4) // v5 =", v5_std, v5_ft);

	v5_ft.erase(v5_ft.begin() + 1, v5_ft.begin() + 3);
	v5_std.erase(v5_std.begin() + 1, v5_std.begin() + 3);
	display("Erase (begin + 1, begin + 3) // v5 =", v5_std, v5_ft);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	std::vector<int> v6_std;
	v6_std.push_back(1);
	v6_std.push_back(2);
	ft::vector<int> v6_ft;
	v6_ft.push_back(1);
	v6_ft.push_back(2);
	display("Push back (1, 2) // v6 =", v6_std, v6_ft);
	v5_ft.swap(v6_ft);
	v5_std.swap(v6_std);
	display("Swap (v5, v6) // v5 =", v5_std, v5_ft);
	display("Swap (v5, v6) // v6 =", v6_std, v6_ft);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	v5_ft.resize(4);
	v5_std.resize(4);
	display("Resize (4) // v5 =", v5_std, v5_ft);
	v5_ft.resize(7, 1);
	v5_std.resize(7, 1);
	display("Resize (7, 1) // v5 =", v5_std, v5_ft);
	v5_ft.resize(5);
	v5_std.resize(5);
	display("Resize (5) // v5 =", v5_std, v5_ft);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	std::vector <int> v7_std = v5_std;
	ft::vector <int> v7_ft = v5_ft;
	display("Copy (v5) // v7 =", v7_std, v7_ft);
	display_bool("Empty (v5) =", v5_std.empty(), v5_ft.empty());
	v5_ft.clear();
	v5_std.clear();
	display("Clear (v5) // v5 =", v5_std, v5_ft);
	display_bool("Empty (v5) =", v5_std.empty(), v5_ft.empty());
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	v7_std.reserve(20);
	v7_ft.reserve(20);
	display("Reserve (20) // v7 =", v7_std, v7_ft);
	display("Capacity (v7) =", v7_std.capacity(), v7_ft.capacity());
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	std::vector <int> v8_std;
	ft::vector <int> v8_ft;
	int * p_std = v8_std.get_allocator().allocate(5);
	int * p_ft = v8_ft.get_allocator().allocate(5);
	for (size_t i = 0; i < 3; i++) 
		v8_std.get_allocator().construct(&p_std[i], i * 2);
	for (size_t i = 0; i < 3; i++) 
		v8_ft.get_allocator().construct(&p_ft[i], i * 2);
	display("Get allocator (alloc + construct 0, 2, 4) // v8 =", p_std, p_ft, 3, 3);
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	display("v6 =", v6_std, v6_ft);
	display("Front (v6) =", v6_std.front(), v6_ft.front());
	display("Back (v6) =", v6_std.back(), v6_ft.back());
	display("Data (v6) =", v6_std.data(), v6_ft.data());
	display("Operator [] // v6[1] =", v6_std[1], v6_ft[1]);
	try
	{
		display("At (v6.at(1)) = ", v6_std.at(1), v6_ft.at(1));
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "At (v6.at(10)) = " << std::endl;
	try
	{
		display("At (v6.at(10)) = ", v6_std.at(10), v6_ft.at(10));
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;

	std::vector <int> v9_std = v6_std;
	ft::vector <int> v9_ft = v6_ft;
	display("v9 = v6 // v6 =", v6_std, v6_ft);
	v9_std[2] = 300;
	v9_ft[2] = 300;
	display("v9[2] = 300 // v9 =", v9_std, v9_ft);
	display_bool("v6 == v9:", v6_std == v9_std, v6_ft == v9_ft);
	display_bool("v6 != v9:", v6_std != v9_std, v6_ft != v9_ft);
	display_bool("v6 > v9:", v6_std > v9_std, v6_ft > v9_ft);
	display_bool("v6 >= v9:", v6_std >= v9_std, v6_ft >= v9_ft);
	display_bool("v6 < v9:", v6_std < v9_std, v6_ft < v9_ft);
	display_bool("v6 <= v9:", v6_std <= v9_std, v6_ft <= v9_ft);

	std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;



	return 0;
}



int main()
{
	std::cout << "\t-------------------------------------" << std::endl;



	std::cout << "Enter a command: vi (vector int), vc (vector char), mi (map int, int), mc (map char, char): ";  
	std::string command;
	std::cin >> command;
	if (command.compare("vi") == 0)
	{
		test_vector_int();
		return 0;
	}
	else if (command.compare("vc") == 0)
	{
		test_vector_char();
		return 0;
	}
	else if (command.compare("mi") == 0)
	{
		test_map_int();
		return 0;
	}
	else if (command.compare("mc") == 0)
	{
		test_map_char();
		return(0);
	}
	else
	{
		std::cout << "Invalid command" << std::endl;
		return 0;
	}
*/