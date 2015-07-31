#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX	5

struct node {
	struct node *child;
	int row_index;
};

struct vertex {
	bool visited;
	char label;
};

struct vertex graph[MAX];
int adj_mat[MAX][MAX];
int num_vertices;
struct node *stack;

void push(int i)
{
	struct node *peek;
	struct node *n;

	n = (struct node *)malloc(sizeof(*n));
	n->row_index = i;
	
	peek = stack;
	stack = n;
	n->child = peek;
}

struct node *pop() 
{
	struct node *top;
	
	if (stack == NULL)
		return NULL;

	top = stack;
	stack = stack->child;

	return top;
}

struct node *peek()
{
	return stack;
}

void add_vertex(char l)
{
	graph[num_vertices].label = l;
	graph[num_vertices].visited = false;
	num_vertices++;
}

void add_edge(int a, int b)
{
	adj_mat[a][b] = 1;
	adj_mat[b][a] = 1;
}

int get_unvisited_edge(struct node *n)
{
	int i, j;

	i = n->row_index;

	for (j = 0; j < MAX; j++)
		if (adj_mat[i][j] && !graph[j].visited)
			return j;
	return -1;
}

void display(int i)
{
	printf("%c", graph[i].label);
}

bool is_empty()
{
	return stack == NULL;
}

void dfs()
{
	struct node *n;

	graph[0].visited = true;
	display(0);
	push(0);

	while (!is_empty()) {
		n = peek();

		int i = get_unvisited_edge(n);
		if (i == -1) {
			n = pop();
			free(n);
		} else {
			graph[i].visited = true;
			display(i);
			push(i);			
		}
	}
}

int main(int arvc, char *argc[])
{
	add_vertex('a');
	add_vertex('b');
	add_vertex('c');
	add_vertex('d');
	add_vertex('e');

	add_edge(0, 1);
	add_edge(1, 2);
	add_edge(0, 3);
	add_edge(3, 4);

	printf("Visits: ");
	dfs();
	printf("\n");

	return 0;
}
