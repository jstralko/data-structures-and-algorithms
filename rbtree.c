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

struct node *create_new_rb_node(int value)
{
	struct node *n;
       
	n = (struct node *)malloc(sizeof(*n));
	if (n == NULL) {
		printf("Failed to create new rb node\n");
		return NULL;
	}
	n->color = RED;
	n->value = 1;

	return n;
}

void init_rb_tree(int value)
{
	rb_root = create_new_rb_node(1);
	if (rb_root == NULL)
		return;
	rb_root->color = BLACK;
	rb_root->value = value;
}

/*
 * This handles where the parent (P) is
 * RED and the uncle (U) is BLACK or "null child"
 * and the node we are inserting (n) is a 
 * outer grand child of G (P's parent). 
 *
 * By defintion the outer grandparent is
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
void pr_ub_n_outer_gc_insert(struct node *n)
{

}

void insert_rb_node(struct node *n)
{
	struct node *c, *p, *u;
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

	n->parent = p;
	if (is_left)
		p->left = n;
	else
		p->right = n;

	if (p->color == RED) {
		u = uncle(n);
		if (u == NULL || u->color == BLACK) {
			pr_ub_n_outer_gc_insert(n);
		}
	}


}

int main(int argv, char *argc[])
{
	struct node *n1;

	init_rb_tree(1);

	n1 = create_new_rb_node(2);
	insert_rb_node(n1);

	return 0;
}
