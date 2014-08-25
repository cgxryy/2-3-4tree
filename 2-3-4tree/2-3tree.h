// =====================================================================================
// 
//       Filename:  2-3tree.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年08月18日 21时38分29秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Reazon (Changgongxiaorong), cgxryy@gmail.com
//        Company:  Class 1203 of Network Engineering
// 
// =====================================================================================

#include <iostream>
#include <vector>
#include <map>


//this can be use as the number of links
#define TWO_LINK 2
#define THREE_LINK 3
#define FOUR_LINK 4

using namespace std;

class Node 
{
	protected
		:
		int key[3]; 			//the max number of key_value is 3
		string value[3];
						//value can support genericity(now just string)
		vector<Node*> node_list; 	//it can have two, three or four links
	
	public
		:
		bool put(Node** node, int key, string value);
		string search_node(Node* node, int key);
		Node();
		Node(int key, string value);
		~Node();
	private
		:
		int flag_node; 			//TWO_NODE THREE_NODE FOUR_NODE

		string search_two(Node* node, int key);
		string search_three(Node* node, int key);
		Node* deal_links(Node** child, Node** now, int key, string value, int depth);
		void  add_second_node(Node** now, int key, string value);
		void  add_third_node(Node** now, int key, string value);
		Node* deal_four_links(Node** child, Node** now);
		void  deal_top_tree(Node** now);
		Node* put_node(Node** node, int key, string value, int depth);
		Node* put_two(Node** node, int key, string value, int depth);
		Node* put_three(Node** node, int key, string value, int depth);
};






