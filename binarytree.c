#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
/**
 * Found this marco in the linux kernel.
 * container_of - cast a member of a structure out to the containing structure
 * 	@ptr:	the pointer to the member.
 * 	@type:	the type of the container struct this is embedded in.
 *	@member: the name of the member within the struct.
*/
#define container_of(ptr, type, member) ({ 			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

struct node {
	struct node *left;
	struct node *right;
};

struct node *root_node;

struct person {
	int id;
	struct node node;
};

struct node *find_successor(struct node *node)
{
	struct node *successor;
	struct node *current;
	struct node *parent;

	successor = parent = node;
	current = node->right;
	while (successor != NULL) {
		parent = successor;
		successor = current;
		current = current->left;
	}

	if (successor != node->right) {
		/*
		 * Successor is not the right child,
		 * make the connection now.
		 */
		parent->left = successor->right;
		successor->right = node->right;
	}

	return successor;
}	

bool delete(struct person *person)
{
	struct person *cur_p;
	struct node *parent;
	struct node *current;
	bool is_left = true;

	if (root_node == NULL)
		return false;
	
	current = parent = root_node;
	cur_p = container_of(current, struct person, node);
	//very similar to find - find the node we are deleting
	while (cur_p->id != person->id) {
		parent = current;

		if (cur_p->id > person->id) {
			is_left = true;
			current = current->left;
		} else {
			is_left = false;
			current = current->right;
		}

		if (current == NULL)
			//didn't find the person in the tree :(
			return false;
	}

	//Case One: handle node with zero children (leaf node)
	if (current->left == NULL && current->right == NULL) {
		if (current == root_node)
			root_node = NULL;
		else if (is_left)
			parent->left = NULL;
		else
			parent->left = NULL;

		//TODO: free memory
	//Case Two A: handle node with one child (right node only)
	} else if (current->left == NULL) {
		if (current == root_node)
			root_node = current->right;
		else if (is_left)
			parent->left = current->right;			
		else
			parent->right = current->right;
	//Case Two B: handle node with one child (left node only)
	} else if (current->right == NULL) {
		if (current == root_node)
			root_node = current->left;
		else if (is_left)
			parent->left = current->right;
		else
			parent->right = current->right;
	//Case Three: handle node with two children
	} else {
		/*
		 * This is when the fun happens.
		 *
		 * Two sub cases we need to handle:
		 * 	A. Successor is Right Child of deleted node (DN)
		 *	   1. Set current's parents left child (or right
		 *	     depending on the path we took) to the 
		 *	     successor node.
		 *	   2. Set the successor's left child to the deleted
		 *	   node's left child.
		 *	B. Successor is Left Descendant of Right Child of DN
		 *	   1. set the right child of successor to the left child
		 *	   of the successor's parent.
		 *	   2. set the right child of successor to the right child of
		 *	   the deleted node.
		 *	   3. (same as A 1)
		 *	   4. (same as A 2) 
		 *
		 *  Part B, 1 and 2 is performed in the find_successor function
		 */

		//first get the successor of the deleted node
		struct node *successor;
	       
		successor = find_successor(current);
		if (current == root_node)
			root_node = successor;
		else if (is_left)
			parent->left = successor;
		else
			parent->right = successor;
	}

	return true;

}

void traverse_in_order(struct node *node)
{
	struct person *p;

	if (node != NULL) {
		traverse_in_order(node->left);
		
		p = container_of(node, struct person, node);	
		printf("%d\n", p->id);

		traverse_in_order(node->right);
	}
}

struct person *find(struct person *p_to_find)
{
	struct node *current;
	struct person *p;

	if (root_node == NULL) return NULL;

	current = root_node;
	p = container_of(current, struct person, node);
	while (p->id != p_to_find->id) {
		if (p_to_find->id > p->id)
			current = current->right;
		else 
			current = current->left;

		if (current == NULL)
			return NULL;

		p = container_of(current, struct person, node);
	}
	return p;
}

void insert(struct person *p)
{
	struct node *cur_node;
	struct node *parent;

	if (root_node == NULL) {
		root_node = &p->node;
		return;
	}
	
	cur_node = root_node;
	while(1) {
		struct person *cur_p;
	       
		parent = cur_node;
		cur_p = container_of(cur_node, struct person, node);
		if (cur_p->id > p->id) {
			cur_node = cur_node->left;
			if (cur_node == NULL) {
				parent->left = &p->node;
				return;
			}
		} else {
			cur_node = cur_node->right;
			if (cur_node == NULL) {
				parent->right = &p->node;
				return;
			}
		}

	}
}

int main(int argv, char *argc[])
{

	struct person *p1, *p2, *p3, *find_p;

	p1 = (struct person *)malloc(sizeof(*p1));
	if (p1 == NULL) {
		printf("Error malloc-ing p1\n");
		return -1;
	}
	p1->id = 3;

	p2 = (struct person *)malloc(sizeof(*p2));
	if (p2 == NULL) {
		printf("Error malloc-ing p2\n");
		return -1;
	}
	p2->id = 2;

	p3 = (struct person *)malloc(sizeof(*p3));
	if (p3 == NULL) {
		printf("Error malloc-ing p3\n");
		return -1;
	}
	p3->id = 4;

	insert(p1);
	insert(p2);
	insert(p3);

	printf("Traversing the tree in order\n");
	traverse_in_order(root_node);
	
	printf("\n");
	find_p = find(p1);

	if (find_p != NULL) 
		printf("Found person: %d\n", find_p->id);
	else
		printf("Person NOT Found for %d\n", p1->id);

	printf("\n");
	return 0;
}
