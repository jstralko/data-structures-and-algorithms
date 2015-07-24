#include <stdio.h>
#include <stdlib.h>

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

int main(int argv, char *argc[])
{
	init_rb_tree(1);

	return 0;
}
