/**
 * Red-Black Tree Implementation 
 *
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

struct node *create_new_rb_node(int value)
{
	struct node *n;
       
	n = (struct node *)malloc(sizeof(*n));
	if (n == NULL) {
		printf("Failed to create new rb node\n");
		return NULL;
	}
	n->color = RED;
	n->value = value;

	return n;
}

/*
 * This handles where the parent (P) is
 * RED and the uncle (U) is BLACK or "null child"
 * and the node we are inserting (n) is a 
 * outside grand child of G (P's parent). 
 *
 * By definition the outside grandchild is
 * where P is the left side of G 
 * and N is the left side of the P.
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
 * This handles where the parent (P) is
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

void insert_rb_node(struct node *n)
{
	struct node *c, *p, *u, *g;
	bool is_left = true;

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
		if (u == NULL || u->color == BLACK) {
			g = grandparent(n);
			if (is_left && g->left == n->parent)
				pr_ub_n_out_gc_insert(n);
			else
				pr_ub_n_in_gc_insert(n);
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

	n1 = create_new_rb_node(5);
	insert_rb_node(n1);

	n2 = create_new_rb_node(3);
	insert_rb_node(n2);

	n3 = create_new_rb_node(4);
	insert_rb_node(n3);

	traverse_in_order(rb_root);
	return 0;
}
