/**
 * Red-Black Tree Implementation 
 *
 * Theses are the rules one must obey when implementing a red-black tree.
 *  
 *  1. Every node is either red or black
 *  2. The root is always black
 *  3. If a node is red, its child must be black (although the converse isn't
 *  necessarily true)
 *  4. Every path from the root to a leaft, or to a null child, must contain the same
 *  number of black nodes.  (black height).
 *
 *  If all these rules are kept, then you will have a self balancing tree with
 *  Big-0(log(n)) for insertion, deletion, search - regardless of the ordering 
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

/*
 * This handles when the parent (P) is
 * RED and the uncle (U) is BLACK or a "null child"
 * and the node we are inserting (n) is a 
 * outside grand child of G (P's parent). 
 *
 * By definition the outside grandchild is
 * where P is the left side of G 
 * and N is the left side of P.
 * OR
 * where P is right side of G and
 * n is the right side of the P.
 *
 * This function name is pretty lame, but 
 * I wanted it to somewhat describe what 
 * type of insert it is doing.
 */
void pr_ub_n_out_gc_insert(struct node *n)
{
	struct node *g;

	g = grandparent(n);
	n->parent->color = BLACK;
	g->color = RED;

	if (n == n->parent->left)
		rotate_right(g);
	else
		rotate_left(g);
}

/**
 * This handles when the parent (P) is
 * RED and the uncle (U) is BLACK or "null child"
 * and the node we are inserting (n) is a
 * inside grand child of G (P's parent).
 *
 */
void pr_ub_n_in_gc_insert(struct node *n)
{
	struct node *g;

	rotate_left(n->parent);
	pr_ub_n_out_gc_insert(n->left);
}

void repaint_tree(struct node *n)
{
	if (n->parent == NULL)
		n->color = BLACK;
	else
		printf("case not handled yet\n");
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

	/*
	 * Init the rbtree with a root node. 
	 * Remeber root node is always BLACK.
	 */
	if (p == NULL) {
		n->color = BLACK;
		rb_root = n;
		return;
	}

	n->parent = p;
	if (is_left)
		p->left = n;
	else
		p->right = n;

	if (p->color == RED) {
		u = uncle(n);
		/*
		 * 
		 */
		g = grandparent(n);
		if (u == NULL || u->color == BLACK) {
			/*
			 * Check if we are a outside grand child, 
			 * either on the left or right.
			 */
			if ((is_left && g->left == n->parent) ||
				(!is_left && g->right == n->parent))
				pr_ub_n_out_gc_insert(n);
			else
				pr_ub_n_in_gc_insert(n);
		} else {
			/*
			 * Both P and U are red.  Paint them black
			 */
			p->color = BLACK;
			if (u != NULL) 
				u->color = BLACK;
			if (g != NULL) {
				g->color = RED;
				repaint_tree(g);
			}
		}
	}
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
	
	//create_new_rb_node(&n8, 18);
	//insert_rb_node(n8);
	
	//create_new_rb_node(&n9, 62);
	//insert_rb_node(n9)

	traverse_in_order(rb_root);
	return 0;
}
