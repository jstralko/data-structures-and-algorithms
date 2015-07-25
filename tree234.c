/*
 * 2-3-4 Tree Implementation
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ORDER	4
#define ARRAY_LEN(x)	sizeof(x)/sizeof(*x)

struct data {
	int value;
};

struct node {
	struct node *children[ORDER];
	struct data *items[ORDER-1];
	struct node *parent;
	int num_items;
};

struct node *tree_root;

void create_node(struct node **node)
{
	*node = (struct node *)malloc(sizeof(**node));
	memset(*node, '\0', sizeof(**node));
}

bool node_is_full(struct node *n)
{
	/*
	 * Remember L = D + 1
	 * where L is the children nodes and 
	 * D are the items within the node.
	 */
	return n->num_items == ORDER - 1 ? true : false;
}

bool node_is_leaf(struct node *n)
{
	return n->children[0] == NULL;
}

int create_data_item(struct data **d)
{
	*d = (struct data *)malloc(sizeof(**d));
	if (*d == NULL) {
		printf("Failed to alloc struct data\n");
		return -1;
	}
	return 0;
}

int insert_into_node(struct node *n, int v)
{
	struct data *d;
	int i;

	n->num_items++;
	for (i = n->num_items - 1; i >= 0; i--) {
		/*
		 * convert the array into a pointer
		 * and see if the pointer is null
		 */
		if (n->items[i] == NULL)
			continue;

		d = n->items[i+1];
		if (d == NULL) {
			/*
			 * TODO: add error handling
			 */
			create_data_item(&d);
			n->items[i+1] = d;
		}
		
		if (n->items[i]->value > v) {	
			d->value = n->items[i]->value;
		} else {
			d->value = v;
			return i+1;
		}
	}
	
	d = n->items[0];
	if (d == NULL) 
		create_data_item(&d);
	d->value = v;
	n->items[0] = d;

	return 0;
}

struct node *get_next_child(struct node *n, int v)
{
	struct node *next;
	int i;

	for (i = 0; i < ORDER - 2; i++) {
		if (v < n->items[i]->value) {
			next = n->children[i];
			return next;
		}
	}

	next = n->children[ORDER-1];
	return next;
}

/*
 * Probably the most complext part of the 2-3-4 tree
 * implementation.
 */
void split(struct node *n)
{
	int insert_index, total_items, i;
	struct node *new_node, *tmp;

	if (n == tree_root) {
		struct node *new_root;

		create_node(&new_root);
		
		new_root->children[0] = n;
		n->parent = new_root;
		tree_root = new_root;

		insert_into_node(new_root, n->items[1]->value);
	}

	/*
	 * Rules are simple on a split.
	 * 
	 * 1. Create a new node, it's a sibling
	 * of the node being split and its place
	 * to the right.
	 * 
	 * 2. Data item C (index 2) is moved into new new node.
	 *
	 * 3. Data item B (index 1) is moved into parent of the node being 
	 * split.
	 *
	 * 4. Data item A (index 0) remains where it is.
	 *
	 * 5. The rightmost two children are disconnected from the node 
	 * being split and connected to the new node.
	 */
	create_node(&new_node);
	insert_into_node(new_node, n->items[2]->value);
	free(n->items[2]);
	n->items[2] = NULL;

	insert_index = insert_into_node(n->parent, n->items[1]->value);
	free(n->items[1]);
	n->items[1] = NULL;

	/*
	 * After an insert adjust the children pointers.
	 * Shift children nodes to the right if need be.
	 */
	total_items = n->parent->num_items;
	for (i = total_items - 1; i > insert_index; i--) {
		tmp = n->parent->children[i];
		n->parent->children[i+1] = tmp;
	}
	/*
	 * connect the new node to the parent node.
	 */
	n->parent->children[insert_index] = new_node;
	new_node->parent = n->parent;

	/*
	 * connect the new node to its children nodes.
	 * (if any exists)
	 */
	if (n->children[2] != NULL) {
		new_node->children[0] = n->children[2];
		n->children[2]->parent = new_node;
		n->children[2] = NULL;
	}
	
	if (n->children[3] != NULL) {
		new_node->children[1] = n->children[3];
		n->children[3]->parent = new_node;
		n->children[3] = NULL;
	}
}

void insert(int value)
{
	struct node *cur;

	if (tree_root == NULL)
		create_node(&tree_root);

	cur = tree_root;
	for(;;) {
	
		if (node_is_full(cur)) {
			split(cur);
			break;
		} else if (node_is_leaf(cur)) {
			insert_into_node(tree_root, value);
			break;
		} else {
			cur = get_next_child(cur, value);
		}
	}
}

int main(int argv, char *argc[])
{
	insert(50);
	insert(40);
	insert(60);
	insert(30);
	return 0;
}
