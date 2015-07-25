/**
 * Red-Black Tree Implementation 
 *
 * Theses are the rules one must obey when implementing a red-black tree.
 *  
 *  1. Every node is either red or black
 *  2. The root is always black
 *  3. If a node is red, its child must be black (although the converse isn't
 *  necessarily true)
 *  4. Every path from the root to a leaf, or to a null child, must contain the same
 *  number of black nodes.  (black height).
 *
 *  If all these rules are kept, then you will have a self balancing tree with
 *  Big-0(log(n)) for insertion, deletion, and searching - regardless of the order 
 *  of the data.  Fully sorted or random data the tree will always be balanced and 
 *  support Big-O(log(n)).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum node_color { RED, BLACK };

struct node {
	struct node *left;
	struct node *right;
	struct node *parent;
	enum node_color color;
	int value;
};

struct node *rb_root;

void repaint_tree(struct node *n);

struct node *grandparent(struct node *n)
{
	if (n != NULL && n->parent != NULL)
		return n->parent->parent;
	return NULL;
}

struct node *uncle(struct node *n)
{
	struct node *g;

	g = grandparent(n);
	if (g == NULL)
		return NULL;
	if (g->left == n->parent)
		return g->right;
	return g->left;
}

void rotate_right(struct node *n)
{
	struct node *c;

	c = n->left;
	if (n->parent == NULL)
		rb_root = c;

	n->left = c->right;
	if (c->right != NULL)
		c->right->parent = n;
	
	c->right = n;
	n->parent = c;
}

void rotate_left(struct node *n)
{
	struct node *c;

	c = n->right;
	if (n->parent == NULL)
		rb_root = c;
	else
		n->parent->left = c;

	c->parent = n->parent;
	n->parent = c;
	n->right = c->left;
	c->left = n;
}

void create_new_rb_node(struct node **node, int value)
{
	*node = (struct node *)malloc(sizeof(**node));
	if (*node == NULL) {
		printf("Failed to create new rb node\n");
	}
	(*node)->color = RED;
	(*node)->value = value;
}

void rebalance_tree(struct node *n)
{
	struct node *g;

	/*
	 * Check if we are a inside grandchild
	 *
	 * By definition the inside grandchild is
 	 * where P is the left side of G 
 	 * and N is the right side of P.
 	 * OR
 	 * where P is right side of G and
 	 * n is the left side of the P.
	 *
	 * Visual the relationship makes a zigzag
	 * instead of a straight line.
	 */
	g = grandparent(n);
	if (n == n->parent->right && n->parent == g->left) {
		rotate_left(n->parent);
		n = n->left;
	} else if (n == n->parent->left && n->parent == g->right) {
		rotate_right(n->parent);
		n = n->right;
	}
	/*
	 * Now at this point we are either a outside grandchild
	 * and rotated the inside grandchild to become
	 * a outside grandchild.
	 *
	 * n chould have changed so get grandparent node again
	 */
	g = grandparent(n);
	n->parent->color = BLACK;
	g->color = RED;
	if (n == n->parent->left)
		rotate_right(g);
	else
		rotate_left(g);
}

void parent_is_red(struct node *n)
{
	struct node *u, *g;

	u = uncle(n);
	if (u != NULL && u->color == RED) {
		g = grandparent(n);
		
		n->parent->color = BLACK;
		u->color = BLACK;
		g->color = RED;
		
		repaint_tree(g);
	} else 
		rebalance_tree(n);
}

void repaint_tree(struct node *n)
{
	/*
	 * Rule 2: root is always black
	 */
	if (n->parent == NULL)
		n->color = BLACK;
	/*
	 * The tree is still valid and n's parent 
	 * is black and n is red.
	 */
	else if (n->parent->color == BLACK)
		return;
	else
		parent_is_red(n);
}

void insert_rb_node(struct node *n)
{
	struct node *c, *p, *u, *g;
	bool is_left = true;

	/*
	 * Find our parent we are going to
	 * attach ourself to.
	 */
	p = c = rb_root;
	while (c != NULL) {
		p = c;
		if (c->value > n->value) {
			c = c->left;
			is_left = true;
		} else {
			c = c->right;
			is_left = false;
		}
	}

	n->parent = p;
	if (is_left && p != NULL)
		p->left = n;
	else if (p != NULL)
		p->right = n;
	else
		rb_root = n;

	repaint_tree(n);	
}

/*
 * Helps in debugging what the state
 * of the tree is after coloring and
 * rotation.
 */
void traverse_in_order(struct node *n)
{
	if (n != NULL) {
		traverse_in_order(n->left);

		printf("%d (%s) %s\n", n->value, 
				n->color == RED ? "Red" : "Black",
				n == rb_root ? "Root" : "");

		traverse_in_order(n->right);
	}
}

int main(int argv, char *argc[])
{
	struct node *n1, *n2, *n3;
	struct node *n4, *n5, *n6;
	struct node *n7, *n8, *n9;
	struct node *n10;

	create_new_rb_node(&n1, 50);
	insert_rb_node(n1);

	create_new_rb_node(&n2, 25);
	insert_rb_node(n2);

	create_new_rb_node(&n3, 75);
	insert_rb_node(n3);
	
	create_new_rb_node(&n4, 12);
	insert_rb_node(n4);
	
	create_new_rb_node(&n5, 37);
	insert_rb_node(n5);
	
	create_new_rb_node(&n6, 62);
	insert_rb_node(n6);
	
	create_new_rb_node(&n7, 6);
	insert_rb_node(n7);
	
	create_new_rb_node(&n8, 18);
	insert_rb_node(n8);
	
	create_new_rb_node(&n9, 87);
	insert_rb_node(n9);
	
	create_new_rb_node(&n9, 3);
	insert_rb_node(n9);

	traverse_in_order(rb_root);
	return 0;
}
