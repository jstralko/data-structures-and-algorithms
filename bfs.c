#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX	5

struct node {
	struct node *previous;
	struct node *next;
	int row_index;
};

struct vertex {
	bool visited;
	char label;
};

struct queue {
	int front;
	int rear;
	int num_items;
	int array[MAX];
};

struct queue bfsq = {
	.front = 0,
	.rear = -1,
	.num_items = 0
};

struct vertex graph[MAX];
int adj_mat[MAX][MAX];
int num_vertices;

void enqueue(int i)
{
	if (bfsq.num_items == MAX)
		return;
	if (bfsq.rear - 1 == MAX)
		bfsq.rear = -1;
	bfsq.array[++bfsq.rear] = i;
	bfsq.num_items++;
}

int dequeue() 
{
	int f;

	if (bfsq.front - 1 == MAX)
		bfsq.front = 0;
	f = bfsq.array[bfsq.front++];
	bfsq.num_items--;

	return f;
}

bool is_empty()
{
	return bfsq.num_items == 0;
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

int get_unvisited_edge(int i)
{
	int j;

	for (j = 0; j < MAX; j++)
		if (adj_mat[i][j] && !graph[j].visited)
			return j;
	return -1;
}

void display(int i)
{
	printf("%c", graph[i].label);
}

void dfs()
{
	int i, n;

	graph[0].visited = true;
	display(0);
	enqueue(0);

	while (!is_empty()) {
		n = dequeue();
		while ((i = get_unvisited_edge(n)) != -1) {
			graph[i].visited = true;
			display(i);
			enqueue(i);			
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
