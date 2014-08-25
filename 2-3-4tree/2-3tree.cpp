// =====================================================================================
// 
//       Filename:  2-3tree.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年08月18日 21时38分21秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Reazon (Changgongxiaorong), cgxryy@gmail.com
//        Company:  Class 1203 of Network Engineering
// 
// =====================================================================================

#include <iostream>
#include "2-3tree.h"

using namespace std;

//the left is smaller
Node::Node()
{
	node_list.resize(4);
	this->flag_node = TWO_LINK;
	this->key[0] = 0;
	this->value[0] = "";
	vector<Node*>::iterator iter;
	for (iter = node_list.begin(); iter != node_list.end(); iter++)
		(*iter) = NULL;
}

Node::Node(int key, string value)
{
	node_list.resize(4);
	this->flag_node = TWO_LINK;
	this->key[0] = key;
	this->value[0] = value;
	vector<Node*>::iterator iter;
	for (iter = node_list.begin(); iter != node_list.end(); iter++)
		(*iter) = NULL;
}

Node::~Node()
{
}

//put fuctions
bool  Node::put(Node** node, int key, string value)
{
	if (put_node(node, key, value, 0) != NULL)
	      return true;
	else return false;

}

Node* Node::put_node(Node** node, int key, string value, int depth)
{
	Node* child_node;
	
	if ((*node) == NULL)
	      return NULL;

	switch((*node)->flag_node)
	{
		case TWO_LINK:
			child_node = Node::put_two(node, key, value, depth+1);
			break;
		case THREE_LINK:
			child_node = Node::put_three(node, key, value, depth+1);
			break;
		default:
			return NULL;
	}

	//the tree grow
	return Node::deal_links(&child_node, node, key, value, depth);
}

Node* Node::put_two(Node** node, int key, string value, int depth)
{
	int cmp = key - (*node)->key[0];
	if (cmp > 0)
	{
		return Node::put_node(&((*node)->node_list[1]), key, value, depth);
	}
	else if (cmp < 0)
	{
		return Node::put_node(&((*node)->node_list[0]), key, value, depth);
	}
	else 
	{
		(*node)->value[0] = value;
	}

	return *node;
}

Node* Node::put_three(Node** node, int key, string value, int depth)
{
	if (key <= (*node)->key[0])
	{
		return Node::put_node(&((*node)->node_list[0]), key, value, depth);
	}
	else if (key > (*node)->key[0] && key <= (*node)->key[1])
	{
		return Node::put_node(&((*node)->node_list[1]), key, value, depth);
	}
	else if(key > (*node)->key[1])
	{
		return Node::put_node(&((*node)->node_list[2]), key, value, depth);
	}
	else return NULL; 	//error
}

Node* Node::deal_links(Node** child, Node** now, int key, string value, int depth)
{
	//the end of the tree
	if (*child == NULL)
	{
		switch ((*now)->flag_node)
		{
			case TWO_LINK:
				add_second_node(now, key, value);
				break;
			case THREE_LINK:
				add_third_node(now, key, value);
				break;
			default:
				return NULL; //error
		}
		if (depth == 0 && (*now)->flag_node == FOUR_LINK)
		      deal_top_tree(now);
	
		return (*now);
	}

	//tree 
	if ((*child)->flag_node == FOUR_LINK)
		deal_four_links(child, now);

	//the top of the tree
	if (depth == 0 && (*now)->flag_node == FOUR_LINK)
	      deal_top_tree(now);

	return (*now);
}

void Node::deal_top_tree(Node** now)
{
	Node* root = new Node((*now)->key[1], (*now)->value[1]);
	Node* child_left = new Node((*now)->key[0], (*now)->value[0]);
	Node* child_right = new Node((*now)->key[2], (*now)->value[2]);

	child_left->node_list[0] = (*now)->node_list[0];
	child_left->node_list[1] = (*now)->node_list[1];
	child_right->node_list[0] = (*now)->node_list[2];
	child_right->node_list[1] = (*now)->node_list[3];
	
	root->node_list[0] = child_left;
	root->node_list[1] = child_right;

	(*now) = root;

}

//排大小
void  Node::add_second_node(Node** now, int key, string value)
{
	(*now)->flag_node = THREE_LINK;
	
	if (key < (*now)->key[0])
	{
		(*now)->key[1] = (*now)->key[0];
		(*now)->value[1] = (*now)->value[0];
	}
	int location = (key > (*now)->key[0]) ? 1 : 0;
	(*now)->key[location] = key;
	(*now)->value[location] = value;
}

void  Node::add_third_node(Node** now, int key, string value)
{
	(*now)->flag_node = FOUR_LINK;

	if (key < (*now)->key[0])
	{
		(*now)->key[2] = (*now)->key[1];
		(*now)->value[2] = (*now)->value[1];
		(*now)->key[1] = (*now)->key[0];
		(*now)->value[1] = (*now)->key[0];
		(*now)->key[0] = key;
		(*now)->value[0] = value;
	}
	else if (key < (*now)->key[1] && key > (*now)->key[0])
	{
		(*now)->key[2] = (*now)->key[1];
		(*now)->value[2] = (*now)->value[1];
		(*now)->key[1] = key;
		(*now)->value[1] = value;
	}
	else if (key > (*now)->key[1])
	{
		(*now)->key[2] = key;
		(*now)->value[2] = value;
	}
	else if (key == (*now)->key[0])
	{
		(*now)->flag_node = THREE_LINK;
		(*now)->value[0] = value;
	}
	else if (key == (*now)->key[1])
	{
		(*now)->flag_node = THREE_LINK;
		(*now)->value[1] = value;
	}
}

Node* Node::deal_four_links(Node** child, Node** now)
{
	if ((*now)->flag_node == TWO_LINK)
	{
		add_second_node(now, (*child)->key[1], (*child)->value[1]);
	}
	else if ((*now)->flag_node == THREE_LINK)
	{
		add_third_node(now, (*child)->key[1], (*child)->value[1]);
	}
	Node* child_left = new Node((*child)->key[0], (*child)->value[0]);
	Node* child_right = new Node((*child)->key[2], (*child)->value[2]);
	child_left->node_list[0] = (*child)->node_list[0];
	child_left->node_list[1] = (*child)->node_list[1];
	child_right->node_list[0] = (*child)->node_list[2];
	child_right->node_list[1] = (*child)->node_list[3];

	//分情况
	if ((*child) == (*now)->node_list[0])
	{
		(*now)->node_list[3] = (*now)->node_list[2];
		(*now)->node_list[2] = (*now)->node_list[1];
		(*now)->node_list[0] = child_left;
		(*now)->node_list[1] = child_right;
	}
	else if ((*child) == (*now)->node_list[1])
	{
		(*now)->node_list[3] = (*now)->node_list[2];
		(*now)->node_list[1] = child_left;
		(*now)->node_list[2] = child_right;
	}
	else if ((*child) == (*now)->node_list[2])
	{
		(*now)->node_list[2] = child_left;
		(*now)->node_list[3] = child_right;
	}
	delete (*child);

	return (*now);
}

//search functions
string Node::search_node(Node* node, int key)
{
	switch (node->flag_node)
	{
		case TWO_LINK:
			return Node::search_two(node, key);
		case THREE_LINK:
			return Node::search_three(node, key);
		default :
			return NULL;//this is error
	}
}

string Node::search_two(Node* node, int key)
{
	int cmp = key - node->key[0];
	if (cmp > 0)
	{
		return Node::search_node(node->node_list[1], key);
	}
	else if (cmp < 0)
	{
		return Node::search_node(node->node_list[0], key);
	}
	else 
	{
		return node->value[0];
	}
}

string Node::search_three(Node* node, int key)
{
	if (key < node->key[0])
	{
		return Node::search_node(node->node_list[0], key);
	}
	else if (key > node->key[0] && key < node->key[1])
	{
		return Node::search_node(node->node_list[1], key);
	}
	else if(key > node->key[1])
	{
		return Node::search_node(node->node_list[2], key);
	}
	else if (key == node->key[0])
	{
		return node->value[0];
	}
	else if (key == node->key[1])
	{
		return node->value[1];
	}
	else return NULL; 	//error
}

int main(int argc, char *argv[])
{
	Node* root = new Node(8, "root");
	
	char ch[10][2] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
	int random;
	for ( int i = 1; i <= 10; i++)
	{
		random = i+2;
		root->put(&root, random, (string)ch[i-1]);
	}

	for (int i = 1; i <= 10; i++)
	{
		random = i+2;
		cout << root->search_node(root, random) << endl;	
	}

	return 0;
}

